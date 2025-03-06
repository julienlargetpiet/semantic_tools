#include<iostream>
#include<vector>
#include<map>

//@I This minimalist RegEx flavor allows basic RegEx features such as:
//@I 
//@I - **or context** which is the set of elements that are inside `[]`, evaluates the expression from left to right 
//@I - **range elements** matches every elements that are between `x-y` acording to the ASCII table
//@I - **repetition** is the number of times a set of elements have to be matched, this is declared inside `{n}` after the set of elements
//@I - **greedyness** allows to match a given number of times a set of elements or more, this is declared by `{+n}` after the set of elements
//@I - '\\' is used to escape special characters, apart when it is in a range context, so `\\-x` or `x-\\` are valid
//@I 
//@I The rule of thumb is to not put same set of elements side to side as the first 2 conditions.
//@I 
//@I In **or context**, do not put set of elements that have commun elements. Convert them to multiple exactly different sets with no commun elements.

//@T regex_findrmid
//@U std::map&lt;std::vector&lt;int&gt;, std::map&lt;bool, std::string&gt;&gt; regex_findrmid(std::string searched, std::string x)
//@X
//@D ReGex dialect that handles break patterns declared as <code>{?pattern}</code>.
//@A searched : is the searche string
//@A x : is the string to search in
//@X
//@E std::string inpt_str = "uuppplchhdcpdedmepp";
//@E std::string searched = "[u{1}]{2}p{3}[lpm]{?p{3}}chh{?mepp}d{?mepp}";
//@E std::map&lt;std::vector&lt;int&gt;, std::map&lt;bool, std::string&gt;&gt; outmp = regex_findrmid(searched, inpt_str);
//@E std::map&lt;std::vector&lt;int&gt;, std::map&lt;bool, std::string&gt;&gt;::iterator it = outmp.begin();
//@E std::vector&lt;int&gt; vec1 = it-&gt;first;
//@E std::map&lt;bool, std::string&gt;::iterator it2b = it-&gt;second.begin();
//@E std::cout &lt;&lt; vec1[0] << "\n";
//@E std::cout &lt;&lt; vec1[1] << "\n";
//@E std::cout &lt;&lt; it2b->first << "\n";
//@E std::cout &lt;&lt; it2b->second << "\n";
//@E 0
//@E 9
//@E 1
//@E "uuppplchhd"
//@E inpt_str = "uouuupeieeeppppiimiooo";
//@E searched = "[p]{4}i{?ooo}i[a-zm]";
//@E outmp = regex_findrmid(searched, x);
//@E it = outmp.begin();
//@E vec1 = it-&gt;first;
//@E it2b = it-&gt;second.begin();
//@E vec1[0] << "\n";
//@E vec1[1] << "\n";
//@E it2b->first << "\n";
//@E it2b->second << "\n";
//@E 11
//@E 17
//@E 1
//@E "ppppiim"
//@X

//@T regex_findr2sub
//@U std::map&lt;std::vector&lt;unsigned int&gt;, std::map&lt;bool, std::string&gt;&gt; regex_findr2sub(std::string &searched, std::string &x)
//@X
//@D This function is used by others more abstract functions. It performs the regex dialect, but only matches if the first characters contiguously respect the search string.
//@A searched : is the search string
//@A x : is the string to search in for patterns
//@X
//@U
//@X

