#include "delimiters.h"

//main method
int main (int argc, char **argv) {
  if (argc > 1){
    delimiters d;
    d.called(string(argv[1]));
  } else {
    cout << "You need to enter a file name." << endl;
  }
  return 0;
}
