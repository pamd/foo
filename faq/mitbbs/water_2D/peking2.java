/* Java code by peking2, copied from:
 * http://blog.sina.com.cn/s/blog_b9285de20101j9a7.html
 *
 * dhu: no main function, not compile.
 */

class waterContainer{
    private int m;
    private int n;
    private int[][] mat;
    private boolean[][] visited;
    private PriorityQueue<Cell> pq;
    private int count;
    
    class Cell implements Comparable<Cell>{
        int x;
        int y;
        int height;
        public Cell(int x,int y,int height){
            this.x=x;
            this.y=y;
            this.height=height;
        }
        
        public int compareTo(Cell o){
            return height-o.height;
        }
    }
    
    public waterContainer(int[][] input){
        mat=input;
        m=mat.length;
        n=mat[0].length;
        visited=new boolean[m][n];
        pq=new PriorityQueue<Cell>();
        count=0;
    }
    
    private void check(int x, int y, int lowest){
        if (x < 0 || x >= m || y<0 || y >= n || visited[x][y]) 
	    return;

        if (mat[x][y] < lowest) 
	    count += lowest - mat[x][y];

        visited[x][y] = true;
        pq.offer(new Cell(x, y, Math.max(lowest, mat[x][y])));
    }
    
    public int solve(){
        for(int i=0;i<m;i++){
            visited[i][0]=true;
            pq.offer(new Cell(i,0,mat[i][0]));
                
            visited[i][n-1]=true;
            pq.offer(new Cell(i,n-1,mat[i][n-1]));
        }
        
        for(int j=1;j<n-1;j++){
            visited[0][j]=true;
            pq.offer(new Cell(0,j,mat[0][j]));
                
            visited[m-1][j]=true;
            pq.offer(new Cell(m-1,j,mat[m-1][j]));
        }

        while(!pq.isEmpty()){
            Cell curr=pq.poll();
            check(curr.x-1,curr.y,curr.height);
            check(curr.x+1,curr.y,curr.height);
            check(curr.x,curr.y-1,curr.height);
            check(curr.x,curr.y+1,curr.height);
        }
        
        return count;
    }
}