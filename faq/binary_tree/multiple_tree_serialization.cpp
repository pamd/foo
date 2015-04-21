/* Discussion 412: serialize and de-serialize multiple tree
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32149567.html
 */

/* peking2 python code: deserialize
class Element:
    def __init__(self,str):
        self.str=str
        self.l=[]
    
    def add(self,e):
        self.l.append(e)
        
    def ifstr(self):
        return self.str!=None
    
input="[Apple,[Orange,Banana,[A,B,C]]"
i=0

def dfs():
    global i
    e=None
    while input[i]==',' or input[i]==' ':
        i+=1
    if input[i]=='[':
        e=Element(None)
        i+=1
        while input[i]!=']':
            e.add(dfs())
    else:
        j=i+1
        while input[j]!=',' and input[j]!=']':
            j+=1
        e=Element(input[i:j])
        i=j
    return e
            
root=dfs()

*/

// babyfacenan (not tested yet)
class Node {
public:
  int data;
  vector<char*> child;
}

Node* deserialize(FILE* fin) {
  Node* node = 0;
  char* token = 0;

  if(*(token = readToken(fin))=='['){
    node = new Node();
    while(*(token = readToken(fin))!=']') {
      if(*token=='[') {
	fin->seek(-1);
	Node* tmp = deserialize(fin);
	node->child.push(tmp);
      } else if(isLetter(*token)) {
	node->child.push(token);
      }
    }
  }
  
  return node;
}

void serialize(FILE* fin, char* root) {
  if (root==NULL) {
    return;
  }
  
  if(root->child.size()=0) {
    fin->append (root->data);
  } else {
    fin->append('[');
    for (int idx=0; idx < root->child.size(); ++idx) {
      serialize(fin, root->child.at(idx));
    }
    fin->append(']');
  }
}
