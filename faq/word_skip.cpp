/* Google phone question:
Given a dictionary and a string, write a program to output the valid words 
while minimizing the numbers of skipped characters. The substring that 
consists of a valid word in the dictionary may swap the characters. For 
example, Given a dictionary d = {window, cat} and a string "iwndowdcta", the
output is "window cat". In this case, there is only one number of skipped 
character which is 'd'. 
Refer to:
http://www.mitbbs.com/article_t/JobHunting/32104785.html
*/

// Java code by DataMining
static String word2Anagram(final String word) {
        if (word == null) {
            return null;
        }
        
        int ht[] = new int[256];
        for (int i = 0; i < word.length(); ++i) {
            int charVal = (int) word.charAt(i);
            ht[charVal] ++;
        }
        
        StringBuilder anagram = new StringBuilder();
        for (int i = 0; i < ht.length; ++i) {
            if (ht[i] > 0) {
                anagram.append((char)i).append(ht[i]);
            }
        }
        
        return anagram.toString();
    }
    
    static Map<String, List<String>> dict2Anagram(final Set<String> dict) {
        if (dict == null) {
            return null;
        }
        final Map<String, List<String>> anagrams = new HashMap<String, List<
String>>();
        for (final String word : dict) {
            final String anagram = word2Anagram(word);
            if (anagrams.containsKey(anagram)) {
                anagrams.get(anagram).add(word);
            } else {
                List<String> words = new ArrayList<String>();
                words.add(word);
                anagrams.put(anagram, words);
            }
        }
        
        return anagrams;
    }
    
    /*
     *     
Given a dictionary and a string, write a program to output the valid words
while minimizing the numbers of skipped characters. The substring that
consists of a valid word in the dictionary may swap the characters. For
example, Given a dictionary d = {window, cat} and a string "iwndowdcta", the
output is "window cat". In this case, there is only one number of skipped
character which is 'd'.   
     * */
    static int findValidWordsWithMinSkip (final String input, final Set<
String> dict)  {
        if (input == null) {
            throw new IllegalArgumentException("");
        }
        final Map<String, List<String>> anagrams = dict2Anagram(dict);
        int dp[] = new int[input.length() + 1];
        
        for (int i = 1; i <= input.length(); ++i) {
            int min = Integer.MAX_VALUE;
            for (int j = 0; j < i; ++j) {
                final String anagram = word2Anagram(input.substring(j, i));
                if (anagrams.containsKey(anagram)) {
                    if (min > dp[j]) {
                        min = dp[j];
                    }
                } else {
                    if (min > dp[j] + i - j) {
                        min = dp[j] + i - j;
                    }
                }
            }
            dp[i] = min;
        }
        
        
        return dp[input.length()];
    }
    
    static void testFindValidWordsWithMinSkip () {
        Set<String> dict = new HashSet<String>();
        dict.add("window");
        dict.add("cat");
        
        String input = "iwndowdcta";
        System.out.println(findValidWordsWithMinSkip(input, dict));
    }

