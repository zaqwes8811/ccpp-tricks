/* ====================================================================
 * Copyright (c) 1997-2000
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
 * be found on http://www.simpleweb.org/software/packages/smash/.
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
 *    Also thanked are:
 *    - The Simple group of the University of Twente,
 *          http://www.simpleweb.org/
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

#include "common/config.h"

#include <smash/__smash_impl.h>
#include <smash/smash.h>

#include <mib_api/mib_api.h>
#include <asn1/asn1.h>
#include <common/snmp_string_abstr.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

// http://stackoverflow.com/questions/3597743/where-is-ptrdiff-t-defined-in-c
#include <stddef.h>

#define MAX_COMMUNITIES    10 
/* MIB search types */
#define G_AGENT_NEXT  1

#define CFG_SIZE_PKG_WTF 10  // не ясно что это вообще

/* MIB parse phases */
#define RESERVE1  0
#define CHECK          0
#define COMMIT    2
#define ACTION    3
#define FREE    4

typedef struct {
  char string[MAX_COMMUNITY_LEN];
  int length;
  int number;
} Community_t;

#ifdef SNMP_GROUP
long  snmpInPkts_instance;
long  snmpInBadVersions_instance;
long  snmpInASNParseErrs_instance;
#endif

static unsigned char* __parseOneVarbind(
    unsigned char *data, mapiOid_t *p_oid_var,
    unsigned char *var_val_type, int *var_val_len,
    unsigned char **var_val,
    int* listlength)
  {
  ptrdiff_t p;
  unsigned char varbind_type;
  int varbind_len = *listlength;
  unsigned char* varbind_start = data;

  data = asn_parse_header(data, &varbind_len, &varbind_type);
  RETURN_ON_PARSE_ERROR(data, "");

  if (varbind_type != (unsigned char)(ASN_SEQUENCE | ASN_CONSTRUCTOR))
    return NULL;
  data = asn_parse_objid(data, &varbind_len, &varbind_type, p_oid_var->name, &(p_oid_var->namelen));
  RETURN_ON_PARSE_ERROR(data, "");

  if (varbind_type != (unsigned char)(ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_OBJECT_ID))
    return NULL;

  /* save pointer to this object */
  *var_val = data;

  /* find out what type of object this is */
  data = asn_parse_header(data, &varbind_len, var_val_type);
  RETURN_ON_PARSE_ERROR(data, "");
  // FIXME: maybe it's wrong
  *var_val = data;  // add Igor

  *var_val_len = varbind_len;
  data += varbind_len;
  *listlength -= (int)(data - varbind_start);
  return data;
}

