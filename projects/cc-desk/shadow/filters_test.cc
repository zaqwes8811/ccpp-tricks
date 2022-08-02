#include "heart/config.h"

#include "model_layer/entities.h"
#include "model_layer/filters.h"
#include "model_layer/model.h"

#include <gtest/gtest.h>

namespace {
using entities::Task;
using filters::DoneFilter;
using filters::Filter;
using filters::FilterPtr;
using filters::SortByPriorityFilter;

TEST(ChainFilter, Base) {
  Filter *f = new DoneFilter;
  SortByPriorityFilter *e = dynamic_cast<SortByPriorityFilter *>(f);
  EXPECT_FALSE(e);

  DoneFilter *e_ = dynamic_cast<DoneFilter *>(f);
  EXPECT_TRUE(e_);
  delete f;
}
} // namespace
