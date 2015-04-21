// Connect nodes in binary tree by levels
// http://www.mitbbs.com/article_t1/JobHunting/32130301_0_4.html

// jingoshine 
void LinkSameLayer(Node *head) {
    Node *tail = *head;
    Node *layerTail = *head;

    if(!head) return;
    head->next = NULL;
    while(head) {
      if(head->left)
        tail = tail->next = head->left;
      if(head->right)
        tail = tail->next = head->right;
      tail->next = NULL;

      if(head == layerTail) {
        Node *next = head->next;
        head->next = NULL;
        layerTail = tail;
        head = next;
      }
      else head = head->next;
    }

  }

// wangx3
void linkSamelayer(node * root)
{
    head=root;
    tail=root;
    head->next=NULL;
    while(head)
    {
        if(head->left)
        {
            tail->next=head-left;
            tail=tail->next;
         }
         if(head->right)
        {
            tail->next=hed->right;
            tail=tail->next;
         }
        tail->next=NULL;
        head=head->next;
     }
}