std::map<std::vector<unsigned int>, std::map<bool, std::string>> regex_findr2sub(std::string &searched, std::string &x) {
  char cur_chr;
  unsigned int i = 0;
  unsigned int cnt = 0;
  unsigned int ref_cnt;
  const unsigned int n = searched.length();
  const unsigned int n2 = x.length();
  bool agn;
  bool agn2;
  bool or_state = 0;
  unsigned int ref_int1;
  unsigned int ref_int2;
  bool range_state;
  bool cur_found;
  unsigned int rep_val;
  unsigned int rep_val_cnt;
  unsigned int ref_rep_val = 1;
  unsigned int jump_i;
  unsigned int jump_i2;
  unsigned int cur_lmt;
  unsigned int ref_cur_lmt;
  unsigned int bf_rep_val;
  bool greedy_state1 = 0;
  bool greedy_state2 = 0;
  std::string cur_matched_str = "";
  std::string matched_str = "";
  std::string rtn_str;
  unsigned int lst_cnt;
  unsigned int pre_cnt;
  unsigned int cur_ref_cnt;
  unsigned int cur_ref_i;
  unsigned int temp_i;
  bool is_repetition = 0;
  bool alrd_zero = 0;
  bool or_found_alrd;
  unsigned int cur_idx;
  unsigned int bf_cnt_zero = 0;
  unsigned int bgn_i;
  while (i < n & cnt < n2) {
    greedy_state2 = 0;
    if (searched[i] == '\\') {
      i += 1;
    } else {
      if (searched[i] == '[') {
        or_found_alrd = 0;
        ref_cnt = cnt;
        or_state = 1;
        i += 1;
        bgn_i = i;
        jump_i = i;
        while (searched[jump_i] != ']' & searched[jump_i - 1] != '\\') {
          jump_i += 1;
        };
        jump_i2 = jump_i;
        if (jump_i + 2 < n) {
          if (searched[jump_i + 1] == '{') {
            is_repetition = 1;
            jump_i += 2;
            if (jump_i + 1 < n) {
              if (searched[jump_i] == '+') {
                  greedy_state1 = 1;
                  jump_i += 1;
              };
            } else {
              return {{{0, 0}, {{0, ""}}}};
            };
            if (searched[jump_i] != '}') {
              ref_rep_val = (int(searched[jump_i]) - 48);
              jump_i += 1;
              while (searched[jump_i] != '}') {
                ref_rep_val *= 10;
                ref_rep_val += (int(searched[jump_i]) - 48);
                jump_i += 1;
              };
            } else {
              return {{{0, 0}, {{0, ""}}}};
            };
          };
        };
      };
    };
    rep_val = 1;
    cur_found = 0;
    range_state = 0;
    ref_int1 = int(searched[i]);
    if (i + 1 < n) {
      if (searched[i + 1] == '-') {
        i += 2;
        if (!(i < n)) {
          return {{{0, 0}, {{0, ""}}}};
        };
        range_state = 1;
        ref_int2 = int(searched[i]);
        if (int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2) {
          cur_found = 1;
        };
      } else if (ref_int1 == int(x[cnt])) {
        cur_found = 1;
      };
    } else if (ref_int1 == int(x[cnt])) {
      cur_found = 1;
    };
    cur_matched_str = x[cnt];
    i += 1;
    cnt += 1;
    if (cur_found & i < n) {
      if (searched[i] != '\\') {
        if (searched[i] == '{') {
          is_repetition = 1;
          i += 1;
          if (searched[i] == '+') {
            greedy_state2 = 1;
            i += 1;
          };
          if (searched[i] != '}') {
            rep_val = int(searched[i]) - 48;
            i += 1;
            while (searched[i] != '}') {
              rep_val *= 10;
              rep_val += (int(searched[i]) - 48);
              i += 1;
            };
          } else {
            return {{{0, 0}, {{0, ""}}}};
          };
          i += 1;
        };
      } else {
        i += 1;
      };
      if (greedy_state2 & rep_val == 0) {
        rep_val = 1;
        if (ref_rep_val == 0) {
          ref_rep_val = 1;
        };
      };
      if (greedy_state1 & ref_rep_val == 0) {
        ref_rep_val = 1;
        if (rep_val == 0) {
          rep_val = 1;
        };
      };
      bf_rep_val = rep_val;
      if (range_state & is_repetition & rep_val != 0 & ref_rep_val != 0) {
        agn = 1;
        rep_val *= ref_rep_val;
        rep_val -= 1;
        rep_val_cnt = 0;
        while (rep_val_cnt < rep_val) {
          agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
          if (agn2) {
            cur_matched_str.push_back(x[cnt]);
            if (!(cnt + 1 < n2) & rep_val - rep_val_cnt > 1) {
              agn = 0;
              break;
            } else {
              cnt += 1;
            };
            rep_val_cnt += 1;
          } else {
            agn = 0;
            break;
          };
        };
        if (!agn) {
          cur_found = 0;
        } else if (greedy_state1 || greedy_state2) {
          if (greedy_state1 & greedy_state2) {
            cur_lmt = bf_rep_val * ref_rep_val;
          } else if (greedy_state1) {
            cur_lmt = bf_rep_val;
          } else if (greedy_state2) {
            cur_lmt = ref_rep_val;
          };
          while (agn) {
            rep_val_cnt = 0;
            while (rep_val_cnt < cur_lmt) {
              agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
              if (agn2) {
                cur_matched_str.push_back(x[cnt]);
                if (!(cnt + 1 < n2) & cur_lmt - rep_val_cnt > 1) {
                  agn = 0;
                  break;
                } else {
                  cnt += 1;
                };
                rep_val_cnt += 1;
              } else {
                agn = 0;
                break;
              };
            };
          };
        };
        rep_val = 1;
      } else if (is_repetition & rep_val != 0 & ref_rep_val != 0) {
        agn = 1;
        rep_val *= ref_rep_val;
        rep_val -= 1;
        rep_val_cnt = 0;
        while (rep_val_cnt < rep_val) {
          agn2 = int(x[cnt]) == ref_int1;
          if (agn2) {
            cur_matched_str.push_back(x[cnt]);
            if (!(cnt + 1 < n2) & rep_val - rep_val_cnt > 1) {
              agn = 0;
              break;
            } else {
              cnt += 1;
            };
            rep_val_cnt += 1;
          } else {
            agn = 0;
            break;
          };
        };
        if (!agn) {
          cur_found = 0;
        } else if (greedy_state1 || greedy_state2) {
          if (greedy_state1 & greedy_state2) {
            cur_lmt = bf_rep_val * ref_rep_val;
          } else if (greedy_state1) {
            cur_lmt = bf_rep_val;
          } else if (greedy_state2) {
            cur_lmt = ref_rep_val;
          };
          while (agn) {
            rep_val_cnt = 0;
            while (rep_val_cnt < cur_lmt) {
              agn2 = int(x[cnt]) == ref_int1;
              if (agn2) {
                cur_matched_str.push_back(x[cnt]);
                if (!(cnt + 1 < n2) & cur_lmt - rep_val_cnt > 1) {
                  agn = 0;
                  break;
                } else {
                  cnt += 1;
                };
                rep_val_cnt += 1;
              } else {
                agn = 0;
                break;
              };
            };
          };
        };
        rep_val = 1;
      };
      if (rep_val == 0 || ref_rep_val == 0) {
        cur_found = 0;
      };
    } else {
      if (ref_rep_val == 0) {
        if (cur_found) {
          cur_found = 0;
        } else {
          cur_found = 1;
        };
        if (i + 3 < n) {
          if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
            i += 3;
          } else if (searched[i] == '{' & searched[i + 1] == '+' & searched[i + 2] == '0' & searched[i + 3] == '}') {
            i += 4;
          };
        } else if (i + 3 == n) {
          if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
            i += 3;
          };
        };
      } else if (i + 3 < n) {
        if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
          i += 3;
          rep_val = 0;
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
          };
        } else if (searched[i] == '{' & searched[i + 1] == '+' & searched[i + 2] == '0' & searched[i + 3] == '}') {
          i += 4;
          rep_val = 0;
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
          };
        };
      } else if (i + 3 == n) {
          if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
          i += 3;
          rep_val = 0;
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
          };
        };
      };
    };
    if (or_state) {
      rep_val = 1;
      if (cur_found) {
        ref_cnt = cnt;
        or_found_alrd = 1;
        matched_str += cur_matched_str;
        i = bgn_i;
        if (cur_matched_str != "") {
          lst_cnt = cnt - 1;
        } else {
          lst_cnt = cnt;
        };
      } else {
        if (i == jump_i2) {
          if (!or_found_alrd) {
            return {{{0, 0}, {{0, ""}}}};
          } else {
            cur_found = 1;
            i = jump_i + 1;
            or_state = 0;
            greedy_state1 = 0;
            is_repetition = 0;
            ref_rep_val = 1;
          };
        } else {
          cnt = ref_cnt;
        };
      };
    } else if (!cur_found) {
      return {{{0, 0}, {{0, ""}}}};
    } else {
      matched_str += cur_matched_str;
      if (cur_matched_str != "") {
        lst_cnt = cnt - 1;
      } else {
        lst_cnt = cnt;
      };
      is_repetition = 0;
      rep_val = 1;
    };
  };
  rtn_str = matched_str;
  pre_cnt = lst_cnt - matched_str.length() + 1;
  return {{{pre_cnt, lst_cnt}, 
          {{cur_found, rtn_str}}}}; 
};

