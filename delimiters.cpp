//implementation for delimiters.cpp
#include "delimiters.h"
#include <fstream>

void delimiters::called(string txt){ //calling method
  ifstream file(txt);

  done = false;
  perfect = true;
  commentSmall = false;
  commentBig = false;

  stack = new GenStack<char>();

  if (file.is_open()) {
    string tempLine;
    int lines = 1;

    //for testing :)
    /*
    ]
    */
    //]

    while (getline(file, tempLine) && done == false) { //loops until no more lines or issue
      for (int i = 0; i < tempLine.length(); ++i){
        char t = tempLine[i];

        if (i < tempLine.length()-1 && t == '/' && tempLine[i+1] == '/'){ // checks for small comments
          commentSmall = true;
        }
        if (i < tempLine.length()-1 && t == '/' && tempLine[i+1] == '*'){ //checks for beginning of big comments
          commentBig = true;
        }
        if (i < tempLine.length()-1 && t == '*' && tempLine[i+1] == '/'){ //checks for end of big comments
          commentBig = false;
        }

        if (t == '\'' || t == '\"'){ //checks for single and double quotes
          if (stack->peek() == '\'' || stack->peek() == '\"'){
            stack->pop();
          } else {
            stack->push(t);
          }
        }
        if (((commentBig == false) && (commentSmall == false) && (stack->peek() != '\'') && (stack->peek() != '\"')) && ((t == '(') || (t == '{') || (t == '[')) ){
          //adds to stack if all requirements are met
          stack->push(t);
        } else if (((commentBig == false) && (commentSmall == false) && (stack->peek() != '\'') && (stack->peek() != '\"')) && ((t == ')') || (t == '}') || (t == ']')) ){
          //checks for mismatch
          char check = stack->pop();
          if ((check == '(') && (t != ')')){
            cout << "Line " << lines << ": Expected ) and found " << t << endl;
            done = true;
            perfect = false;
            break;
          } else if ((check == '{') && (t != '}')){
            cout << "Line " << lines << ": Expected } and found " << t << endl;
            done = true;
            perfect = false;
            break;
          } else if ((check == '[') && (t != ']')){
            cout << "Line " << lines << ": Expected ] and found " << t << endl;
            done = true;
            perfect = false;
            break;
          }
        }
      }
      commentSmall = false;
      lines++;
    }
    char expected = 'a';
    //checks for extra lines
    if (stack->getSize() != 0 && done == false){
      char check = stack->pop();
      perfect = false;
      if (check == '('){
        expected = ')';
      } else if (check == '{'){
        expected = '}';
      } else if (check == '['){
        expected = ']';
      }
      cout << "Reached end of file: missing " << expected << endl;
    }
  }
  else { //could not open file
    cout << "Could not open file." << endl;
  }
  file.close();
  if (commentBig == true){ //checks if */ exists (caused a small error)
    cout << "Could not check your program because you had /* without */" << endl;
  } else if (perfect == true){ //if everything worked out then the program returns a smile
    cout << "Your program is all good :)" << endl;
  }
  delete stack;
}
