#include "Simple_RegEx_for_semantic_tools/layer4.h"
#include <string_view>

int main(int argc, char** argv) {
  using namespace std::literals;
  std::string cur_str;
  std::string matched_str;
  std::string searched = argv[1];
  std::string pre_str;
  std::string post_str;
  unsigned int cnt = 2;
  unsigned int cnt2;
  std::map<std::vector<int>, std::map<bool, std::string>> out_mp;
  std::map<std::vector<int>, std::map<bool, std::string>>::iterator out_it;
  std::map<bool, std::string>::iterator rslt_it;
  std::vector<int> idx_v;
  int pre_cnt;
  int post_cnt;
  std::string row_nb_str;
  unsigned int row_nb;
  unsigned int stop_row_nb;
  std::vector<unsigned int> vec_idx = {};
  while (cnt < argc) {
    row_nb_str = argv[cnt];
    row_nb = int(row_nb_str[0]) - 48;
    cnt2 = 1;
    while (cnt2 < row_nb_str.length() & row_nb_str[cnt2] != '-') {
      row_nb *= 10;
      row_nb += (int(row_nb_str[cnt2]) - 48);
      cnt2 += 1;
    };
    if (cnt2 < row_nb_str.length()) {
      cnt2 += 1;
      stop_row_nb = int(row_nb_str[cnt2]) - 48;
      cnt2 += 1;
      while (cnt2 < row_nb_str.length()) {
        stop_row_nb *= 10;
        stop_row_nb += (int(row_nb_str[cnt2]) - 48);
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
  const unsigned int n = vec_idx.size();
  cnt = 0;
  unsigned int cnt3 = 0;
  if (n == 0) {
    while (std::cin) {
      std::getline(std::cin, cur_str);
      if (cur_str.length() > 0) {
        out_mp = regex_search(searched, cur_str);
        out_it = out_mp.begin();
        rslt_it = out_it->second.begin();
        if (rslt_it->first) {
          cnt2 = 0;
          idx_v = out_it->first;
          pre_cnt = idx_v[0];
          post_cnt = idx_v[1];
          matched_str = rslt_it->second;
          pre_str = "";
          while (cnt2 < pre_cnt) {
            pre_str.push_back(cur_str[cnt2]);
            cnt2 += 1;
          };
          post_str = "";
          cnt2 = post_cnt + 1;
          while (cnt2 < cur_str.length()) {
            post_str.push_back(cur_str[cnt2]);
            cnt2 += 1;
          };
          std::cout << cnt << ": " << pre_str;
          std::cout << "\033[1;31m" << matched_str << "\033[0m";
          std::cout << post_str << "\n";
        };
      };
      cnt += 1;
    };
  } else {
    while (std::cin) {
      std::getline(std::cin, cur_str);
      if (cur_str.length() > 0) {
        if (cnt3 < n) {
          if (cnt == vec_idx[cnt3]) {
            out_mp = regex_search(searched, cur_str);
            out_it = out_mp.begin();
            rslt_it = out_it->second.begin();
            if (rslt_it->first) {
              cnt2 = 0;
              idx_v = out_it->first;
              pre_cnt = idx_v[0];
              post_cnt = idx_v[1];
              matched_str = rslt_it->second;
              pre_str = "";
              while (cnt2 < pre_cnt) {
                pre_str.push_back(cur_str[cnt2]);
                cnt2 += 1;
              };
              post_str = "";
              cnt2 = post_cnt + 1;
              while (cnt2 < cur_str.length()) {
                post_str.push_back(cur_str[cnt2]);
                cnt2 += 1;
              };
              std::cout << cnt << ": " << pre_str;
              std::cout << "\033[1;31m" << matched_str << "\033[0m";
              std::cout << post_str << "\n";
            };
            cnt3 += 1;
          };
        } else {
          return 0;
        };
      };
      cnt += 1;
    };
  };
  return 0;
};