/* IN - pointer to the beginning of the output buffer */
/* IN - object id of variable */
/* IN - type of variable */
/* IN - length of variable */
/* IN - value of variable */
/* IN/OUT - number of valid bytes left in output buffer*/
static unsigned char* __emitOneVarbind(
    register unsigned char *p_in_data, mapiOid_t* p_var_oid
    , unsigned char  var_val_type, int var_val_len, unsigned char *var_val
    , register int *r_p_listlength)
{
  int dummyLen = 0;
  int headerLen = 0;
  unsigned char* dataPtr = 0;
  const asn1OidElem_t oid_elem = 0;

  dummyLen = *r_p_listlength;
  dataPtr = p_in_data;
  p_in_data += 4;
  dummyLen -=4;
  if (dummyLen < 0)
    return NULL;

  headerLen = p_in_data - dataPtr;
  *r_p_listlength -= headerLen;
  p_in_data = asn_build_objid(
      p_in_data,
      r_p_listlength,
      (unsigned char)(ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_OBJECT_ID),
      p_var_oid->name,
      p_var_oid->namelen);
  RETURN_ON_BUILD_ERROR (p_in_data, "cannot add objectId in varbind");

  switch(var_val_type){
    case ASN_INTEGER:
      p_in_data = asn_build_int(
          p_in_data, r_p_listlength, var_val_type,
          (long *)var_val, var_val_len);
      break;
    case SNMP_GAUGE:
    case SNMP_COUNTER:
    case SNMP_TIMETICKS:
      /* case SNMP_UINTEGER: this is covered by SNMP_GAUGE */
      p_in_data = asn_build_unsigned_int(
          p_in_data, r_p_listlength, var_val_type,
          (unsigned long *)var_val, var_val_len);
      break;
    case SNMP_COUNTER64:
      p_in_data = asn_build_unsigned_int64(
          p_in_data, r_p_listlength, var_val_type,
          (struct counter64 *)var_val,
          var_val_len);
      break;

    case SNMP_IPADDRESS:
      p_in_data = asn_build_IPAddress(p_in_data, r_p_listlength, var_val_type,(unsigned long *)var_val);
      break;

    case ASN_OCTET_STR:
    case SNMP_OPAQUE:
    case SNMP_NSAP:
      p_in_data = asn_build_string(
          p_in_data, r_p_listlength, var_val_type,
          var_val, var_val_len);
      break;
    case ASN_OBJECT_ID:
      p_in_data = asn_build_objid(
          p_in_data, r_p_listlength, var_val_type,
          (asn1OidElem_t*)var_val, var_val_len / sizeof oid_elem);
      break;
    case ASN_NULL:
      p_in_data = asn_build_null(p_in_data, r_p_listlength, var_val_type);
      break;
    case ASN_BIT_STR:
      p_in_data = asn_build_bitstring(
          p_in_data, r_p_listlength, var_val_type,
          var_val, var_val_len);
      break;
    case SNMP_NOSUCHOBJECT:
    case SNMP_NOSUCHINSTANCE:
    case SNMP_ENDOFMIBVIEW:
      p_in_data = asn_build_null(p_in_data, r_p_listlength, var_val_type);
      break;
    default:
      PRINT_ERROR("wrong type");
      return NULL;
  }
  RETURN_ON_BUILD_ERROR(p_in_data, "Wrong ASN.1 sequence built\n");
  dummyLen = (p_in_data - dataPtr) - headerLen;

  asn_build_sequence(
      dataPtr, &dummyLen,
      (unsigned char)(ASN_SEQUENCE | ASN_CONSTRUCTOR), dummyLen);
  return p_in_data;
}

void map_types_smiv2_to_smiv1_NI(unsigned char *smi_type) {
  /* This is empty, but need to be sorted out. */
}

static void s_mapErrorStatusSnmpv2ToSnmpv1_(long *error_status);
static void s_mapErrorStatusSnmpv2ToSnmpv1_(long *error_status) {
  switch (*error_status) {
    case SNMP_ERROR_WRONGTYPE:
    case SNMP_ERROR_WRONGLENGTH:
    case SNMP_ERROR_WRONGENCODING:
    case SNMP_ERROR_WRONGVALUE:
    case SNMP_ERROR_INCONSISTENTVALUE:
      *error_status = SNMP_ERROR_BADVALUE;
      break;
    case SNMP_ERROR_NOACCESS:
    case SNMP_ERROR_NOTWRITABLE:
    case SNMP_ERROR_NOCREATION:
    case SNMP_ERROR_INCONSISTENTNAME:
    case SNMP_ERROR_AUTHORIZATIONERROR:
      *error_status = SNMP_ERROR_NOSUCHNAME;
      break;
    case SNMP_ERROR_RESOURCEUNAVAILABLE:
    case SNMP_ERROR_COMMITFAILED:
    case SNMP_ERROR_UNDOFAILED:
      *error_status = SNMP_ERROR_GENERR;
      break;
    default: break;
  }
}

static int __isGoodValue( unsigned char inType, int inLen
                               , unsigned char actualType, int actualLen)
{
  if (inLen > actualLen)
    return FALSE;
  return (inType == actualType);
}

