/* Preorder traversal of a tree in which a node may have multiple children. 
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
  Node(const string& s) { dat = s; }

  string dat;
  vector<Node*> children;
};

void print(Node* root, int level) {
  if (!root)
    return;

  for (int i = 0; i < level; i++) 
    cout << "   ";  // three extra space characters
  cout << root->dat << endl;
  for (size_t i = 0; i < root->children.size(); i++) {
    print(root->children[i], level + 1);
  }
}

int main() {
  Node* lifeform = new Node("lifeform");
  Node* animal = new Node("animal");
  Node* fish = new Node("fish");
  Node* mammal = new Node("mammal");
  Node* cat = new Node("cat");
  Node* lion = new Node("lion");
  Node* bird = new Node("bird");

  lifeform->children.push_back(animal);
  animal->children.push_back(fish);
  animal->children.push_back(mammal);
  animal->children.push_back(bird);
  mammal->children.push_back(cat);
  cat->children.push_back(lion);

  print(lifeform, 0);

  /*
lifeform
   animal
      fish
      mammal
         cat
            lion
      bird
  */

  return 0;
}
