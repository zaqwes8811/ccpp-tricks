class matrix {
public:
  matrix(int r=2, int c=2) {
    nrows_ = r;
    ncols_ = c;
    m_ = new double[r*c];
  }
  
  double get(int r, int c) {
    return m_[r*ncols_ + c];
  }
  
  //void put
  
private:
  int nrows_;
  int ncols_;
  double *m_;
};