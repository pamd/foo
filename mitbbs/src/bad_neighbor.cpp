// Use DP twice to get the answer.
int double_dp(int donations[], int N) {
   if (N == 1) {
      return donations[0];
   }
   if (N == 2) {
      return max(donations[0], donations[1]);
   }

   // DP #1: excluding the last element.
   vector<int> DP1(N, 0);
   DP1[0] = donations[0];
   DP1[1] = max(donations[0], donations[1]);
   for (size_t i = 2; i < N - 1; ++i) {
      DP1[i] = max(DP1[i - 1], DP1[i - 2] + donations[i]);
   }
   int ret1 = DP1[N - 2];

   // DP #2: excluding the first element.
   vector<int> DP2(N, 0);
   DP2[1] = donations[1];
   DP2[2] = max(donations[1], donations[2]);
   for (size_t i = 3; i < N; ++i) {
      DP2[i] = max(DP2[i - 1], DP2[i - 2] + donations[i]);
   }
   int ret2 = DP2[N - 1];
   
   return max(ret1, ret2);
}