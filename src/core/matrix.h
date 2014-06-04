
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class matrix {
public:
  matrix(int r=2, int c=2) {
    nrows_ = r;
    ncols_ = c;
    m_ = new double[r*c];
  }
  
  double get(int r, int c) const {
    return m_[r*ncols_ + c];
  }
  
  void put(int r, int c, double d) {
    m_[r*ncols_ + c] = d;
  }
  
  // Step 1:
  ~matrix() {
    delete [] m_;
  }
  
private:
  int nrows_;
  int ncols_;
  double *m_;
  
  // Protection
  // http://stackoverflow.com/questions/2173746/how-do-i-make-this-c-object-non-copyable
  matrix( const matrix& ); // non construction-copyable - copy constructor
  const matrix& operator=( const matrix& );  // non copyable - assignment operator
};