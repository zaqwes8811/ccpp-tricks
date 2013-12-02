#include "palette_engine.h"

// Other
#include "v8.h"
#include <gtest/gtest.h>

TEST(V8, Palette) {
  v8::V8::InitializeICU();
  string file = "..\\scripts\\palette.js";
  EXPECT_NE(true, file.empty());


  /// Isolate and context be injected!
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope handle_scope(isolate);

  // Script
  Handle<String> source = ReadFile(file);
  EXPECT_NE(true, source.IsEmpty());

  ///@Objects
  Palette palette;
  palette.array_[0] = 100;
  palette.point_array[1].x_ = 100;

  // Engine
  PaletteEngine engine(isolate, source, &palette);

  EXPECT_EQ(10, palette.point_array[1].x_);
}