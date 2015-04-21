/* Given an input string and a dictionary of words, segment the input 
 * string into a space-separated sequence of dictionary words if possible. 
 * For example, if the input string is "applepie" and dictionary contains 
 * a standard set of English words, then we would return the string 
 * "apple pie" as output.
 * Refer to:
 * http://thenoisychannel.com/2011/08/08/retiring-a-great-interview-problem/
 * http://www.mitbbs.com/article_t1/JobHunting/31996705_0_3.html
 * http://www.mitbbs.com/article_t/JobHunting/32006067.html
 */

#include <set>
#include <map>
#include <string>
#include <iostream>

using namespace std;

/* Naive solution, returns any valid word separation. 
 * For example, if input string is "applepie", 
 * output will be "apple pie".
 * Return an empty string if input string can not be separated.
 * Based on java code in noisychannel website "A general solution" part. 
 * Running time: O(2^n).
 */
string SegmentString(const string& input, const set<string>& dict) {
  if (dict.find(input) != dict.end()) 
    return input;

  int len = input.size();
  for (int i = 1; i < len; i++) {
    string prefix = input.substr(0, i);
    if (dict.find(prefix) != dict.end()) {
      string suffix = input.substr(i);
      string segSuffix = SegmentString(suffix, dict); // Recursive call
      if (segSuffix.size()) {
        return prefix + " " + segSuffix;
      }
    }
  }
  return "";
}

/* Effcient solution: based on java code in noisychannel website 
 * "An Efficient Solution" part. 
 * Running time: O(n^2).
 * Here we assume dp and dict can search a key in O(1), although
 * in std::set and std::map, they are actually O(logn). 
 *
 * The DP table is built in top-bottom fashion using recursion.
 * Alternatively, we can do it in bottom-top fashion by scanning 
 * the string either from left to right, or from right to left.
 *
 * Also refer to: epi/12_meta_algorithm/12_word_breaking.cpp
 */
string SegmentString(const string& input, const set<string>& dict,
		     map<string, string>& dp) {
  // The key in dp map is string segment, the value is sepearated
  // version of the key. For example, dp["applepie"] = "apple pie".
  if (dp.find(input) != dp.end())
    return dp[input];

  // Is input a valid single word in dictionary?
  if (dict.find(input) != dict.end()) {
    dp[input] = input;
    return dp[input];
  }

  for (size_t i = 1; i < input.size(); i++) {
    string prefix = input.substr(0, i);
    if (dict.find(prefix) != dict.end()) {
      string suffix = input.substr(i);
      string segSuffix = SegmentString(suffix, dict, dp);
      if (segSuffix.size()) {
	dp[input] = prefix + " " + segSuffix;
	return dp[input];
      }
    }
  }

  dp[input] = "";
  return dp[input];
}

/* A slightly different problem:
 * Suppose we are given a dictionary and a string, what is minimum number
 * of seperators that we will need to divide the string into multiple
 * words in dictionary.
 * Refer to:
 * http://www.mitbbs.com/article_t1/JobHunting/31996705_0_3.html
 */

/* Java code written by noonknow. 
void noonknow_java(String[] args) {
  String dict_str = "app ap le pie apple pie pi ie a b c d e f g h i j
k l m n o p q r s t u v w x y z";
  String tar_str = "applepieie";
  List<String> dict = Arrays.asList(dict_str.split(" "));

  int tar_str_len = tar_str.length();
  int[] cost = new int[tar_str_len + 1];
  cost[0] = 0;
  for (int i = 1; i <= tar_str.length(); ++i) {
    cost[i] = Integer.MAX_VALUE;
    //for all possible cut from 0 to i -1
    for(int possible_cut = i - 1; possible_cut >= 0; --possible_cut) {
      //check if substring is valid. yes, try this cut 
      if(dict.indexOf(tar_str.substring(possible_cut, i)) != -1){
	//if it is better than existing cut, store it
	if(cost[possible_cut] + 1 < cost[i])
	  cost[i] = cost[possible_cut] + 1;
      }
    }
    System.out.println("cost " + i + ": " + (cost[i]));
  }
  System.out.println("min cut is " + (cost[tar_str_len] - 1));
}
*/

// dhu: Build a min_cut[] array from right to left. 
// min_cut[i] keeps track of the minimum number of cuts 
// needed to divide the input string's suffix of lenght i.
int get_min_cut(const string& str, const set<string>& dict) {
  int min_cut[str.size() + 1];
  min_cut[0] = 0;
  for (size_t i = 1; i <= str.size(); i++) {
    // suffix is the substring of the last i chars in input string 
    string suffix = str.substr(str.size() - i);
    // If suffix is a single valid word, set min_cut to 0, 
    // and try the next iteration.
    if (dict.find(suffix) != dict.end()) {
      min_cut[i] = 0;
      continue;
    }

    int tmp_min = -1;
    // Because suffix.size() == i, so i - j will be always > 0.
    for (size_t j = 1; j < suffix.size(); j++) {
      // prefix is the substring of the first j chars in suffix
      string prefix = suffix.substr(0, j);
      if (dict.find(prefix) != dict.end() && min_cut[i - j] != -1) {
	if (tmp_min == -1)
	  tmp_min = 1 + min_cut[i - j];
	else
	  tmp_min = min(tmp_min, 1 + min_cut[i - j]);
      }
    }

    // min_cut[i] is -1 when suffix can not be seperated into valid words. 
    min_cut[i] = tmp_min;
  }

  return min_cut[str.size()];
}

// Test harness
int main() {
  set<string> dict;
  dict.insert("a");
  dict.insert("app");
  dict.insert("apple");
  dict.insert("pie");
  dict.insert("le");
  dict.insert("pi");
  dict.insert("e");
  dict.insert("applepie");

  string str("applepie");
  cout << "min cut: " << get_min_cut(str, dict) << endl;

  return 0;
}
