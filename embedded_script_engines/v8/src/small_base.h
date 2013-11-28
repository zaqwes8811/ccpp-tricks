#ifndef SMALL_BASE
#define SMALL_BASE
typedef unsigned char uchar;
namespace scenarios {
class SmallBase {
 public:
	 SmallBase(int temp) : temp_(temp) { }
	 int temp_;
	 unsigned int idx_oned_etv_;
	 uchar var_char;
	 uchar ibRadioMode_; 


};
}
#endif // SMALL_BASE