//@T regex_findr1sub
//@U std::map&lt;std::vector&lt;unsigned int&gt;, std::map&lt;bool, std::string&gt;&gt; regex_findr1sub(std::string &searched, std::string &x)
//@X
//@D This function is used by others more abstract functions. It performs the regex dialect, but only returns the characters that respect the first condition of the search string.
//@A searched : is the search string
//@A x : is the string to search in for patterns
//@X
//@U
//@X

std::map<std::vector<unsigned int>, std::map<bool, std::string>> regex_findr1sub(std::string searched, std::string x) {
  char cur_chr;
  unsigned int i = 0;
  unsigned int cnt = 0;
  unsigned int ref_cnt;
  unsigned int bf_cnt2;
  unsigned int n = searched.length();
  const unsigned int n2 = x.length();
  bool agn;
  bool agn2;
  unsigned int ref_int1;
  unsigned int ref_int2;
  bool range_state;
  bool cur_found;
  unsigned int rep_val;
  unsigned int rep_val_cnt;
  unsigned int ref_rep_val = 1;
  unsigned int jump_i;
  unsigned int idx_cnt = 0;
  unsigned int cur_lmt;
  unsigned int ref_cur_lmt;
  unsigned int bf_rep_val;
  bool greedy_state1 = 0;
  bool greedy_state2 = 0;
  std::string cur_matched_str = "";
  unsigned int lst_cnt = -1;
  unsigned int pre_cnt;
  unsigned int cur_ref_cnt;
  unsigned int temp_i;
  bool is_repetition = 0;
  unsigned int cur_idx;
  unsigned int bf_cnt_zero = 0;
  if (searched[0] == '[') {
    cnt = 1;
    while (1) {
      if (searched[cnt] == ']' & searched[cnt - 1] != '\\') {
        break;
      };
      cnt += 1;
    };
    idx_cnt = cnt;
    cnt += 1;
    if (cnt < n) {
      if (searched[cnt] == '{') {
        is_repetition = 1;
        cnt += 1;
        if (searched[cnt] != '?') { 
          if (searched[cnt] == '+') {
            greedy_state1 = 1;
            cnt += 1;
          };
          ref_rep_val = int(searched[cnt]) - 48;
          cnt += 1;
          while (searched[cnt] != '}') {
            ref_rep_val *= 10;
            ref_rep_val += (int(searched[cnt]) - 48);
            cnt += 1;
          };
        };
        while (searched[idx_cnt] != '}') {
          searched.erase(searched.begin() + idx_cnt);
          n -= 1;
        };
      };
    };
    searched.erase(searched.begin() + idx_cnt);
    searched.erase(searched.begin());
    n -= 2;
  };
  cnt = 0;
  while (cnt < n2) {
    greedy_state2 = 0;
    if (searched[i] == '\\') {
      i += 1;
    };
    rep_val = 1;
    cur_found = 0;
    range_state = 0;
    ref_int1 = int(searched[i]);
    if (i + 1 < n) {
      if (searched[i + 1] == '-') {
        i += 2;
        if (!(i < n)) {
          return {{{0, 0}, {{0, ""}}}};
        };
        range_state = 1;
        ref_int2 = int(searched[i]);
        while (!cur_found & cnt < n2) {
          cur_found = (int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2);
          cnt += 1;
        };
      } else {
        while (!cur_found & cnt < n2) {
          cur_found = (ref_int1 == int(x[cnt])); 
          cnt += 1;
        };
      };
    } else {
      while (!cur_found & cnt < n2) {
        cur_found = (ref_int1 == int(x[cnt])); 
        cnt += 1;
      };
    };
    bf_cnt2 = cnt;
    cur_matched_str = x[cnt - 1];
    i += 1;
    if (cur_found & i < n) {
      if (searched[i] != '\\') {
        if (searched[i] == '{') {
          is_repetition = 1;
          i += 1;
          if (searched[i] == '+') {
            greedy_state2 = 1;
            i += 1;
          };
          if (searched[i] != '}') {
            rep_val = int(searched[i]) - 48;
            i += 1;
            while (searched[i] != '}') {
              rep_val *= 10;
              rep_val += (int(searched[i]) - 48);
              i += 1;
            };
          } else {
            return {{{0, 0}, {{0, ""}}}};
          };
          i += 1;
        };
      } else {
        i += 1;
      };
      if (greedy_state2 & rep_val == 0) {
        rep_val = 1;
        if (ref_rep_val == 0) {
          ref_rep_val = 1;
        };
      };
      if (greedy_state1 & ref_rep_val == 0) {
        ref_rep_val = 1;
        if (rep_val == 0) {
          rep_val = 1;
        };
      };
      bf_rep_val = rep_val;
      if (range_state & is_repetition & rep_val != 0 & ref_rep_val != 0) {
        agn = 1;
        bf_rep_val = rep_val;
        rep_val *= ref_rep_val;
        rep_val -= 1;
        rep_val_cnt = 0;
        while (rep_val_cnt < rep_val) {
          agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
          if (agn2) {
            cur_matched_str.push_back(x[cnt]);
            if (!(cnt + 1 < n2) & rep_val - rep_val_cnt > 1) {
              agn = 0;
              break;
            } else {
              cnt += 1;
            };
            rep_val_cnt += 1;
          } else {
            agn = 0;
            break;
          };
        };
        if (!agn) {
          cur_found = 0;
        } else if (greedy_state1 || greedy_state2) {
          if (greedy_state1 & greedy_state2) {
            cur_lmt = bf_rep_val * ref_rep_val;
          } else if (greedy_state1) {
            cur_lmt = bf_rep_val;
          } else if (greedy_state2) {
            cur_lmt = ref_rep_val;
          };
          while (agn) {
            rep_val_cnt = 0;
            cur_ref_cnt = cnt;
            while (rep_val_cnt < cur_lmt) {
              agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
              if (agn2) {
                cur_matched_str.push_back(x[cnt]);
                if (!(cnt + 1 < n2) & cur_lmt - rep_val_cnt > 1) {
                  agn = 0;
                  break;
                } else {
                  cnt += 1;
                };
                rep_val_cnt += 1;
              } else {
                agn = 0;
                break;
              };
            };
          };
          cnt = cur_ref_cnt;
        };
        rep_val = 1;
      } else if (is_repetition & rep_val != 0 & ref_rep_val != 0) {
        agn = 1;
        bf_rep_val = rep_val;
        rep_val *= ref_rep_val;
        rep_val -= 1;
        rep_val_cnt = 0;
        while (rep_val_cnt < rep_val) {
          agn2 = int(x[cnt]) == ref_int1;
          if (agn2) {
            cur_matched_str.push_back(x[cnt]);
            if (!(cnt + 1 < n2) & rep_val - rep_val_cnt > 1) {
              agn = 0;
              break;
            } else {
              cnt += 1;
            };
            rep_val_cnt += 1;
          } else {
            agn = 0;
            break;
          };
        };
        if (!agn) {
          cur_found = 0;
        } else if (greedy_state1 || greedy_state2) {
          if (greedy_state1 & greedy_state2) {
            cur_lmt = bf_rep_val * ref_rep_val;
          } else if (greedy_state1) {
            cur_lmt = bf_rep_val;
          } else if (greedy_state2) {
            cur_lmt = ref_rep_val;
          };
          while (agn) {
            rep_val_cnt = 0;
            cur_ref_cnt = cnt;
            while (rep_val_cnt < cur_lmt) {
              agn2 = int(x[cnt]) == ref_int1;
              if (agn2) {
                cur_matched_str.push_back(x[cnt]);
                if (!(cnt + 1 < n2) & cur_lmt - rep_val_cnt > 1) {
                  agn = 0;
                  break;
                } else {
                  cnt += 1;
                };
                rep_val_cnt += 1;
              } else {
                agn = 0;
                break;
              };
            };
          };
          cnt = cur_ref_cnt;
        };
        rep_val = 1;
      };
    } else {
      if (ref_rep_val == 0) {
        if (cur_found) {
          cur_found = 0;
        } else {
          cur_found = 1;
        };
        if (i + 3 < n) {
          if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
            i += 3;
          } else if (searched[i] == '{' & searched[i + 1] == '+' & searched[i + 2] == '0' & searched[i + 3] == '}') {
            i += 4;
          };
        } else if (i + 3 == n) {
          if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
            i += 3;
          };
        };
      } else if (i + 3 < n) {
        if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
          rep_val = 0;
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
          };
          i += 3;
        } else if (searched[i] == '{' & searched[i + 1] == '+' & searched[i + 2] == '0' & searched[i + 3] == '}') {
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
          };
          i += 4;
        };
      } else if (i + 3 == n) {
        if (searched[i] == '{' & searched[i + 1] == '0' & searched[i + 2] == '}') {
          rep_val = 0;
          if (cur_found) {
            cur_found = 0;
          } else {
            cur_found = 1;
          };
          i += 3;
        };
      } else {
        if (cur_found) {
          idx_cnt = 1;
          if (!range_state) {
            while (cur_found & cnt < n2 & idx_cnt < ref_rep_val) {
              cur_found = (ref_int1 == int(x[cnt]));
              cur_matched_str.push_back(x[cnt]);
              cnt += 1;
              if (cur_found) {
                idx_cnt += 1;
              };
            };
            if (idx_cnt == ref_rep_val) {
              cur_found = 1;
            } else {
              cur_found = 0;
            };
            if (greedy_state1 & cur_found) {
              while (cnt < n2) {
                if (ref_int1 == int(x[cnt])) {
                  cur_matched_str.push_back(x[cnt]);
                } else {
                  break;
                };
                cnt += 1;
              };
            };
          } else {
            while (cur_found & cnt < n2 & idx_cnt < ref_rep_val) {
              cur_found = (int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2);
              cur_matched_str.push_back(x[cnt]);
              cnt += 1;
              if (cur_found) {
                idx_cnt += 1;
              };
            };
            if (idx_cnt == ref_rep_val) {
              cur_found = 1;
            } else {
              cur_found = 0;
            };
            if (greedy_state1 & cur_found) {
              while (cnt < n2) {
                if (int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2) {
                  cur_matched_str.push_back(x[cnt]);
                } else {
                  break;
                };
                cnt += 1;
              };
            };
          };
        };
      };
    };
    if (cnt < n2 & cur_found) {
      if (range_state) {
        agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
        if (agn2) {
          for (temp_i = 0; temp_i + 1 < cur_matched_str.length(); ++temp_i) {
            cur_matched_str[temp_i] = cur_matched_str[temp_i + 1];   
          };
          cur_matched_str[cur_matched_str.length() - 1] = x[cnt];
          cnt += 1;
          while (agn2 & cnt < n2) {
            agn2 = int(x[cnt]) >= ref_int1 & int(x[cnt]) <= ref_int2;
            if (agn2) {
              for (temp_i = 0; temp_i + 1 < cur_matched_str.length(); ++temp_i) {
                cur_matched_str[temp_i] = cur_matched_str[temp_i + 1];   
              };
              cur_matched_str[cur_matched_str.length() - 1] = x[cnt];
              cnt += 1;
            };
          };
        };
      } else {
        agn2 = int(x[cnt]) == ref_int1;
        if (agn2) {
          cnt += 1;
          while (agn2 & cnt < n2) {
            agn2 = int(x[cnt]) == ref_int1;
            if (agn2) {
              cnt += 1;
            };
          };
        };
      };
    };
    if (rep_val == 0 || ref_rep_val == 0) {
      if (bf_cnt_zero + 1 < bf_cnt2) {
        if (bf_cnt2 > 1) {
          if (bf_cnt2 < n2) {
            lst_cnt = bf_cnt2 - 2;
          } else {
            lst_cnt = bf_cnt2 - 1;
          };
          cur_matched_str = x[lst_cnt];
          pre_cnt = lst_cnt;
          cur_found = 1;
          break;
        };
      };
      bf_cnt_zero = cnt;
    };
    if (cur_found & rep_val != 0 & ref_rep_val != 0) {
      lst_cnt = cnt - 1;
      pre_cnt = cnt - cur_matched_str.length();
      break;
    };
    i = 0;
  };
  if (lst_cnt == -1) {
    return {{{0, 0}, {{0, ""}}}};
  };
  return {{{pre_cnt, lst_cnt}, 
          {{cur_found, cur_matched_str}}}}; 
};

