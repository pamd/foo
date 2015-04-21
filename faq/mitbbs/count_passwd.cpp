/* Count password based on:
 * 1 2 3
 * 4 5 6
 * 7 8 9
 *
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32123235.html
 */

#include <iostream>
#include <vector>

using namespace std;

/*
// Code by flier0
void print(int* set, int size) {
  for (int i = 0; i < size && set[i] > 0; i++)
    cout << set[i];
  cout << endl;
}

int PadPathNum(const vector<vector<int> >& graph, int num, int first) {
  static int path_num = 0;
  static int visit[9] = {0};
  static int set[9] = {0};
  static int index = 0;

  visit[first] = 1;
  set[index++] = first + 1;
  print(set, num);

  path_num++;

  for (int i = 0; i < num; i++)
    if (graph[first][i] == 1 && visit[i] == 0)
      PadPathNum(graph, num, i);

  visit[first] = 0;
  set[--index] = 0;
  
  return path_num;
}
*/

/* Passwd that starts from 1
1
12
123
1235
12354
123547
1235478
12354786
123547869
12354789
123547896
123548
1235486
12354869
1235487
1235489
12354896
12356
123568
1235684
12356847
1235687
*/

// dhu
int count(int start, const vector<vector<int> >& graph, 
	  string& passwd, bool used[9]) {
  if (used[start])
    return 0;

  int ret = 1;
  passwd.push_back('0' + start);
  cout << passwd << endl;
  used[start] = true;
  for (size_t i = 0; i < graph[start].size(); i++)
    ret += count(graph[start][i], graph, passwd, used);

  passwd.resize(passwd.size() - 1);
  used[start] = false;

  return ret;
}
  
// Graph is hard-coded
void buildGraph(vector<vector<int> >& graph) {
  graph[1].push_back(2);
  graph[1].push_back(4);
  graph[1].push_back(5);

  graph[2].push_back(1);
  graph[2].push_back(3);
  graph[2].push_back(4);
  graph[2].push_back(5);
  graph[2].push_back(6);

  graph[3].push_back(2);
  graph[3].push_back(5);
  graph[3].push_back(6);

  graph[4].push_back(1);
  graph[4].push_back(7);
  graph[4].push_back(2);
  graph[4].push_back(5);
  graph[4].push_back(8);

  graph[5].push_back(1);
  graph[5].push_back(2);
  graph[5].push_back(3);
  graph[5].push_back(4);
  graph[5].push_back(6);
  graph[5].push_back(7);
  graph[5].push_back(8);
  graph[5].push_back(9);

  graph[6].push_back(2);
  graph[6].push_back(5);
  graph[6].push_back(8);
  graph[6].push_back(3);
  graph[6].push_back(9);

  graph[7].push_back(4);
  graph[7].push_back(5);
  graph[7].push_back(8);

  graph[8].push_back(4);
  graph[8].push_back(5);
  graph[8].push_back(6);
  graph[8].push_back(7);
  graph[8].push_back(9);

  graph[9].push_back(6);
  graph[9].push_back(5);
  graph[9].push_back(8);
}

// Test harness
int main() {
  vector<vector<int> > graph(10);
  buildGraph(graph);

  bool used[10] = { false }; 
  string passwd;
  cout << "1: " << count(1, graph, passwd, used) << endl;
  cout << "2: " << count(2, graph, passwd, used) << endl;
  cout << "5: " << count(5, graph, passwd, used) << endl;
}
