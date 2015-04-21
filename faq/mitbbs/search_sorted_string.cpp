/*
: Given a string of sorted integers, e.g. "1 52 69 456789 994546566";
: and a  a number e.g. 69.
: You need to tell if it is in the input, e.g. 69=>true.
: Write the code using the fastest algorithm.

* Refer to:
* http://www.mitbbs.com/article_t/JobHunting/32122887.html

curInt
curStr
flag=1
*/


// dango: O(n) time, O(1) space
bool findInput(string in, int target){
      string s = intToString(target);
      int i=0;
      int flag=1;
      int curInt=0;
      while(i<in.size()){
           
           if(in[i]!=' '&&flag==1){
              curInt = curInt*10+(in[i]-'0');

           } else if(in[i]!=' '&&flag==0){
                curInt= in[i]-'0';
                i++;
           } else if(in[i]==' '&&flag==1){
                if(curInt==target) return true;
                else if(curInt>target) return false;
                else {
                   curInt=0;
                   flag=0;
                }
           } else{
                 curInt=0;
                 flag=0;
           }
           i++;
      }
      if(i==in.size()){
            if(curInt==target) return true;
            else if(curInt>target) return false;
      }
      return false;
}

// dango #2: Time average O(lgn), worst O(n)
int findSubInt(string in,int mid,int& subBegin,int& subEnd){
      subBegin=mid;
      subEnd=mid;
      while(in[subBegin]!=' '){
           subBegin--;
      }
      if(in[subBegin]==' ') subBegin++;
      
      while(in[subEnd]!=' '){
           subEnd++;
      }
      if(in[subEnd]==' ') subEnd--;
      string subStr = in.substr(subBegin,subEnd-subBegin+1);
      return atoi(subStr.c_str());
}

bool findInt(string in, int target){
     int begin =0;
     int end = in.size();
     while(begin<=end){
          long long mid = (begin+end)/2;
          while(mid>=0&&in[mid]==' '){
              mid--;
          }
          if(mid<0){
              begin=(begin+end)/2+1;
              continue;
          } else if(in[mid]!=' '){
                int subBegin=0;
                int subEnd=0;
                int subInt = findSubInt(in,mid,subBegin,subEnd);
                if(subInt>target){
                      end=subBegin-1;
                      continue;
                } else if(subInt==target) return true;
                else {
                      begin=subEnd+1;
                      continue;
                }
          }
     }
     return false;
}

// eswine: java code
public boolean isFind(String s, int n) {
        
        int mid = s.length() / 2;
        char midChar = s.charAt( mid );
        if ( midChar == ' ' ) 
            return isFind( s.substring( 0, mid ), n ) || isFind( s.
substring( mid + 1, s.length() ), n );
        
        int rightMostLetterIdx = findRightMostLetterIndex( s, mid );
        int leftMostLetterIdx = findLeftMostLetterIndex( s, mid );
        
        String midNum = s.substring( leftMostLetterIdx, rightMostLetterIdx +
1  );
        int midNumInt = Integer.parseInt(midNum);
        if ( midNumInt == n )
            return true;
        
        if ( midNumInt < n && rightMostLetterIdx < s.length() - 2 )  
            return isFind( s.substring(rightMostLetterIdx + 2, s.length() ),
n );

        
        if ( midNumInt > n && leftMostLetterIdx > 1 )
            return isFind( s.substring(0, leftMostLetterIdx -1 ), n );
        
        return false;
    }
    
    public int findRightMostLetterIndex(String s, int rightMostLetterIdx) {
        while ( s.charAt( rightMostLetterIdx ) != ' ' && rightMostLetterIdx 
< s.length() - 1 )
            rightMostLetterIdx++;
        if ( rightMostLetterIdx < s.length() - 1 )
            rightMostLetterIdx--;
        
        return rightMostLetterIdx;
    }
    
    public int findLeftMostLetterIndex(String s, int leftMostLetterIdx) {
        while ( s.charAt( leftMostLetterIdx ) != ' ' && leftMostLetterIdx > 
0 )
            leftMostLetterIdx--;
        if ( leftMostLetterIdx > 0 )
        leftMostLetterIdx++;
        
        return leftMostLetterIdx;
    }
