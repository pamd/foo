/* Multiply two integers represented by strings. 
 * http://www.mitbbs.com/article_t/JobHunting/32125333.html
 * Code from wwwyhx. */

// Multiple two strings "1234" * "23" = "28382"

//A Facebook phone interview problem, suppose to done within 
//15 minutes, I believe is mission impossible. The solution below
//uses a common way to solve this problem, does not deal with the
//sign, the logic is still refined several times.
string Multiple(string str1, string str2)
{
    assert(str1.size() > 0 && str2.size() > 0);

    string strRes;
    for (int i = str2.size() - 1; i >= 0; i--)
    {
        //Calculate digit multiple
        int nAdd = 0;
        string strCur;
        for (int j = str1.size() - 1; j >= 0; j--)
        {
            int nTmpI = str2[i] - '0';
            int nTmpJ = str1[j] - '0';
            int nRes = nTmpJ * nTmpI + nAdd;

            nAdd = nRes / 10;
            strCur.insert(strCur.begin(), nRes%10 + '0');
        }

        if (nAdd > 0) //pitfall, don't forget to deal with the rest
            strCur.insert(strCur.begin(), nAdd + '0');

        //Remember the "add" rule
        strCur.append(str2.size() - i - 1, '0');

        //Add to previous result
        nAdd = 0;
        int nRes = strRes.size() - 1;
        int nCur = strCur.size() - 1;
        
        string strTmpRes;
        //the logic will be much much worse if use "while (nCur >= 0 && nRes >= 0)"
        //because you have to deal with lots of the "rest logic"
        while (nCur >= 0 || nRes >= 0)
        {
            //if goes beyond a operand, just make the current digit 0
            int nTmpCur = nCur >= 0 ? strCur[nCur] - '0' : 0;
            int nTmpRes = nRes >= 0 ? strRes[nRes] - '0' : 0;
            int nDigit = nTmpCur + nTmpRes + nAdd;

            nAdd = nDigit / 10;
            strTmpRes.insert(strTmpRes.begin(), nDigit%10 + '0');
            nRes--, nCur--;
        }

        if (nAdd > 0) //pitfall, don't forget to deal with the rest
            strTmpRes.insert(strTmpRes.begin(), nAdd + '0');

        strRes = strTmpRes;
    }

    return strRes;
}
