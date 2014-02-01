

/*

*/

class New2D : public Hello {
public:
  void SendUpPower() {

  }

  int SendChannel(const int* channel) {

  }

  // state
  // Not Work
  int currents[2][4];
  int voltages[9];

  // Work
  // GMock cppclean воспринимает только скаляры
  int command;
  vector<String> journal;
};