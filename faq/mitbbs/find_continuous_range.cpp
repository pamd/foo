/* Discussion #398:
 * http://www.mitbbs.com/article_t/JobHunting/32125727.html
 */

// Code based on jingoshine's idea
//i use static linked list here
//change map to hash_map, then O(n)

struct NodeInfo{
    int data;
    int next;
    bool has_pre;
    NodeInfo(int d):data(d), next(-1), has_pre(false){ }
    NodeInfo(){}
};

vector<int> MaxForSeq(int a[], int len){
    vector<int> ret;
    vector<NodeInfo> vn(len);
    map<int, int> mp; //data to index in vector vn
    for (int i = 0; i < len; ++i){
        if (mp.find(a[i]) == mp.end()){
            vn.push_back(NodeInfo(a[i]));
            mp[a[i]] = vn.size() - 1;
        }
    }
    for (vector<NodeInfo>::iterator it = vn.begin(); it != vn.end(); ++it){
        if (mp.find(it->data - 1) == mp.end()){
            continue;
        } else {
            it->next = mp[it->data - 1];
            vn[mp[it->data - 1]].has_pre = true;
        }
    }
    int max = 0;
    int idxmax = -1; 
    for (vector<NodeInfo>::iterator it = vn.begin(); it != vn.end(); ++it){
        if (!it->has_pre){
            int count = 1;
            for (int i = it->next; i != -1; i = vn[i].next){
                ++count;
            }
            if (count > max){
                max = count;
                idxmax = it - vn.begin();
            }
        }
    }
    for (int i = idxmax; i != -1; i = vn[i].next){
        ret.push_back(vn[i].data);
    }
    return ret;
}

void TestMaxForSeq(){
    vector<int> a;
    int b[] = {1,3,2};
    a = MaxForSeq(b, 3);
    int c[] = {3, 5,1, 8, 9, 7, 0, 2};
    a = MaxForSeq(c, 8);
}
