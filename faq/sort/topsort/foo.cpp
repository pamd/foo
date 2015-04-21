#include <iostream>
#include <cassert>

using namespace std;

void buildMap(const char* str[], int n, int nBeg, bool bMap[26][26])
{
    if (str == NULL || n <= 1) // <= 1 not 0
        return;

    int nPrev = 0;
    while (str[nPrev][nBeg] == 0 && nPrev < n) // missing nPrev < n
        nPrev++;

    int nIter = nPrev + 1;
    while (nIter < n)
    {
        if (str[nPrev][nBeg] != str[nIter][nBeg])
        {
            assert(str[nPrev][nBeg] >= 'a' && str[nPrev][nBeg] <= 'z');
            assert(str[nIter][nBeg] >= 'a' && str[nIter][nBeg] <= 'z');

            bMap[str[nPrev][nBeg] - 'a'][str[nIter][nBeg] - 'a'] = true;
            buildMap(str + nPrev, nIter - nPrev, nBeg + 1, bMap);
            nPrev = nIter;
        }

        nIter++; //forget ++
    }

    buildMap(str + nPrev, nIter - nPrev, nBeg + 1, bMap);
}

void printOrder(bool bMap[26][26], int rec[26], bool visit[26], char order[26], int nIndex)
{
    if (nIndex >= 26)
    {
        for (int i = 0; i < 26; i++)
            cout<<order[i]<<" ";
        cout<<endl;

        return;
    }

    for (int i = 0; i < 26; i++)
    {
        if (visit[i] || rec[i] != 0) continue;

        visit[i] = true;
        order[nIndex] = 'a' + i;
        for (int j = 0; j < 26; j++)
            if (bMap[i][j]) rec[j]--;

        printOrder(bMap, rec, visit, order, nIndex+1);

        for (int j = 0; j < 26; j++)
            if (bMap[i][j]) rec[j]++;
        visit[i] = false;
    }
}

void PrintAllOrder(const char* str[], int n)
{
    if (NULL == str || n <= 0)
        return;

    bool bMap[26][26] = { false };
    buildMap(str, n, 0, bMap);

    int rec[26] = { 0 };
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            if (bMap[i][j]) rec[j]++;
    
    char order[26];
    bool visit[26] = { false };
    printOrder(bMap, rec, visit, order, 0);
}

int main() {
  const char* str[26];
  str[0] = "aa";
  str[1] = "ab";
  str[2] = "c";
  str[3] = "d";
  str[4] = "e";
  str[5] = "f";
  str[6] = "g";
  str[7] = "h";
  str[8] = "i";
  str[9] = "j";

  str[10] = "k";
  str[11] = "l";
  str[12] = "m";
  str[13] = "n";
  str[14] = "o";
  str[15] = "p";
  str[16] = "q";
  str[17] = "r";
  str[18] = "s";
  str[19] = "t";

  str[20] = "u";
  str[21] = "v";
  str[22] = "w";
  str[23] = "x";
  str[24] = "y";
  str[25] = "z";

  PrintAllOrder(str, 26); 
  
  return 0;
}
