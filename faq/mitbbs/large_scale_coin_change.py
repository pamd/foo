#!/usr/bin/python

l=[1,5,10,25,100,500,1000,2000,5000,10000]
n=40000

dp=[[0]*(len(l)+1) for i in xrange(10000)]

for j in xrange(len(l)+1):
    dp[0][j]=1

for i in xrange(1, n+1):
    dp[i%10000][0]=1
    for j in xrange(1, len(l)):
        dp[i%10000][j]=dp[i%10000][j-1]+dp[(i-l[j])%10000][j]

print dp[n%10000][len(l)-1]
