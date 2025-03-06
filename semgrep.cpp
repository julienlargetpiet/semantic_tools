#include "Simple_RegEx_for_semantic_tools/layer4.h"
#include <string_view>

int main(int argc, char** argv) {
  using namespace std::literals;
  std::string cur_str;
  std::string matched_str;
  std::string searched = argv[1];
  std::string pre_str;
  std::string post_str;
  unsigned int cnt = 0;
  unsigned int cnt2;
  std::map<std::vector<int>, std::map<bool, std::string>> out_mp;
  std::map<std::vector<int>, std::map<bool, std::string>>::iterator out_it;
  std::map<bool, std::string>::iterator rslt_it;
  std::vector<int> idx_v;
  int pre_cnt;
  int post_cnt;
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
  return 0;
};


