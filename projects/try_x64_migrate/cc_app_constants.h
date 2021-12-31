#ifndef SERVER_SIDE_CODE_TOP_HEADERS_APP_CONSTANTS_H_
#define SERVER_SIDE_CODE_TOP_HEADERS_APP_CONSTANTS_H_

// лучше сделать строками! т.к. информ. прихожит с вебстраницы
static const unsigned char kSetExciterACodeCmdFromWeb = 11;  // '1'+'number_vtv' !! Danger !!
static const unsigned char kSetExciterBCodeCmdFromWeb = 12;
static const unsigned char gk_powerUp = 13;
static const unsigned char gk_powerDown = 14;

// Разметка
//static const int kByte0Alrms = 5+2;
//static const int kByteStateTmitter = 5+0;
//static const int kPowerTH = 5+7;
//static const int kFRWHL = 5+9;
//static const int kBytePAB2Status = 5+10+5+28+5+28+6+10+7*4; //
//static const int kBytePAB1Status = 5+10+5+28+5+28; // 81

//
#define  TR_LEN_REQ        7    //total length
#define  TR_LEN_REQ_v1      3    //total length
#define  TR_LEN_MAINPAR_ANS    16
#define  TR_LEN_CFG_ANS_M    24    //22+2 (without reservet byte)

#define   kMaxExciters         4   
#define  kMaxPABs        12
  #define  g_NUM_PAB_4KWATT      10
#define  kMaxTAsPerPAB        4
#define  kMaxBCLs        2
#define  kMaxDBs        5

#define  g_MAX_LEN_ALLPARAM    1500    //7+9+33*2+44*12+5*27+4*6+1>
#define  g_LEN_HEAD          7
#define  g_LEN_HED_v1        4
#define  g_LEN_IB_TR        10    //info block of Transmit
#define  g_LEN_IB_TR_v1      9    //info block of Transmit
#define  g_LEN_VTV_MPAR      5
#define  g_LEN_VTV_MPAR_AN      2
#define  LEN_VTV_MOD        28   
#define  g_LEN_PAB_MPAR      6    //main param PAB
#define  LEN_PAB_PREA      10    //preamplif
#define  LEN_PAB_PA        7    //power amp
#define  g_LEN_PAB_v1        27    //power amp
#define  g_LEN_CS          1
#define g_LEN_TIME        7

#define  kLengthRequestCmd        5    //length
#define  kLengthRequestCmd_v1      3    //length

#define  kCmdRequest        0x41  //code type of request
#define  GkCmdRequest_v1      0x09  //code type of request
#define  kCfgRequest        0x44  //code type of cfg req

#define  TR_REQ_STATUS      0x1
#define  kRequestCfgTransmitter      0x1
#define  TR_REQ_CHANNEL      0xA
#define  TR_REQ_POWER      0xB
#define  TR_REQ_FRW        0xC
#define kRequestMainParameters      (0xD)

#define kRequestAllParameters  (0xE)

#if defined(G_FEATURE_SEND_IP_SOME_OPTION)
#define kRequestWithIpSettings (21)
//#elif
//#define kRequestWithIpSettings (19)
#else
#  error("Unknown option")
#endif

#define GkRequestAllParameters_v1    (0x3)
#define kRequestProtocolEvent      0xF

#define  TR_CMD_CTL        0x01  //code type of ctl

#define  PROTO_TR_CTL_TR_ON        0x01
#define  PROTO_TR_CTL_TR_OFF        0x02
#define  PROTO_TR_CTL_TR_LOCK      0x03
#define  PROTO_TR_CTL_TR_UNLOCK      0x04
#define  PROTO_TR_CTL_TR_RST_ERR      0x05

#define  PROTO_TR_CTL_TR_SET_ADDR    0x07

#define  PROTO_TR_CTL_TR_SET_HALF    0x08
#define  PROTO_TR_CTL_TR_SET_FULL    0x09

#define kSetExciterACmd  0x10
#define kSetExciterBCmd  0x11

#define gkV0PowerUp (0x0d)
#define gkV0PowerDown (0x0e)

