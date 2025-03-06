#include <iostream>
#include <vector>
#include <string_view>
#include <fstream>

int main(int argc, char* argv[]) {
  using namespace std::literals;
  unsigned int cnt = 2;
  unsigned int cnt2;
  std::string row_val;
  std::string currow;
  std::vector<unsigned int> vec_idx = {};
  unsigned int row_nb;
  unsigned int stop_row_nb;
  std::string file_name = argv[1];
  std::fstream stream_file(file_name);
  while (cnt < argc) {
    row_val = argv[cnt];
    row_nb = int(row_val[0]) - 48;
    cnt2 = 1;
    while (cnt2 < row_val.length() & row_val[cnt2] != '-') {
      row_nb *= 10;
      row_nb += (int(row_val[0]) - 48);
      cnt2 += 1;
    };
    if (cnt2 < row_val.length()) {
      cnt2 += 1;
      stop_row_nb = int(row_val[cnt2]) - 48;
      cnt2 += 1;
      while (cnt2 < row_val.length()) {
        stop_row_nb *= 10;
        stop_row_nb += (int(row_val[cnt2]) - 48);
        cnt2 += 1;
      };
      while (row_nb <= stop_row_nb) {
        vec_idx.push_back(row_nb);
        row_nb += 1;
      };
    } else {
      vec_idx.push_back(row_nb);
    };
    cnt += 1;
  };
  cnt = 0;
  cnt2 = 0;
  const unsigned int n = vec_idx.size();
  if (n == 0) {
    while (getline(stream_file, currow)) {
      std::cout << cnt << ": " << currow << "\n";
      cnt += 1;
    };
  } else {
    while (getline(stream_file, currow)) {
      if (cnt2 < n) {
        if (cnt == vec_idx[cnt2]) {
          std::cout << cnt << ": " << currow << "\n";
          cnt2 += 1;
        };
      } else {
        return 0;
      };
      cnt += 1;
    };
  };
  return 0;
};


