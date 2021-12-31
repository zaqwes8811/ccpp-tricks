//#include "platform_specific/c_platform_spec_types.h"

#include "mib_api/mib_api.h"
#include "__mib_impl.h"

//#include <boost/thread/mutex.hpp>

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

#include "common/snmp_string_abstr.h"

#include <stdio.h>
#include <stddef.h>

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define  FALSE  0
#endif

// http://bytes.com/topic/c/answers/755688-min-max-stdlib-h
#ifndef max
#define max(a,b) (((a) (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

using std::ostream;
using std::vector;
using std::cout;
using std::endl;

static const mapiTreeLeaf_t* s_pMibTree = 0;
static int s_countRecords = 0;
static const int SIZE_GUARD = 100;

static int mib_initialize(const mapiTreeLeaf_t* pBase, const int size_data_base) {
  s_pMibTree = pBase;
  s_countRecords = size_data_base;
  return 0;
}

int mib_findExact(const mapiOid_t* const key, mapiTreeLeaf_t* const r_pResultVar)
{
  if (!(key && r_pResultVar))
      return -1;

  {
    const mapiTreeLeaf_t* pLookUpTable = s_pMibTree;
    const unsigned long lookUpSize = s_countRecords;
    unsigned int i = 0;
    unsigned int n = 0;
    const asn1OidElem_t* pInOidName = key->name;
    const int inOidLen = key->namelen;
    const int elemSize = sizeof pLookUpTable[0].oid[0];
    const int sizeInOid = inOidLen * elemSize;

    for (i = 0; i < lookUpSize; i++) {
      const int currentOidLen = pLookUpTable[i].oidlen * elemSize;

      if (currentOidLen != sizeInOid)
        continue;

      // only equal length here
      n = memcmp(pInOidName, pLookUpTable[i].oid, currentOidLen);
      if (n == 0) {
        *r_pResultVar = pLookUpTable[i];
        return i;
      }
    }
  }
  return -1;
}

unsigned char* mib_searchExact(
    mapiOid_t* const r_pInOid,
    mapiVarInfo_t* const r_pVarInfo,
    const int search_type,
    mapiSetFunc_t* r_pSetter,
    int *r_pNoSuchObj)
  {
  mapiOid_t savedInOid;
  mapiTreeLeaf_t record;
  int found;
  int needStoreOid = 0;

  if (search_type == G_AGENT_EXACT)
    needStoreOid = 1;

  // In check
  if (!(r_pInOid && r_pVarInfo && r_pNoSuchObj))
    return NULL;

  if (s_pMibTree == NULL) {
    *r_pNoSuchObj = TRUE;
    return NULL;
  }

  // Action
  if (needStoreOid) {
    bcopy(r_pInOid->name, savedInOid.name, r_pInOid->namelen*sizeof(r_pInOid->name[0]));
    savedInOid.namelen = r_pInOid->namelen;
  }

  // OID приходит полный! Никак его не обрезать!
  // Убираем последний индекс для поиска. Остается magic
  {
    asn1OidElem_t t;
    mapiOid_t key;
    key.namelen = r_pInOid->namelen;
    memcpy(key.name, r_pInOid->name, r_pInOid->namelen * sizeof t);
    found = mib_findExact(&key, &record);
    if (found < 0) {
      *r_pNoSuchObj = TRUE;
      return NULL;
    }
  }

  // Can't show exact
  if (ACCESS_NOACCESS == record.access) {
    *r_pNoSuchObj = FALSE;
    return NULL;
  }

  {
    unsigned char* pVarVal = NULL;

    // FIXME: make get immidiatly - BAD
    if (found >= 0) {
      mapiTableIndex_t index;
      mapiGetFunc_t getter = record.get;
      *r_pSetter = record.set;
      // Если запрошеный лист - лист таблицы, то вернуть 0 ключ
      // Вставляем индекс
      index.index_value[0] = record.magic;

      // FIXME:
      {
        asn1OidElem_t t;
        mapiOid_t key;
        mapiOidPack_t oidValue;
        int err;

        // http://stackoverflow.com/questions/1292586/char-array-in-a-struct-incompatible-assignment
        key.namelen = r_pInOid->namelen;
        memcpy(key.name, r_pInOid->name, r_pInOid->namelen * sizeof t);
        oidValue.magic = record.magic;
        // http://stackoverflow.com/questions/13162159/how-to-assign-an-array-to-struct-member-array
        oidValue.oid = key;  // FIXME: ...
        // http://bytes.com/topic/c/answers/670947-struct-assignment
        //memcpy()
        pVarVal = (unsigned char *)(*getter)(oidValue, &r_pVarInfo->varlen, &index, &err);

        if (pVarVal) {
          r_pVarInfo->asn1Type = record.var_type;
          r_pVarInfo->accessType = record.access;
          *r_pNoSuchObj = FALSE;
          return pVarVal;
        } else {
          *r_pNoSuchObj = TRUE;
        }
      }  // for msvc90
    }

    if (needStoreOid) {
      bcopy(savedInOid.name, r_pInOid->name, savedInOid.namelen * sizeof savedInOid.name[0]);
      r_pInOid->namelen = savedInOid.namelen;
      *r_pNoSuchObj = FALSE;
    }
    return pVarVal;
  }
}

