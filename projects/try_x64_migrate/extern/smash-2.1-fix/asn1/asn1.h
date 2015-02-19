/*
 * Definitions for Abstract Syntax Notation One, ASN.1
 * As defined in ISO/IS 8824 and ISO/IS 8825
 *
 *
 */
/***********************************************************
  Copyright 1988, 1989 by Carnegie Mellon University

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of CMU not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

CMU DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
CMU BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
******************************************************************/

#ifndef _ASN1_H_
#define _ASN1_H_

#ifdef HAVE_CONFIG_H
#include "agent/_snmp_config.h"
#endif

#define SA_MAX_OID_LEN  32

/* changed by H.H. */
typedef struct {
    unsigned long high;
    unsigned long low;
} Counter64;

/* added by H.H. */
//typedef unsigned long  asn1OidElem_t;
#ifndef SMALL_SUBIDS
  typedef unsigned long  asn1OidElem_t;  // 4 byte
  #define MAX_SUBID   0xFFFFFFFF
#else
  typedef unsigned char  asn1OidElem_t;
  #define MAX_SUBID   0xFF
#endif

#define ASN_BOOLEAN      (0x01)

#define ASN_INTEGER      (0x02)

#define ASN_BIT_STR      (0x03)
#define ASN_OCTET_STR      (0x04)
#define ASN_NULL      (0x05)
#define ASN_OBJECT_ID      (0x06)
#define ASN_SEQUENCE      (0x10)

#define ASN_UNIVERSAL      (0x00)
#define ASN_APPLICATION     (0x40)
#define ASN_CONTEXT      (0x80)
#define ASN_PRIVATE      (0xC0)

#define ASN_PRIMITIVE      (0x00)
#define ASN_CONSTRUCTOR      (0x20)

#define ASN_LONG_LEN      (0x80)
#define ASN_EXTENSION_ID    (0x1F)
#define ASN_BIT8      (0x80)

#define IS_CONSTRUCTOR(byte)  ((byte) & ASN_CONSTRUCTOR)
#define IS_EXTENSION_ID(byte)  (((byte) & ASN_EXTENSION_ID) == ASN_EXTENSION_ID)

unsigned char  *asn_parse_int(unsigned char *data, int *datalength, unsigned char *type, long *intp, int intsize);
unsigned char  *asn_parse_unsigned_int(unsigned char *data, int *datalength, unsigned char *type, unsigned long *intp, int intsize);
unsigned char  *asn_build_int(/*unsigned char *data, int *datalength, unsigned char type, long *intp, int intsize*/);
unsigned char  *asn_build_unsigned_int(/*unsigned char *data, int *datalength,  unsigned char type, unsigned long *intp, int intsize*/);

/*
 * asn_parse_string - pulls an octet string out of an ASN octet string type.
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the beginning of the next object.
 *
 *  "string" is filled with the octet string.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 */
unsigned char  *asn_parse_string(unsigned char *data, int *datalength, unsigned char *type, unsigned char *string, int *strlength);
unsigned char  *asn_build_string(/*unsigned char *data, int *datalength, unsigned char type, unsigned char *string, int strlength*/);
unsigned char  *asn_build_IPAddress(/*unsigned char *data, int *datalength, unsigned char type, long *intp*/);
unsigned char  *asn_parse_header(unsigned char *data, int *datalength, unsigned char *type);
unsigned char  *asn_build_header(/*unsigned char *data, int *datalength, unsigned char type, int length*/);
unsigned char  *asn_build_sequence(/*unsigned char *data, int *datalength, unsigned char type, int length*/);
unsigned char  *asn_parse_length(unsigned char *data, unsigned long *datalength);
unsigned char  *asn_build_length(unsigned char *data, int *datalength, int length);
unsigned char  *asn_parse_objid(unsigned char  *data, int *datalength, unsigned char *type, asn1OidElem_t *objid, int *objidlength);
unsigned char  *asn_build_objid(/*unsigned char  *data, int *datalength, unsigned char type, oid *objid, int objidlength*/);
unsigned char  *asn_parse_null(unsigned char *data, int *datalength, unsigned char *type);
unsigned char  *asn_build_null(/*unsigned char *data, int *datalength, unsigned char *type*/);
unsigned char  *asn_parse_bitstring();
unsigned char  *asn_build_bitstring();
unsigned char  *asn_parse_unsigned_int64();
unsigned char  *asn_build_unsigned_int64();

/* The standard SNMP-ports */
#define SNMP_PORT               161
#define SNMP_TRAP_PORT          162

/* The maximum accepted packet length */
#define SNMP_MAX_MSG_LENGTH    1500
#define SNMP_MAX_COMMUNITY_LENGTH  1500


/* SNMP versions */
#define SNMP_VERSION_1 0x00  /*snmpv1*/
#define SNMP_VERSION_2C 0x01  /*snmpv2c*/
#define SNMP_VERSION_2      2
#define SNMP_VERSION_3 0x03  /*snmpv3*/

/* The SNMP Protocol Data Units */
#define SNMP_GET_REQ_PDU    (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x0)
#define SNMP_GETNEXT_REQ_PDU    (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x1)
#define SNMP_GET_RSP_PDU    (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x2)
#define SNMP_SET_REQ_PDU    (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x3)
#define SNMP_TRP_REQ_PDU    (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x4)
#define SNMP_GETBULK_REQ_PDU    (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x5)
#define SNMP_INFORM_REQ_PDU    (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x6)
#define SNMP_TRP2_REQ_PDU    (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x7)
#define SNMP_REPORT_PDU      (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x8)

