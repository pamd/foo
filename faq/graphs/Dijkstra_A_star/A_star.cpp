//
// An overly simple A* search example, which uses the distance
// from current position to the exit as the priority in priority queue.
//
#include <queue>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <utility>
#include <cstdlib>
#include <cassert>

using namespace std;

typedef pair<int, int> Position;
vector<Position> offsets;

typedef vector<string> GameBoard;
GameBoard board;

// Return Manhattan distance between two positions in the maze.
// Based on:
// https://github.com/ProgrammingProblems/Volume1/blob/master/graphical_search/distance_heuristic.cpp
size_t manhattan(const Position& p1, const Position& p2) {
   return abs(p1.first - p2.first) + abs(p2.second - p2.second);
}

// Is the input position valid? ('.' is used to denote a valid position.)
// Base on:
// https://github.com/ProgrammingProblems/Volume1/blob/master/graphical_search/main.cpp
bool passable(const Position& pos) {
  return board[pos.first][pos.second] == '.';
}

// A* search algorithm that uses the distance from current position
// to the exit as the priority in priority queue.
// Based on:
// https://github.com/ProgrammingProblems/Volume1/blob/master/graphical_search/maze.cpp
void A_star(const GameBoard& maze, const Position& source, const Position& exit, list<Position>* route)
{
   map<Position, Position> parent; // Key: position in a maze; Value: position from which key comes.
   priority_queue<pair<size_t, Position>, vector<pair<size_t, Position> >, greater<pair<size_t, Position> > > pq;
   // pair::size_t:   distance from current position to exit;
   // pair::Position: current position.

   pq.push(make_pair(manhattan(source, exit), source));
   parent[source] = source;
   while (!pq.empty()) {
      Position current = pq.top().second;
      if (exit == current) { // If currenty position is the exit, populate the route, then return.
         do {
            route->push_front(current);
            current = parent[current];
         } while (current != source);
         route->push_front(source);
         return;
      }

      // If current position is not the exit, pop it out of pq,
      // then push its unvisited neighbors into pq.
      pq.pop();
      cout << "Pop out (" << current.first << ", " << current.second << ")" << endl; // For debug only

      for (size_t i = 0; i < offsets.size(); ++i) {
         Position neighbor = Position(current.first + offsets[i].first, current.second + offsets[i].second);
         if (neighbor.first < maze.size() && neighbor.second < maze[neighbor.first].size()
            // Make sure neighbor position is not out of the maze
            && parent.end() == parent.find(neighbor) // Make sure neighbor has not been visited.
            && passable(neighbor)) {    // Make sure neighbor is a valid position.
            parent[neighbor] = current; // Memorize the position that the neighbor comes from.
            pq.push(make_pair(manhattan(neighbor, exit), neighbor));
            // Note that the DISTANCE FROM NEIGHBOR TO THE EXIT is used as the priority.
         }
      } // end of "for"
   } // end of "while"
}

void print_route(const list<Position>& route) {
   if (route.size()) {
      for (list<Position>::const_iterator it = route.begin(); it != route.end(); ++it) {
         cout << "(" << it->first << ", " << it->second << ")" << endl;
      }
   }
   else {
      cout << "None" << endl;
   }
   cout << endl;
}

// Test harness
int main() {
   offsets.push_back(make_pair(-1, 0));
   offsets.push_back(make_pair(1, 0));
   offsets.push_back(make_pair(0, -1));
   offsets.push_back(make_pair(0, 1));
   // make_pair(1, 0), make_pair(0, -1), make_pair(0, 1) };

   list<Position> route;

   /*
   // Test #1:
   board.push_back("..");
   board.push_back("..");

   Position s1(0, 0);
   Position g1(1, 1);
   A_star(board, s1, g1, &route);
   cout << "Route in Test #1: " << endl;
   print_route(route);

   // Test #2:
   route.clear();
   board.clear();
   board.push_back(".x");
   board.push_back("x.");
   Position s2(0, 0);
   Position g2(1, 1);
   A_star(board, s2, g2, &route);
   cout << "Route in Test #2: " << endl;
   print_route(route);

   // Test #3:
   route.clear();
   board.clear();
   board.push_back("....");
   board.push_back("....");
   board.push_back(".xxx");
   board.push_back("....");
   Position s3(0, 0);
   Position g3(3, 3);
   A_star(board, s3, g3, &route);
   cout << "Route in Test #3: " << endl;
   print_route(route);
   */

   // Test #4:
   route.clear();
   board.clear();
   board.push_back(".....");
   board.push_back(".x...");
   board.push_back(".x.x.");
   board.push_back("...x.");
   Position s4(0, 0);
   Position g4(3, 4);
   A_star(board, s4, g4, &route);
   cout << "\nRoute in Test #4: " << endl;
   print_route(route);
   //
   // Test #4 shows that this algorithm may not give us the shortest path.
   // The graph in this test is:
   //
   //                 s . . . .
   //                 . x . . .
   //                 . x . x .
   //                 . . . x t
   //
   // s is the source node, t is goal, '.' means valid position, 'x' mean invalid position.
   // The path found by the algorithm includes 12 nodes:
   //
   //                 (0, 0)
   //                 (1, 0)
   //                 (2, 0)
   //                 (3, 0)
   //                 (3, 1)
   //                 (3, 2)
   //                 (2, 2)
   //                 (1, 2)
   //                 (1, 3)
   //                 (1, 4)
   //                 (2, 4)
   //                 (3, 4)
   //
   // But the shortest path includes only 8 nodes:
   //
   //                 (0, 0)
   //                 (0, 1)
   //                 (0, 2)
   //                 (0, 3)
   //                 (0, 4)
   //                 (1, 4)
   //                 (2, 4)
   //                 (3, 4)
   //
   // The reason is because the priority key in pq is the Mahattan distance from current node to the goal,
   // so some of the nodes in optimal path have lower priority than the nodes in sub-optimal path.
   //
   // A correct implementation should use the SUM of distance from source node to the current node AND
   // the Mahattan distance from current node to the goal.
   //

   return 0;
}
