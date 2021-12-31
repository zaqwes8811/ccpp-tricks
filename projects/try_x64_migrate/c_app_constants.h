// Блок информации по всему ПРД
//БИ ПРД (9 байт)               // 10 байт
//БИ ВТВ-1 (33 байт)
//БИ ВТВ-2 (33 байт)
//БИ БУМ-1-600 (44 байт)
//БИ БУМ-2-600 (44 байт)
//БИ БУМ-3-600 (44 байт)
//БИ БУМ-4-600 (44 байт)
//БИ БУМ-5-600 (44 байт)
//БИ БУМ-6-600 (44 байт)
//БИ БУМ-7-600 (44 байт)
//БИ БУМ-8-200 (44 байт)
//БИ БУМ-9-200 (44 байт)
//БИ БКН-1 (6 байт)
//БИ БД-1 (6 байт)

// Notes:
//   GBIM_.. - Global one bit mask


#ifndef APP_PROTOCOL_CONSTANTS_H_
#define APP_PROTOCOL_CONSTANTS_H_

#include <asn1/asn1.h>

// Байт состояния ПРД - 1
#define GBIM_CONTROL_IS_REMOTE      (1<<0)          // Режим управления – местный  – дистанционный  
#define bANTENNA_OFF    (1<<1)          // Нагрузка – антенна  – эквивалент  
#define bDIGITAL_ON     (1<<2)          // Аналоговый режим ПРД - Цифровой режим ПРД
#define bWORK_OK        (1<<3)          // Работа – не норма - Работа – норма    
#define bPVTV_CLOSE     (1<<4)          // ВТВ отперт - ВТВ заперт
#define bUM_CLOSE       (1<<5)          // УМ отперт -  УМ заперт  
#define GBIM_TRANSMITTER_LOCK      (1<<6)          // ПРД отперт - ПРД заперт  
#define GBIM_IS_ON         (1<<7)          // ПРД отключен - ПРД включен

// Байт состояния ПРД - 2
#define GBIM_ETV1_ON        (1<<0)          // Включен ВТВ: ВТВ 1
#define GBIM_ETV2_ON        (1<<1)          // Включен ВТВ: ВТВ 2
#define bPRD_RESERV     (1<<2)          // Включен Основной ПРД - Резервный ПРД
#define bPRD_RDY        (1<<3)          // ПРД не готов к управлению - ПРД готов к управлению  
#define bINPSTREAM_ERR  (1<<6)          // Входной поток– есть - Ошибка входного потока нет
#define bEXTSYNC_ERR    (1<<7)          // Внешняя синхронизация - есть Внешняя синхронизация - НЕТ???

// Байт отказов ПРД 
#define GBIM_GLOBAL_DISREPAIR        (1<<0)          // Неисправность ПРД
#define GBIM_GLOBAL_FAILURE       (1<<1)          // Отказ ПРД
#define bNET_FAIL       (1<<4)          // Отказ СЕТЬ
#define bBALL_FAIL      (1<<5)          // Отказ Балласт
#define bKBV_FAIL       (1<<6)          // Отказ КБВ
#define bCOOL_FAIL      (1<<7)          // Отказ Охлаждения

// Байт отказов устройств ПРД – 1 
#define bBUM1_FAIL      (1<<0)          // Отказ БУМ1
#define bBUM2_FAIL      (1<<1)          // Отказ БУМ2
#define bBUM3_FAIL      (1<<2)          // Отказ БУМ3
#define bBUM4_FAIL      (1<<3)          // Отказ БУМ4
#define bBUM5_FAIL      (1<<4)          // Отказ БУМ5
#define bBUM6_FAIL      (1<<5)          // Отказ БУМ6
#define bBUM7_FAIL      (1<<6)          // Отказ БУМ7
#define bBUM8_FAIL      (1<<7)          // Отказ БУМ8

// Байт отказов устройств ПРД – 2
#define bBUM9_FAIL      (1<<0)          // Отказ БУМ9
#define bBUM10_FAIL     (1<<1)          // Отказ БУМ10
#define bRS485_FAIL     (1<<2)          // Отказ RS485
#define bI2C_FAIL       (1<<3)          // Отказ I2C
#define bVTV1_FAIL      (1<<6)          // Отказ ВТВ1
#define bVTV2_FAIL      (1<<7)          // Отказ ВТВ2

