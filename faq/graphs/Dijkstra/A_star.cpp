// An overly simple A* search example, which uses the distance
// from current position to the exit as the priority in priority queue.
//
// Base on B. Green "Programming Problems" Volume 1, pages 130-
// https://github.com/ProgrammingProblems/Volume1/blob/master/graphical_search/maze.cpp
// https://github.com/ProgrammingProblems/Volume1/blob/master/graphical_search/main.cpp
// https://github.com/ProgrammingProblems/Volume1/blob/master/graphical_search/distance_heuristic.cpp

#include <priority_queue>
#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

const vector<pair<size_t, size_t> > offsets = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

typedef pair<size_t, size_t> Postion;

// Return Manhattan distance between two positions in the maze.
// Based on:
// https://github.com/ProgrammingProblems/Volume1/blob/master/graphical_search/distance_heuristic.cpp
size_t distance(const Position begin, const Position end) {
   return abs(begin.first - end.first) + abs(begin.second - end.second);
}

// Is the input position valid? ('.' is used to denote a valid position.)
// Base on:
// https://github.com/ProgrammingProblems/Volume1/blob/master/graphical_search/main.cpp
bool passable(const Position& pos) {
  return board[pos.first][pos.second] == '.';
}

// A* search algorithm which uses the distance from current position
// to the exit as the priority in priority queue.
// Based on:
// https://github.com/ProgrammingProblems/Volume1/blob/master/graphical_search/maze.cpp
void A_star(const GameBoard& maze, const Position& start, const Position& exit, list<Position>* route)
{
   map<Position, Position> parent; // Key: position in a maze; Value: position from which key comes.

   priority_queue<pair<size_t, Position>, vector<pair<size_t, Position> >, greater<pair<size_t, Position> > > pq;
   // pair::size_t:   distance from current position to exit;
   // pair::Position: current position.

   pq.push({distance(start, exit), start});
   parent[start] = start;
   while (!pq.empty()) {
      auto current = pq.top().second;

      // If currenty position is the exit, populate the route, then return.
      if (exit == current) {
         do {
            route->push_front(current);
            current = parent[current];
         } while (current != start);
         route->push_front(start);
         return;
      }

      // If current position is not the exit, pop it out of pq,
      // then push its unvisited neighbors into pq.
      pq.pop();
      for (auto offset : offsets) {
         auto neighbor = Position(current.first + offset.first, current.second + offset.second);
         if (neighbor.first < maze.size() && neighbor.second < maze[neighbor.first].size()
            // Make sure neighbor position is not out of the maze
            && parent.end() == parent.find(neighbor) // Make sure neighbor has not been visited.
            && passable(neighbor)) {    // Make sure neighbor is a valid position.
            parent[neighbor] = current; // Memorize the position that the neighbor comes from.
            pq.push({distance(neighbor, exit), neighbor});
            // Note that the DISTANCE FROM NEIGHBOR TO THE EXIT is used as the priority.
         }
      } // end of "for"
   } // end of "while"
}

// Test harness
int main() {
  list<Position> route;
  board = { {'.', '.'}, {'.', '.'} };
  A_star(board, {0, 0}, {1, 1}, &route);
  ASSERT(!route.empty());
  ASSERT(route.size() == 3);

  route.clear();
  board = { {'.', '*'}, {'*', '.'} };
  maze(board, {0, 0}, {1, 1}, &route);
  ASSERT(route.empty());

  return 0;
}
