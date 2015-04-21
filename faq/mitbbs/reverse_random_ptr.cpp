/* Consider a Linked List with each Node, in addition to having a 'next' 
 * pointer also has a 'random' pointer. The 'random' pointer points to some 
 * random other Node on the linked list. It may also point to NULL. To simplify
 * things, no two 'random' pointers will point to the same node, but more than
 * 1 Node's random pointer can point to NULL. 
 * Now please reverse all the random pointers using space O(1).
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32066125.html
 */

// Java code by DataMining
/* This is a pretty tricky question, especially for the loop handling. 
 * Here is my java code, tested with looped case and non-looped case.
 */
    public static class DLLNode {
        DLLNode prev;
        DLLNode next;
        int value;
        
        public DLLNode(int value) {
            this.value = value;
            prev = null;
            next = null;
        }
    }
    static DLLNode dummy = new DLLNode(-1);
    static DLLNode loopDummy = new DLLNode(-2);
    static void printLL(final DLLNode head) {
         DLLNode current = head;
         while (current != null) {
             String s = current.value + ":" + (current.prev != null ? "" + 
current.prev.value : "null") + "--";
             System.out.print(s);
             current = current.next;
         }
         System.out.println();
     }

    static DLLNode getRandStart(DLLNode head, DLLNode target) {
        if (head == null) {
            return head;
        }
        DLLNode parent = target;
        while (parent != null) {
            boolean found = false;
            DLLNode iter = head;
            while (iter != null) {
                if (iter.prev == parent) {
                    found = true;
                    break;
                } else {
                    iter = iter.next;
                }
            }
            if (found) {
                parent = iter;
            } else {
                break;
            }
        }
        return parent;
    }
     static DLLNode reverseLLRand(DLLNode head) {
         if (head == null || head.prev == null) {
             return head;
         }
         DLLNode cur = head;
         DLLNode next = cur.prev;
         boolean connectLoop = false;
         while (next != null) {
             if (next == loopDummy) {
                 // cur used to be the break point of a loop, reconnect
                 connectLoop = true;
                 head.prev = loopDummy;
                 break;
             }
             DLLNode nextnext = next.prev;
             next.prev = cur;
             cur = next;
             next = nextnext;
         }
         if (!connectLoop) {
             head.prev = dummy;
         }
         return head;
     }
     static DLLNode reverseRandPointer(DLLNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        
        DLLNode out = head;
        while (out != null) {
	  // break the loop if it is
	  // Check if the rand LL that out is on is already reversed by 
	  // traverse till the end and check if it's null or dummy
	  DLLNode tail = out.prev;
	  DLLNode secondToTail = out;
	  // Check if the rand LL that out is on is a loop
	  while (tail != null && tail != dummy && tail != loopDummy) {
	    if (tail == out) {
	      // there is a loop, break
	      secondToTail.prev = loopDummy;
	      tail = null;
	      break;
	    }
	    secondToTail = tail;
	    tail = tail.prev;
	  }
	  if (tail != dummy && tail != loopDummy) {
	    // get the start of the random LL which out is part of
	    DLLNode start = tail == loopDummy ? out : getRandStart(head, out);
                reverseLLRand(start);
            }
            
            out = out.next;
        }
        

        DLLNode start = head;
        while (start != null) {
            // update dummy pointer to null
            if (start.prev == dummy ) {
                start.prev = null;
            }
            
            //  reconnect loop
            if (start.prev == loopDummy ) {
                start.prev = getRandStart(head, start);
            }
            
            start = start.next;
        }
        
        return head;
    }
    
    static void testReverseRandPointer() {
        DLLNode a = new DLLNode(1);
        DLLNode b = new DLLNode(2);
        DLLNode c = new DLLNode(3);
        DLLNode d = new DLLNode(4);
        DLLNode e = new DLLNode(5);
        
        a.next = b;
        b.next = c;
        c.next = d;
        d.next = e;
        
        a.prev = c;
        c.prev = e;
        b.prev = d;
        printLL(a);
        a = reverseRandPointer(a);
        printLL(a);

        a.prev = c;
        c.prev = e;
        e.prev = a;
        b.prev = d;
        d.prev = null;
        printLL(a);
        a = reverseRandPointer(a);
        printLL(a);

    }
