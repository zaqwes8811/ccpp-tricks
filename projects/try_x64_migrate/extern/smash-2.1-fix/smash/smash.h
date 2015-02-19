#ifndef AGENT_IAGENT_H_
#define AGENT_IAGENT_H_

#include "platform_specific/network_main_header.h"

#include "asn1/asn1.h"
#include "mib_api/mib_api.h"

// FIXME: no way
// http://stackoverflow.com/questions/1102542/how-to-define-an-enumerated-type-enum-in-c
//typedef enum {RANDOM, IMMEDIATE, SEARCH} strategy;

// Library interface
// http://stackoverflow.com/questions/22998212/decode-snmp-pdus-where-to-start
typedef struct {
    long version;
    unsigned char pdutype;

    /* Access identification info */
    union {
        /* SNMPv1 and SNMPv2c community based info */
        struct {
          char string[64];
          int  length;
          int  number;
        } community_based;
    } access_info;

    /* message variables */
    // http://www.rane.com/note161.html
    long request_id;  /* Identifying Request number */
} smashSnmpInfo_t;

typedef struct {
    smashSnmpInfo_t mesg;
    /* originator address */
    struct sockaddr_in originatorAddress;
    int originatorAddressLength;

    /* The SNMP request (BER-encoded data) */
    //int
    size_t
    request_length;
    unsigned char request[
    //size_t
    (SNMP_MAX_MSG_LENGTH)
    ];
    unsigned char* request_varbind_sequence;
    int request_varbind_sequence_length;

    /* The SNMP response (BER-encoded data) */
    // FIXME: DANGER: some must be init real memory!
    unsigned char* response_version;
    unsigned char* response_pdu;
    unsigned char* response_request_id;
    unsigned char* response_error_index;
    unsigned char* response_error_status;
    unsigned char* response_varbind_sequence;
    unsigned char* response_first_varbind;
    unsigned char* response_packet_end;
    int response_length;
    unsigned char  response[SNMP_MAX_MSG_LENGTH*2];
} smashSnmpPackage_t;

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

// FIXME: global trouble - if failed util function, how fail in terms SNMP protocol?
//   Package not builded - what make - no respond?
typedef int smash_CApiStatus;
typedef enum {
  SMASH_WRONG_ASN1_TYPE_HEADER,
  SMASH_ERROR_PARSE_HEADER,
  SMASH_ALL_RIGHT,
  SMASH_BUILD_ERROR,
  SMASH_PARSE_ERROR,
  SMASH_PARSE_COMMUNITY_ERROR,
  SMASH_WRONG_ARGS,
  SMASH_WRONG_ASN1_TYPE,
  SMASH_OUT_OF_SPACE
} smash_Statuses;

/**
  \brief build TRAP/INFORMS package

  \param[in] Inform_Oid - oids mask for package
  \param[in] type_request - 0 - response? PDU type

  \return: package size
*/
EXTERNC smash_CApiStatus smash_buildInform(
    smashSnmpPackage_t* pi, mapiOid_t* Inform_Oid, int Count, char type_request);

/**
  \brief Parse package and build response pdu
*/
EXTERNC smash_CApiStatus smash_parseAndEmitMessage(smashSnmpPackage_t *pi, const int isAuthorized);

EXTERNC smash_CApiStatus smash_parsePDUAndCommunity(smashSnmpPackage_t *r_pPackage);

#undef EXTERNC

#ifdef __cplusplus
namespace smash {
static const char kINFORM_PDU = (char)(SNMP_INFORM_REQ_PDU);
static const char kTRAPV2_PDU = (char)(SNMP_TRP2_REQ_PDU);
static const char kInt32Size = 4;  // troubles with crossplatform coding

static const char kGETBULK_REQ_PDU = (char)SNMP_GETBULK_REQ_PDU;
static const char kGET_RSP_PDU = (char)SNMP_GET_RSP_PDU;
static const char kGET_REQ_PDU = (char)SNMP_GET_REQ_PDU;
static const char kGETNEXT_REQ_PDU = (char)SNMP_GETNEXT_REQ_PDU;
static const char kSET_REQ_PDU = (char)SNMP_SET_REQ_PDU;

static const char kVERSION_2C = (char)SNMP_VERSION_2C;
}
#endif // __cplusplus

#endif
