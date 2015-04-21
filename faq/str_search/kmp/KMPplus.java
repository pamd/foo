/***************************************************************
 *  dhu note: This is an improved version that takes time and 
 *  space proportional to M + N (independent of the alphabet 
 *  size R). It is different from approaches found in wikipedia 
 *  and Topcoder tutorials.
 *  
 *  Downloaded from algs4 website:
 *  http://algs4.cs.princeton.edu/53substring/KMPplus.java.html
 * 
 *  Mentioned on ALGS4 website at:
 *  http://algs4.cs.princeton.edu/53substring/
 * 
 *  Compilation:  javac KMPplus.java
 *  Execution:    java  KMPplus pattern text
 * 
 *  Knuth-Morris-Pratt algorithm over UNICODE alphabet.
 *
 *  % java KMPplus ABABAC BCBAABACAABABACAA
 *  text:    BCBAABACAABABACAA
 *  pattern:          ABABAC
 *
 *  % java KMPplus aabaaaba ccaabaabaabaaabaab
 *  text:    ccaabaabaabaaabaab
 *  pattern:         aabaaaba
 *
 *  % java KMPplus aabaaabb ccaabaabaabaaabaab
 *  text:    ccaabaabaabaaabaab
 *  pattern:                   aabaaabb
 *
 ***************************************************************/

public class KMPplus {
    private String pattern;
    private int[] next;

    // Create Knuth-Morris-Pratt NFA from pattern
    public KMPplus(String pattern) {
        this.pattern = pattern;
        int M = pattern.length();

	// next[i] points to the next automaton state 
        next = new int[M];

	/* Original implementation
        int j = -1;
        for (int i = 0; i < M; i++) {
            if (i == 0) 
		next[i] = -1;
            else if (pattern.charAt(i) != pattern.charAt(j)) 
		next[i] = j;
            else  
		next[i] = next[j];

            while (j >= 0 && pattern.charAt(i) != pattern.charAt(j)) 
                j = next[j];
            j++;
        }
	*/

	// dhu revision to make the code easier to understand
	// This implementation uses NFA instead of DFA. 
	// See the graphs in UC Irvine tutorial:
	// http://www.ics.uci.edu/~eppstein/161/960227.html

	next[0] = -1;  // next[0] is always 0

	// j keeps track of the longest overlap between
        int j = 0; 
        for (int i = 1; i < M; i++) {
	    // If pattern[i] is equal to pattern[j], follow next[j].
            if (pattern.charAt(i) == pattern.charAt(j)) { 
		next[i] = next[j];
	    }

	    // If pattern[i] is not equal to pattern[j], instead of 
	    // finding where pattern[i] should match, go back to 
	    // previous match position. So this is NON-deterministic
	    // finite state automaton. 
            else { 
		next[i] = j;
		// Move j back to where the match is
		while (j >= 0 && pattern.charAt(i) != pattern.charAt(j)) 
		    j = next[j];
	    }

	    // No matter pattern[i] is equal or not equal to pattern[j],
	    // increment j by 1. 
	    j++;
        } 

	// Print out KMP table (for debugging only)
        for (int i = 0; i < M; i++)
            StdOut.println("next[" + i + "] = " + next[i]);
    }

    // Return offset of first occurrence of text in pattern (or N if no match)
    // simulate the NFA to find match
    public int search(String text) {
        int M = pattern.length();
        int N = text.length();
        int i, j;
        for (i = 0, j = 0; i < N && j < M; i++) {
            while (j >= 0 && text.charAt(i) != pattern.charAt(j))
                j = next[j];
            j++;
        }

        if (j == M) 
	    return i - M;

        return N;
    }

    // Test client
    public static void main(String[] args) {
        String pattern = args[0];
        String text    = args[1];
        int M = pattern.length();
        int N = text.length();

        // substring search
        KMPplus kmp = new KMPplus(pattern);
	int offset = kmp.search(text);

        // print results
        StdOut.println("text:    " + text);
        StdOut.print("pattern: ");
        for (int i = 0; i < offset; i++)
            StdOut.print(" ");
        StdOut.println(pattern);
    }

}

/*
  next[0] = -1
  next[1] = 0
  next[2] = -1
  next[3] = 0
  next[4] = -1
  next[5] = 3
  text:    BCBAABACAABABACAA
  pattern:          ABABAC
*/