//@T regex_findr_first_condition_idx
//@U int regex_findr_first_condition_idx(std::string searched)
//@X
//@D Returns the index of the character where the second condition is sensed to begin. Used by more abstract functions.
//@A searched : is the search string
//@X
//@E
//@X

int regex_findr_first_condition_idx(std::string searched) {
  const unsigned int n = searched.length();
  unsigned int cnt = 0;
  unsigned int cur_par;
  if (searched[cnt] == '[') {
    while (searched[cnt] != ']') {
      cnt += 1;
    };
    cnt += 1;
  } else {
    cnt += 1;
    if (cnt < n) {
      if (searched[cnt] == '-') {
        cnt += 2;
      };
    } else {
      return cnt;
    };
  };
  if (!(cnt < n)) {
    return cnt;
  } else if (searched[cnt] == '{') {
    cnt += 1;
    if (searched[cnt] == '?') {
      cnt += 1;
      cur_par = 1;
      while (1) {
        if (searched[cnt] == '}' & searched[cnt - 1] != '\\') {
          cur_par -= 1;
          if (cur_par == 0) {
            break;
          };
        } else if (searched[cnt] == '{' & searched[cnt - 1] != '\\') {
          cur_par += 1;
        };
        cnt += 1;
      };
    } else {
      while (searched[cnt] != '}') {
        cnt += 1;
      };
    };
    cnt += 1;
    return cnt;
  } else {
    return cnt;
  };
};

