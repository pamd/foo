/* Print All different Combinations of a Number as a Sum of Candidate Numbers.
 * Recursive and iterative solutions. 
 * Copied from:
 * http://www.mitbbs.com/article_t/JobHunting/32091749.html
 * Code not tested yet. 
 */

/* Recursive solution, by wwwyhx. */
//Print All different Combinations of a Number as a Sum of Candidate Numbers 

//Before start coding, several things to consider
//1. How to deal with duplicated numbers (sort them)
//2. What exactly is the successful ending condition
//3. What exactly is the failure ending condition
//4. For the container, pass by reference or by value

void _inner_print(int a[], int n, int nSum, vector<int>& vecRes)
{
    //the success ending condition is nSum == 0 and at the 
    //same time n == 0!! not nSum == 0 only
    //consider 1, 2, -13, 13 ==> (3)
    //another error logic is :
    //if (nSum == 0) { print all; (no return here) }
    //this logic will generate duplicated pairs
    if (nSum == 0 && n == 0)
    {
        for (vector<int>::iterator it = vecRes.begin();
            it != vecRes.end(); it++)
            cout<<*it<<" ";
        cout<<endl;
        return;
    }

    if (n == 0) return;

    int nDup = 1;
    while (nDup < n && a[nDup-1] == a[nDup])
        nDup++;

    //choose 0 a[0]
    _inner_print(a + nDup, n - nDup, nSum, vecRes);
    for (int i = 1; i <= nDup; i++)
    {
        vecRes.push_back(a[0]);
        nSum -= a[0];
        _inner_print(a + nDup, n - nDup, nSum, vecRes);
    }

    //for reference, below logic is required
    //think in this way, all called "_inner_print"
    //must restore the vecRes' status as it passed in
    for (int i = 1; i <= nDup; i++)
        vecRes.pop_back();
}

void PrintAllComb(int a[], int n, int nSum)
{
    assert(a && n > 0);

    sort(a, a+n);
    vector<int> vecRes;

    _inner_print(a, n, nSum, vecRes);
}

// Java code, iterative solution, by yishan
void PrintCombinations(int[] numbers, int sum)
{
    int[] numberCounts = new int[numbers.Length];
    int index = 0;
    int tempSum = sum;
    bool subDone = false;

    while (index >= 0)
    {
        if (index == numbers.Length - 1)
        {
            if (tempSum % numbers[index] == 0)
            {
                numberCounts[index] = tempSum / numbers[index];
                // Print Combination
                for (int i = 0; i < numbers.Length; i++)
                    for (int j = 0; j < numberCounts[i]; j++)
                        Console.Write(" " + numbers[i]);
            }
            index--;
            subDone = true;
        }
        else if (subDone)
        {
            tempSum -= numbers[index];
            numberCounts[index]++;
            subDone = false;
        }
        else if (tempSum >= 0)
        {
            index++;
        }
        else
        {
            tempSum += numberCounts[index] * numbers[index];
            numberCounts[index] = 0;
            index--;
            subDone = true;
        }
    }
}