#define  PROTO_TR_CTL_TR_ON_v1      0x1    //USED
#define  PROTO_TR_CTL_TR_OFF_v1      0x2    //USED
#define  TR_CTL_VLOCK_v1      0x3    //USED FOR ALL TR
#define  TR_CTL_VUNLOCK_v1    0x4    //USED FOR ALL TR
#define  TR_CTL_SUNLOCK_v1    0x5        //UNUSED
#define  TR_CTL_SLOCK_v1      0x6        //UNUSED
#define  PROTO_TR_CTL_TR_RST_ERR_v1    0x7    //USED
#define  TR_CTL_VT1ON_v1      0x8
#define  TR_CTL_VT2ON_v1      0x9
#define  PROTO_TR_CTL_TR_LOCK_v1    0xA        //UNUSED
#define  TR_CTL_ANALOG_v1    0xB        //UNUSED
#define  TR_CTL_DIGIT_v1      0xC        //UNUSED
#define  PROTO_TR_CTL_TR_UNLOCK_v1    0xD        //UNUSED



#define kQuerySize        100

#define SNMP_CM1        1
#define SNMP_CM2        2    //cntrl_mode
#define SNMP_CM3        3    //input str
#define SNMP_CM4        4    //out_sync
#define SNMP_CM5        5    //status
#define SNMP_CM6        6    //tr lock
#define SNMP_CM7        7    //tr off on
#define SNMP_CM8        8    //asi12
#define SNMP_CM9        9    //power bounds
#define SNMP_CM10        10    //frw bounds
#define SNMP_CM11        11    //temre bounds
#define SNMP_CM12        12    //loading
#define SNMP_CM13        13    //overmod
#define SNMP_CM14        14    //vtvsig_off on
#define SNMP_CM15        15    //pab turnoff when trm unlock
#define SNMP_CM16        16    //pab lock unlock when trm unlock

#define POWER_PERCENT_H      110
#define POWER_PERCENT_L      90
#define TEMRE_DEGREE_H      80
#define TEMRE_DEGREE_L      0
#define FRW_VALUE_H        100
#define FRW_VALUE_L        60
#define kMinAlivePeriod    30


#define  MAX_INIT_UNLOCK_CNT    3
#define PRINT_POWER_PERIOD    5

// Маски
#define M0  (0x01)
#define mSH0(value) ( (value)& M0)

#define __M1  (0x02)
#define mSH1(value) (( (value)& M1) >> 1)

#define __M2  0x04
#define mSH2(value) ((value)& M2) >> 2
#define M3  0x08
  #define mSH3(value) ((value)& M3) >> 3

#define M4  0x10
  #define mSH4(value) ((value)& M4) >> 4
#define M5  0x20
  #define mSH5(value) ((value)& M5) >> 5
#define M6  0x40
  #define mSH6(value) ((value)& M6) >> 6
#define M7  0x80
  #define mSH7(value) ((value)& M7) >> 7

// form top_header
//defines
#define    PI        3.14159265359

//COM1 predcorrection
#define COM1_BUF_SIZE        3000 // in bytes
#define  COM1_0X0D_DATA_SIZE      300

#define TIME_WAIT_REQUEST      300 // 300 msec

#define BUFSIZE            65536
#define IN_VAL            3
#define  LOG_MEM            400  
#define PAGENUM_STR_LOG        20 // max on page
#define NUM_LOG_PAGES        (LOG_MEM/PAGENUM_STR_LOG)
#define  MAX_NUM_IP          20
#define  MAX_ETHERNET_ADAPTER    100
#define MAX_LOG_FILE_SIZE      1048576*7

#define WMI_GET_NET          1  //net set for current adapter
#define WMI_SET_IP_MASK        2
#define WMI_SET_GATEWAY        3
#define WMI_ENABLE_DHCP        4
#define WMI_SET_DNSORDER      5
#define WMI_SCAN_ADAPTER      6
#define WMI_SET_WINS        7


const int kSNMPTimerEvent_ = 3;
const int kSNMPSendByEventEvent_ = 4;
const int kSNMPStartEvent_ = 5;


static const unsigned char EV_STOP_COM1_THREAD = 0;
static const unsigned char EV_WRITE_DATA = 1;
static const unsigned char EV_READ_DATA = 2;
static const unsigned char EV_READ_DATA_TO_TOPDEAMON = 3;
static const unsigned char EV_TIMER_EVENT = 4;
static const unsigned char EV_SEND_BY_CONTROL_CMD = 5;
static const unsigned char kCentralEventBoundUpdate = 6;

// Связано с SNMP 
const int kGMaxCounterValue = 2;

#endif  // SERVER_SIDE_CODE_TOP_HEADERS_APP_CONSTANTS_H_