// Байт состояния ВТВ
#define bREMOTE_VTV      (1<<0)         // Режим управления – местный  – дистанционный  
#define bRESERV_VTV      (1<<1)          // Основной ВТВ - Резервный ВТВ
#define bDIGITAL_VTV     (1<<2)         // Аналоговый ВТВ - Цифровой ВТВ
#define bUS_VTV_CLOSE    (1<<3)         // УС ВТВ отперт - УС ВТВ заперт
#define bMOD_CLOSE       (1<<4)         // МОД отперт - МОД заперт
#define bVTV_CLOSE       (1<<5)         // ВТВ отперт - ВТВ заперт
#define bVTV_READY       (1<<6)         // ВТВ не готов - ВТВ заперт
#define bVTV_WORK_OK     (1<<7)         // Работа – не норма - Работа – норма    

// Байт отказов ВТВ Failure VTV
#define bVTV_ERR         (1<<0)         // Неисправность ВТВ
#define bVTV_FAIL        (1<<1)         // Отказ ВТВ
#define bMOD_FAIL        (1<<2)         // Отказ МОД
#define bUS_FAIL         (1<<3)         // Отказ УС
#define bMOD_CLOSED      (1<<4)         // Модулятор реально заперт
#define bMOD_LOADED      (1<<5)         // Модулятор загружен
#define bINP_FAIL        (1<<6)         // Отказ Входной поток
#define bESYNC_FAIL      (1<<7)         // Отказ Внешней синхронизации

#define bNET_MCS        (3<<0)          // Сеть МЧС
#define bNET_OCS        (4<<0)          // Сеть ОЧС
#define bDVBT_OFF       (1<<4)          //  DVB-T отключен
#define bDVBT_ON        (1<<5)          //  DVB-T включен
#define bMIP_OFF        (1<<6)          //  MIP  отключен
#define bMIP_ON         (1<<7)          //  MIP  включен

// Байт состояния ASI1 - ASI2
#define bASI1_MAIN      (1<<0)
#define bASI1_RESERV    (2<<0)
#define bASI2_MAIN      (1<<4)
#define bASI2_RESERV    (2<<4)

//Тип модуляции
#define MOD_QPSK        (1<<4)
#define MOD_QAM16       (2<<4)
#define MOD_QAM64       (3<<4)

// Скорость Кода
#define SPEED_1_2       (1<<4)
#define SPEED_2_3       (2<<4)
#define SPEED_3_4       (3<<4)
#define SPEED_5_6       (4<<4)
#define SPEED_7_8       (5<<4)

// Защитный интервал
#define PTIME_1_4       (1<<4)
#define PTIME_1_8       (2<<4)
#define PTIME_1_16      (3<<4)
#define PTIME_1_32      (4<<4)

// Иерархический режим
#define HIERAR_NONE     (1<<0)
#define HIERAR_H1       (2<<0)
#define HIERAR_H2       (3<<0)
#define HIERAR_H3       (4<<0)

// Число несущих
#define FREQ_COUNT_2K   (1<<0)
#define FREQ_COUNT_4K   (2<<0)
#define FREQ_COUNT_8K   (3<<0)

// Статус Корректора
#define NKORR_OFF       (1<<0)
#define NKORR_ON        (2<<0)
#define LKORR_OFF       (1<<4)
#define LKORR_ON        (2<<4)
/*Нелинейный предкорректор Включен/Отключен
1 – отключен
2 – включен 

Линейный предкорректор Включен/Отключен
1 – отключен
2 – включен*/

// Режим теста
#define TEST_OFF        (1)
#define TEST_TON        (2)
#define TEST_PSP        (3)
#define TEST_PSPA       (4)
#define TEST_SWEEP2     (5)

// Байт состояния БУМ
#define bBUM_ON          (1<<0)         // БУМ выключен - включен
#define bBUM_CLOSE       (1<<1)          // БУМ отперт - заперт
#define bBUM_DIGITAL     (1<<3)         // Аналоговый - Цифровой режим БУМ
#define bBUM_INP_POW_ERR (1<<4)         // Входная мощность не в норме

// Байт отказов БУМ 
#define bBUM_FAIL        (1<<0)         // Отказ БУМ
#define bBUM_OUT_POW_LOW (1<<1)         // Выходная мощность <Рмин
#define bBUM_KBV_FAIL    (1<<2)         // Отказ по КБВ

// --------------------------------------------------------------------------
// Блок информации предварительного усилителя БУМ (БИ УП БУМ)