std::vector<std::vector<unsigned int>> Parser_tokenizer_full(std::string &x, char frst_chr = '(', char scd_chr = ')') {
  std::vector<unsigned int> num_par;
  std::vector<int> cur_val;
  std::vector<unsigned int> idx_vec;
  int i2;
  unsigned int cur_num = 0;
  const unsigned int n = x.length();
  bool alrd;
  for (int i = 0; i < n; ++i) {
    if (x[i] == frst_chr) {
      idx_vec.push_back(i);
      num_par.push_back(0);
      for (i2 = 0; i2 < cur_val.size(); ++i2) {
        cur_val[i2] += 1;
      };
      cur_val.push_back(1);
    } else if (x[i] == scd_chr) {
        idx_vec.push_back(i);
        i2 = cur_val.size() - 1;
        num_par.push_back(0);
        cur_val.push_back(1);
        alrd = 0;
        while (i2 > -1) {
          cur_val[i2] -= 1;
          if (cur_val[i2] == 0 & !alrd) {
            num_par[i2] = cur_num;
            num_par[num_par.size() - 1] = cur_num;
            cur_val[cur_val.size() - 1] = 0;
            cur_num += 1;
            alrd = 1;
          };
          i2 -= 1;
        };
    };
  };
  return {num_par, idx_vec};
};


