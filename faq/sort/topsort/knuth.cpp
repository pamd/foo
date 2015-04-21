/* Topological sort, C++ code copied from:
 * http://www.mitbbs.com/article_t/JobHunting/31865333.html
 */

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

/* Assume the input graph does not have loops, the following pseudo-code 
 * shows how to get all valid topsort sequences. Based on:  
 * D. E. Knuth and J. L. Szwarcfiter. 
 * "A structured program to generate all topological sorting arrangements",
 * Information Processing Letters, 2:153-157, 1974.
 */

/* To simplify the problem, we assume each node is identified by a unique 
 * digit 0-9, and the nodes that directly depends on it are identified by 
 * a string. */
struct TaskNode {
  TaskNode(char c = 0) : dat(c), in_degree(0) { }
 
  char dat;
  string children;

  // in_degree is the number of nodes that the current node depends on, 
  // aka, nodes that are before this node in topsort.  
  size_t in_degree; 
};

/* Update graph based on an input string. 
 * We also assume that no loop is available. */
void buildGraph(const string& str, TaskNode nodes[]) {
  for (size_t i = 0; i < str.size(); i++) {
    int idx = str[i] - '0';
    if (nodes[idx].dat == 0) 
      nodes[idx].dat = str[i];

    if (i > 0)
      nodes[idx].in_degree++;

    if (i != str.size() - 1) 
      nodes[idx].children.push_back(str[i + 1]);
  }
}

// Print out all valid topsort sequences
// dhu note: instead of using std::deque, we can also use std::list.
void getAllTopSort(deque<TaskNode>& free_nodes, TaskNode nodes[], 
		   vector<char>& seq, size_t node_num) {
  if (free_nodes.size() == 0) {
    if (seq.size() != node_num) {
      cout << "Loop found!" << endl;
      exit(1);
    }

    // Print out current sequence and quit
    for (size_t i = 0; i < seq.size(); i++) 
      cout << seq[i] << " ";
    cout << endl;
    return;
  }

  size_t len = free_nodes.size();
  for (size_t i = 0; i < len; i++) {
    TaskNode tail = free_nodes.back();
    seq.push_back(tail.dat);
    free_nodes.pop_back();
    // Delete edges that starts from tail, and update free_nodes
    for (size_t j = 0; j < tail.children.size(); j++) {
      int idx = tail.children[j] - '0';
      nodes[idx].in_degree--;
      // Add new free nodes to the end of free_nodes
      if (nodes[idx].in_degree == 0)
	free_nodes.push_back(nodes[idx]);
    }

    // Recursively call
    getAllTopSort(free_nodes, nodes, seq, node_num);

    // Remove tail element from sequence
    seq.pop_back();

    // Recover edges that start from tail node
    for (size_t j = 0; j < tail.children.size(); j++) {
      int idx = tail.children[j] - '0';
      nodes[idx].in_degree++;
      // Remove newly added nodes in free_nodes
      if (nodes[idx].in_degree == 1)
	free_nodes.pop_back();
    }
    // Alternatively, we can the following one-liner 
    // to remove newly added nodes in free_nodes:
    //free_nodes.resize(len - 1);

    // Move tail node to the front of free_nodes
    free_nodes.push_front(tail); 
  }
}

// Similar idea to get only one valid topsort sequence
void getOneTopSort(deque<TaskNode>& free_nodes, TaskNode nodes[], 
		   vector<char>& seq, size_t node_num) {
  if (free_nodes.size() == 0) {
    if (seq.size() != node_num) {
      cout << "Loop found!" << endl;
      exit(1);
    }

    for (size_t i = 0; i < seq.size(); i++) 
      cout << seq[i] << " ";
    cout << endl;
    return;
  }

  TaskNode tail = free_nodes.back();
  seq.push_back(tail.dat);
  free_nodes.pop_back();
  for (size_t j = 0; j < tail.children.size(); j++) {
    int idx = tail.children[j] - '0';
    nodes[idx].in_degree--;
    if (nodes[idx].in_degree == 0)
      free_nodes.push_back(nodes[idx]);
  }

  getOneTopSort(free_nodes, nodes, seq, node_num);
}

// Test harness
int main() {
  TaskNode nodes[10];

  /* // Example from Knuth paper
  buildGraph("13", nodes);
  buildGraph("21", nodes);
  buildGraph("24", nodes);
  buildGraph("43", nodes);
  buildGraph("45", nodes);
  */
  // buildGraph("52", nodes);  // Add a loop on purpose

  // dhu test #1
  buildGraph("12", nodes);
  buildGraph("24", nodes);
  buildGraph("34", nodes);

  /*
  // dhu test #2: No any dependencies
  buildGraph("1", nodes);
  buildGraph("2", nodes);
  buildGraph("3", nodes);
  buildGraph("4", nodes);
  buildGraph("5", nodes);
  */

  deque<TaskNode> free_nodes;
  size_t node_num = 0;
  for (int i = 0; i < 10; i++) {
    if (nodes[i].dat) {
      node_num++;
      if (nodes[i].in_degree == 0)
	free_nodes.push_back(nodes[i]);
    }
  }

  vector<char> seq;

  getAllTopSort(free_nodes, nodes, seq, node_num); 

  //getOneTopSort(free_nodes, nodes, seq, node_num); 
  
}
