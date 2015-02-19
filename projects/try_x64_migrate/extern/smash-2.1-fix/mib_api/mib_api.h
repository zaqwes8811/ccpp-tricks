/* ====================================================================
 * Copyright (c) 1997-1999
 *                      SMASH, Harrie Hazewinkel.  All rights reserved.
 *
 * This product is developed by Harrie Hazewinkel and updates the
 * original SMUT compiler made as his graduation project at the
 * University of Twente.
 *
 * SMASH is a software package containing an SNMP MIB compiler and
 * an SNMP agent system. The package can be used for development
 * of monolithic SNMP agents and contains a compiler which compiles
 * MIB definitions into C-code to developed an SNMP agent.
 * More information about him and this software product can
 * be found on http://operations.ceo.org/~harrie/smash/.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by Harrie Hazewinkel"
 *
 * 4. The name of the Copyright holder must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission.
 *
 * 5. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by Harrie Hazewinkel"
 *    Also acknowledged are:
 *    - The Simple group of the University of Twente,
 *          http://wwwsnmp.cs.utwente.nl/
 *    - The MUSIQ workpackage of the DESIRE project,
 *          http://www-musiq.jrc.it/
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR, ITS DISTRIBUTORS
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================*/

/**
  \attention No diff in table or not - oids harcoded. No creating now

*/
#ifndef _AGT_MIB_H_
#define _AGT_MIB_H_

#include "asn1/asn1.h"

#define CFG_MAX_OID_SIZE 24  // Максимальная длина ключа

/*access of object type*/
#define ACCESS_RW  1       /*read-write*/
#define ACCESS_RONLY  2    /*read-only*/
#define ACCESS_NOACCESS  3 /*no-access*/

/*define a leaf is a single or table object*/
#define LEAF_TYPE_NONE  0
#define LEAF_TYPE_SINGLE 1
#define LEAF_TYPE_TABLE 2
#define LEAF_TYPE_ENTRY  3
#define LEAF_TYPE_TABLEAF 4
#define LEAF_TYPE_AGGREGATE 5
#define LEAF_NOTIN_MIB -1

/* MIB search types - public */
#define G_AGENT_EXACT  0

// No text!!
typedef struct _table_idx_t {
  int type;
  long index_value[64];
  int length;
  int result;
} mapiTableIndex_t;

typedef struct smashValue_s {
    const int snmpType;
    const unsigned char* const pValue;
    const int valLen;
} mapiValue_t;

typedef struct {
   int namelen;
   asn1OidElem_t name[SA_MAX_OID_LEN];
} mapiOid_t;

typedef struct {
    char magic;
    mapiOid_t oid;
} mapiOidPack_t;

/**
  \param[out] varlen
  \return Указатель на данные и в varlen их длине в байтах
*/
struct _mibvar;
typedef void* (*mapiGetFunc_t)(
    const mapiOidPack_t oid, int* const varlen,
    const mapiTableIndex_t* const index, int* const error);

typedef void* (*mapiSetFunc_t)(
    const mapiOidPack_t oid, int* const varlen, const mapiValue_t value,
    const mapiTableIndex_t* const index, int* const error);

/*mib tree leaf*/
typedef struct _mibvar{
  char  magic;      /*identify object in callback function*/
  unsigned char  access;     /*access exp. read-only,read-write,etc*/
  unsigned char  var_type;   /*asn.1 type of object*/
  unsigned char  leaf_type;  /*is leaf  is single object or table or entry or a leaf of table*/
  mapiGetFunc_t get;       /*get callback function*/
  mapiSetFunc_t set;       /*set callback function*/
  int  oidlen;     /*oid length*/
  asn1OidElem_t oid[CFG_MAX_OID_SIZE];      /*oid*/
} mapiTreeLeaf_t;

typedef struct {
  unsigned char asn1Type;
  int varlen;
  unsigned short accessType;
} mapiVarInfo_t;

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

/**
  \attention MIB is sorted. We can use std:: functions for sorted collections
  Then O(n) -> O(logn)
*/

typedef int mib_CApiStatus;

typedef enum {
  MIB_INITIALIZED,
  MIB_INIT_FAILURE,
  MIB_DESTROYED
} helper_Mib;

// no thread-safe, but other calls safe
EXTERNC mib_CApiStatus mib_helperInitialize(const mapiTreeLeaf_t* base, const int size);
EXTERNC mib_CApiStatus mib_destroy();
/**
  \attention bad api

  \return > 0 ok else
*/
EXTERNC int mib_mibCheck(const mapiTreeLeaf_t* cMib, int size);

/**
  \brief Expendes search - no direct by OID
  \attention FIXME: base must be sorted?
  \attention bad api

  \param[in] 0..N if success or -1 if error occure

  http://archive.oreilly.com/pub/a/perl/excerpts/system-admin-with-perl/twenty-minute-snmp-tutorial.html
  "the "first lexicographic successor" in RFC terms"
  !! http://sourceforge.net/p/net-snmp/mailman/message/21542960/
  http://stackoverflow.com/questions/2744181/how-to-call-c-function-from-c
*/
EXTERNC int mib_findNext(const mapiOid_t* const key, mapiTreeLeaf_t* const r_pResultVar);

/**
  \attention bad api

  \param[in] pResultVar
  \return 0..N if success or -1 if error occure
*/
EXTERNC int mib_findExact(const mapiOid_t* const key, mapiTreeLeaf_t* const r_pResultVar);

/**
  \brief Возможно обработка GET/GETNEXT и SET похоже тоже.
    Поиск реализуется в файле с mib базой - это нужно реализовать на своей базе!
  \attention FIXME: Danger! used not type-safe callbacks
  \attention bad api

  \param передается массив функций ! но похоже не используется
  \return buffer with Var Value - it static in mib file. NULL if error occure
*/
EXTERNC unsigned char* mib_searchNext(
    mapiOid_t * r_requested_oid, mapiVarInfo_t* const r_varInfo,
    const int searchType, mapiSetFunc_t* r_setter_, int *r_no_such_obj);
    
/**
  \attention FIXME: Danger! used not type-safe callbacks - it's trouble
  \attention bad api

  \param[in] requested_oid - what find
  \param[in] setter - call if SET request (on COMMIT stage now)
  \return buffer with Var Value - it static in mib file
*/
EXTERNC unsigned char* mib_searchExact(
    mapiOid_t* const r_pRequestedOid, mapiVarInfo_t* const r_pVarInfo,
    const int searchType, mapiSetFunc_t* r_setter, int *r_no_such_obj);

#undef EXTERNC
#endif  //_AGT_MIB_H_
