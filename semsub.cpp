#include "Simple_RegEx_for_semantic_tools/layer5.h"
#include <string_view>
#include <fstream>

int main(int argc, char** argv) {
  using namespace std::literals;
  std::string currow;
  std::string all_text;
  std::string file_name = argv[1];
  std::fstream stream_file(file_name);
  std::string searched = argv[2];
  std::string replacer = argv[3];
  std::string cur_nb;
  unsigned int cnt = 4;
  unsigned int cnt2;
  unsigned int stop_row_val;
  unsigned int row_val;
  std::vector<unsigned int> vec_idx = {};
  while (cnt < argc) {
    cur_nb = argv[cnt];
    row_val = int(cur_nb[0]) - 48;
    cnt2 = 1;
    while (cnt2 < cur_nb.length() & cur_nb[cnt2] != '-') {
      row_val *= 10;
      row_val += int(cur_nb[cnt2]) - 48;
      cnt2 += 1;
    };
    if (cnt2 < cur_nb.length()) {
      cnt2 += 1;
      stop_row_val = int(cur_nb[cnt2]) - 48;
      cnt2 += 1;
      while (cnt2 < cur_nb.length()) {
        stop_row_val *= 10;
        stop_row_val += int(cur_nb[cnt2]) - 48;
        cnt2 += 1;
      };
      while (row_val <= stop_row_val) {
        vec_idx.push_back(row_val);
        row_val += 1;
      };
    } else {
      vec_idx.push_back(row_val);      
    };
    cnt += 1;
  };
  const unsigned int n = vec_idx.size();
  if (vec_idx.size() == 0) { 
    while (getline(stream_file, currow)) {
      regex_subin_all(searched, replacer, currow);
      all_text += currow;
      all_text.push_back('\n');
    };
  } else {
    cnt = 0;
    cnt2 = 0;
    while (getline(stream_file, currow)) {
      if (cnt2 < n) {
        if (cnt == vec_idx[cnt2]) {
          regex_subin_all(searched, replacer, currow);
          cnt2 += 1;
        };
      };
      all_text += currow;
      all_text.push_back('\n');
      cnt += 1;
    };
  };
  std::fstream out_file(file_name, std::ios::out);
  out_file << all_text;
  out_file.close();
  return 0;
};


