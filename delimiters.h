//implementation for delimiters.h
#include "GenStack.h"

//header file for delimiters.cpp
class delimiters{
  public:
    void called(string txt); //calling method
  private:
    bool done; //If there is an error it boolean for breaking out of loop
    bool perfect; //Checks to make sure no errors
    bool commentSmall; //Boolean for // comments
    bool commentBig; //Boolean for /* */ comments

    GenStack<char> *stack; //a char stack
};
