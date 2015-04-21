/* Boyer-Moore function implementation: 
 * Based on Brad Green Book, Volume 2, pages 98-100. 
 * The section of building good suffix table in this 
 * implementation is easier to understand, but find()
 * function is a little buggy.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* Based on Listing 10.4 on Page 98.
 * Build the bad character table. */
void make_bad_char_table(const string& needle, vector<int>& table) {
  for (size_t i = 0; i < needle.length() - 1; i++) {
    table[needle[i]] = i;
  }
}

/* Page 98: 
 * "The good suffix table has length equal to the pattern.
 * The table is built up in two passes of the pattern, 
 * scanning from right to left, then left to right. In the
 * first pass, the shift that is stored in table[] insures 
 * that the best known suffix alignment is found. That is, 
 * if k is the best detected prefix of the pattern that starts 
 * at j, then the value stored at position k is m-k+j. 
 * This allows shifting the alignment so the prefix of the 
 * pattern matching the suffix is shifted passes k. The second 
 * pass ensures that the minimum shift is recorded."   
 *
 * dhu note: We build z[] in the same fashion as we do the 
 * table in KMP algorithm. See build_kmp_table().  
 * The key difference is: in KMP, we build the table by scanning 
 * the needle string from left to right, and kmp_table[i] is the 
 * length of the longest prefix of needle that is identical to the 
 * substring that ends at needle[i-1].
 * But in Boyer-Moore, we build z[] by scanning the needle string from 
 * right to left, and z[i] is the starting INDEX of the longest 
 * suffix of needle string that overlaps with the substring 
 * needle[i : (m-1)]. The overlapped section is needle[z[i] : (m-1)].  
 *
 * For example, for needle string "ANPANMAN", we have:
 *
 *      index: 0 1 2 3 4 5 6 7 8
 *    ---------------------------
 *     needle: A N P A N M A N -
 *    ----------------------------
 *        z[]: 6 7 8 6 7 8 8 8 9  (z[i] is always larger than i.)
 *    -----------------------------------------------------------------
 *    table[]: 0 0 0 0 0 0 3 0 1  (during the process of building z[])
 *    ----------------------------------------------------------------
 *    table[]: 6 6 6 6 6 6 3 8 1  (final values)
 *    -------------------------------------------
 *
 * Yet another example:
 *
 *      index: 0 1 2 3 4 5 
 *     needle: A A A A A - 
 *        z[]: 1 2 3 4 5 6 
 *    table[]: 0 0 0 0 0 0   (during the process of building z[])
 *    table[]: 1 1 2 3 4 5   (final values)
 *
 * table[i] is the minimum distance of right shift when needle[i-1] 
 * does not match haystack[], but after right shift, the needle's suffix, 
 * needle[i:(m-1)] will be identical to needle[x:(x+m-i)],
 * in which x = (i - table[i]) >= 0. 
 * For example, table[6] = 3 means:
 *
 *      index: 0 1 2 3 4 |5| 6 7 8                        
 *     needle: A N P A N |M| A N - 
 *                   A N |P| A N M A N (Right shift 3 positions)
 *                           
 * When x < 0, right shifting "table[i]" positions will make the  
 * first (table[i] - i) characters in the suffix needle[i:(m-1)] 
 * align with blank spaces in shifted needle string. 
 * For example, table[5] = 6 means:
 *
 *      index: 0 1 2 3 |4| 5 6 7 8                        
 *     needle: A N P A |N| M A N - 
 *                           A N P A N M A N (right shift 6 positions)
 *
 * So in this scenario, table[i] ensures that needle[table[i] : (m-1)] 
 * is identical to needle[0 : (m-table[i]-1)].
 *
 * In KMP, if we build table[] for reversed needle string "NAMNAPNA",
 * we have:
 *
 *     index:  0 1 2 3 4 5 6 7 8
 *    needle:  N A M N A P N A -
 *     kmp[]: -1 0 0 0 1 2 0 1 2
 * m - kmp[]:  9 8 8 8 7 6 8 7 6
 * 
 * So z[] is actually the reversed version of m - kmp[].
 *
 * When building z[], table[i] is set for table[i] > i.
 * After z[] is built, the other elements in table[] are set. 
 * Note that in this approach, table[0] will be never used.
 * As a matter of fact, we can disgard this element.
 */