// Байт отказов УП БУМ 
#define bUP_VT1_FAIL    (1<<0)             // VT 1 – отказ
#define bUP_VT2_FAIL    (1<<1)             // VT 2 – отказ
#define bUP_TEMP_FAIL   (1<<2)             // Температура – отказ
#define bUP_MIP_FAIL    (1<<3)             // МИП – отказ 
#define bUP_ARU_FAIL    (1<<4)             // АРУ – отказ 
#define bUP_15V_FAIL    (1<<5)             // Дежурное +15 – отказ


// --------------------------------------------------------------------------
// Блок информации усилителя мощности БУМ (БИ УМ БУМ).

// Байт отказов УМ БУМ 
#define bUM_VT1_FAIL    (1<<0)             // VT 1 – отказ
#define bUM_VT2_FAIL    (1<<1)             // VT 2 – отказ
#define bUM_TEMP_FAIL   (1<<2)             // Температура – отказ
#define bUM_MIP_FAIL    (1<<3)             // МИП – отказ 

//Блок информации БУМ-10Вт (БИ БУМ-10) – УП (ПРД: моноблок)
//№ п/п  № байта в БИ  Описание (состав)
//1  2  3
//1  0 .. 5  БИ ОПАР БУМ
//2  6 .. 15  БИ УП БУМ

//Блок информации БУМ-100Вт (БИ БУМ-100) – УП и УМ (ПРД: моноблок).
//№ п/п  № байта в БИ  Описание (состав)
//1  2  3
//1  0 .. 5  БИ ОПАР БУМ
//2  6 .. 15  БИ УП БУМ
//3  16 .. 22  БИ УМ БУМ
    
//    Блок информации БУМ-200Вт (БИ БУМ-200) – УП и 2 УМ (ПРД:ВТВ и БУМ 4U или ПРД: многоблочный).
//№ п/п  № байта в БИ  Описание (состав)
//1  2  3
//1  0 .. 5  БИ ОПАР БУМ
//2  6 .. 15  БИ УП БУМ
//3  16 .. 22  БИ УМ1 БУМ
//4  23 .. 29  БИ УМ 2БУМ

    
//Блок информации БУМ 600Вт (БИ БУМ-600) – УП и 4 УМ (ПРД:ВТВ и БУМ 3U или ПРД: многоблочный).
//№ п/п  № байта в БИ  Описание (состав)
//1  2  3
//1  0 .. 5  БИ ОПАР БУМ
//2  6 .. 15  БИ УП БУМ
//3  16 .. 22  БИ УМ1 БУМ
//4  23 .. 29  БИ УМ 2БУМ
//5  30 .. 36  БИ УМ3 БУМ
//6  37 .. 43  БИ УМ 4БУМ
    
// Байт состояния БКН
#define bBKN_PRD_ON             (1<<0)         // ПРД выключен - включен
#define bBKN_PRD_CLOSE          (1<<1)         // ПРД отперт - заперт
#define bBKN_FAIL               (1<<3)         // БКН отказ
#define bBKN_DIGITAL            (1<<4)         // Аналоговый - Цифровой режим 
#define bBKN_LOW_POW            (1<<6)         // Мощность снижена

// Состояние отказов БКН
#define bRB_1_FAIL              (1<<0)          // Rб 1  отказ
#define bRB_2_FAIL              (1<<1)          // Rб 2  отказ
#define bT_RB_1_FAIL            (1<<2)          // T Rб 1  отказ
#define bT_RB_2_FAIL            (1<<3)          // T Rб 2  отказ
#define bT_RB_3_FAIL            (1<<4)          // T Rб 3  отказ
#define bT_RB_4_FAIL            (1<<5)          // T Rб 4  отказ
#define bRB_3_FAIL              (1<<6)          // Rб 3  отказ
#define bRB_4_FAIL              (1<<7)          // Rб 4  отказ

// Состояние отказов БКН 2
#define bRB_5_FAIL              (1<<0)          // Rб 5  отказ
#define bRB_6_FAIL              (1<<1)          // Rб 6  отказ
#define bT_RB_5_FAIL            (1<<2)          // T Rб 5  отказ
#define bT_RB_6_FAIL            (1<<3)          // T Rб 6  отказ
#define bT_RB_7_FAIL            (1<<4)          // T Rб 7  отказ
#define bT_RB_8_FAIL            (1<<5)          // T Rб 8  отказ
#define bRB_7_FAIL              (1<<6)          // Rб 7  отказ
#define bRB_8_FAIL              (1<<7)          // Rб 8  отказ

