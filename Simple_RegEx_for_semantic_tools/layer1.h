#include "layer0.h"

std::map<std::vector<std::vector<unsigned int>>, std::vector<std::vector<std::string>>> regex_findr_bgn_low(std::string &searched, std::string &x) {
  std::vector<unsigned int> conditions_idxv = {};
  const unsigned int n = searched.length();
  const unsigned int n2 = x.length();
  unsigned int cnt = 0;
  unsigned int cnt2 = 0;
  unsigned int rtn_lst_cnt;
  unsigned int ref_rep_val;
  bool is_ref = 0;
  bool is_greedy1 = 0;
  std::string cur_searched = "";
  std::string cur_str;
  std::string cur_x = x;
  std::vector<std::vector<unsigned int>> idx_hmn;
  std::vector<std::vector<std::string>> str_hmn;
  std::map<std::vector<unsigned int>, std::map<bool, std::string>> cur_mp;
  std::map<std::vector<unsigned int>, std::map<bool, std::string>>::iterator cur_it;
  std::map<bool, std::string>::iterator rslt_mp;
  std::vector<unsigned int> idx_v;
  std::vector<unsigned int> cur_idx_hmn;
  std::vector<std::string> cur_str_hmn;
  if (searched[0] == '[') {
    cnt = 1;
    while (1) {
      conditions_idxv.push_back(cnt);
      if (searched[cnt] == ']' & searched[cnt - 1] != '\\') {
        break;
      };
      if (searched[cnt + 1] == '-' & searched[cnt] != '\\') {
        cnt += 2;
      };
      if (searched[cnt + 1] == '{') {
        cnt += 1;
        while (searched[cnt] != '}') {
          cnt += 1;
        };
      };
      cnt += 1;
    };
    if (cnt + 1 < n) {
      cnt += 1;
      if (searched[cnt] == '{') {
        is_ref = 1;
        cnt += 1;
        if (searched[cnt] == '+') {
          cnt += 1;
          is_greedy1 = 1;
        };
        ref_rep_val = int(searched[cnt]) - 48;
        cnt += 1;
        while (searched[cnt] != '}') {
          ref_rep_val *= 10;
          ref_rep_val += (int(searched[cnt]) - 48);
          cnt += 1;
        };
      };
    };
    for (cnt = 0; cnt < conditions_idxv.size() - 1; ++cnt) {
      cur_searched = "";
      cur_x = x;
      for (cnt2 = conditions_idxv[cnt]; cnt2 < conditions_idxv[cnt + 1]; ++cnt2) {
        cur_searched.push_back(searched[cnt2]);
      };
      if (is_ref) {
        cur_searched.insert(0, 1, '[');
        cur_searched.push_back(']');
        cur_searched.push_back('{');
        if (is_greedy1) {
          cur_searched.push_back('+');
        };
        cur_searched += std::to_string(ref_rep_val);
        cur_searched.push_back('}');
      };
      cur_mp = regex_findr1sub(cur_searched, cur_x);
      cur_it = cur_mp.begin();
      rslt_mp = cur_it->second.begin();
      cur_idx_hmn = {};
      cur_str_hmn = {};
      if (rslt_mp->first) {
        idx_v = cur_it->first;
        rtn_lst_cnt = idx_v[1];
        cur_str = rslt_mp->second;
        cur_str_hmn.push_back(cur_str);
        cur_idx_hmn.push_back(rtn_lst_cnt);
        cur_x = "";
        for (cnt2 = rtn_lst_cnt + 1; cnt2 < n2; ++cnt2) {
          cur_x.push_back(x[cnt2]);
        };
        while (1) {
          cur_mp = regex_findr1sub(cur_searched, cur_x);
          cur_it = cur_mp.begin();
          rslt_mp = cur_it->second.begin();
          if (rslt_mp->first) {
            idx_v = cur_it->first;
            rtn_lst_cnt += idx_v[1];
            cur_str = rslt_mp->second;
            cur_str_hmn.push_back(cur_str);
            rtn_lst_cnt += 1;
            cur_idx_hmn.push_back(rtn_lst_cnt);
            cur_x = "";
            for (cnt2 = rtn_lst_cnt + 1; cnt2 < n2; ++cnt2) {
              cur_x.push_back(x[cnt2]);
            };
          } else {
            break;
          };
        };
      idx_hmn.push_back(cur_idx_hmn);
      str_hmn.push_back(cur_str_hmn);
      };
    };
  } else {
    cur_searched.push_back(searched[0]);
    if (n > 2) {
      cnt += 1;
      if (searched[cnt] == '-') {
        cur_searched.push_back(searched[1]);
        cur_searched.push_back(searched[2]);
        cnt += 2;
      };
      if (searched[cnt] == '{') {
        cur_searched.push_back('{');
        cnt += 1;
        while (searched[cnt] != '}') {
          cur_searched.push_back(searched[cnt]);
          cnt += 1;
        };
        cur_searched.push_back('}');
      };
    };
    cur_mp = regex_findr1sub(cur_searched, cur_x);
    cur_it = cur_mp.begin();
    rslt_mp = cur_it->second.begin();
    cur_idx_hmn = {};
    cur_str_hmn = {};
    if (rslt_mp->first) {
      idx_v = cur_it->first;
      rtn_lst_cnt = idx_v[1];
      cur_str = rslt_mp->second;
      cur_str_hmn.push_back(cur_str);
      cur_idx_hmn.push_back(rtn_lst_cnt);
      cur_x = "";
      for (cnt2 = rtn_lst_cnt + 1; cnt2 < n2; ++cnt2) {
        cur_x.push_back(x[cnt2]);
      };
      while (1) {
        cur_mp = regex_findr1sub(cur_searched, cur_x);
        cur_it = cur_mp.begin();
        rslt_mp = cur_it->second.begin();
        if (rslt_mp->first) {
          idx_v = cur_it->first;
          rtn_lst_cnt += idx_v[1];
          rtn_lst_cnt += 1;
          cur_str = rslt_mp->second;
          cur_str_hmn.push_back(cur_str);
          cur_idx_hmn.push_back(rtn_lst_cnt);
          cur_x = "";
          for (cnt2 = rtn_lst_cnt + 1; cnt2 < n2; ++cnt2) {
            cur_x.push_back(x[cnt2]);
          };
        } else {
          break;
        };
      };
      idx_hmn.push_back(cur_idx_hmn);
      str_hmn.push_back(cur_str_hmn);
    };
  };  
  return {{idx_hmn, str_hmn}};
};


