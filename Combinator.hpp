
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Combinator {
public:
  Combinator(std::string);
  ~Combinator();

  void readInputFile();
  void printInput();
  bool findLeftMost(unsigned int&, char& function);
  bool variablesAvailable(unsigned int& index, int number);
  void compute();
  void computeString();

  void I(unsigned int index);
  void K(unsigned int index);
  void S(unsigned int index);
  void Y(unsigned int index);
  void B(unsigned int index);

  void getArgument(unsigned int start, unsigned int& end);
  void cut(int, int);
  void rmSingleElementParenthesis();
  //void rmFirstParenthesis();

private:
  std::string inputFileName;
  std::vector<std::string> inputStrings;
  std::vector<std::string> outputStrings;
  std::string computationString;
};
