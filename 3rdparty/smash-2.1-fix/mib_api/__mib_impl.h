#ifndef SNMPAGENT_M_H
#define SNMPAGENT_M_H

#include "common/config.h"
#include "asn1/asn1.h"

#ifndef MAX_LEAF_COUNT      /*the max tree node of mib*/ 
#define MAX_LEAF_COUNT 500  /*default is 100*/
#endif

/*in table */
#define INDEX_TYPE_GET  0
#define INDEX_TYPE_GETFIRST  1
#define INDEX_TYPE_GETNEXT  2
#define INDEX_TYPE_SET  3

/*the result of campare two object identifier*/
#define CPOID_GT 1       /*greater than exp. 1.3.6.1.2>1.3.6.1.1*/
#define CPOID_LT 2       /*less than exp. 1.3.6.1.1<1.3.6.1.2*/
#define CPOID_EQU 3      /*equal exp. 1.3.6.1.1 = 1.3.6.1.1*/ 
#define CPOID_INSTANCE 4 /*instance exp 1.3.6.1.1.0 is instance of 1.3.6.1.1*/
#define CPOID_EQU_LG 5   /*equal but length greater than exp. 1.3.6.1.1.1 and 1.3.6.1.1 */ 
#define CPOID_EQU_LL 6   /*equal but length less than exp. 1.3.6.1.1 and 1.3.6.1.1.1 */ 

/*community access controll*/
#define COMMUNITY_RONLY 1
#define COMMUNITY_WONLY 2
#define COMMUNITY_RW 3
#define COMMUNITY_NOACCESS 4

/*mib-ii snmp group counter*/ 
#define SNMPINPKTS 1
#define SNMPOUTPKTS 2
#define SNMPINBADVERSIONS 3
#define SNMPINBADCOMMUNITYNAMES 4
#define SNMPINBADCOMMUNITYUSES 5
#define SNMPINASNPARSEERRS 6
#define SNMPINTOOBIGS 8
#define SNMPINNOSUCHNAMES 9
#define SNMPINBADVALUES 10
#define SNMPINREADONLYS 11
#define SNMPINGENERRS 12
#define SNMPINTOTALREQVARS 13
#define SNMPINTOTALSETVARS 14
#define SNMPINGETREQUESTS 15
#define SNMPINGETNEXTS 16
#define SNMPINSETREQUESTS 17
#define SNMPINGETRESPONSES 18
#define SNMPINTRAPS 19
#define SNMPOUTTOOBIGS 20
#define SNMPOUTNOSUCHNAMES 21
#define SNMPOUTBADVALUES 22
#define SNMPOUTGENERRS 24
#define SNMPOUTGETREQUESTS 25
#define SNMPOUTGETNEXTS 26
#define SNMPOUTSETREQUESTS 27
#define SNMPOUTGETRESPONSES 28
#define SNMPOUTTRAPS 29
#define SNMPENABLEAUTHENTRAPS 30

#define MAX_COMMUNITY_LENGTH  32
  

#endif //SNMPAGENT_M_H

