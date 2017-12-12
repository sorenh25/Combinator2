#include "Combinator.hpp"

using namespace std;

Combinator::Combinator(string inputFile) {
  inputFileName = inputFile;
}

Combinator::~Combinator() {

}

void Combinator::readInputFile() {
  ifstream CombinatorFile;
  CombinatorFile.open(inputFileName.c_str());
  if (!CombinatorFile.is_open()) {
    cerr << " Input File could not be opened" << endl;
    return;
  }

  string line;
  while(!CombinatorFile.eof()) {
    getline(CombinatorFile, line);
    if (line[line.length() - 1] == '\r') {
      line.pop_back();
    }
    if (line.empty()) {
      break;
    }
    if (line[0] == '-') {
      break;
    }
    line = '(' + line + ')';
    inputStrings.push_back(line);
  }
  while(!CombinatorFile.eof()) {
    getline(CombinatorFile, line);
    if (line[line.length() - 1] == '\r') {
      line.pop_back();
    }
    if (line.empty()) {
      break;
    }
    outputStrings.push_back(line);
  }
}

void Combinator::printInput() {
  for (unsigned int i = 0; i < inputStrings.size(); i++) {
    cout << inputStrings[i] << endl;
    cout << outputStrings[i] << endl;
  }
}

bool Combinator::findLeftMost(unsigned int& index, char& function) {
  for (unsigned int i = 0; i < computationString.size(); i++) {
    if (computationString[i] == 'I') {
      if (variablesAvailable(i, 0)) {
        function = 'I';
        index = i;
        return true;
      }
      continue;
    }
    if (computationString[i] == 'K') {
      if (variablesAvailable(i, 2)) {
        function = 'K';
        index = i;
        return true;
      }
      continue;
    }
    if (computationString[i] == 'S') {
      if (variablesAvailable(i, 3)) {
        function = 'S';
        index = i;
        return true;
      }
      continue;
    }
    if (computationString[i] == 'Y') {
      if (variablesAvailable(i, 2)) {
        function = 'Y';
        index = i;
        return true;
      }
      continue;
    }
    if (computationString[i] == 'B') {
      if (variablesAvailable(i, 3)) {
        function = 'B';
        index = i;
        return true;
      }
      continue;
    }
  }
  return false;
}

bool Combinator::variablesAvailable(unsigned int& index, int number) {
  //cout << "Index: " << index << " function: " << computationString[index] << endl;
  string temp = computationString;
  int indexChange = 0;
  int i = index;
  while (i > 0) {
    unsigned int start, end;
    start = i - 1;
    if (start == 0) {
      break;
    }
    if (computationString[start] != '(') {
      break;
    }
    getArgument(start, end);
    if (computationString[start] == '(' && computationString[end] == ')') {
      cut(end, end);
      cut(start, start);
      //cout << "Removing Parenthesis at indices:" << start << end << " => " << computationString << endl;
      indexChange--;
      //cout << "Index " << indexChange << endl;
    }
    else {
      break;
    }
  }
  int temporaryIndex = index + indexChange;
  int argumentCount = 0;
  unsigned int start, end;
  while (argumentCount < number) {
    start = temporaryIndex + 1;
    if (computationString[start] == ')') {
      break;
    }
    getArgument(start, end);
    if (end == computationString.length() - 1) {
      argumentCount++;
      break;
    }
    argumentCount++;
    temporaryIndex = end;
  }
  if (argumentCount == number) {
    index = index + indexChange;
    //cout << "New index = " << index << endl;
    return true;
  }
  else {
    computationString = temp;
    return false;
  }
}

void Combinator::compute() {
  for (unsigned int i = 0; i < inputStrings.size(); i++) {
    computationString = inputStrings[i];
    computeString();
  }
}

void Combinator::computeString() {
  cout << "Computation on: " << computationString << endl;
  unsigned int index = 0;
  char variable, function;
  while (findLeftMost(index, function)) {
    //cout << "Computation based on: " << computationString[index] <<  index << endl;
    variable = computationString[index];
    if (variable == 'I' && function == 'I' ) {
      I(index);
      cout << "=>"<< computationString << endl;
    }
    else if (variable == 'K' && function == 'K') {
      K(index);
      cout << "=>"<< computationString << endl;
    }
    else if (variable == 'S' && function == 'S') {
      S(index);
      cout << "=>"<< computationString << endl;
    }
    else if (variable == 'Y' && function == 'Y') {
      Y(index);
      cout << "=>"<< computationString << endl;
    }
    else if (variable == 'B' && function == 'B') {
      B(index);
      cout << "=>"<< computationString << endl;
    }
    else if (variable != function) {
      cerr << "Variable does not equal function after findLemost" << endl;
      cout << variable << " function " << function << " " << computationString << index << endl;
      return;
    }
  }
  rmSingleElementParenthesis();
  unsigned int start, end;
  bool test = true;
  while (test) {
    start = 0;
    getArgument(start, end);
    if (computationString[start] == '(' && computationString[end] == ')') {
      if (end == computationString.length() - 1) {
        cut(end, end);
        cut(start, start);
        continue;
      }
    }
    test = false;
  }
  cout << "=>"<< computationString << endl;
}

