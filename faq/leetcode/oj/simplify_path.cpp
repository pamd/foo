/* Leetcode OJ: Given an absolute path for a file (Unix-style), simplify it.
 * For example,
 * path = "/home/", => "/home"
 * path = "/a/./b/../../c/", => "/c"
 *
 * Corner Cases:
 * Did you consider the case where path = "/../"?
 * In this case, you should return "/".
 * Another corner case is the path might contain multiple slashes '/' together, 
 * such as "/home//foo/". In this case, you should ignore redundant slashes and 
 * return "/home/foo".
 */

#include <string>
#include <iostream>
#include <vector>

using namespace std;

// 40ms for large dataset
class Solution {
public:
  /* dhu note: the input path is assumed to be 
   * always a valid ABSOLUTE path in unix style. 
   * So the output string will always start with '/'. 
   */ 
  string simplifyPath(string path) {
    vector<string> dirs;
    string tmp;
    for (size_t i = 0; i < path.size(); i++) {
      if (path[i] == '/') {
	if (tmp.size() == 0 && dirs.size() == 0) 
	  dirs.push_back("/");
	else if (tmp == ".." && dirs.size() > 1) 
	  dirs.pop_back();	
	else if (tmp.size() && tmp != "." && tmp != "..") 
	  dirs.push_back(tmp);
	
	tmp.clear();
      }
      else 
	tmp.push_back(path[i]);
    }
	
    if (tmp == ".." && dirs.size() > 1) 
      dirs.pop_back();
    else if (tmp.size() && tmp != "." && tmp != "..")
      dirs.push_back(tmp);

    if (dirs.size() == 0)
      return "/";

    if (dirs.size() == 1)
      return dirs[0];

    string result = dirs[0];
    for (size_t i = 1; i < dirs.size(); i++) 
      result += dirs[i] + "/";
    result.resize(result.size() - 1);

    return result;
  }
};

/*
int main() {
  Solution foo;
  string str("/a/./b///../c/../././../d/..//../e/./f/./g/././//.//h///././/..///");
	     //	"ef/g"	"/e/f/g"
  cout << foo.simplifyPath(str) << endl;
}
*/

/*************************************
 *  Dropbox solution 
 *************************************/
// path: an absolute path for a file (Unix-style)
string SimplifyPath(string path) {
  path.push_back('/'); // make sure the last path would be push to stack
  stack<size_t> iStack; // index of each directory in the path
  size_t pos = 0; // position for next directory to append
  iStack.push(pos);

  // Since the path is absolute, the first character would always be '/' 
  for (int i = 1; i < path.size(); ++i) {
    char c = path[i];
    if (c != '/') {
      path[++pos] = c;
      continue;
    }

    if (path[i-1] == '/') 
      continue;
        
    path[++pos] = c;// c == '/'
    int dir = iStack.top();
    if (path[dir+1]  == '.')
      switch (path[dir+2]) {
	//stay in current directory
      case '/': 
	pos = dir; break;
	
      case '.':
	if (path[dir+3] != '/') //hiden file
	  iStack.push(pos);
	else {
	  //back to the position of previous directory
	  if(iStack.size() > 1) iStack.pop();
	  pos = iStack.top();
	}
	break;
        
      default: //hiden file
	iStack.push(pos);
	break;
      }
    else //simple directory
      iStack.push(pos);
  }

  if (pos == 0)
    pos = pos + 1; // the path is back to the root
	
  path.erase(pos);
  return path;
}

// This method using a vector to save each directories
// path: an absolute path for a file (Unix-style)
string SimplifyPath2(string path) {
  vector<string> pathStack;
  string directory;
  path.push_back('/'); // make sure the last path would be push to stack
  for (int i = 0; i < path.size(); ++i) {
    char c = path[i];
    if (c != '/') {
      directory.push_back(c);
      continue;
    }
    
    if (directory.size() <= 0) 
      continue;
    
    if (directory[0] == '.') {
      if (directory.size() > 1) {
	if(directory[1] == '.') {   
	  if (directory.size() > 2) // hiden file
	    pathStack.push_back(directory);
	  else
	    if (pathStack.size() > 0)
	      pathStack.pop_back();
	}
	// go to parent path
	else // hiden file
	  pathStack.push_back(directory);
      }
      // else go to current path, do nothing
    }
    else // simple path
      pathStack.push_back(directory);
    
    directory.clear();
  }
  
  path.clear();
  for (int i = 0; i < pathStack.size(); ++i)
    path += '/' + pathStack[i];
  
  if (path.size() <= 0)
    path = "/";
  
  return path;
}

int main(int argc, char** argv) {
  string s = "/home/../..";
  cout << s << " => " << SimplifyPath(s) << endl;
  s = "/a/./.b/../../c/";
  cout << s << " => " << SimplifyPath2(s) << endl;
  s = "/home/of/foo/../../bar/../../is/./here/.";
  cout << s << " => " << SimplifyPath2(s) << endl;
  /**
 
     /home/../.. => /
     /a/./.b/../../c/ => /c
     /home/of/foo/../../bar/../../is/./here/. => /is/here
     
  **/
	
  return 0;
}