template <typename T> std::vector<T> sort_ascout(const std::vector<T> &x) {
  std::vector<T> rtn = x;
  const unsigned int n = x.size();
  int i = 1;
  T ref;
  while (i < n) {
    if (rtn[i] < rtn[i - 1]) {
      ref = rtn[i];
      rtn[i] = rtn[i - 1];
      rtn[i - 1] = ref;
      if (i > 1) {
        i -= 1;
      } else {
        i += 1;
      };
    } else {
      i += 1;
    };
  };
  return rtn;
};

template <typename T, typename T2> unsigned int match(const std::vector<T> &source, const T2 &ptrn) {
  int cnt = 0;
  for (typename std::vector<T>::const_iterator i = source.begin(); i != source.end(); ++i) {
    if (*i == ptrn) {
      return cnt;
    };
    cnt += 1;
  };
  return -1;
};

bool is_intricated (unsigned int &idx, std::vector<unsigned int> &tkn_v) {
  std::vector<int> alrd_tkn = {};
  unsigned int i;
  unsigned int i2;
  unsigned int cur_tkn;
  if (idx == 0) {
    return 0;
  };
  for (i = 0; i < idx + 1; ++i) {
    alrd_tkn.push_back(tkn_v[i]);
  };
  i = 0;
  const unsigned int n2 = alrd_tkn.size();
  while (i + 1 < n2) {
    if (alrd_tkn[i] != -1) {
      cur_tkn = alrd_tkn[i];
      i2 = i + 1;
      while (1) {
        if (i2 == n2) {
          return 1;
        } else if (cur_tkn == alrd_tkn[i2]) {
          alrd_tkn[i2] = -1;
          break;
        };
        i2 += 1;
      };
    };
    i += 1;
  };
  return 0;
};


