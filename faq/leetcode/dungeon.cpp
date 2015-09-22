class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int prev = 0;
        int row = dungeon.size();
        int col = dungeon[0].size();
        vector<int> x(col, 0);

        for (int i = col - 1; i >= 0; --i) {
	  if (prev + dungeon[m-1][i] < 0) {
	    x[i] = prev + dungeon[m-1][i];
	  }
	  else {
	      x[i] = 0;
	  }
	  prev=x[i];
        }

        for (int j=m-2;j>=0;j--)
         for (int i=n-1;i>=0;i--){
             if(i==n-1){
                 x[i]=min(0,x[i]+dungeon[j][i]);
                 prev=x[i];
             }
             else{
                 x[i]=min(0,max(prev,x[i])+dungeon[j][i]);
                 prev=x[i];
             }

         }
         return -x[0]+1;
    }
};
