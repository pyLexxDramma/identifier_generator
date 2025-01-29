#include <iostream>
#include "IdentifierGenerator.h"

int main() {
  IdentifierGenerator generator;
  std::string id = "";

  try {

      std::cout << "id = " << id << std::endl;
       for (int i = 0; i < 100; ++i)
       {
           id = generator.GenerateNextIdentifier(id);
           std::cout << "Next id = " << id << std::endl;
        }
  } catch (const std::invalid_argument& e){
      std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}