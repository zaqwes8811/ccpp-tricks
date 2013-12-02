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
	
	 
  int PABTotal_;
	int total_bcl_;
	int excitersTotal_;
	int DBTotal_;
	int transmitterID___;
	int terminal_amps_per_block___;
	int sizeBlockPreampParams_;
	int sizeBlockTerminalAmpParams_;
	int sizeBlockBCNParams_;
	int sizeBlockDBParams_;
	int sizeBlockModParams_;
	
};
}
#endif // SMALL_BASE