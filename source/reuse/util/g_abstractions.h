// encoding : utf8
// #include "g_abstractions.h"
#ifndef GLOBAL_ABSTRACTIONS
#define GLOBAL_ABSTRACTIONS
  //typedef UCHAR uchar;
  // абстракция к winapi
  typedef void (__stdcall * atom_lock)(LPCRITICAL_SECTION);
  typedef void (__stdcall * atom_unlock)(LPCRITICAL_SECTION);
  typedef void (__stdcall * init_locker)(LPCRITICAL_SECTION);
  typedef void (__stdcall * free_locker)(LPCRITICAL_SECTION);

  /*
      // абстракция к атомартной потокозащите
  *.h
  atom_lock _alock;
  atom_unlock  _aunlock;
  init_locker _init_locker;
  free_locker _free_locker;
  CRITICAL_SECTION _csTransLayer;

  *.cc
  CMonoblockView::CMonoblockView() {
    _alock = ::EnterCriticalSection;
    _aunlock = ::LeaveCriticalSection;
    _init_locker = ::InitializeCriticalSection;
    _free_locker = ::DeleteCriticalSection;
    _init_locker(&_csTransLayer);
  }

  CMonoblockView::~CMonoblockView() {
  _free_locker(&_csTransLayer);
  }
  */
  
// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
// !! Danger !! с наследование могут быть проблемы!
#define DISALLOW_COPY_AND_ASSIGN_G(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&);
#endif