void Combinator::I(unsigned int index) {
  if (computationString[index] != 'I') {
    cerr << "No 'I' to replace " << computationString << endl;
    return;
  }
  computationString.erase(index, 1);
}

void Combinator::K(unsigned int index) {
  unsigned int startIndexOfSecondArgument, endIndexOfSecondArgument;
  startIndexOfSecondArgument = index + 1;
  getArgument(startIndexOfSecondArgument, endIndexOfSecondArgument);
  startIndexOfSecondArgument = endIndexOfSecondArgument + 1;
  getArgument(startIndexOfSecondArgument, endIndexOfSecondArgument);
  cut(startIndexOfSecondArgument, endIndexOfSecondArgument);
  cut(index, index);
}

void Combinator::S(unsigned int index) {
  //cout << index << endl;
  unsigned int startOne, endOne, startTwo, endTwo, startThree, endThree;
  startOne = index + 1;
  //cout << "Start One " << startOne << endl;
  getArgument(startOne, endOne);
  startTwo = endOne + 1;
  //cout << "Start two " << startTwo << endl;
  getArgument(startTwo, endTwo);
  startThree = endTwo + 1;
  //cout << "startThree " << startThree << endl;
  getArgument(startThree, endThree);
  string begin, two, three, end;
  begin = computationString.substr(0, startTwo);
  //cout << "Begin " << begin << endl;
  two = computationString.substr(startTwo, endTwo - startTwo + 1);
  //cout << "Two " << two << endl;
  three = computationString.substr(startThree, endThree - startThree + 1);
  //cout << "Three " << three << endl;
  end = computationString.substr(endThree + 1);
  //cout << "End " << end << endl;
  computationString = begin + three + "(" + two + three + ')' + end;
  //cout << "computationString " << computationString << endl;
  cut(index, index);
  //cout << "computationString " << computationString << endl;
}

void Combinator::Y(unsigned int index) {
  if (computationString[index] != 'Y') {
    cerr << "No 'Y' to replace " << computationString << endl;
    return;
  }
  unsigned int startOne, endOne, startTwo, endTwo;
  startOne = index + 1;
  getArgument(startOne, endOne);
  startTwo = endOne + 1;
  getArgument(startTwo, endTwo);
  string begin, one, two, end;
  begin = computationString.substr(0, startOne);
  one = computationString.substr(startOne, endOne - startOne + 1);
  two = computationString.substr(startTwo, endTwo - startTwo + 1);
  end = computationString.substr(endTwo + 1);
  computationString = begin + one + "(" + 'Y' + one + ')' + two + end;
  cut(index, index);
}

void Combinator::B(unsigned int index) {
  if (computationString[index] != 'B') {
    cerr << "No 'B' to replace " << computationString << endl;
    return;
  }
  unsigned int startOne, endOne, startTwo, endTwo, startThree, endThree;
  startOne = index + 1;
  getArgument(startOne, endOne);
  startTwo = endOne + 1;
  getArgument(startTwo, endTwo);
  startThree = endTwo + 1;
  getArgument(startThree, endThree);
  string begin, two, three, end;
  begin = computationString.substr(0, startTwo);
  two = computationString.substr(startTwo, endTwo - startTwo + 1);
  three = computationString.substr(startThree, endThree - startThree + 1);
  end = computationString.substr(endThree + 1);

  computationString = begin + "(" + two + three + ')' + end;
  cut(index, index);
}

void Combinator::cut(int startIndex, int endIndex) {
  computationString.erase(startIndex, (endIndex - startIndex + 1));
}

void Combinator::getArgument(unsigned int start, unsigned int& end) {
    if (computationString[start] == '(') {
      int parenthasisBalance = 1;
      for (unsigned int j = start + 1; j < computationString.length(); j++) {
        if (computationString[j] == '(') {
          parenthasisBalance++;
        }
        if (computationString[j] == ')') {
          parenthasisBalance--;
        }
        if (parenthasisBalance == 0) {
          end = j;
          return;
        }
      }
    }
    if (computationString[start] == ')') {
      cout << "This is not right. We got an ')'" <<  computationString << endl;
    }
    end = start;
}

void Combinator::rmSingleElementParenthesis() {
  unsigned int start, end;
  for (unsigned int i = 0; i < computationString.length(); i++) {
    if (computationString[i] == '(') {
      start = i;
      getArgument(start, end);
      if (computationString[start] == '(' && computationString[end] == ')') {
        if (end - start == 2) {
          cut(end, end);
          cut(start, start);
        }
      }
    }
    else {
      continue;
    }
  }
}

/*
void Combinator::rmFirstParenthesis() {
  unsigned int start, end;
  start = 0;
  getArgument(start, end);
  if (computationString[start] == '(' && computationString[end] == ')') {
    cut(end, end);
    cut(start, start);
  }
}
*/