static int s_emitVarbindsWithAction(
    unsigned char* const r_pInData, const int in_length,
    unsigned char* r_pOutData, const int out_length,
    const long error_status, long * const r_pErrorIndex,
    smashSnmpPackage_t * const r_raw_mesg, const int action)
{
  long localErrorStatus = error_status;
  long storedLocalErrorIndex = *r_pErrorIndex;
  int localInLength = in_length;
  int localOutLength = out_length;
  const long snmpVersion = r_raw_mesg->mesg.version;
  const unsigned char pduType = r_raw_mesg->mesg.pdutype;
  unsigned char* localpInDataPtr = r_pInData;

  {
    //const smashSnmpInfo_t* const pResponse = &(r_raw_mesg->mesg);
    int typeSearch = G_AGENT_EXACT;
    if (pduType == SNMP_GETNEXT_REQ_PDU || pduType == SNMP_GETBULK_REQ_PDU) typeSearch = G_AGENT_NEXT;

    *r_pErrorIndex = 1;
    // Похоже учитывается попытки собрать пакет?
    while (localInLength > 0 && localErrorStatus > 0) {
      unsigned char* pMibVarVal;
      unsigned char* pPkgVarVal;
      mapiVarInfo_t varInfo;
      mapiOid_t localOid;
      mapiSetFunc_t setterCallback;
      int noSuchObj;
      int varValLen;
      unsigned char varValType;

      localOid.namelen = SA_MAX_OID_LEN;
      // Похоже разбираем запрос, и выделяем OID
      localpInDataPtr = __parseOneVarbind
          (localpInDataPtr, &localOid, &varValType, &varValLen, &pPkgVarVal, &localInLength);

      if (localpInDataPtr == NULL) return PARSE_ERROR;

      // Search
      if (typeSearch == G_AGENT_NEXT) {
           pMibVarVal
          = mib_searchNext(&localOid, &varInfo, typeSearch, &setterCallback, &noSuchObj);
        }
      else pMibVarVal
          = mib_searchExact(&localOid, &varInfo, typeSearch, &setterCallback, &noSuchObj);

      // Choose method
      if (pduType == SNMP_SET_REQ_PDU) {
        // FIXME: check community and leaf type - auth
        //if (__isAuth(comm, commLen, varInfo.accessType, pduType) == ERR_AUTHORIZATIONERROR)
        //    return ERR_AUTHORIZATIONERROR;

        if (ACCESS_RW != varInfo.accessType) return SNMP_ERROR_NOTWRITABLE;
        if (setterCallback == NULL) {
          if (pMibVarVal == NULL) return SNMP_ERROR_NOTWRITABLE;
          else {
            if (!__isGoodValue(varValType, varValLen, varInfo.asn1Type, varInfo.varlen))
              return(SNMP_ERROR_WRONGTYPE);
            return(SNMP_ERROR_NOTWRITABLE);
          }
        // SET with work
        } else {
          if (!__isGoodValue(varValType, varValLen, varInfo.asn1Type, varInfo.varlen))
            return(SNMP_ERROR_WRONGTYPE);

          // FIXME: FOR ALL SET!!
          // FIXME: now only Int32 > 0
          if (ASN1_INTEGER == varValType
            && (COMMIT == action || CHECK == action || ACTION == action || FREE == action)
            )
          {
            int negative = 0;
            if (varValLen < 1) return SNMP_ERROR_WRONGTYPE;
            if (pPkgVarVal[0] & 0x80) negative = 1;
            if (negative) return SNMP_ERROR_WRONGVALUE;

            {
              int err = SNMP_ERROR_NOERROR;
              char magic = localOid.name[(localOid.namelen-1)-1];
              mapiValue_t setValue = {varValType, pPkgVarVal, varValLen};
              mapiOidPack_t oidVal;
              oidVal.magic = magic;
              oidVal.oid = localOid;

              if (COMMIT == action)
                pMibVarVal = (*setterCallback)(oidVal, &varInfo.varlen, setValue, NULL, &err);

              // FIXME: maybe something else
              if (err == SNMP_ERROR_NOERROR) return err;
              else return SNMP_ERROR_NOTWRITABLE;
            }
          }
        }  // SET with..
      } else {
        // GET/GETNEXT?
        if (pMibVarVal == NULL) {
          varInfo.varlen = 0;
          if (typeSearch == G_AGENT_EXACT) {
            if (noSuchObj == TRUE) varInfo.asn1Type = SNMP_NOSUCHOBJECT;
            else varInfo.asn1Type = SNMP_NOSUCHINSTANCE;
          } else
            varInfo.asn1Type = SNMP_ENDOFMIBVIEW;
        }

        if (snmpVersion == SNMP_VERSION_1) map_types_smiv2_to_smiv1_NI(&varInfo.asn1Type);

        // Похоже создает ответ, но в OID запроса!
        r_pOutData = __emitOneVarbind
            (r_pOutData, &localOid
             , varInfo.asn1Type, varInfo.varlen, pMibVarVal, &localOutLength);

        if (r_pOutData == NULL) return SNMP_ERROR_TOOBIG;
      }
      (*r_pErrorIndex)++;
      localErrorStatus--;
    }  // while
  }

  // FIXME: Work under pack vars
  // Read next?
  /* Now we start working on the repeater list */
  {
    mapiOid_t pOidsAcc[CFG_SIZE_PKG_WTF];
    int msgIsFull = FALSE;
    unsigned char* pOutDataSave;
    int lastPtr = 0;
    {int recordPtr = 0;
    for (recordPtr = 0; recordPtr < CFG_SIZE_PKG_WTF; recordPtr++) {
      mapiVarInfo_t varInfo;
      mapiSetFunc_t setter;
      int noSuchObj;
      int varValLen;
      unsigned char  varValType;
      unsigned char* pPkgVarVal;
      lastPtr++;

      if (!(localInLength > 0 && !msgIsFull))
        break;

      pOidsAcc[recordPtr].namelen = SA_MAX_OID_LEN;
      localpInDataPtr = __parseOneVarbind(
          localpInDataPtr, &pOidsAcc[recordPtr],
          &varValType, &varValLen, &pPkgVarVal, (int *)&localInLength);

      RETURN_INT_ON_PARSE_ERROR(localpInDataPtr, "");

      // Деламе обычные запросы
      pPkgVarVal
          = mib_searchExact(&pOidsAcc[recordPtr], &varInfo, G_AGENT_NEXT, &setter, &noSuchObj);

      if (pPkgVarVal == NULL) {
        varInfo.asn1Type = SNMP_ENDOFMIBVIEW;
        varInfo.varlen = 0;
      }

      {
        int out_length_save = localOutLength;
        pOutDataSave = r_pOutData;
        if (snmpVersion == SNMP_VERSION_1) map_types_smiv2_to_smiv1_NI(&varInfo.asn1Type);

        r_pOutData = __emitOneVarbind(
            r_pOutData, &pOidsAcc[recordPtr],
            varInfo.asn1Type, varInfo.varlen, pPkgVarVal, &localOutLength);

        if (varInfo.asn1Type == SNMP_ENDOFMIBVIEW) pOidsAcc[recordPtr].namelen = 0;

        if (r_pOutData == NULL){
            r_pOutData = pOutDataSave;
            localOutLength = out_length_save;
            msgIsFull = TRUE;
        }
      }
    }}

    // Что происходит?
    // Readed only from MIB
    while (--storedLocalErrorIndex > 0) {
      int j = 0;
      for (j = 0; j < lastPtr; j++) {
        if (msgIsFull)
           break;

        if (pOidsAcc[j].namelen == 0)
          continue;

        {
          mapiVarInfo_t varInfo;
          mapiSetFunc_t setter;
          unsigned char* pMibVarVal = NULL;
          int noSuchobj;

          pMibVarVal = mib_searchExact(&pOidsAcc[j], &varInfo, G_AGENT_NEXT, &setter, &noSuchobj);

          if (pMibVarVal == NULL)
            varInfo.asn1Type = SNMP_ENDOFMIBVIEW;

          // Продолжаем поиск
          {
            int out_length_save = localOutLength;
            pOutDataSave = r_pOutData;

            if (snmpVersion == SNMP_VERSION_1) map_types_smiv2_to_smiv1_NI(&varInfo.asn1Type);

            r_pOutData = __emitOneVarbind(
                r_pOutData, &pOidsAcc[j], varInfo.asn1Type, varInfo.varlen,
                pMibVarVal, &localOutLength);

            if (varInfo.asn1Type == SNMP_ENDOFMIBVIEW) pOidsAcc[j].namelen = 0;

            if (r_pOutData == NULL){
              r_pOutData = pOutDataSave;
              localOutLength = out_length_save;
              msgIsFull = TRUE;
            }
          }
        }
        //
      }
    }
  }
  r_raw_mesg->response_packet_end = r_pOutData;
  *r_pErrorIndex = 0;
  return SNMP_ERROR_NOERROR;
}

