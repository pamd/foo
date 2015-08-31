
* The problems of finding articulations points (AP) and finding bridges are closely related,
  but not exactly the same problem. For example, for this graph:

                    0---1
                     \ /
                      2
                     / \
                    3---4
 
  Vertex #2 is an AP, but none of the edges of vertex #2 is bridge.

* AP_geeks.cpp and bridge_geeks.cpp are very close, but in AP_geeks.cpp, we have:

       if (parent[u] != -1 && discovery[u] <= low[v]) {
           ap[u] = true;
       }

  But in bridge_geeks.cpp, we have:

       if (discovery[u] < low[v]) {
          cout << "Bridge: " << u << "--" << v << endl;
       }

  THIS IS A KEY DIFFERENCE.

* bridge_algs4.java is copied from Sedgewick's book. The idea is almost identical to bridge_geeks.cpp,
  but this line is different:

       if (low[w] == pre[w]) {
           StdOut.println(v + "-" + w + " is a bridge");
           bridges++;
       }