unsigned char* mib_searchNext(
    mapiOid_t* r_pInOid,
    mapiVarInfo_t* const r_pVarInfo,
    const int searchType_unused,
    mapiSetFunc_t* r_pSetter,
    int *r_pNoSuchObj)
  {
  mapiTreeLeaf_t resultVar;
  resultVar.magic = 0;

  // Фильтруем вход!
  if (!(r_pInOid && r_pVarInfo && r_pNoSuchObj)) {
    return NULL;
  }

  if (s_pMibTree == NULL) {
    *r_pNoSuchObj = TRUE;
    return NULL;
  }

  // Пробуем найти конечный лист - ACCESSEBLE
  {

    int guard = 0;
    asn1OidElem_t* pCurrentOid = r_pInOid->name;
    int currentOidLen = r_pInOid->namelen;

    // Accept start oid
    while (1) {
      if (guard > SIZE_GUARD) {
        break;
      }
      {
        asn1OidElem_t t;
        mapiOid_t key;
        ptrdiff_t found = 0;
        key.namelen = currentOidLen;
        memcpy(key.name, pCurrentOid, currentOidLen * sizeof t);

        // bug here
        found = mib_findNext(&key, &resultVar);

        pCurrentOid = resultVar.oid;
        currentOidLen = resultVar.oidlen;

        // Обошли кругом или возникла ошибка, или просто не нашли.
        if (found < 0) {  // <= 0 was
          r_pVarInfo->asn1Type = resultVar.var_type;
          r_pVarInfo->accessType = resultVar.access;
          *r_pNoSuchObj = TRUE;
          return NULL;
        }
      }  // msvc

      if (ACCESS_NOACCESS != resultVar.access) break;
    }
  }

  {
    int err;
    mapiTableIndex_t index;
    char magic = 0;

    // Может быть NOAccessable
    mapiGetFunc_t getter = resultVar.get;
    *r_pSetter = resultVar.set;
    magic = resultVar.magic;
    // Пакуем row idx
    index.index_value[0] = resultVar.magic;

    // Нужно сделать запрос по выделенному oid'у
    {
      asn1OidElem_t t;
      mapiOid_t key;
      mapiOidPack_t oidValue;
      unsigned char* pVarVal = NULL;

      key.namelen = resultVar.oidlen;
      memcpy(key.name, resultVar.oid, resultVar.oidlen * sizeof t);
      oidValue.magic = magic;
      oidValue.oid = key;
      pVarVal = (unsigned char *)(*getter)(oidValue, &r_pVarInfo->varlen, &index, &err);

      bcopy(resultVar.oid, r_pInOid->name, resultVar.oidlen * sizeof resultVar.oid[0]);
      r_pInOid->namelen = resultVar.oidlen;

      *r_pNoSuchObj = TRUE;
      if (pVarVal) {
        r_pVarInfo->asn1Type = resultVar.var_type;
        r_pVarInfo->accessType = resultVar.access;
        *r_pNoSuchObj = FALSE;
        return pVarVal;
      }
      return pVarVal;
    }
  }
}

