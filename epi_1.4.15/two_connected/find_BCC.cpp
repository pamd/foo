/* Variant 16.4.1 Part 3: Let G be a connected graph. A biconnected component (BCC) 
 * of G is a maximal set of edges having the property that any two edges in the set 
 * lie on common simple cycle. Design algorithms for computing BCCs.
 *
 * According to this page:
 *    http://en.wikipedia.org/wiki/Biconnected_graph
 * A BCC should not have any articulation point, so an articulation point 
 * in input graph will be on multiple BCCs. That said, we can not
 * simply find bridge edges first, then remove bridges and return the 
 * remaining components as BCCs. See the figure in:
 *    http://en.wikipedia.org/wiki/Biconnected_component
 * 
 * The following lecture talks about finding BCCs:
 *    https://www.cs.purdue.edu/homes/ayg/CS251/slides/chap9d.pdf
 * (Locally saved as purdure_chap9d.pdf)  
 * 
 * Pseudo code on finding BCCs:
 *    http://www.ics.uci.edu/~dan/class/161/notes/8/Bicomps.html
 *
 */

 /* Detailed pseudo code based on:
 * -------------------------------------------------------------
 *  http://www.cs.umd.edu/class/fall2005/cmsc451/biconcomps.pdf
 * (Locally saved as: umd_biconcomps.pdf  
 *
 */

