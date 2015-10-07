// http://www.mitbbs.com/article_t/JobHunting/32705761.html
// Implement read_line() based on read4k()

#include <string>

using namespace std;

string read4k() {
  // We assume this function is already available.
}

// Our implementarion
string read_line() {
  static string buffer;
  string ret;
  if (buffer.size()) { // We have characters left from previous reading.
      int i = 0;
      while (i < buffer.size() && buffer[i] != '\n') { // Try to read one line from buffer
	ret.push_back(buffer[i]);
	++i;
      }
      buffer = buffer.substring(i + 1);
      if (i == buffer.size()) {  // Need to read the next 4k to get '\n' character.
	return ret + readLine(); // Recursive function call.
      }
      else {
	return ret;
      }
  }
  else { // Buffer is empty, so we need to call read4k().
    buffer = read4k();
    if (!buffer.size()) { // Something is wrong with read4k()!
      return ret;
    }
    return readLine();
  }
}