//Backtracking, by DataMining
static class DPElement {
        int value;
        int prevCostIdx; // 0-based cost idx
        int takenThisElement; // 0/1, indicating whether taking current 
element, idx 0 based.
        public DPElement() {
            value = 0;
            prevCostIdx = 0;
            takenThisElement = 0;
        }
    }
    static String word2Anagram(final String word) {
        if (word == null) {
            return null;
        }
        
        int ht[] = new int[256];
        for (int i = 0; i < word.length(); ++i) {
            int charVal = (int) word.charAt(i);
            ht[charVal] ++;
        }
        
        StringBuilder anagram = new StringBuilder();
        for (int i = 0; i < ht.length; ++i) {
            if (ht[i] > 0) {
                anagram.append((char)i).append(ht[i]);
            }
        }
        
        return anagram.toString();
    }
    
    static Map<String, List<String>> dict2Anagram(final Set<String> dict) {
        if (dict == null) {
            return null;
        }
        final Map<String, List<String>> anagrams = new HashMap<String, List<
String>>();
        for (final String word : dict) {
            final String anagram = word2Anagram(word);
            if (anagrams.containsKey(anagram)) {
                anagrams.get(anagram).add(word);
            } else {
                List<String> words = new ArrayList<String>();
                words.add(word);
                anagrams.put(anagram, words);
            }
        }
        
        return anagrams;
    }
    
    /*
     *     
Given a dictionary and a string, write a program to output the valid words
while minimizing the numbers of skipped characters. The substring that
consists of a valid word in the dictionary may swap the characters. For
example, Given a dictionary d = {window, cat} and a string "iwndowdcta", the
output is "window cat". In this case, there is only one number of skipped
character which is 'd'.   
     * */
    static List<String> findValidWordsWithMinSkip (final String input, final
Set<String> dict)  {
        if (input == null) {
            throw new IllegalArgumentException("");
        }
        final Map<String, List<String>> anagrams = dict2Anagram(dict);
        DPElement dp[] = new DPElement[input.length() + 1];
        for (int i = 0; i < dp.length; ++i) {
            dp[i] = new DPElement();
        }
        for (int i = 1; i <= input.length(); ++i) {
            int min = Integer.MAX_VALUE;
            int minIdx = -1;
            for (int j = 0; j < i; ++j) {
                final String anagram = word2Anagram(input.substring(j, i));
                if (anagrams.containsKey(anagram)) {
                    if (min > dp[j].value) {
                        min = dp[j].value;
                        minIdx = j;
                    }
                } else {
                    if (min > dp[j].value + i - j) {
                        min = dp[j].value + i - j;
                        minIdx = j;
                    }
                }
            }
            dp[i].value = min;
            dp[i].prevCostIdx = minIdx;
        }
        
        List<String> words = new ArrayList<String>();
        int idx = input.length();
        while (idx > 0) {
            int prevIdx = dp[idx].prevCostIdx;
            if (dp[idx].value == dp[prevIdx].value) {
                words.addAll(anagrams.get(word2Anagram(input.substring(
prevIdx, idx))));
            }
            idx = prevIdx;
        }
        return words;
    }
    
    static void testFindValidWordsWithMinSkip () {
        Set<String> dict = new HashSet<String>();
        dict.add("window");
        dict.add("cat");
        dict.add("act");
        dict.add("widnow");
        
        String input = "iwndowdcta";
        System.out.println(findValidWordsWithMinSkip(input, dict));
    }


// redknight
string minSkip(vector<string>& dictionary, string& str) {
    multimap<string, string> ana2word;
    size_t maxLength = 0;
    for (size_t i = 0; i < dictionary.size(); ++i) {
        string s = dictionary[i];
        sort(s.begin(), s.end());
        ana2word.insert(pair<string, string>(s, dictionary[i]));
        maxLength = max(maxLength, s.size());
    }
    vector<int> minSkips(str.size() + 1, INT_MAX);
    vector<string> validWords(str.size() + 1);
    minSkips[0] = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if (minSkips[i] + 1 < minSkips[i + 1]) {
            minSkips[i + 1] = minSkips[i] + 1;
            validWords[i + 1] = " ";
        }
        for (size_t n = 1; n <= min(maxLength, str.size() - i); ++n) {
            string s = str.substr(i, n);
            sort(s.begin(), s.end());
            multimap<string, string>::iterator it = ana2word.find(s);
            if (it != ana2word.end() && minSkips[i] < minSkips[i + n]) {
                minSkips[i + n] = minSkips[i];
                validWords[i + n] = it->second;
            }
        }
    }
    string rtn;
    for (size_t i = str.size(); i > 0; i -= validWords[i].size())
        if (validWords[i] != " ")
            rtn = validWords[i] + " " + rtn;
    return rtn;
}
