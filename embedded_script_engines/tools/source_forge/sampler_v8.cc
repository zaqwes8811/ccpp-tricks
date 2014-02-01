#include "sampler_v8.h"
#include "process.h"

using v8::String;
using v8::ObjectTemplate;
using v8::Object;
using v8::HandleScope;
using v8::Handle;
using v8::Local;
using v8::Value;
using v8::External;
using v8::Isolate;
using v8::Number;
using v8::Undefined;

namespace tmitter_web_service {
v8::Handle<v8::ObjectTemplate> InMemoryStorageImplV8::CreateOwnBlueprint(
      v8::Isolate* isolate) 
  {
  HandleScope handle_scope(isolate);

  Handle<ObjectTemplate> result = ObjectTemplate::New();
  result->SetInternalFieldCount(1);
  result->SetAccessor(
      String::New("printPABLock_"), 
      ZLGetter_printPABLock_);
  result->SetAccessor(
      String::New("printPABLockEvent_"), 
      ZLGetter_printPABLockEvent_);
  result->SetAccessor(
      String::New("printPABNoInPower_"), 
      ZLGetter_printPABNoInPower_);
  result->SetAccessor(
      String::New("printPABNoInPowerEvent_"), 
      ZLGetter_printPABNoInPowerEvent_);
  result->SetAccessor(
      String::New("printPABUnlock_"), 
      ZLGetter_printPABUnlock_);
  result->SetAccessor(
      String::New("printPABInPowerOk_"), 
      ZLGetter_printPABInPowerOk_);
  result->SetAccessor(
      String::New("snmpEventsQuery_"), 
      ZLGetter_snmpEventsQuery_);
  result->SetAccessor(
      String::New("typesCodesInQuery_"), 
      ZLGetter_typesCodesInQuery_);
  result->SetAccessor(
      String::New("typeMsgsQuery_"), 
      ZLGetter_typeMsgsQuery_);
  result->SetAccessor(
      String::New("vtvSigOnOffTgrD_"), 
      ZLGetter_vtvSigOnOffTgrD_);
  result->SetAccessor(
      String::New("vtvSigOnOffTgrQ_"), 
      ZLGetter_vtvSigOnOffTgrQ_);
  result->SetAccessor(
      String::New("vtvOverModTgrD_"), 
      ZLGetter_vtvOverModTgrD_);
  result->SetAccessor(
      String::New("vtvOverModTgrQ_"), 
      ZLGetter_vtvOverModTgrQ_);
  result->SetAccessor(
      String::New("ibVtvModStatus"), 
      ZLGetter_ibVtvModStatus);
  result->SetAccessor(
      String::New("ibVtvUsStatus"), 
      ZLGetter_ibVtvUsStatus);
  result->SetAccessor(
      String::New("ibPABOutPowerStatus"), 
      ZLGetter_ibPABOutPowerStatus);
  result->SetAccessor(
      String::New("ibPreVT12status"), 
      ZLGetter_ibPreVT12status);
  result->SetAccessor(
      String::New("ibPreTemStaus"), 
      ZLGetter_ibPreTemStaus);
  result->SetAccessor(
      String::New("ibPreMIP"), 
      ZLGetter_ibPreMIP);
  result->SetAccessor(
      String::New("ibBCVstatus"), 
      ZLGetter_ibBCVstatus);
  result->SetAccessor(
      String::New("bcl_R1"), 
      ZLGetter_bcl_R1);
  result->SetAccessor(
      String::New("bcl_TR1"), 
      ZLGetter_bcl_TR1);
  result->SetAccessor(
      String::New("bcl_R2"), 
      ZLGetter_bcl_R2);
  result->SetAccessor(
      String::New("bcl_TR2"), 
      ZLGetter_bcl_TR2);
  result->SetAccessor(
      String::New("bcl_R3"), 
      ZLGetter_bcl_R3);
  result->SetAccessor(
      String::New("bcl_TR3"), 
      ZLGetter_bcl_TR3);
  result->SetAccessor(
      String::New("bcl_R4"), 
      ZLGetter_bcl_R4);
  result->SetAccessor(
      String::New("bcl_TR4"), 
      ZLGetter_bcl_TR4);
  result->SetAccessor(
      String::New("bcl_R5"), 
      ZLGetter_bcl_R5);
  result->SetAccessor(
      String::New("bcl_TR5"), 
      ZLGetter_bcl_TR5);
  result->SetAccessor(
      String::New("bcl_R6"), 
      ZLGetter_bcl_R6);
  result->SetAccessor(
      String::New("bcl_TR6"), 
      ZLGetter_bcl_TR6);
  result->SetAccessor(
      String::New("bcl_R7"), 
      ZLGetter_bcl_R7);
  result->SetAccessor(
      String::New("bcl_TR7"), 
      ZLGetter_bcl_TR7);
  result->SetAccessor(
      String::New("bcl_R8"), 
      ZLGetter_bcl_R8);
  result->SetAccessor(
      String::New("bcl_TR8"), 
      ZLGetter_bcl_TR8);
  result->SetAccessor(
      String::New("ibBDstatus"), 
      ZLGetter_ibBDstatus);
  result->SetAccessor(
      String::New("uiPort"), 
      ZLGetter_uiPort);
  result->SetAccessor(
      String::New("cExt"), 
      ZLGetter_cExt);
  result->SetAccessor(
      String::New("ibVtvCntrlMode"), 
      ZLGetter_ibVtvCntrlMode);
  result->SetAccessor(
      String::New("ibVtvRadioMode"), 
      ZLGetter_ibVtvRadioMode);
  result->SetAccessor(
      String::New("etv_digital_"), 
      ZLGetter_etv_digital_);
  result->SetAccessor(
      String::New("ibUsVtvLock"), 
      ZLGetter_ibUsVtvLock);
  result->SetAccessor(
      String::New("ibModVtvLock"), 
      ZLGetter_ibModVtvLock);
  result->SetAccessor(
      String::New("ibOwnVtvLock"), 
      ZLGetter_ibOwnVtvLock);
  result->SetAccessor(
      String::New("ibVtvReady"), 
      ZLGetter_ibVtvReady);
  result->SetAccessor(
      String::New("ibVtvWork"), 
      ZLGetter_ibVtvWork);
  result->SetAccessor(
      String::New("ibVtvStatus"), 
      ZLGetter_ibVtvStatus);
  result->SetAccessor(
      String::New("exciterIstream_"), 
      ZLGetter_exciterIstream_);
  result->SetAccessor(
      String::New("connection_state_etv"), 
      ZLGetter_connection_state_etv);
  result->SetAccessor(
      String::New("ibVtvOutSync"), 
      ZLGetter_ibVtvOutSync);
  result->SetAccessor(
      String::New("exciterIstreamError_"), 
      ZLGetter_exciterIstreamError_);
  result->SetAccessor(
      String::New("ibVtvErrMod"), 
      ZLGetter_ibVtvErrMod);
  result->SetAccessor(
      String::New("ibVtvOutPower"), 
      ZLGetter_ibVtvOutPower);
  result->SetAccessor(
      String::New("iVtvOutPower"), 
      ZLGetter_iVtvOutPower);
  result->SetAccessor(
      String::New("ibVtvSKSStatus"), 
      ZLGetter_ibVtvSKSStatus);
  result->SetAccessor(
      String::New("ibVtvSChMStatus"), 
      ZLGetter_ibVtvSChMStatus);
  result->SetAccessor(
      String::New("ibVtvSPChStatus"), 
      ZLGetter_ibVtvSPChStatus);
  result->SetAccessor(
      String::New("ibVtvVideoLock"), 
      ZLGetter_ibVtvVideoLock);
  result->SetAccessor(
      String::New("ibVtvPowerStatus"), 
      ZLGetter_ibVtvPowerStatus);
  result->SetAccessor(
      String::New("ibVtvSound"), 
      ZLGetter_ibVtvSound);
  result->SetAccessor(
      String::New("ibVtvChanNumAnalog"), 
      ZLGetter_ibVtvChanNumAnalog);
  result->SetAccessor(
      String::New("iVtvChanNumAnalog"), 
      ZLGetter_iVtvChanNumAnalog);
  result->SetAccessor(
      String::New("exciterASI12TgrVar_"), 
      ZLGetter_exciterASI12TgrVar_);
  result->SetAccessor(
      String::New("ibVtvNet"), 
      ZLGetter_ibVtvNet);
  result->SetAccessor(
      String::New("ibVtvDVBTOnOf"), 
      ZLGetter_ibVtvDVBTOnOf);
  result->SetAccessor(
      String::New("ibVtvMIPOnOf"), 
      ZLGetter_ibVtvMIPOnOf);
  result->SetAccessor(
      String::New("ibVtvQAM"), 
      ZLGetter_ibVtvQAM);
  result->SetAccessor(
      String::New("ibVtvCodRate"), 
      ZLGetter_ibVtvCodRate);
  result->SetAccessor(
      String::New("ibVtvGI"), 
      ZLGetter_ibVtvGI);
  result->SetAccessor(
      String::New("ibVtvHierar"), 
      ZLGetter_ibVtvHierar);
  result->SetAccessor(
      String::New("ibVtvCarNum"), 
      ZLGetter_ibVtvCarNum);
  result->SetAccessor(
      String::New("ibVtvChannel"), 
      ZLGetter_ibVtvChannel);
  result->SetAccessor(
      String::New("iVtvChannel"), 
      ZLGetter_iVtvChannel);
  result->SetAccessor(
      String::New("iVtvFreq"), 
      ZLGetter_iVtvFreq);
  result->SetAccessor(
      String::New("ibVtvOutLevel"), 
      ZLGetter_ibVtvOutLevel);
  result->SetAccessor(
      String::New("iVtvOutLevel"), 
      ZLGetter_iVtvOutLevel);
  result->SetAccessor(
      String::New("ibVtvTransmNum"), 
      ZLGetter_ibVtvTransmNum);
  result->SetAccessor(
      String::New("iVtvTransmNum"), 
      ZLGetter_iVtvTransmNum);
  result->SetAccessor(
      String::New("ibVtvIDCellNum"), 
      ZLGetter_ibVtvIDCellNum);
  result->SetAccessor(
      String::New("iVtvIDCellNum"), 
      ZLGetter_iVtvIDCellNum);
  result->SetAccessor(
      String::New("ibVtvAdDelay"), 
      ZLGetter_ibVtvAdDelay);
  result->SetAccessor(
      String::New("iVtvAdDelay"), 
      ZLGetter_iVtvAdDelay);
  result->SetAccessor(
      String::New("ibVtvPrecLineNum"), 
      ZLGetter_ibVtvPrecLineNum);
  result->SetAccessor(
      String::New("iVtvPrecLineNum"), 
      ZLGetter_iVtvPrecLineNum);
  result->SetAccessor(
      String::New("ibVtvPrecLOnOff"), 
      ZLGetter_ibVtvPrecLOnOff);
  result->SetAccessor(
      String::New("ibVtvPrecNonLOnOff"), 
      ZLGetter_ibVtvPrecNonLOnOff);
  result->SetAccessor(
      String::New("ibVtvTestMode"), 
      ZLGetter_ibVtvTestMode);
  result->SetAccessor(
      String::New("ibVTVNoconnet"), 
      ZLGetter_ibVTVNoconnet);
  result->SetAccessor(
      String::New("PABOnOffTgrVar_"), 
      ZLGetter_PABOnOffTgrVar_);
  result->SetAccessor(
      String::New("PABLockTgrVar_"), 
      ZLGetter_PABLockTgrVar_);
  result->SetAccessor(
      String::New("pab_connection_state_"), 
      ZLGetter_pab_connection_state_);
  result->SetAccessor(
      String::New("ibPABAnlgDigit"), 
      ZLGetter_ibPABAnlgDigit);
  result->SetAccessor(
      String::New("ibPABInPowerStatus"), 
      ZLGetter_ibPABInPowerStatus);
  result->SetAccessor(
      String::New("ibPABStatus"), 
      ZLGetter_ibPABStatus);
  result->SetAccessor(
      String::New("ibPABFRWStatus"), 
      ZLGetter_ibPABFRWStatus);
  result->SetAccessor(
      String::New("ibPABInPow"), 
      ZLGetter_ibPABInPow);
  result->SetAccessor(
      String::New("iPABInPow"), 
      ZLGetter_iPABInPow);
  result->SetAccessor(
      String::New("ibPABOutPow"), 
      ZLGetter_ibPABOutPow);
  result->SetAccessor(
      String::New("iPABOutPow"), 
      ZLGetter_iPABOutPow);
  result->SetAccessor(
      String::New("ibPABFRW"), 
      ZLGetter_ibPABFRW);
  result->SetAccessor(
      String::New("iPABFRW"), 
      ZLGetter_iPABFRW);
  result->SetAccessor(
      String::New("ibPreAGC"), 
      ZLGetter_ibPreAGC);
  result->SetAccessor(
      String::New("ibPrePlus15"), 
      ZLGetter_ibPrePlus15);
  result->SetAccessor(
      String::New("ibPreCurVT1"), 
      ZLGetter_ibPreCurVT1);
  result->SetAccessor(
      String::New("iPreCurVT1"), 
      ZLGetter_iPreCurVT1);
  result->SetAccessor(
      String::New("ibPreCurVT2"), 
      ZLGetter_ibPreCurVT2);
  result->SetAccessor(
      String::New("iPreCurVT2"), 
      ZLGetter_iPreCurVT2);
  result->SetAccessor(
      String::New("ibPreTemValue"), 
      ZLGetter_ibPreTemValue);
  result->SetAccessor(
      String::New("iPreTemValue"), 
      ZLGetter_iPreTemValue);
  result->SetAccessor(
      String::New("ibPreMIPVoltage"), 
      ZLGetter_ibPreMIPVoltage);
  result->SetAccessor(
      String::New("iPreMIPVoltage"), 
      ZLGetter_iPreMIPVoltage);
  result->SetAccessor(
      String::New("ibPreAttenVoltage"), 
      ZLGetter_ibPreAttenVoltage);
  result->SetAccessor(
      String::New("iPreAttenVoltage"), 
      ZLGetter_iPreAttenVoltage);
  result->SetAccessor(
      String::New("ibPrePhaseVoltage"), 
      ZLGetter_ibPrePhaseVoltage);
  result->SetAccessor(
      String::New("iPreAPhaseVoltage"), 
      ZLGetter_iPreAPhaseVoltage);
  result->SetAccessor(
      String::New("ibPreReferVoltage"), 
      ZLGetter_ibPreReferVoltage);
  result->SetAccessor(
      String::New("iPreReferVoltage"), 
      ZLGetter_iPreReferVoltage);
  result->SetAccessor(
      String::New("sum_bcl_"), 
      ZLGetter_sum_bcl_);
  result->SetAccessor(
      String::New("ibBCVTrOnOf"), 
      ZLGetter_ibBCVTrOnOf);
  result->SetAccessor(
      String::New("ibBCVTrLock"), 
      ZLGetter_ibBCVTrLock);
  result->SetAccessor(
      String::New("bcl_a_or_d_WTF"), 
      ZLGetter_bcl_a_or_d_WTF);
  result->SetAccessor(
      String::New("ibBCVPowerStat"), 
      ZLGetter_ibBCVPowerStat);
  result->SetAccessor(
      String::New("iBCV_R1PowTemp"), 
      ZLGetter_iBCV_R1PowTemp);
  result->SetAccessor(
      String::New("iBCV_R2PowTemp"), 
      ZLGetter_iBCV_R2PowTemp);
  result->SetAccessor(
      String::New("iBCV_R3PowTemp"), 
      ZLGetter_iBCV_R3PowTemp);
  result->SetAccessor(
      String::New("iBCV_R4PowTemp"), 
      ZLGetter_iBCV_R4PowTemp);
  result->SetAccessor(
      String::New("iBCV_R5PowTemp"), 
      ZLGetter_iBCV_R5PowTemp);
  result->SetAccessor(
      String::New("iBCV_R6PowTemp"), 
      ZLGetter_iBCV_R6PowTemp);
  result->SetAccessor(
      String::New("iBCV_R7PowTemp"), 
      ZLGetter_iBCV_R7PowTemp);
  result->SetAccessor(
      String::New("iBCV_R8PowTemp"), 
      ZLGetter_iBCV_R8PowTemp);
  result->SetAccessor(
      String::New("iBCV_R1Tem"), 
      ZLGetter_iBCV_R1Tem);
  result->SetAccessor(
      String::New("iBCV_R1Pow"), 
      ZLGetter_iBCV_R1Pow);
  result->SetAccessor(
      String::New("iBCV_R2Tem"), 
      ZLGetter_iBCV_R2Tem);
  result->SetAccessor(
      String::New("iBCV_R2Pow"), 
      ZLGetter_iBCV_R2Pow);
  result->SetAccessor(
      String::New("iBCV_R3Tem"), 
      ZLGetter_iBCV_R3Tem);
  result->SetAccessor(
      String::New("iBCV_R3Pow"), 
      ZLGetter_iBCV_R3Pow);
  result->SetAccessor(
      String::New("iBCV_R4Tem"), 
      ZLGetter_iBCV_R4Tem);
  result->SetAccessor(
      String::New("iBCV_R4Pow"), 
      ZLGetter_iBCV_R4Pow);
  result->SetAccessor(
      String::New("iBCV_R5Tem"), 
      ZLGetter_iBCV_R5Tem);
  result->SetAccessor(
      String::New("iBCV_R5Pow"), 
      ZLGetter_iBCV_R5Pow);
  result->SetAccessor(
      String::New("iBCV_R6Tem"), 
      ZLGetter_iBCV_R6Tem);
  result->SetAccessor(
      String::New("iBCV_R6Pow"), 
      ZLGetter_iBCV_R6Pow);
  result->SetAccessor(
      String::New("iBCV_R7Tem"), 
      ZLGetter_iBCV_R7Tem);
  result->SetAccessor(
      String::New("iBCV_R7Pow"), 
      ZLGetter_iBCV_R7Pow);
  result->SetAccessor(
      String::New("iBCV_R8Tem"), 
      ZLGetter_iBCV_R8Tem);
  result->SetAccessor(
      String::New("iBCV_R8Pow"), 
      ZLGetter_iBCV_R8Pow);
  result->SetAccessor(
      String::New("sum_about_db_"), 
      ZLGetter_sum_about_db_);
  result->SetAccessor(
      String::New("ibBDTrOnOf"), 
      ZLGetter_ibBDTrOnOf);
  result->SetAccessor(
      String::New("ibBDTrLock"), 
      ZLGetter_ibBDTrLock);
  result->SetAccessor(
      String::New("ibBDAnlgDigit"), 
      ZLGetter_ibBDAnlgDigit);
  result->SetAccessor(
      String::New("ibBDChannel"), 
      ZLGetter_ibBDChannel);
  result->SetAccessor(
      String::New("ibBDFactor"), 
      ZLGetter_ibBDFactor);
  result->SetAccessor(
      String::New("sound_power_"), 
      ZLGetter_sound_power_);
  result->SetAccessor(
      String::New("sound_power_Temp"), 
      ZLGetter_sound_power_Temp);
  result->SetAccessor(
      String::New("iBDOutPowerTemp"), 
      ZLGetter_iBDOutPowerTemp);
  result->SetAccessor(
      String::New("iBDOutPower"), 
      ZLGetter_iBDOutPower);
  result->SetAccessor(
      String::New("iBDFRW"), 
      ZLGetter_iBDFRW);
  result->SetAccessor(
      String::New("lengthAllParams___"),
      V8ScalarGetter_lengthAllParams___, 
      V8ScalarSetter_lengthAllParams___);
  result->SetAccessor(
      String::New("counterDebug___"),
      V8ScalarGetter_counterDebug___, 
      V8ScalarSetter_counterDebug___);
  result->SetAccessor(
      String::New("typeControl_"),
      V8ScalarGetter_typeControl_, 
      V8ScalarSetter_typeControl_);
  result->SetAccessor(
      String::New("failsReseted_"),
      V8ScalarGetter_failsReseted_, 
      V8ScalarSetter_failsReseted_);
  result->SetAccessor(
      String::New("currentQueryIndex_"),
      V8ScalarGetter_currentQueryIndex_, 
      V8ScalarSetter_currentQueryIndex_);
  result->SetAccessor(
      String::New("powerOkTTgr_"),
      V8ScalarGetter_powerOkTTgr_, 
      V8ScalarSetter_powerOkTTgr_);
  result->SetAccessor(
      String::New("needPrintFullPower_"),
      V8ScalarGetter_needPrintFullPower_, 
      V8ScalarSetter_needPrintFullPower_);
  result->SetAccessor(
      String::New("needPrintOkPower_"),
      V8ScalarGetter_needPrintOkPower_, 
      V8ScalarSetter_needPrintOkPower_);
  result->SetAccessor(
      String::New("FRWOkTTgr_"),
      V8ScalarGetter_FRWOkTTgr_, 
      V8ScalarSetter_FRWOkTTgr_);
  result->SetAccessor(
      String::New("needPrintFullFRW_"),
      V8ScalarGetter_needPrintFullFRW_, 
      V8ScalarSetter_needPrintFullFRW_);
  result->SetAccessor(
      String::New("needPrintOkFRW_"),
      V8ScalarGetter_needPrintOkFRW_, 
      V8ScalarSetter_needPrintOkFRW_);
  result->SetAccessor(
      String::New("ctrlModeTgrVar_"),
      V8ScalarGetter_ctrlModeTgrVar_, 
      V8ScalarSetter_ctrlModeTgrVar_);
  result->SetAccessor(
      String::New("typeLoadTgrVar_"),
      V8ScalarGetter_typeLoadTgrVar_, 
      V8ScalarSetter_typeLoadTgrVar_);
  result->SetAccessor(
      String::New("tmitterLockTgrVar___"),
      V8ScalarGetter_tmitterLockTgrVar___, 
      V8ScalarSetter_tmitterLockTgrVar___);
  result->SetAccessor(
      String::New("tmitterOnTgrVar___"),
      V8ScalarGetter_tmitterOnTgrVar___, 
      V8ScalarSetter_tmitterOnTgrVar___);
  result->SetAccessor(
      String::New("powHalfModeTgrVar_"),
      V8ScalarGetter_powHalfModeTgrVar_, 
      V8ScalarSetter_powHalfModeTgrVar_);
  result->SetAccessor(
      String::New("istreamTgrVar_"),
      V8ScalarGetter_istreamTgrVar_, 
      V8ScalarSetter_istreamTgrVar_);
  result->SetAccessor(
      String::New("outSynTgrVar_"),
      V8ScalarGetter_outSynTgrVar_, 
      V8ScalarSetter_outSynTgrVar_);
  result->SetAccessor(
      String::New("statusTmitterTgrVar_"),
      V8ScalarGetter_statusTmitterTgrVar_, 
      V8ScalarSetter_statusTmitterTgrVar_);
  result->SetAccessor(
      String::New("type_tm_digital_"),
      V8ScalarGetter_type_tm_digital_, 
      V8ScalarSetter_type_tm_digital_);
  result->SetAccessor(
      String::New("ibWork_"),
      V8ScalarGetter_ibWork_, 
      V8ScalarSetter_ibWork_);
  result->SetAccessor(
      String::New("exciterLock_"),
      V8ScalarGetter_exciterLock_, 
      V8ScalarSetter_exciterLock_);
  result->SetAccessor(
      String::New("ibPowAmpLock_"),
      V8ScalarGetter_ibPowAmpLock_, 
      V8ScalarSetter_ibPowAmpLock_);
  result->SetAccessor(
      String::New("idx_oned_etv_"),
      V8ScalarGetter_idx_oned_etv_, 
      V8ScalarSetter_idx_oned_etv_);
  result->SetAccessor(
      String::New("idx_oned_etv_q_"),
      V8ScalarGetter_idx_oned_etv_q_, 
      V8ScalarSetter_idx_oned_etv_q_);
  result->SetAccessor(
      String::New("ibRadioMode_"),
      V8ScalarGetter_ibRadioMode_, 
      V8ScalarSetter_ibRadioMode_);
  result->SetAccessor(
      String::New("transmitterReady_"),
      V8ScalarGetter_transmitterReady_, 
      V8ScalarSetter_transmitterReady_);
  result->SetAccessor(
      String::New("failNet_"),
      V8ScalarGetter_failNet_, 
      V8ScalarSetter_failNet_);
  result->SetAccessor(
      String::New("failBallast_"),
      V8ScalarGetter_failBallast_, 
      V8ScalarSetter_failBallast_);
  result->SetAccessor(
      String::New("failFRW_"),
      V8ScalarGetter_failFRW_, 
      V8ScalarSetter_failFRW_);
  result->SetAccessor(
      String::New("failCoolling_"),
      V8ScalarGetter_failCoolling_, 
      V8ScalarSetter_failCoolling_);
  result->SetAccessor(
      String::New("ibPAB"),
      V8ScalarGetter_ibPAB, 
      V8ScalarSetter_ibPAB);
  result->SetAccessor(
      String::New("ibVtv"),
      V8ScalarGetter_ibVtv, 
      V8ScalarSetter_ibVtv);
  result->SetAccessor(
      String::New("failsTotalD_"),
      V8ScalarGetter_failsTotalD_, 
      V8ScalarSetter_failsTotalD_);
  result->SetAccessor(
      String::New("failsTotalQ_"),
      V8ScalarGetter_failsTotalQ_, 
      V8ScalarSetter_failsTotalQ_);
  result->SetAccessor(
      String::New("failsTotalQQ_"),
      V8ScalarGetter_failsTotalQQ_, 
      V8ScalarSetter_failsTotalQQ_);
  result->SetAccessor(
      String::New("ibRS485"),
      V8ScalarGetter_ibRS485, 
      V8ScalarSetter_ibRS485);
  result->SetAccessor(
      String::New("ibI2C"),
      V8ScalarGetter_ibI2C, 
      V8ScalarSetter_ibI2C);
  result->SetAccessor(
      String::New("channalValuePacked_"),
      V8ScalarGetter_channalValuePacked_, 
      V8ScalarSetter_channalValuePacked_);
  result->SetAccessor(
      String::New("iChannel"),
      V8ScalarGetter_iChannel, 
      V8ScalarSetter_iChannel);
  result->SetAccessor(
      String::New("iChannelSetup"),
      V8ScalarGetter_iChannelSetup, 
      V8ScalarSetter_iChannelSetup);
  result->SetAccessor(
      String::New("ibPower"),
      V8ScalarGetter_ibPower, 
      V8ScalarSetter_ibPower);
  result->SetAccessor(
      String::New("realPowerRepresent___"),
      V8ScalarGetter_realPowerRepresent___, 
      V8ScalarSetter_realPowerRepresent___);
  result->SetAccessor(
      String::New("ibValueFRW"),
      V8ScalarGetter_ibValueFRW, 
      V8ScalarSetter_ibValueFRW);
  result->SetAccessor(
      String::New("FRWValue___"),
      V8ScalarGetter_FRWValue___, 
      V8ScalarSetter_FRWValue___);
  result->SetAccessor(
      String::New("ibSoundLock"),
      V8ScalarGetter_ibSoundLock, 
      V8ScalarSetter_ibSoundLock);
  result->SetAccessor(
      String::New("ibSU2St"),
      V8ScalarGetter_ibSU2St, 
      V8ScalarSetter_ibSU2St);
  result->SetAccessor(
      String::New("failBallast_Power"),
      V8ScalarGetter_failBallast_Power, 
      V8ScalarSetter_failBallast_Power);
  result->SetAccessor(
      String::New("iBallastPower"),
      V8ScalarGetter_iBallastPower, 
      V8ScalarSetter_iBallastPower);
  result->SetAccessor(
      String::New("transmitterAddress___"),
      V8ScalarGetter_transmitterAddress___, 
      V8ScalarSetter_transmitterAddress___);
  result->SetAccessor(
      String::New("iMaxTemre"),
      V8ScalarGetter_iMaxTemre, 
      V8ScalarSetter_iMaxTemre);
  result->SetAccessor(
      String::New("iMaxStatus"),
      V8ScalarGetter_iMaxStatus, 
      V8ScalarSetter_iMaxStatus);
  result->SetAccessor(
      String::New("new_max_temperature_"),
      V8ScalarGetter_new_max_temperature_, 
      V8ScalarSetter_new_max_temperature_);
  result->SetAccessor(
      String::New("iNewMaxStatus"),
      V8ScalarGetter_iNewMaxStatus, 
      V8ScalarSetter_iNewMaxStatus);
  result->SetAccessor(
      String::New("connecton_state___"),
      V8ScalarGetter_connecton_state___, 
      V8ScalarSetter_connecton_state___);
  result->SetAccessor(
      String::New("snmp_connecton_status___"),
      V8ScalarGetter_snmp_connecton_status___, 
      V8ScalarSetter_snmp_connecton_status___);
  result->SetAccessor(
      String::New("transmitter_number_to_set_"),
      V8ScalarGetter_transmitter_number_to_set_, 
      V8ScalarSetter_transmitter_number_to_set_);
  result->SetAccessor(
      String::New("fixedAlrmRecordIndex_"),
      V8ScalarGetter_fixedAlrmRecordIndex_, 
      V8ScalarSetter_fixedAlrmRecordIndex_);
  result->SetAccessor(
      String::New("hasMsgForSnmp_"),
      V8ScalarGetter_hasMsgForSnmp_, 
      V8ScalarSetter_hasMsgForSnmp_);
  result->SetAccessor(
      String::New("statusRecordIndex_"),
      V8ScalarGetter_statusRecordIndex_, 
      V8ScalarSetter_statusRecordIndex_);
  result->SetAccessor(
      String::New("newFailOccure_"),
      V8ScalarGetter_newFailOccure_, 
      V8ScalarSetter_newFailOccure_);
  result->SetAccessor(
      String::New("currentMWFCode_"),
      V8ScalarGetter_currentMWFCode_, 
      V8ScalarSetter_currentMWFCode_);
  result->SetAccessor(
      String::New("currentAliveFaWa___"),
      V8ScalarGetter_currentAliveFaWa___, 
      V8ScalarSetter_currentAliveFaWa___);
  result->SetAccessor(
      String::New("FRWOk_"),
      V8ScalarGetter_FRWOk_, 
      V8ScalarSetter_FRWOk_);
  result->SetAccessor(
      String::New("temperatureWasOk_"),
      V8ScalarGetter_temperatureWasOk_, 
      V8ScalarSetter_temperatureWasOk_);
  result->SetAccessor(
      String::New("counterFailsAndWarns_"),
      V8ScalarGetter_counterFailsAndWarns_, 
      V8ScalarSetter_counterFailsAndWarns_);
  result->SetAccessor(
      String::New("iUsedTime"),
      V8ScalarGetter_iUsedTime, 
      V8ScalarSetter_iUsedTime);
  result->SetAccessor(
      String::New("iUsedReserv"),
      V8ScalarGetter_iUsedReserv, 
      V8ScalarSetter_iUsedReserv);
  result->SetAccessor(
      String::New("lengthCfgAnswer"),
      V8ScalarGetter_lengthCfgAnswer, 
      V8ScalarSetter_lengthCfgAnswer);
  result->SetAccessor(
      String::New("nominalPower___"),
      V8ScalarGetter_nominalPower___, 
      V8ScalarSetter_nominalPower___);
  result->SetAccessor(
      String::New("numExcitersPack_"),
      V8ScalarGetter_numExcitersPack_, 
      V8ScalarSetter_numExcitersPack_);
  result->SetAccessor(
      String::New("excitersTotal_"),
      V8ScalarGetter_excitersTotal_, 
      V8ScalarSetter_excitersTotal_);
  result->SetAccessor(
      String::New("ibNumPAB"),
      V8ScalarGetter_ibNumPAB, 
      V8ScalarSetter_ibNumPAB);
  result->SetAccessor(
      String::New("PABTotal_"),
      V8ScalarGetter_PABTotal_, 
      V8ScalarSetter_PABTotal_);
  result->SetAccessor(
      String::New("ibNumPAinPAB"),
      V8ScalarGetter_ibNumPAinPAB, 
      V8ScalarSetter_ibNumPAinPAB);
  result->SetAccessor(
      String::New("terminal_amps_per_block___"),
      V8ScalarGetter_terminal_amps_per_block___, 
      V8ScalarSetter_terminal_amps_per_block___);
  result->SetAccessor(
      String::New("ibNumBCV"),
      V8ScalarGetter_ibNumBCV, 
      V8ScalarSetter_ibNumBCV);
  result->SetAccessor(
      String::New("current_nominal_power"),
      V8ScalarGetter_current_nominal_power, 
      V8ScalarSetter_current_nominal_power);
  result->SetAccessor(
      String::New("total_bcl_"),
      V8ScalarGetter_total_bcl_, 
      V8ScalarSetter_total_bcl_);
  result->SetAccessor(
      String::New("ibNUMDB"),
      V8ScalarGetter_ibNUMDB, 
      V8ScalarSetter_ibNUMDB);
  result->SetAccessor(
      String::New("DBTotal_"),
      V8ScalarGetter_DBTotal_, 
      V8ScalarSetter_DBTotal_);
  result->SetAccessor(
      String::New("ibSizeIBMod"),
      V8ScalarGetter_ibSizeIBMod, 
      V8ScalarSetter_ibSizeIBMod);
  result->SetAccessor(
      String::New("sizeBlockModParams_"),
      V8ScalarGetter_sizeBlockModParams_, 
      V8ScalarSetter_sizeBlockModParams_);
  result->SetAccessor(
      String::New("ibSizeIBPAPAB"),
      V8ScalarGetter_ibSizeIBPAPAB, 
      V8ScalarSetter_ibSizeIBPAPAB);
  result->SetAccessor(
      String::New("sizeBlockTerminalAmpParams_"),
      V8ScalarGetter_sizeBlockTerminalAmpParams_, 
      V8ScalarSetter_sizeBlockTerminalAmpParams_);
  result->SetAccessor(
      String::New("ibSizeIBPrAPAB"),
      V8ScalarGetter_ibSizeIBPrAPAB, 
      V8ScalarSetter_ibSizeIBPrAPAB);
  result->SetAccessor(
      String::New("sizeBlockPreampParams_"),
      V8ScalarGetter_sizeBlockPreampParams_, 
      V8ScalarSetter_sizeBlockPreampParams_);
  result->SetAccessor(
      String::New("ibSizeIBBCV"),
      V8ScalarGetter_ibSizeIBBCV, 
      V8ScalarSetter_ibSizeIBBCV);
  result->SetAccessor(
      String::New("sizeBlockBCNParams_"),
      V8ScalarGetter_sizeBlockBCNParams_, 
      V8ScalarSetter_sizeBlockBCNParams_);
  result->SetAccessor(
      String::New("ibEventStringSize"),
      V8ScalarGetter_ibEventStringSize, 
      V8ScalarSetter_ibEventStringSize);
  result->SetAccessor(
      String::New("sizeEventsString_"),
      V8ScalarGetter_sizeEventsString_, 
      V8ScalarSetter_sizeEventsString_);
  result->SetAccessor(
      String::New("ibFailStringSize"),
      V8ScalarGetter_ibFailStringSize, 
      V8ScalarSetter_ibFailStringSize);
  result->SetAccessor(
      String::New("sizeFailsString_"),
      V8ScalarGetter_sizeFailsString_, 
      V8ScalarSetter_sizeFailsString_);
  result->SetAccessor(
      String::New("ibSizeDB"),
      V8ScalarGetter_ibSizeDB, 
      V8ScalarSetter_ibSizeDB);
  result->SetAccessor(
      String::New("sizeBlockDBParams_"),
      V8ScalarGetter_sizeBlockDBParams_, 
      V8ScalarSetter_sizeBlockDBParams_);
  result->SetAccessor(
      String::New("transmitterID___"),
      V8ScalarGetter_transmitterID___, 
      V8ScalarSetter_transmitterID___);
  result->SetAccessor(
      String::New("exciterType_"),
      V8ScalarGetter_exciterType_, 
      V8ScalarSetter_exciterType_);
  result->SetAccessor(
      String::New("countReservedTransmitters_"),
      V8ScalarGetter_countReservedTransmitters_, 
      V8ScalarSetter_countReservedTransmitters_);

  return handle_scope.Close(result);
}

Handle<Object> InMemoryStorageImplV8::New(InMemoryStorageImpl* database, v8::Isolate *isolate) {
  HandleScope handle_scope(isolate);
  Context::Scope scope(isolate->GetCurrentContext());

  Handle<ObjectTemplate> raw_template = 
      CreateOwnBlueprint(isolate);    

  Handle<ObjectTemplate> templ =
      Local<ObjectTemplate>::New(isolate, raw_template);

  Handle<Object> result = templ->NewInstance();
  Handle<External> map_ptr = External::New(database);

  result->SetInternalField(0, map_ptr);
  return handle_scope.Close(result);
}

//$LastLevelGetters
void InMemoryStorageImplV8::LLGetterByIdx_printPABLock_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* array = static_cast<bool*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_printPABLockEvent_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* array = static_cast<bool*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_printPABNoInPower_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* array = static_cast<bool*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_printPABNoInPowerEvent_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* array = static_cast<bool*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_printPABUnlock_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* array = static_cast<bool*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_printPABInPowerOk_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* array = static_cast<bool*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_snmpEventsQuery_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kQuerySize) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_typesCodesInQuery_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kQuerySize) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_typeMsgsQuery_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kQuerySize) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_vtvSigOnOffTgrD_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_vtvSigOnOffTgrQ_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_vtvOverModTgrD_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_vtvOverModTgrQ_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvModStatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvUsStatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPABOutPowerStatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPreVT12status(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPreTemStaus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPreMIP(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibBCVstatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_R1(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_TR1(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_R2(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_TR2(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_R3(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_TR3(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_R4(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_TR4(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_R5(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_TR5(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_R6(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_TR6(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_R7(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_TR7(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_R8(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_TR8(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibBDstatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_uiPort(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_cExt(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < 30) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    char* array = static_cast<char*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvCntrlMode(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvRadioMode(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_etv_digital_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibUsVtvLock(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibModVtvLock(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibOwnVtvLock(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvReady(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvWork(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvStatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_exciterIstream_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_connection_state_etv(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvOutSync(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_exciterIstreamError_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvErrMod(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvOutPower(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iVtvOutPower(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvSKSStatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvSChMStatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvSPChStatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvVideoLock(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvPowerStatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvSound(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvChanNumAnalog(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iVtvChanNumAnalog(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_exciterASI12TgrVar_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvNet(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvDVBTOnOf(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvMIPOnOf(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvQAM(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvCodRate(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvGI(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvHierar(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvCarNum(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvChannel(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iVtvChannel(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iVtvFreq(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvOutLevel(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iVtvOutLevel(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvTransmNum(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iVtvTransmNum(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvIDCellNum(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iVtvIDCellNum(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvAdDelay(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iVtvAdDelay(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvPrecLineNum(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iVtvPrecLineNum(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvPrecLOnOff(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvPrecNonLOnOff(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVtvTestMode(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibVTVNoconnet(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxExciters) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_PABOnOffTgrVar_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_PABLockTgrVar_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_pab_connection_state_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPABAnlgDigit(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPABInPowerStatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPABStatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPABFRWStatus(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPABInPow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iPABInPow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPABOutPow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iPABOutPow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPABFRW(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iPABFRW(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPreAGC(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPrePlus15(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPreCurVT1(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iPreCurVT1(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPreCurVT2(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iPreCurVT2(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPreTemValue(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iPreTemValue(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPreMIPVoltage(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iPreMIPVoltage(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPreAttenVoltage(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iPreAttenVoltage(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPrePhaseVoltage(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iPreAPhaseVoltage(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibPreReferVoltage(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* array = static_cast<uint*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iPreReferVoltage(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxPABs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_sum_bcl_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibBCVTrOnOf(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibBCVTrLock(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_bcl_a_or_d_WTF(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibBCVPowerStat(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R1PowTemp(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R2PowTemp(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R3PowTemp(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R4PowTemp(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R5PowTemp(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R6PowTemp(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R7PowTemp(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R8PowTemp(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R1Tem(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R1Pow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R2Tem(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R2Pow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R3Tem(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R3Pow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R4Tem(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R4Pow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R5Tem(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R5Pow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R6Tem(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R6Pow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R7Tem(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R7Pow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R8Tem(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBCV_R8Pow(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxBCLs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_sum_about_db_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibBDTrOnOf(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibBDTrLock(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibBDAnlgDigit(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibBDChannel(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_ibBDFactor(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_sound_power_(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_sound_power_Temp(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBDOutPowerTemp(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBDOutPower(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* array = static_cast<int*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLGetterByIdx_iBDFRW(
      uint32_t index, 
      const v8::PropertyCallbackInfo<v8::Value>& info)
  {
  if (index < kMaxDBs) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* array = static_cast<uchar*>(ptr);
    info.GetReturnValue().Set(Number::New(array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

//$LastLevelSetters
void InMemoryStorageImplV8::LLSetterByIdx_printPABLock_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* danger_array = static_cast<bool*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_printPABLockEvent_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* danger_array = static_cast<bool*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_printPABNoInPower_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* danger_array = static_cast<bool*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_printPABNoInPowerEvent_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* danger_array = static_cast<bool*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_printPABUnlock_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* danger_array = static_cast<bool*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_printPABInPowerOk_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    bool* danger_array = static_cast<bool*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_snmpEventsQuery_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kQuerySize) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_typesCodesInQuery_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kQuerySize) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_typeMsgsQuery_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kQuerySize) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_vtvSigOnOffTgrD_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_vtvSigOnOffTgrQ_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_vtvOverModTgrD_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_vtvOverModTgrQ_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvModStatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvUsStatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPABOutPowerStatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPreVT12status(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPreTemStaus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPreMIP(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibBCVstatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_R1(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_TR1(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_R2(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_TR2(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_R3(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_TR3(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_R4(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_TR4(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_R5(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_TR5(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_R6(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_TR6(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_R7(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_TR7(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_R8(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_TR8(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibBDstatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_uiPort(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_cExt(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < 30) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    char* danger_array = static_cast<char*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvCntrlMode(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvRadioMode(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_etv_digital_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibUsVtvLock(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibModVtvLock(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibOwnVtvLock(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvReady(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvWork(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvStatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_exciterIstream_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_connection_state_etv(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvOutSync(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_exciterIstreamError_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvErrMod(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvOutPower(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iVtvOutPower(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvSKSStatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvSChMStatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvSPChStatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvVideoLock(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvPowerStatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvSound(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvChanNumAnalog(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iVtvChanNumAnalog(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_exciterASI12TgrVar_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvNet(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvDVBTOnOf(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvMIPOnOf(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvQAM(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvCodRate(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvGI(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvHierar(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvCarNum(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvChannel(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iVtvChannel(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iVtvFreq(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvOutLevel(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iVtvOutLevel(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvTransmNum(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iVtvTransmNum(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvIDCellNum(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iVtvIDCellNum(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvAdDelay(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iVtvAdDelay(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvPrecLineNum(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iVtvPrecLineNum(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvPrecLOnOff(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvPrecNonLOnOff(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVtvTestMode(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibVTVNoconnet(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxExciters) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_PABOnOffTgrVar_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_PABLockTgrVar_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_pab_connection_state_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPABAnlgDigit(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPABInPowerStatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPABStatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPABFRWStatus(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPABInPow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iPABInPow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPABOutPow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iPABOutPow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPABFRW(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iPABFRW(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPreAGC(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPrePlus15(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPreCurVT1(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iPreCurVT1(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPreCurVT2(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iPreCurVT2(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPreTemValue(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iPreTemValue(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPreMIPVoltage(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iPreMIPVoltage(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPreAttenVoltage(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iPreAttenVoltage(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPrePhaseVoltage(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iPreAPhaseVoltage(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibPreReferVoltage(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uint* danger_array = static_cast<uint*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iPreReferVoltage(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxPABs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_sum_bcl_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibBCVTrOnOf(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibBCVTrLock(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_bcl_a_or_d_WTF(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibBCVPowerStat(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R1PowTemp(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R2PowTemp(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R3PowTemp(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R4PowTemp(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R5PowTemp(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R6PowTemp(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R7PowTemp(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R8PowTemp(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R1Tem(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R1Pow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R2Tem(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R2Pow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R3Tem(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R3Pow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R4Tem(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R4Pow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R5Tem(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R5Pow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R6Tem(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R6Pow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R7Tem(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R7Pow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R8Tem(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBCV_R8Pow(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxBCLs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_sum_about_db_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibBDTrOnOf(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibBDTrLock(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibBDAnlgDigit(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibBDChannel(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_ibBDFactor(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_sound_power_(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_sound_power_Temp(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBDOutPowerTemp(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBDOutPower(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* danger_array = static_cast<int*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

void InMemoryStorageImplV8::LLSetterByIdx_iBDFRW(
    uint32_t index,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (index < kMaxDBs) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    uchar* danger_array = static_cast<uchar*>(ptr);
    danger_array[index] = value->Int32Value();  
    info.GetReturnValue().Set(v8::Number::New(danger_array[index]));
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}

//$ZeroLevelGetters
void InMemoryStorageImplV8::ZLGetter_printPABLock_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABLock_,
          LLSetterByIdx_printPABLock_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABLock_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_printPABLockEvent_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABLockEvent_,
          LLSetterByIdx_printPABLockEvent_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABLockEvent_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_printPABNoInPower_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABNoInPower_,
          LLSetterByIdx_printPABNoInPower_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABNoInPower_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_printPABNoInPowerEvent_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABNoInPowerEvent_,
          LLSetterByIdx_printPABNoInPowerEvent_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABNoInPowerEvent_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_printPABUnlock_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABUnlock_,
          LLSetterByIdx_printPABUnlock_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABUnlock_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_printPABInPowerOk_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_printPABInPowerOk_,
          LLSetterByIdx_printPABInPowerOk_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->printPABInPowerOk_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_snmpEventsQuery_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_snmpEventsQuery_,
          LLSetterByIdx_snmpEventsQuery_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->snmpEventsQuery_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_typesCodesInQuery_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_typesCodesInQuery_,
          LLSetterByIdx_typesCodesInQuery_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->typesCodesInQuery_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_typeMsgsQuery_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_typeMsgsQuery_,
          LLSetterByIdx_typeMsgsQuery_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->typeMsgsQuery_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_vtvSigOnOffTgrD_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_vtvSigOnOffTgrD_,
          LLSetterByIdx_vtvSigOnOffTgrD_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->vtvSigOnOffTgrD_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_vtvSigOnOffTgrQ_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_vtvSigOnOffTgrQ_,
          LLSetterByIdx_vtvSigOnOffTgrQ_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->vtvSigOnOffTgrQ_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_vtvOverModTgrD_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_vtvOverModTgrD_,
          LLSetterByIdx_vtvOverModTgrD_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->vtvOverModTgrD_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_vtvOverModTgrQ_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_vtvOverModTgrQ_,
          LLSetterByIdx_vtvOverModTgrQ_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->vtvOverModTgrQ_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvModStatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvModStatus,
          LLSetterByIdx_ibVtvModStatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvModStatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvUsStatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvUsStatus,
          LLSetterByIdx_ibVtvUsStatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvUsStatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPABOutPowerStatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPABOutPowerStatus,
          LLSetterByIdx_ibPABOutPowerStatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPABOutPowerStatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPreVT12status(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPreVT12status,
          LLSetterByIdx_ibPreVT12status));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPreVT12status);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPreTemStaus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPreTemStaus,
          LLSetterByIdx_ibPreTemStaus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPreTemStaus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPreMIP(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPreMIP,
          LLSetterByIdx_ibPreMIP));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPreMIP);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibBCVstatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibBCVstatus,
          LLSetterByIdx_ibBCVstatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibBCVstatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_R1(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_R1,
          LLSetterByIdx_bcl_R1));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_R1);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_TR1(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_TR1,
          LLSetterByIdx_bcl_TR1));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_TR1);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_R2(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_R2,
          LLSetterByIdx_bcl_R2));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_R2);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_TR2(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_TR2,
          LLSetterByIdx_bcl_TR2));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_TR2);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_R3(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_R3,
          LLSetterByIdx_bcl_R3));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_R3);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_TR3(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_TR3,
          LLSetterByIdx_bcl_TR3));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_TR3);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_R4(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_R4,
          LLSetterByIdx_bcl_R4));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_R4);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_TR4(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_TR4,
          LLSetterByIdx_bcl_TR4));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_TR4);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_R5(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_R5,
          LLSetterByIdx_bcl_R5));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_R5);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_TR5(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_TR5,
          LLSetterByIdx_bcl_TR5));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_TR5);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_R6(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_R6,
          LLSetterByIdx_bcl_R6));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_R6);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_TR6(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_TR6,
          LLSetterByIdx_bcl_TR6));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_TR6);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_R7(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_R7,
          LLSetterByIdx_bcl_R7));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_R7);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_TR7(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_TR7,
          LLSetterByIdx_bcl_TR7));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_TR7);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_R8(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_R8,
          LLSetterByIdx_bcl_R8));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_R8);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_TR8(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_TR8,
          LLSetterByIdx_bcl_TR8));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_TR8);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibBDstatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibBDstatus,
          LLSetterByIdx_ibBDstatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibBDstatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_uiPort(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_uiPort,
          LLSetterByIdx_uiPort));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->uiPort);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_cExt(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_cExt,
          LLSetterByIdx_cExt));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->cExt);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvCntrlMode(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvCntrlMode,
          LLSetterByIdx_ibVtvCntrlMode));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvCntrlMode);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvRadioMode(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvRadioMode,
          LLSetterByIdx_ibVtvRadioMode));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvRadioMode);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_etv_digital_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_etv_digital_,
          LLSetterByIdx_etv_digital_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->etv_digital_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibUsVtvLock(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibUsVtvLock,
          LLSetterByIdx_ibUsVtvLock));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibUsVtvLock);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibModVtvLock(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibModVtvLock,
          LLSetterByIdx_ibModVtvLock));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibModVtvLock);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibOwnVtvLock(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibOwnVtvLock,
          LLSetterByIdx_ibOwnVtvLock));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibOwnVtvLock);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvReady(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvReady,
          LLSetterByIdx_ibVtvReady));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvReady);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvWork(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvWork,
          LLSetterByIdx_ibVtvWork));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvWork);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvStatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvStatus,
          LLSetterByIdx_ibVtvStatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvStatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_exciterIstream_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_exciterIstream_,
          LLSetterByIdx_exciterIstream_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->exciterIstream_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_connection_state_etv(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_connection_state_etv,
          LLSetterByIdx_connection_state_etv));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->connection_state_etv);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvOutSync(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvOutSync,
          LLSetterByIdx_ibVtvOutSync));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvOutSync);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_exciterIstreamError_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_exciterIstreamError_,
          LLSetterByIdx_exciterIstreamError_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->exciterIstreamError_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvErrMod(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvErrMod,
          LLSetterByIdx_ibVtvErrMod));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvErrMod);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvOutPower(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvOutPower,
          LLSetterByIdx_ibVtvOutPower));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvOutPower);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iVtvOutPower(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iVtvOutPower,
          LLSetterByIdx_iVtvOutPower));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iVtvOutPower);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvSKSStatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvSKSStatus,
          LLSetterByIdx_ibVtvSKSStatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvSKSStatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvSChMStatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvSChMStatus,
          LLSetterByIdx_ibVtvSChMStatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvSChMStatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvSPChStatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvSPChStatus,
          LLSetterByIdx_ibVtvSPChStatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvSPChStatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvVideoLock(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvVideoLock,
          LLSetterByIdx_ibVtvVideoLock));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvVideoLock);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvPowerStatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvPowerStatus,
          LLSetterByIdx_ibVtvPowerStatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvPowerStatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvSound(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvSound,
          LLSetterByIdx_ibVtvSound));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvSound);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvChanNumAnalog(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvChanNumAnalog,
          LLSetterByIdx_ibVtvChanNumAnalog));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvChanNumAnalog);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iVtvChanNumAnalog(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iVtvChanNumAnalog,
          LLSetterByIdx_iVtvChanNumAnalog));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iVtvChanNumAnalog);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_exciterASI12TgrVar_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_exciterASI12TgrVar_,
          LLSetterByIdx_exciterASI12TgrVar_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->exciterASI12TgrVar_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvNet(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvNet,
          LLSetterByIdx_ibVtvNet));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvNet);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvDVBTOnOf(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvDVBTOnOf,
          LLSetterByIdx_ibVtvDVBTOnOf));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvDVBTOnOf);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvMIPOnOf(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvMIPOnOf,
          LLSetterByIdx_ibVtvMIPOnOf));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvMIPOnOf);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvQAM(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvQAM,
          LLSetterByIdx_ibVtvQAM));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvQAM);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvCodRate(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvCodRate,
          LLSetterByIdx_ibVtvCodRate));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvCodRate);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvGI(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvGI,
          LLSetterByIdx_ibVtvGI));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvGI);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvHierar(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvHierar,
          LLSetterByIdx_ibVtvHierar));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvHierar);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvCarNum(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvCarNum,
          LLSetterByIdx_ibVtvCarNum));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvCarNum);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvChannel(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvChannel,
          LLSetterByIdx_ibVtvChannel));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvChannel);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iVtvChannel(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iVtvChannel,
          LLSetterByIdx_iVtvChannel));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iVtvChannel);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iVtvFreq(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iVtvFreq,
          LLSetterByIdx_iVtvFreq));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iVtvFreq);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvOutLevel(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvOutLevel,
          LLSetterByIdx_ibVtvOutLevel));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvOutLevel);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iVtvOutLevel(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iVtvOutLevel,
          LLSetterByIdx_iVtvOutLevel));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iVtvOutLevel);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvTransmNum(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvTransmNum,
          LLSetterByIdx_ibVtvTransmNum));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvTransmNum);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iVtvTransmNum(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iVtvTransmNum,
          LLSetterByIdx_iVtvTransmNum));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iVtvTransmNum);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvIDCellNum(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvIDCellNum,
          LLSetterByIdx_ibVtvIDCellNum));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvIDCellNum);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iVtvIDCellNum(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iVtvIDCellNum,
          LLSetterByIdx_iVtvIDCellNum));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iVtvIDCellNum);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvAdDelay(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvAdDelay,
          LLSetterByIdx_ibVtvAdDelay));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvAdDelay);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iVtvAdDelay(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iVtvAdDelay,
          LLSetterByIdx_iVtvAdDelay));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iVtvAdDelay);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvPrecLineNum(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvPrecLineNum,
          LLSetterByIdx_ibVtvPrecLineNum));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvPrecLineNum);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iVtvPrecLineNum(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iVtvPrecLineNum,
          LLSetterByIdx_iVtvPrecLineNum));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iVtvPrecLineNum);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvPrecLOnOff(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvPrecLOnOff,
          LLSetterByIdx_ibVtvPrecLOnOff));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvPrecLOnOff);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvPrecNonLOnOff(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvPrecNonLOnOff,
          LLSetterByIdx_ibVtvPrecNonLOnOff));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvPrecNonLOnOff);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVtvTestMode(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVtvTestMode,
          LLSetterByIdx_ibVtvTestMode));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVtvTestMode);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibVTVNoconnet(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibVTVNoconnet,
          LLSetterByIdx_ibVTVNoconnet));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibVTVNoconnet);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_PABOnOffTgrVar_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_PABOnOffTgrVar_,
          LLSetterByIdx_PABOnOffTgrVar_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->PABOnOffTgrVar_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_PABLockTgrVar_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_PABLockTgrVar_,
          LLSetterByIdx_PABLockTgrVar_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->PABLockTgrVar_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_pab_connection_state_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_pab_connection_state_,
          LLSetterByIdx_pab_connection_state_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->pab_connection_state_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPABAnlgDigit(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPABAnlgDigit,
          LLSetterByIdx_ibPABAnlgDigit));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPABAnlgDigit);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPABInPowerStatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPABInPowerStatus,
          LLSetterByIdx_ibPABInPowerStatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPABInPowerStatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPABStatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPABStatus,
          LLSetterByIdx_ibPABStatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPABStatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPABFRWStatus(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPABFRWStatus,
          LLSetterByIdx_ibPABFRWStatus));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPABFRWStatus);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPABInPow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPABInPow,
          LLSetterByIdx_ibPABInPow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPABInPow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iPABInPow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iPABInPow,
          LLSetterByIdx_iPABInPow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iPABInPow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPABOutPow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPABOutPow,
          LLSetterByIdx_ibPABOutPow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPABOutPow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iPABOutPow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iPABOutPow,
          LLSetterByIdx_iPABOutPow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iPABOutPow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPABFRW(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPABFRW,
          LLSetterByIdx_ibPABFRW));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPABFRW);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iPABFRW(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iPABFRW,
          LLSetterByIdx_iPABFRW));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iPABFRW);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPreAGC(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPreAGC,
          LLSetterByIdx_ibPreAGC));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPreAGC);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPrePlus15(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPrePlus15,
          LLSetterByIdx_ibPrePlus15));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPrePlus15);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPreCurVT1(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPreCurVT1,
          LLSetterByIdx_ibPreCurVT1));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPreCurVT1);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iPreCurVT1(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iPreCurVT1,
          LLSetterByIdx_iPreCurVT1));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iPreCurVT1);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPreCurVT2(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPreCurVT2,
          LLSetterByIdx_ibPreCurVT2));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPreCurVT2);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iPreCurVT2(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iPreCurVT2,
          LLSetterByIdx_iPreCurVT2));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iPreCurVT2);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPreTemValue(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPreTemValue,
          LLSetterByIdx_ibPreTemValue));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPreTemValue);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iPreTemValue(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iPreTemValue,
          LLSetterByIdx_iPreTemValue));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iPreTemValue);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPreMIPVoltage(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPreMIPVoltage,
          LLSetterByIdx_ibPreMIPVoltage));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPreMIPVoltage);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iPreMIPVoltage(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iPreMIPVoltage,
          LLSetterByIdx_iPreMIPVoltage));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iPreMIPVoltage);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPreAttenVoltage(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPreAttenVoltage,
          LLSetterByIdx_ibPreAttenVoltage));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPreAttenVoltage);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iPreAttenVoltage(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iPreAttenVoltage,
          LLSetterByIdx_iPreAttenVoltage));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iPreAttenVoltage);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPrePhaseVoltage(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPrePhaseVoltage,
          LLSetterByIdx_ibPrePhaseVoltage));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPrePhaseVoltage);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iPreAPhaseVoltage(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iPreAPhaseVoltage,
          LLSetterByIdx_iPreAPhaseVoltage));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iPreAPhaseVoltage);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibPreReferVoltage(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibPreReferVoltage,
          LLSetterByIdx_ibPreReferVoltage));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibPreReferVoltage);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iPreReferVoltage(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iPreReferVoltage,
          LLSetterByIdx_iPreReferVoltage));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iPreReferVoltage);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_sum_bcl_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_sum_bcl_,
          LLSetterByIdx_sum_bcl_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->sum_bcl_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibBCVTrOnOf(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibBCVTrOnOf,
          LLSetterByIdx_ibBCVTrOnOf));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibBCVTrOnOf);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibBCVTrLock(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibBCVTrLock,
          LLSetterByIdx_ibBCVTrLock));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibBCVTrLock);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_bcl_a_or_d_WTF(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_bcl_a_or_d_WTF,
          LLSetterByIdx_bcl_a_or_d_WTF));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->bcl_a_or_d_WTF);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibBCVPowerStat(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibBCVPowerStat,
          LLSetterByIdx_ibBCVPowerStat));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibBCVPowerStat);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R1PowTemp(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R1PowTemp,
          LLSetterByIdx_iBCV_R1PowTemp));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R1PowTemp);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R2PowTemp(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R2PowTemp,
          LLSetterByIdx_iBCV_R2PowTemp));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R2PowTemp);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R3PowTemp(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R3PowTemp,
          LLSetterByIdx_iBCV_R3PowTemp));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R3PowTemp);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R4PowTemp(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R4PowTemp,
          LLSetterByIdx_iBCV_R4PowTemp));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R4PowTemp);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R5PowTemp(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R5PowTemp,
          LLSetterByIdx_iBCV_R5PowTemp));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R5PowTemp);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R6PowTemp(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R6PowTemp,
          LLSetterByIdx_iBCV_R6PowTemp));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R6PowTemp);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R7PowTemp(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R7PowTemp,
          LLSetterByIdx_iBCV_R7PowTemp));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R7PowTemp);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R8PowTemp(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R8PowTemp,
          LLSetterByIdx_iBCV_R8PowTemp));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R8PowTemp);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R1Tem(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R1Tem,
          LLSetterByIdx_iBCV_R1Tem));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R1Tem);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R1Pow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R1Pow,
          LLSetterByIdx_iBCV_R1Pow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R1Pow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R2Tem(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R2Tem,
          LLSetterByIdx_iBCV_R2Tem));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R2Tem);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R2Pow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R2Pow,
          LLSetterByIdx_iBCV_R2Pow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R2Pow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R3Tem(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R3Tem,
          LLSetterByIdx_iBCV_R3Tem));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R3Tem);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R3Pow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R3Pow,
          LLSetterByIdx_iBCV_R3Pow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R3Pow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R4Tem(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R4Tem,
          LLSetterByIdx_iBCV_R4Tem));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R4Tem);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R4Pow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R4Pow,
          LLSetterByIdx_iBCV_R4Pow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R4Pow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R5Tem(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R5Tem,
          LLSetterByIdx_iBCV_R5Tem));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R5Tem);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R5Pow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R5Pow,
          LLSetterByIdx_iBCV_R5Pow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R5Pow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R6Tem(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R6Tem,
          LLSetterByIdx_iBCV_R6Tem));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R6Tem);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R6Pow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R6Pow,
          LLSetterByIdx_iBCV_R6Pow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R6Pow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R7Tem(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R7Tem,
          LLSetterByIdx_iBCV_R7Tem));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R7Tem);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R7Pow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R7Pow,
          LLSetterByIdx_iBCV_R7Pow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R7Pow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R8Tem(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R8Tem,
          LLSetterByIdx_iBCV_R8Tem));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R8Tem);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBCV_R8Pow(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBCV_R8Pow,
          LLSetterByIdx_iBCV_R8Pow));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBCV_R8Pow);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_sum_about_db_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_sum_about_db_,
          LLSetterByIdx_sum_about_db_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->sum_about_db_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibBDTrOnOf(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibBDTrOnOf,
          LLSetterByIdx_ibBDTrOnOf));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibBDTrOnOf);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibBDTrLock(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibBDTrLock,
          LLSetterByIdx_ibBDTrLock));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibBDTrLock);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibBDAnlgDigit(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibBDAnlgDigit,
          LLSetterByIdx_ibBDAnlgDigit));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibBDAnlgDigit);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibBDChannel(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibBDChannel,
          LLSetterByIdx_ibBDChannel));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibBDChannel);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_ibBDFactor(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_ibBDFactor,
          LLSetterByIdx_ibBDFactor));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->ibBDFactor);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_sound_power_(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_sound_power_,
          LLSetterByIdx_sound_power_));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->sound_power_);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_sound_power_Temp(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_sound_power_Temp,
          LLSetterByIdx_sound_power_Temp));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->sound_power_Temp);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBDOutPowerTemp(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBDOutPowerTemp,
          LLSetterByIdx_iBDOutPowerTemp));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBDOutPowerTemp);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBDOutPower(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBDOutPower,
          LLSetterByIdx_iBDOutPower));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBDOutPower);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