// Байт состояния БД
#define bBD_PRD_ON             (1<<0)         // ПРД выключен - включен
#define bBD_PRD_CLOSE          (1<<1)         // ПРД отперт - заперт
#define bBD_FAIL               (1<<3)         // БКН отказ
#define bBD_DIGITAL            (1<<4)         // Аналоговый - Цифровой режим 
#define bBD_KAN_FAIL           (1<<6)         // Канал ?отказ
#define bBD_MUL_10             (1<<7)         // Множитель х10

// Байт состояния БР
#define bBR_CONTROL            (1<<0)         // Есть управление БР
#define bBR_PRD_1_ON           (1<<1)        // Скоммутирован ПРД1
#define bBR_PRD_2_ON           (1<<2)         // Скоммутирован ПРД2
#define bBR_RDY                (1<<4)         // БР готов

#define bBR_CONTROL_PRD1       (1<<6)         // Есть управление ПРД1
#define bBR_CONTROL_PRD2       (1<<7)         // Есть управление ПРД2
 

// Байт состояния 2 (отказов) БР
#define bBR_RELE_FAIL          (1<<0)         // Есть управление БР
#define bBR_LIN_PRD1_FAIL      (1<<1)        // Скоммутирован ПРД1
#define bBR_LIN_PRD2_FAIL      (1<<2)         // Скоммутирован ПРД2


#define trapAlive       (0x10<<24)
#define trapMessage     (0x20<<24)
#define trapWarning     (0x30<<24)
#define trapFailure     (0x40<<24)
#define trapParValue    (0x50<<24)
#define TRAP_SIMPLY_MSG  (0x60<<24)

#define GBIV_GLOBAL_WARNING    (1<<0)
#define GBIV_GLOBAL_FAILURE    (1<<1)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@OwnIDs
// Так и приходит
#define GID_MART_NEVA_AIR_10W (13)
#define GID_MART_NEVA_AIR_100W (14)
#define GID_MART_NEVA_AIR_200W (15)
#define GID_MART_NEVA_AIR_500W (16)

///@IDsAAT
#ifdef FEATURE_AAT_CONFIGURATION
//@HighPower
//@InActive
//#define GID_AAT_LIQ_CBV1_5KW (0)  // = 5000 W (б/у v1, жидк.охл)
//#define GID_AAT_LIQ_CBV1_2KW (1)  // = 2000 W (б/у v1, жидк.охл)
// 2 = 1000 W (б/у v1, жидк.охл)

//@LowPower
//@InActive
//#define GID_AAT_LIQ_NOCB_500W (5)  // = 500 W (без б/у, жидк.охл)

//@LowPower
//@Active
#define GID_AAT_AIR_NOCB_10W (6)  // 6 = 10 W (без б/у, возд.охл)
#define GID_AAT_AIR_NOCB_250W (7)  // = 250 W (без б/у, возд.охл)
#define GID_AAT_AIR_NOCB_100W (8)// 8 = 100 W (без б/у, возд.охл)
//@InActive
//#define GID_AAT_AIR_NOCB_50W // 11 = 50 W (без б/у, возд.охл)
//@Active
#define GID_AAT_AIR_CB2_500W (501)  // = 500 W (б/у v2, возд.охл)

//@HighPower
//@InActive
// 1000 = 1000 W (б/у v2, жидк.охл)
// 2000 = 2000 W (б/у v2, жидк.охл)
// 5000 = 5000 W (б/у v2, жидк.охл)

#endif  // FEATURE_AAT_CONFIGURATION

///@SNMP
//@SNMPGetGetNext
#define GCODE_IS_MAIN_MOD (10)
#define GCODE_IS_RESERVED_MOD (11)

#define GCODE_VSWR_NORMAL (1)
#define GCODE_VSWR_FAILURE (7)

/// Other

#ifdef __cplusplus
}
#endif // __cplusplus

/*
    // settings
    unsigned int dist_port = 163;
    unsigned char community[] = "private";//"public";
    unsigned int size_community = 7;//6;

    message.originatorAddress.sin_family = AF_INET;
    message.originatorAddress.sin_port = htons(dist_port);
    message.originatorAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    message.originatorAddressLength = sizeof message.originatorAddress;
    message.mesg.version = SNMP_VERSION_2C;
    memcpy(message.mesg.access_info.community_based.string, community, size_community);
    message.mesg.access_info.community_based.length = size_community;
    message.mesg.request_id = 42;
*/


#endif  // APP_PROTOCOL_CONSTANTS_H_