/* SNMP version 1 error-codes */
#define SNMP_ERROR_NOERROR    (0x0)
#define SNMP_ERROR_TOOBIG    (0x1)
#define SNMP_ERROR_NOSUCHNAME    (0x2)
#define SNMP_ERROR_BADVALUE    (0x3)
#define SNMP_ERROR_READONLY    (0x4)
#define SNMP_ERROR_GENERR    (0x5)

/* SNMP version 2 error-codes */
// FIXME: error in names!!
#define SNMP_ERROR_NOACCESS    (0x6)
#define SNMP_ERROR_WRONGTYPE    (0x7)
#define SNMP_ERROR_WRONGLENGTH    (0x8)
#define SNMP_ERROR_WRONGENCODING  (0x9)
#define SNMP_ERROR_WRONGVALUE    (0x10)
#define SNMP_ERROR_NOCREATION    (0x11)
#define SNMP_ERROR_INCONSISTENTVALUE  (0x12)
#define SNMP_ERROR_RESOURCEUNAVAILABLE  (0x13)
#define SNMP_ERROR_COMMITFAILED    (0x14)
#define SNMP_ERROR_UNDOFAILED    (0x15)
#define SNMP_ERROR_AUTHORIZATIONERROR  (0x16)
#define SNMP_ERROR_NOTWRITABLE    (0x17)
#define SNMP_ERROR_INCONSISTENTNAME  (0x18)

#define SNMP_TRAP_COLDSTART    (0x0)
#define SNMP_TRAP_WARMSTART    (0x1)
#define SNMP_TRAP_LINKDOWN    (0x2)
#define SNMP_TRAP_LINKUP    (0x3)
#define SNMP_TRAP_AUTHFAIL    (0x4)
#define SNMP_TRAP_EGPNEIGHBORLOSS  (0x5)
#define SNMP_TRAP_ENTERPRISESPECIFIC  (0x6)

/* SNMP VarBinds. */
#define SNMP_NOSUCHOBJECT    (ASN_CONTEXT | ASN_PRIMITIVE | 0x0)
#define SNMP_NOSUCHINSTANCE  (ASN_CONTEXT | ASN_PRIMITIVE | 0x1)
#define SNMP_ENDOFMIBVIEW    (ASN_CONTEXT | ASN_PRIMITIVE | 0x2)


/* Object Syntax - universal types */
#define SNMP_INTEGER     ASN_INTEGER
#define SNMP_STRING      ASN_OCTET_STR
#define SNMP_OBJID       ASN_OBJECT_ID
#define SNMP_NULLOBJ     ASN_NULL
#define SNMP_BITSTRING   ASN_BIT_STR
#define SNMP_BITS        ASN_BIT_STR

/* Object Syntax - application types */
#define SNMP_IPADDRESS   (ASN_APPLICATION | 0)
#define SNMP_COUNTER     (ASN_APPLICATION | 1)
#define SNMP_GAUGE       (ASN_APPLICATION | 2)
#define SNMP_UINTEGER    (ASN_APPLICATION | 2)
#define SNMP_TIMETICKS   (ASN_APPLICATION | 3)
#define SNMP_OPAQUE      (ASN_APPLICATION | 4)
#define SNMP_NSAP        (ASN_APPLICATION | 5)
#define SNMP_COUNTER64   (ASN_APPLICATION | 6)

// http://msdn.microsoft.com/en-us/library/windows/desktop/aa378974(v=vs.85).aspx
/*error field of snmp package*/
#define ERR_NOERROR 0
#define ERR_TOOBIG 1
#define ERR_NOSUCHNAME 2
#define ERR_BADVALUE 3
#define ERR_READONLY 4
#define ERR_GENERR 5

#define ERR_NOACCESS 6
#define ERR_WRONGTYPE 7
#define ERR_WRONGLENGTH 8
#define ERR_WRONGENCODING 9
#define ERR_WRONGVALUE 10
#define ERR_NOCREATION 11
#define ERR_INCONSISTENTVALUE 12
#define ERR_RESOURCEUNAVAILABLE 13
#define ERR_COMMITFAILED 14
#define ERR_UNDOFAILED 15
#define ERR_AUTHORIZATIONERROR 16
#define ERR_NOTWRITABLE 17
#define ERR_INCONSISTENTNAME 18

#define PDU_ERR_EOFTAB 6
#define PDU_ERR_EOFCOLUMN 7


#define ACTION_SET_VALIDATE 1
#define ACTION_SET_COMMIT  2

/**/
#define ASN1_INTEGER 0x02
#define ASN1_SEQUENCE 0x30
#define ASN1_NULL 0x05
#define ASN1_OID 0x06
#define ASN1_OCTSTRING 0x04

#define ASN1_IPADDRESS 0x40
#define ASN1_COUNTER  0x41
#define ASN1_GAUGE   0x42
#define ASN1_TIMETICKS  0x43
#define ASN1_OPAQUE 0x44

#define ASN1_INTEGER32 2
#define ASN1_COUNTER32 0x41
#define ASN1_GAUGE32  0x42
#define ASN1_UNSIGNED32 0x42
#define ASN1_COUNTER64 0x46

#define PDU_GET_REQUEST 0xA0
#define PDU_GETNEXT_REQUEST 0xA1
#define PDU_GET_RESPONSE 0xA2
#define PDU_SET_REQUEST 0xA3
#define PDU_TRAPV1 0XA4
#define PDU_GETBULK_REQUEST 0xA5
#define PDU_TRAPV2 0XA7

#define ASN1_NOSUCHOBJECT 0x80
#define ASN1_NOSUCHINSTANCE 0x81
#define ASN1_ENDOFMIBVIEW 0x82

/**/
#define MAX_COMMUNITY_LEN 64



#endif