/**
  \brief

  \param[in, out]  type_request = 0 - RESP?
*/
static unsigned char *s_emitResponseWithoutVarbinds(
    smashSnmpPackage_t *r_pPackage
    , char type_request)
{
  unsigned char *out_data = r_pPackage->response;
  int out_length = SNMP_MAX_MSG_LENGTH;
  long zero = 0;

  out_data = asn_build_sequence(
      out_data, &out_length,
      (unsigned char)(ASN_SEQUENCE | ASN_CONSTRUCTOR), 0);
  RETURN_ON_BUILD_ERROR(out_data, "build sequence header");

  r_pPackage->response_version = out_data;
  out_data = asn_build_int(
      out_data, &out_length,
      (unsigned char)(ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
      &(r_pPackage->mesg.version), sizeof(r_pPackage->mesg.version));
  RETURN_ON_BUILD_ERROR(out_data, "build snmp-version");

  out_data = asn_build_string(
      out_data, &out_length,
      (unsigned char)(ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_OCTET_STR),
      r_pPackage->mesg.access_info.community_based.string,
      r_pPackage->mesg.access_info.community_based.length);
  RETURN_ON_BUILD_ERROR(out_data, "build snmp-version");

  r_pPackage->response_pdu = out_data;
  if (type_request == 0)
    out_data = asn_build_sequence(out_data, &out_length,(unsigned char)SNMP_GET_RSP_PDU, 0);
  else 
    out_data = asn_build_sequence(out_data, &out_length,(unsigned char)type_request, 0);
  
  r_pPackage->response_request_id = out_data;
  out_data = asn_build_int(
      out_data, &out_length, 
      (unsigned char)(ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
      &(r_pPackage->mesg.request_id), sizeof(r_pPackage->mesg.request_id));
  RETURN_ON_BUILD_ERROR(out_data, "build request-id");

  r_pPackage->response_error_status = out_data;
  out_data = asn_build_int(
      out_data, &out_length, 
      (unsigned char)(ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
      &zero, sizeof(zero));
  RETURN_ON_BUILD_ERROR(out_data, "build error_status");
  
  r_pPackage->response_error_index = out_data;
  out_data = asn_build_int(
      out_data, &out_length, 
      (unsigned char)(ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
      &zero, sizeof(zero));
  RETURN_ON_BUILD_ERROR(out_data, "build error_index");

  r_pPackage->response_varbind_sequence = out_data;
  out_data = asn_build_sequence(
      out_data, &out_length,
      (unsigned char)(ASN_SEQUENCE | ASN_CONSTRUCTOR), 0);
  RETURN_ON_BUILD_ERROR(out_data, "build sequence header");
  return (unsigned char *)out_data;
}

/**
  \return if > 0 - ok else error
*/
static int s_correctResponseWithLengths(
    smashSnmpPackage_t *r_pPackage, long error_status, long error_index,char type_request)
  {
  unsigned char *out_data;
  int out_length;

  if (error_status == SNMP_ERROR_NOERROR) {
    out_length = 4;
    out_data = asn_build_sequence(
        r_pPackage->response_varbind_sequence, &out_length,
        (unsigned char)(ASN_SEQUENCE | ASN_CONSTRUCTOR),
        ((r_pPackage->response_packet_end - r_pPackage->response_varbind_sequence) - 4));
    RETURN_INT_ON_PARSE_ERROR(out_data, "correction error varbind length");
  } else if (error_status == SNMP_ERROR_TOOBIG) {
    if (r_pPackage->mesg.version == SNMP_VERSION_1) {
      fprintf(stderr, "Cannot return SNMP_TOOBIG in V1");
      return(0);
    }
    error_index = 0; /* Just to make sure it is '0' */
    r_pPackage->response_packet_end = r_pPackage->response_varbind_sequence + 4;

    out_length = 3;
    out_data = asn_build_int(
        r_pPackage->response_error_status, &out_length,
        (unsigned char)(ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
        &error_status, sizeof(error_status));
    RETURN_INT_ON_BUILD_ERROR(out_data, "build error_status");

    out_length = 3;
    out_data = asn_build_int(
        r_pPackage->response_error_index, &out_length,
        (unsigned char)(ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
        &error_index, sizeof(error_index));
    RETURN_INT_ON_BUILD_ERROR(out_data, "build error_index");
  } else if (error_status == PARSE_ERROR) {
#ifdef SNMP_GROUP
    snmpInASNParseErrs_instance++;
#endif
    return (ptrdiff_t)(NULL);
  } else {
    /* Make varbindlist identical                */
    /* This is done for the errors as well the SNMP SET (error_status==CREATE_IDENTICAL)  */
    if (error_status == CREATE_IDENTICAL) {
      error_status = 0;
    }
    
    bcopy(
        r_pPackage->request_varbind_sequence,
        r_pPackage->response_varbind_sequence,
        r_pPackage->request_varbind_sequence_length);
        
    r_pPackage->response_packet_end
        = r_pPackage->response_varbind_sequence + r_pPackage->request_varbind_sequence_length;

    out_length = 3;
    out_data = asn_build_int(
        r_pPackage->response_error_status, &out_length,
        (unsigned char)(ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
        &error_status, sizeof(error_status));
    RETURN_INT_ON_BUILD_ERROR(out_data, "build error_status");

    out_length = 3;
    out_data = asn_build_int(
        r_pPackage->response_error_index, &out_length,
        (unsigned char)(ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
        &error_index, sizeof(error_index));
    RETURN_INT_ON_BUILD_ERROR(out_data, "build error_index");
  }

  out_length = 4;
  out_data = asn_build_sequence(
      r_pPackage->response, &out_length,
      (unsigned char)(ASN_SEQUENCE | ASN_CONSTRUCTOR),
      (r_pPackage->response_packet_end - r_pPackage->response_version));
  RETURN_INT_ON_BUILD_ERROR(out_data, "correction error message sequence");

  out_length = 4;
  if(type_request == 0)
    out_data = asn_build_sequence(
          r_pPackage->response_pdu, &out_length, SNMP_GET_RSP_PDU
          , r_pPackage->response_packet_end - r_pPackage->response_request_id);
  else  
    out_data = asn_build_sequence(
        r_pPackage->response_pdu,
        &out_length, type_request, r_pPackage->response_packet_end-r_pPackage->response_request_id);
  
  RETURN_INT_ON_BUILD_ERROR(out_data, "correction error request-id");

  r_pPackage->response_length = r_pPackage->response_packet_end-r_pPackage->response;
  return r_pPackage->response_length;
}

smash_CApiStatus smash_parsePDUAndCommunity(smashSnmpPackage_t *r_pPackage) {
  // http://stackoverflow.com/questions/25645729/what-sets-snmp-error-and-error-index-fields
  unsigned char* in_data = r_pPackage->request;
  int in_length = r_pPackage->request_length;
  {
    unsigned char type = 0;
    in_data = asn_parse_header(in_data, &in_length, &type);
    if (!in_data) {
      return SMASH_ERROR_PARSE_HEADER;
    }
    if (type != (ASN_SEQUENCE | ASN_CONSTRUCTOR)){
      return SMASH_WRONG_ASN1_TYPE_HEADER;
    }
    in_data = asn_parse_int(
        in_data, &in_length, &type,
        &(r_pPackage->mesg.version), sizeof(r_pPackage->mesg.version));

    if(!in_data)
      return SMASH_PARSE_ERROR;

    switch (r_pPackage->mesg.version) {
      case SNMP_VERSION_1:
      case SNMP_VERSION_2C:
        r_pPackage->mesg.access_info.community_based.length = MAX_COMMUNITY_LEN;
        in_data = asn_parse_string(in_data, &in_length, &type,
            (unsigned char*)r_pPackage->mesg.access_info.community_based.string,
            &(r_pPackage->mesg.access_info.community_based.length));

        if (!in_data)
          return SMASH_PARSE_COMMUNITY_ERROR;
        break;
      case SNMP_VERSION_2:
      default:
        return SMASH_WRONG_ARGS;
    }

    in_data = asn_parse_header(in_data, &in_length, &r_pPackage->mesg.pdutype);
    if(!in_data)
      return SMASH_PARSE_ERROR;
  }
  return SMASH_ALL_RIGHT;
}

smash_CApiStatus smash_parseAndEmitMessage(smashSnmpPackage_t *r_pPackage, const int isAuthorized)
{
  // http://stackoverflow.com/questions/25645729/what-sets-snmp-error-and-error-index-fields
  unsigned char* in_data = r_pPackage->request;
  int in_length = r_pPackage->request_length;
  long error_status = 0;
  long error_index = 0;

  {
    unsigned char type = 0;
    in_data = asn_parse_header(in_data, &in_length, &type);
    if (!in_data) {
      return SMASH_ERROR_PARSE_HEADER;
    }
    if (type != (ASN_SEQUENCE | ASN_CONSTRUCTOR)){
      return SMASH_WRONG_ASN1_TYPE_HEADER;
    }
    in_data = asn_parse_int(
        in_data, &in_length, &type,
        &(r_pPackage->mesg.version), sizeof(r_pPackage->mesg.version));

    if(!in_data)
      return SMASH_PARSE_ERROR;

    switch (r_pPackage->mesg.version) {
      case SNMP_VERSION_1:
      case SNMP_VERSION_2C:
        r_pPackage->mesg.access_info.community_based.length = MAX_COMMUNITY_LEN;
        in_data = asn_parse_string(in_data, &in_length, &type,
            (unsigned char*)r_pPackage->mesg.access_info.community_based.string,
            &(r_pPackage->mesg.access_info.community_based.length));

        if (!in_data)
          return SMASH_PARSE_COMMUNITY_ERROR;
        break;
      case SNMP_VERSION_2:
      default:
        return SMASH_WRONG_ARGS;
    }

    in_data = asn_parse_header(in_data, &in_length, &r_pPackage->mesg.pdutype);
    if(!in_data)
      return SMASH_PARSE_ERROR;

    switch (r_pPackage->mesg.pdutype) {
      case SNMP_GETBULK_REQ_PDU:
        if (r_pPackage->mesg.version == SNMP_VERSION_1) {
          return SMASH_WRONG_ARGS;
        }
      case SNMP_GET_RSP_PDU:  //
      case SNMP_GET_REQ_PDU:
      case SNMP_GETNEXT_REQ_PDU:
      case SNMP_SET_REQ_PDU:
        in_data = asn_parse_int(in_data, &in_length, &type
                                , &(r_pPackage->mesg.request_id)
                                , sizeof(r_pPackage->mesg.request_id));
        if(!in_data)
          return SMASH_PARSE_ERROR;
        in_data = asn_parse_int(in_data, &in_length, &type, &error_status, sizeof(error_status));
        if(!in_data)
          return SMASH_PARSE_ERROR;
        in_data = asn_parse_int(in_data, &in_length, &type, &error_index, sizeof(error_index));
        if(!in_data)
          return SMASH_PARSE_ERROR;
        break;

      default:
        return SMASH_WRONG_ARGS;
    }

    r_pPackage->request_varbind_sequence = in_data;
    r_pPackage->request_varbind_sequence_length = in_length;
    in_data = asn_parse_header(in_data, &in_length, &type);
    if (!in_data)
      return SMASH_OUT_OF_SPACE;

    if (type != (unsigned char)(ASN_SEQUENCE | ASN_CONSTRUCTOR)) {
      return SMASH_WRONG_ASN1_TYPE;
    }
  }

  {
    unsigned char* out_data = r_pPackage->response;
    int out_length = SNMP_MAX_MSG_LENGTH;
    long dummyindex;
    int responseLen = 0;

    out_data = s_emitResponseWithoutVarbinds(r_pPackage,0);
    if (!out_data)
      return SMASH_BUILD_ERROR;

    if (!isAuthorized) {
      error_status = ERR_AUTHORIZATIONERROR;
      goto __pack;
    }

    switch (r_pPackage->mesg.pdutype) {
      case SNMP_GETBULK_REQ_PDU:
        error_status = s_emitVarbindsWithAction(
            in_data, in_length,
            out_data, out_length,
            error_status, &error_index, r_pPackage, RESERVE1);
        break;
      case SNMP_GET_REQ_PDU  :
      case SNMP_GETNEXT_REQ_PDU  :
        error_status = s_emitVarbindsWithAction(
            in_data, in_length,
            out_data, out_length,
            9999, &error_index, r_pPackage, RESERVE1);
        break;
      case SNMP_SET_REQ_PDU :
        // Banch of actions
        error_status = s_emitVarbindsWithAction(
            in_data, in_length,
            out_data, out_length,
            9999, &error_index, r_pPackage, CHECK);

        if (error_status == SNMP_ERROR_NOERROR) {
          error_status = s_emitVarbindsWithAction(
              in_data, in_length,
              out_data, out_length,
              9999, &error_index, r_pPackage, COMMIT);
        }

        if (error_status == SNMP_ERROR_NOERROR) {
          int responseLen = 0;
          s_emitVarbindsWithAction(
              in_data, in_length,
              out_data, out_length,
              9999, &dummyindex, r_pPackage, ACTION);

          responseLen = s_correctResponseWithLengths(r_pPackage, CREATE_IDENTICAL, 0,0);
          if (responseLen > 0) {
            if (responseLen != r_pPackage->response_length)
              return SMASH_BUILD_ERROR;
            return SMASH_ALL_RIGHT;
          }
          return SMASH_BUILD_ERROR;

        } else {
          s_emitVarbindsWithAction(
              in_data, in_length,
              out_data, out_length,
              9999, &dummyindex, r_pPackage, FREE);
        }
        break;
      default : {
          return SMASH_WRONG_ARGS;
        }
     }

 __pack:
    if (r_pPackage->mesg.version == SNMP_VERSION_1) {
      s_mapErrorStatusSnmpv2ToSnmpv1_(&error_status);
    }
    responseLen = s_correctResponseWithLengths(r_pPackage, error_status, error_index, 0);
    if (responseLen > 0) {
      if (responseLen != r_pPackage->response_length)
        return SMASH_BUILD_ERROR;
      return SMASH_ALL_RIGHT;
    }
    return SMASH_BUILD_ERROR;
  }
}

static int s_emitVarbindsByTempl(
    mapiOid_t* p_oids_template, int countOids,
    unsigned char *out_data, int out_length,
    long *error_index, smashSnmpPackage_t *raw_mesg, int action)
{
  mapiOid_t oids[64];
  mapiOid_t* pCurrentOid = p_oids_template;
  char x = 0;

  for (x = 0;x < countOids; x++) {
    unsigned char  *p_data;
    const int kTypeSearch = G_AGENT_EXACT;
    mapiVarInfo_t varInfo;
    int noSuchObj = TRUE;
    mapiSetFunc_t setter_ = NULL;
    varInfo.accessType = 0;

    oids[0].namelen = pCurrentOid->namelen;

    // FIXME: 4 - sizeof int32_t
    memcpy(oids[0].name, pCurrentOid->name, pCurrentOid->namelen * 4);

    if (pCurrentOid->namelen == 0)
      return PARSE_ERROR;
    
    // Goto next oid
    pCurrentOid += 1;

    // Передается массив или только первый элемент?
    p_data = mib_searchExact(&oids[0], &varInfo, kTypeSearch,  &setter_, &noSuchObj);

    if (p_data == NULL) {
      varInfo.varlen = 0;
      if (noSuchObj == TRUE)
        varInfo.asn1Type = SNMP_NOSUCHOBJECT;
      else
        varInfo.asn1Type = SNMP_NOSUCHINSTANCE;
    }

    out_data = __emitOneVarbind(
        out_data, &oids[0], varInfo.asn1Type, varInfo.varlen, p_data, &out_length);
    if (out_data == NULL){
      return SNMP_ERROR_TOOBIG;
    }
  }

  raw_mesg->response_packet_end = out_data;
  *error_index = 0;
  return SNMP_ERROR_NOERROR;
}


smash_CApiStatus smash_buildInform(
    smashSnmpPackage_t *r_pIn, mapiOid_t * pOidsTable, int pkgSize , char type_request) {
  unsigned char  *out_data = r_pIn->response;
  int out_length = SNMP_MAX_MSG_LENGTH;
  long error_status = 0;
  long error_index = 0;
  int size = 0;

  *r_pIn->response_version = 1;
  *r_pIn->response_pdu = 0xA6;
  *r_pIn->response_error_index = 0;

  out_data = s_emitResponseWithoutVarbinds(r_pIn, type_request);
  if (!out_data)
    return SMASH_BUILD_ERROR;

  error_status
      = s_emitVarbindsByTempl(pOidsTable, pkgSize, out_data, out_length, &error_index, r_pIn,  RESERVE1);

  size = s_correctResponseWithLengths(r_pIn, error_status, error_index, type_request);
  if (size > 0) {
    if (size != r_pIn->response_length)
        return SMASH_BUILD_ERROR;
    return SMASH_ALL_RIGHT;
  }
  return SMASH_BUILD_ERROR;
}