void InMemoryStorageImplV8::ZLGetter_iBDFRW(
      v8::Local<v8::String> name,
      const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  InMemoryStorageImpl* danger_real_ptr = static_cast<InMemoryStorageImpl*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
      Isolate::GetCurrent(),
      ArrayMakeBlueprint(
          Isolate::GetCurrent(), 
          LLGetterByIdx_iBDFRW,
          LLSetterByIdx_iBDFRW));
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(danger_real_ptr->iBDFRW);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}

  //$ScalarGetters
void InMemoryStorageImplV8::V8ScalarGetter_lengthAllParams___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->lengthAllParams___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_counterDebug___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->counterDebug___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_failsReseted_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  bool value = static_cast<InMemoryStorageImpl*>(ptr)->failsReseted_;
  info.GetReturnValue().Set(Boolean::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_currentQueryIndex_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->currentQueryIndex_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_powerOkTTgr_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  bool value = static_cast<InMemoryStorageImpl*>(ptr)->powerOkTTgr_;
  info.GetReturnValue().Set(Boolean::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_needPrintFullPower_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  bool value = static_cast<InMemoryStorageImpl*>(ptr)->needPrintFullPower_;
  info.GetReturnValue().Set(Boolean::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_needPrintOkPower_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  bool value = static_cast<InMemoryStorageImpl*>(ptr)->needPrintOkPower_;
  info.GetReturnValue().Set(Boolean::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_FRWOkTTgr_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  bool value = static_cast<InMemoryStorageImpl*>(ptr)->FRWOkTTgr_;
  info.GetReturnValue().Set(Boolean::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_needPrintFullFRW_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  bool value = static_cast<InMemoryStorageImpl*>(ptr)->needPrintFullFRW_;
  info.GetReturnValue().Set(Boolean::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_needPrintOkFRW_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  bool value = static_cast<InMemoryStorageImpl*>(ptr)->needPrintOkFRW_;
  info.GetReturnValue().Set(Boolean::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ctrlModeTgrVar_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->ctrlModeTgrVar_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_typeLoadTgrVar_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->typeLoadTgrVar_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_tmitterLockTgrVar___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->tmitterLockTgrVar___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_tmitterOnTgrVar___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->tmitterOnTgrVar___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_powHalfModeTgrVar_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->powHalfModeTgrVar_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_istreamTgrVar_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->istreamTgrVar_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_outSynTgrVar_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->outSynTgrVar_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_statusTmitterTgrVar_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->statusTmitterTgrVar_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_type_tm_digital_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->type_tm_digital_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibWork_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->ibWork_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_exciterLock_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->exciterLock_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibPowAmpLock_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->ibPowAmpLock_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_idx_oned_etv_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->idx_oned_etv_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_idx_oned_etv_q_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->idx_oned_etv_q_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibRadioMode_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->ibRadioMode_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_transmitterReady_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->transmitterReady_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_failNet_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->failNet_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_failBallast_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->failBallast_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_failFRW_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->failFRW_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_failCoolling_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->failCoolling_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibPAB(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibPAB;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibVtv(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->ibVtv;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_failsTotalD_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->failsTotalD_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_failsTotalQ_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->failsTotalQ_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_failsTotalQQ_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->failsTotalQQ_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibRS485(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->ibRS485;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibI2C(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->ibI2C;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_channalValuePacked_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->channalValuePacked_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_iChannel(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->iChannel;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_iChannelSetup(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->iChannelSetup;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibPower(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibPower;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_realPowerRepresent___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->realPowerRepresent___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibValueFRW(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibValueFRW;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_FRWValue___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->FRWValue___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibSoundLock(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->ibSoundLock;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibSU2St(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->ibSU2St;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_failBallast_Power(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->failBallast_Power;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_iBallastPower(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->iBallastPower;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_transmitterAddress___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->transmitterAddress___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_iMaxTemre(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->iMaxTemre;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_iMaxStatus(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->iMaxStatus;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_new_max_temperature_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->new_max_temperature_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_iNewMaxStatus(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->iNewMaxStatus;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_connecton_state___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->connecton_state___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_snmp_connecton_status___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->snmp_connecton_status___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_transmitter_number_to_set_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->transmitter_number_to_set_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_fixedAlrmRecordIndex_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->fixedAlrmRecordIndex_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_hasMsgForSnmp_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  bool value = static_cast<InMemoryStorageImpl*>(ptr)->hasMsgForSnmp_;
  info.GetReturnValue().Set(Boolean::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_statusRecordIndex_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->statusRecordIndex_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_newFailOccure_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  bool value = static_cast<InMemoryStorageImpl*>(ptr)->newFailOccure_;
  info.GetReturnValue().Set(Boolean::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_currentMWFCode_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->currentMWFCode_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_currentAliveFaWa___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uchar value = static_cast<InMemoryStorageImpl*>(ptr)->currentAliveFaWa___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_FRWOk_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  bool value = static_cast<InMemoryStorageImpl*>(ptr)->FRWOk_;
  info.GetReturnValue().Set(Boolean::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_temperatureWasOk_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  bool value = static_cast<InMemoryStorageImpl*>(ptr)->temperatureWasOk_;
  info.GetReturnValue().Set(Boolean::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_counterFailsAndWarns_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->counterFailsAndWarns_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_iUsedTime(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->iUsedTime;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_iUsedReserv(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->iUsedReserv;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_lengthCfgAnswer(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->lengthCfgAnswer;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_nominalPower___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->nominalPower___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_numExcitersPack_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->numExcitersPack_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_excitersTotal_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<InMemoryStorageImpl*>(ptr)->excitersTotal_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibNumPAB(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibNumPAB;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_PABTotal_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->PABTotal_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibNumPAinPAB(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibNumPAinPAB;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_terminal_amps_per_block___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->terminal_amps_per_block___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibNumBCV(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibNumBCV;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_current_nominal_power(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->current_nominal_power;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_total_bcl_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->total_bcl_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibNUMDB(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibNUMDB;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_DBTotal_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->DBTotal_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibSizeIBMod(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibSizeIBMod;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_sizeBlockModParams_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->sizeBlockModParams_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibSizeIBPAPAB(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibSizeIBPAPAB;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_sizeBlockTerminalAmpParams_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->sizeBlockTerminalAmpParams_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibSizeIBPrAPAB(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibSizeIBPrAPAB;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_sizeBlockPreampParams_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->sizeBlockPreampParams_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibSizeIBBCV(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibSizeIBBCV;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_sizeBlockBCNParams_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->sizeBlockBCNParams_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibEventStringSize(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibEventStringSize;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_sizeEventsString_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->sizeEventsString_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibFailStringSize(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibFailStringSize;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_sizeFailsString_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->sizeFailsString_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_ibSizeDB(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->ibSizeDB;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_sizeBlockDBParams_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->sizeBlockDBParams_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_transmitterID___(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->transmitterID___;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_exciterType_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->exciterType_;
  info.GetReturnValue().Set(Integer::New(value));
}

void InMemoryStorageImplV8::V8ScalarGetter_countReservedTransmitters_(
    v8::Local<v8::String> name,
    const v8::PropertyCallbackInfo<v8::Value>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  uint value = static_cast<InMemoryStorageImpl*>(ptr)->countReservedTransmitters_;
  info.GetReturnValue().Set(Integer::New(value));
}

  //$ScalarSetters
void InMemoryStorageImplV8::V8ScalarSetter_lengthAllParams___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->lengthAllParams___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_counterDebug___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->counterDebug___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_failsReseted_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->failsReseted_ = value->BooleanValue();
}

void InMemoryStorageImplV8::V8ScalarSetter_currentQueryIndex_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->currentQueryIndex_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_powerOkTTgr_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->powerOkTTgr_ = value->BooleanValue();
}

void InMemoryStorageImplV8::V8ScalarSetter_needPrintFullPower_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->needPrintFullPower_ = value->BooleanValue();
}

void InMemoryStorageImplV8::V8ScalarSetter_needPrintOkPower_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->needPrintOkPower_ = value->BooleanValue();
}

void InMemoryStorageImplV8::V8ScalarSetter_FRWOkTTgr_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->FRWOkTTgr_ = value->BooleanValue();
}

void InMemoryStorageImplV8::V8ScalarSetter_needPrintFullFRW_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->needPrintFullFRW_ = value->BooleanValue();
}

void InMemoryStorageImplV8::V8ScalarSetter_needPrintOkFRW_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->needPrintOkFRW_ = value->BooleanValue();
}

void InMemoryStorageImplV8::V8ScalarSetter_ctrlModeTgrVar_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ctrlModeTgrVar_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_typeLoadTgrVar_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->typeLoadTgrVar_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_tmitterLockTgrVar___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->tmitterLockTgrVar___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_tmitterOnTgrVar___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->tmitterOnTgrVar___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_powHalfModeTgrVar_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->powHalfModeTgrVar_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_istreamTgrVar_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->istreamTgrVar_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_outSynTgrVar_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->outSynTgrVar_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_statusTmitterTgrVar_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->statusTmitterTgrVar_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_type_tm_digital_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->type_tm_digital_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibWork_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibWork_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_exciterLock_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->exciterLock_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibPowAmpLock_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibPowAmpLock_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_idx_oned_etv_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->idx_oned_etv_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_idx_oned_etv_q_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->idx_oned_etv_q_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibRadioMode_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibRadioMode_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_transmitterReady_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->transmitterReady_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_failNet_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->failNet_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_failBallast_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->failBallast_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_failFRW_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->failFRW_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_failCoolling_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->failCoolling_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibPAB(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibPAB = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibVtv(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibVtv = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_failsTotalD_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->failsTotalD_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_failsTotalQ_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->failsTotalQ_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_failsTotalQQ_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->failsTotalQQ_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibRS485(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibRS485 = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibI2C(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibI2C = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_channalValuePacked_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->channalValuePacked_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_iChannel(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->iChannel = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_iChannelSetup(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->iChannelSetup = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibPower(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibPower = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_realPowerRepresent___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->realPowerRepresent___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibValueFRW(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibValueFRW = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_FRWValue___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->FRWValue___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibSoundLock(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibSoundLock = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibSU2St(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibSU2St = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_failBallast_Power(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->failBallast_Power = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_iBallastPower(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->iBallastPower = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_transmitterAddress___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->transmitterAddress___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_iMaxTemre(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->iMaxTemre = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_iMaxStatus(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->iMaxStatus = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_new_max_temperature_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->new_max_temperature_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_iNewMaxStatus(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->iNewMaxStatus = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_connecton_state___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->connecton_state___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_snmp_connecton_status___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->snmp_connecton_status___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_transmitter_number_to_set_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->transmitter_number_to_set_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_fixedAlrmRecordIndex_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->fixedAlrmRecordIndex_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_hasMsgForSnmp_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->hasMsgForSnmp_ = value->BooleanValue();
}

void InMemoryStorageImplV8::V8ScalarSetter_statusRecordIndex_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->statusRecordIndex_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_newFailOccure_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->newFailOccure_ = value->BooleanValue();
}

void InMemoryStorageImplV8::V8ScalarSetter_currentMWFCode_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->currentMWFCode_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_currentAliveFaWa___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->currentAliveFaWa___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_FRWOk_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->FRWOk_ = value->BooleanValue();
}

void InMemoryStorageImplV8::V8ScalarSetter_temperatureWasOk_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->temperatureWasOk_ = value->BooleanValue();
}

void InMemoryStorageImplV8::V8ScalarSetter_counterFailsAndWarns_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->counterFailsAndWarns_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_iUsedTime(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->iUsedTime = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_iUsedReserv(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->iUsedReserv = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_lengthCfgAnswer(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->lengthCfgAnswer = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_nominalPower___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->nominalPower___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_numExcitersPack_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->numExcitersPack_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_excitersTotal_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->excitersTotal_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibNumPAB(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibNumPAB = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_PABTotal_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->PABTotal_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibNumPAinPAB(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibNumPAinPAB = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_terminal_amps_per_block___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->terminal_amps_per_block___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibNumBCV(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibNumBCV = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_current_nominal_power(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->current_nominal_power = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_total_bcl_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->total_bcl_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibNUMDB(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibNUMDB = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_DBTotal_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->DBTotal_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibSizeIBMod(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibSizeIBMod = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_sizeBlockModParams_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->sizeBlockModParams_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibSizeIBPAPAB(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibSizeIBPAPAB = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_sizeBlockTerminalAmpParams_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->sizeBlockTerminalAmpParams_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibSizeIBPrAPAB(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibSizeIBPrAPAB = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_sizeBlockPreampParams_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->sizeBlockPreampParams_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibSizeIBBCV(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibSizeIBBCV = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_sizeBlockBCNParams_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->sizeBlockBCNParams_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibEventStringSize(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibEventStringSize = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_sizeEventsString_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->sizeEventsString_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibFailStringSize(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibFailStringSize = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_sizeFailsString_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->sizeFailsString_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_ibSizeDB(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->ibSizeDB = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_sizeBlockDBParams_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->sizeBlockDBParams_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_transmitterID___(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->transmitterID___ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_exciterType_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->exciterType_ = value->Int32Value();
}

void InMemoryStorageImplV8::V8ScalarSetter_countReservedTransmitters_(
        v8::Local<v8::String> property, v8::Local<v8::Value> value,
        const v8::PropertyCallbackInfo<void>& info) 
  {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<InMemoryStorageImpl*>(ptr)->countReservedTransmitters_ = value->Int32Value();
}

}