void make_good_suffix_table(const string & needle, vector<int>& table) {
  int m = needle.length();
  table.resize(m+1);
  vector<int> z(m+1);
  // Invariant: i < j 
  int i = m;
  int j = m + 1;

  // z[m] will be always m+1, and z[m-1] will be always m.
  z[i] = j;
  while (i > 0) {
    // Since j > i > 0, we have j >= 2. So table[1] and table[0] will 
    // never be set in the following while loop.
    while (j <= m && needle[i - 1] != needle[j - 1]) {
      // When there is a mismatch between needle[i-1] and needle[j-1],
      // and table[j] is not set yet, set table[j] to (j - i).
      // If table[j] is already set, then we can not set table[j] = j - i,
      // because table[j] is the MINIMUM right shift distance. If table[j] 
      // is already set, then table[j] must be less than (j - i).
      //
      // --------------------------- IMPORTANT ---------------------------
      // All elements in table[] that satisfy table[j] < j are set here!
      // -----------------------------------------------------------------
      //
      if (table[j] == 0)
	table[j] = j - i;

      j = z[j]; // DP idea that is also used when building KMP table.
    }

    // At this point, either j > m, or needle[i-1] == needle[j-1], 
    // so we decrement i and j by 1, then set z[i] = j.
    i--, j--;
    z[i] = j;
  }

  // dhu debugging
  //for (unsigned idx = 0; idx < z.size(); idx++) 
  // cout << z[idx] << " " << table[idx] << endl;
  //cout << endl;

  // According to the definition of z[], z[0] is the minimum right shift
  // distance of the needle string so that the overlapping section between 
  // original needle string and shifted needle string are identical. 
  // In this scenario, the overlapping always occurs between needle string's
  // prefix (in right shifted string) and needle string's suffix (in original
  // needle string).
  j = z[0];
  // Invariant: i <= j.
  for (i = 0; i <= m; ++i) {
    // Because table[0] and table[1] were not set when z[] was built,
    // table[0] will be always equal to z[0].
    //
    // ----------------------- IMPORTANT -------------------------------
    // All elements in table[] that satisfy table[i] >= i are set here!
    // -----------------------------------------------------------------
    //
    if (table[i] == 0) 
      table[i] = j;

    // IMPORTANT: When i is equal to j, to ensure that in the next iteration
    // i <= j, increment j to z[j]. The reason why i <= j is because table[i] 
    // is the minimum distance of right shift when there is a mismatch at 
    // needle[i-1]. If i is equal to j and we do not increment j, then in the 
    // next iteration, i becomes i+1. If table[i+1] is not set, we will have:
    // table[i+1] = j = i. But table[i+1] denotes a mismatch at needle[i];
    // On the other hand, j is always equal to z[x], so needle[j] == needle[i].
    // This means we should right shifting more than j positions.
    // For example, consider "ANPANMAN". 
    //
    //      index: 0 1 2 3 4 5 6 7 8
    //     needle: A N P A N M A N -
    //        z[]: 6 7 8 6 7 8 8 8 9  (z[i] is always larger than i.)
    //    table[]: 0 0 0 0 0 0 3 0 1  (during the process of building z[])
    //    table[]: 6 6 6 6 6 6 3 ? ? 
    //
    // When calculating table[6], i = 6, j = 6. Since table[6] has been set 
    // previously, we do nothing with table[6]. If we do not increament j 
    // to z[6] = 8 at the end of this iteration, then when i = 7, j is still 
    // 6, we will have table[7] = 6. But if we right shift needle 6 positions, 
    //
    //      index: 0 1 2 3 4 5 |6| 7 8
    //     needle: A N P A N M |A| N -
    //                         |A| N P A N M A N
    //
    // Since we know that for table[7], needle[6] is a mismatch with haystack,
    // right shifting 6 positions does not change the character of needle 
    // string at that mismatch position, so we should right shift more. 
    // If table[7] is not set yet, the next minimum right shift distance should 
    // be z[6], which is the left-most position so that needle string's prefix
    // is identical to needle string's suffix. 
    if (i == j)
      j = z[j];

    // When i is 0, j = z[0] > 0, so j won't be reset. 
    // Then i becomes 1 in the next iteration, because table[1] 
    // is not set yet, table[1] will be set to z[0] too. 
    // In another word, it is always true that: 
    //      table[0] = table[1] = z[0].
  }

}

/* Page 100, Listing 10.6. 
 * This function calls make_bad_char_table() and 
 * make_good_suffix_table to search sub in str. */
int bm_search(const string& haystack, const string& needle) {
  if (needle.empty())
    return 0;

  vector<int> bad_char(1 << 8, -1); 
  make_bad_char_table(needle, bad_char);

  int m = needle.size();
  int n = haystack.size();
  vector<int> good_suffix(m + 1);
  make_good_suffix_table(needle, good_suffix);

  int i = 0;
  int j = m - 1;
  while (i <= n - m) {
    if (haystack[i + j] == needle[j]) {
      --j;
      if (j < 0)
	return i;
    }
    else {
      i += max(j - bad_char[haystack[i+j]], good_suffix[j+1]);
      j = m - 1;
    }
  }

  return -1;
}

/* dhu comparison: Build table in KMP algorithm. */
void build_kmp_table(const string& needle, vector<int>& table) {
  int m = needle.size();
  table.resize(m + 1);
  // Inititalize table[0] and table[1]
  table[0] = -1;
  if (m > 0)
    table[1] = 0;
  
  int i = 2;
  // cnt is length of the longest prefix of needle that is 
  // identical to the substring that ends at needle[i - 1]. 
  int cnt = 0; 
  while (i < m + 1) {
    if (needle[i - 1] == needle[cnt]) {
      i++;
      cnt++;
      table[i] = cnt;
    }
    else if (cnt > 0)
      cnt = table[cnt];
    else {
      table[i] = 0;
      i++;
    }
  }
}
 
// Test harness
int main() {
  //string needle("ANPANMAN");
  //string needle("BANANA");
  string needle("ABBABBABB");
  vector<int> table;
  make_good_suffix_table(needle, table);
  for (size_t i = 0; i < table.size(); i++) {
    cout << i << ": " << table[i] << endl;
  }

  //string haystack("amandgerxxxanpanmanwertfgheamanpan"); // 8
  //cout << "ans: " << find(str, needle) << endl;
  
  return 0;
}

// Another example:
// 
//   index: 0 1 2 3 4 5 6
//  needle: B A N A N A - 
//     z[]: 6 3 4 5 6 6 7
// table[]: 0 0 0 2 0 4 1 (during the process of building z[])
// table[]: 6 6 6 2 6 4 1 (final values)
// 
