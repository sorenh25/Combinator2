//main function to instantiate Combinator object and run the Combinator
#include "Combinator.hpp"

int main(int argc, char** argv) {
  Combinator myCombinator(argv[1]);
  myCombinator.readInputFile();
  myCombinator.compute();
}
