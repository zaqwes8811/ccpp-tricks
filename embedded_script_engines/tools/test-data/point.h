class Point {
  public:
   Point(int x, int y) : x_(x),
        y_(y) { }
   int x_;
   int y_;
   const int* ptr;
   std::vector<std::string> vector_values;
   Vector values_range;
   //int array[42];  // Replace to vector!!
};