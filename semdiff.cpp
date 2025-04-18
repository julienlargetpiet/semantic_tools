#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cout << "Files missing";
    return 1;
  } else if (argc < 3) {
    std::cout << "Second file missing";
    return 1;
  };

  std::string sep = " | ";
  if (argc == 4) {
    sep = argv[3];
  };

  std::string name_file1 = argv[1];
  std::string name_file2 = argv[2];

  std::string currow2;
  std::string currow1;
  
  std::fstream file1(name_file1);
  std::fstream file2(name_file2);
  bool comp;
  
  while (getline(file2, currow2)) {
    comp = 0;
    while (getline(file1, currow1)) {
      comp = (currow2 == currow1);
      if (!comp) {
        std::cout << currow1 << sep << "- " << "\n";
      } else {
        break;
      }
    };
    comp = (currow1 == currow2);
    if (comp) {
      std::cout << currow1 << sep << currow2 << "\n"; 
    } else {
      break;
    };
  };
  if (!comp) {
    while (getline(file2, currow2)) {
      std::cout << sep << "+" << currow2 << "\n";
    };
  } else {
    while (getline(file1, currow1)) {
      std::cout << currow1 << sep << "-" << "\n";
    };
  };
  return 0;
}



