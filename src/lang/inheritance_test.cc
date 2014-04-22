// http://alenacpp.blogspot.ru/2005/03/blog-post.html
// http://www.gotw.ca/gotw/031.htm

// Third party
#include <gtest/gtest.h>

class VDtor {
public:
  virtual ~VDtor() = 0;
};

VDtor::~VDtor() {

}

class VDtorImpl : public VDtor {
public:
  virtual ~VDtorImpl() {}  // Могу определить, а могу и нет
};

//VDtorImpl::~VDtorImpl() { }

TEST(Lang, PureVirtualDtor) {
  // 33/M35 - а класс с виртуальным деструктором будет компилироваться?
  // TODO:
  //VDtor anstr;  // не создасться
  VDtorImpl impl;

}

// Как запретить наследование - нужно ли? Может быть лучше protected
//   для нужд тестирования
// http://forum.sources.ru/index.php?showtopic=153352
// http://alenacpp.blogspot.ru/2006/03/blog-post_11.html

TEST(Lang, DisableInh) {

}
