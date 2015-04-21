/* Given an array of words and a length L, format the text such that each line 
 * has exactly L characters and is fully (left and right) justified.
 * You should pack your words in a greedy approach; that is, pack as many words 
 * as you can in each line. Pad extra spaces ' ' when necessary so that each line 
 * has exactly L characters.
 * Extra spaces between words should be distributed as evenly as possible. If the 
 * number of spaces on a line do not divide evenly between words, the empty slots 
 * on the left will be assigned more spaces than the slots on the right.
 * For the last line of text, it should be left justified and no extra space is 
 * inserted between words.
 * Note: Each word is guaranteed not to exceed L in length.
 * Corner Cases:
 * A line other than the last line might contain only one word. What should you do 
 * in this case? In this case, that line should be left-justified.
 */

#include <vector>
#include <string>
#include <iostream>

using namespace std;

// 8ms for large dataset
class Solution {
public:
  vector<string> fullJustify(vector<string> &words, int L) {
    vector<string> result;
    size_t len = 0;
    size_t start_idx = 0;
    size_t end_idx = 0;
    for (size_t i = 0; i < words.size(); i++) {
      if (len == 0)
	len = words[i].size();
      else
	len += 1 + words[i].size();

      if (len < (size_t) L) {
	if (i < words.size() - 1)
	  continue;
	else 
	  break;
      }

      if (len == (size_t) L) {
	if (i < words.size() - 1)
	  end_idx = i;
	else
	  break;
      }
      else {
	end_idx = i - 1;
	len -= 1 + words[i].size();
	i--;
      }

      result.push_back(generateLine(words, start_idx, end_idx, L - len));
      start_idx = end_idx + 1;
      len = 0;
    }

    // Deal with the last line, whcih has different requirement
    string lastLine;
    for (size_t i = start_idx; i < words.size() - 1; i++) {
      lastLine += words[i];
      lastLine.push_back(' ');
    }
    lastLine += words.back();
    lastLine += string(L - len, ' ');
    result.push_back(lastLine);

    return result;
  }

  string generateLine(const vector<string> &words, size_t start_idx, size_t end_idx, 
		      int n_padding) {
    string line;
    size_t word_num = end_idx - start_idx + 1;
    if (word_num == 1) {
      line += words[start_idx];
      line += string(n_padding, ' ');
      return line;
    }
      
    size_t space_num = n_padding / (word_num - 1);
    size_t left_extra = n_padding % (word_num - 1);

    for (size_t i = 0; i < left_extra; i++) {
      line += words[start_idx + i];
      line += string(space_num + 2, ' ');
    }

    for (size_t i = left_extra; i < word_num - 1; i++) {
      line += words[start_idx + i];
      line += string(space_num + 1, ' ');
    }

    line += words[end_idx];

    return line;
  }

};