namespace draw {
ostream& operator<<(ostream& o, mapiOid_t t) {
  o << t.namelen << " ";
  for (int i = 0; i < t.namelen; ++i)
    o << t.name[i] << ".";
  return o;
}

ostream& operator<<(ostream& o, const mapiTreeLeaf_t& t) {
  o << t.oidlen << " ";
  for (int i = 0; i < t.oidlen; ++i)
    o << t.oid[i] << ".";
  return o;
}
}

class compNot //: public std::binary_function<mapiTreeLeaf_t>
{
public:
  bool operator()(const mapiTreeLeaf_t& lhs, const mapiTreeLeaf_t& rhs) const {
    std::vector<asn1OidElem_t> lhs_(lhs.oid, lhs.oid + lhs.oidlen);
    std::vector<asn1OidElem_t> rhs_(rhs.oid, rhs.oid + rhs.oidlen);

    // !(lhs < rhs)
    return !std::lexicographical_compare(
         lhs_.begin(), lhs_.end(),
         rhs_.begin(), rhs_.end());
  }
};

class compEqualCheck : public std::unary_function<mapiTreeLeaf_t, bool> {
public:
  explicit compEqualCheck(const mapiOid_t* const key) : key_(key) { }
  bool operator()(const mapiTreeLeaf_t& rhs) const {
    std::vector<asn1OidElem_t> lhs_(key_->name, key_->name + key_->namelen);
    std::vector<asn1OidElem_t> rhs_(rhs.oid, rhs.oid + rhs.oidlen);

    // lhs < rhs
    return !std::lexicographical_compare(
         lhs_.begin(), lhs_.end(),
         rhs_.begin(), rhs_.end());
  }

private:
  const mapiOid_t* const key_;
};

int mib_mibCheck(const mapiTreeLeaf_t* cMib, int size) {
  if (cMib == NULL)
    return false;

  try {
    std::vector<mapiTreeLeaf_t> mib;
    for (int i = 0; i < size; i++) mib.push_back(cMib[i]);

    return std::adjacent_find(mib.begin(), mib.end(), (compNot())) == mib.end();
  } catch (...) {
    return false;
  }
}

ptrdiff_t mib_findNext(
    const mapiOid_t* const pKey
    , mapiTreeLeaf_t* const r_pResultVar)
{
  try {
    // http://stackoverflow.com/questions/2037867/can-i-convert-a-reverse-iterator-to-a-forward-iterator
    std::vector<mapiTreeLeaf_t> mib;
    for (int i = 0; i < s_countRecords; i++) mib.push_back(s_pMibTree[i]);

    std::vector<mapiTreeLeaf_t>::iterator r
        = std::find_if(mib.begin(), mib.end(), std::not1(compEqualCheck(pKey)));

    if (r == mib.end())
      return -1;

    // http://stackoverflow.com/questions/2152986/best-way-to-get-the-index-of-an-iterator
    ptrdiff_t idx = std::distance(mib.begin(), r);

    // need real link! else return ptr to local variable!
    *r_pResultVar = s_pMibTree[idx];

    return idx;
  } catch (...) {
    return ptrdiff_t(-1);
  }
}

static int s_instances = 0;

mib_CApiStatus mib_helperInitialize(const mapiTreeLeaf_t* cMib, const int size) {
  try {
    if (s_instances > 0)
      return MIB_INIT_FAILURE;

    int r = mib_initialize(cMib, size);
    if (r)
      return MIB_INIT_FAILURE;
    ++s_instances;
    return MIB_INITIALIZED;
  } catch (...) {
    return MIB_INIT_FAILURE;
  }
}


mib_CApiStatus mib_destroy() {
  try {
    --s_instances;
    return MIB_DESTROYED;
  } catch (...) {
    return MIB_INIT_FAILURE;
  }
}






