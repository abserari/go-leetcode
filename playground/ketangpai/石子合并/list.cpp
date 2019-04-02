//
//  main.cpp
//  合并石子
//
//  Created by Yeah on 14-5-13.
//  Copyright (c) 2014年 Yeah. All rights reserved.
//

#include <iostream>
using namespace std;

#define min(a, b) (a < b ? a : b)

int sum[101], dp[101][101];

int main()
{
    unsigned int N(0);
    while (cin >> N)
    {
        for (unsigned int i(1); i <= N; ++i)
        {
            int temp;
            cin >> temp;
            sum[i] = sum[i - 1] + temp; 
        }
        memset(dp, 127, sizeof(dp));
        for (unsigned int i(1); i <= N; ++i)
        {
            dp[i][i] = 0; 
        }
        for (unsigned int i(N); i != 0; --i) 
        {
            for (unsigned int j(i + 1); j <= N; ++j)
            {
                for (unsigned int k(i); k != j; ++k)
                {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
                }
            }
        }
        cout << dp[1][N] << endl;
    }
    return 0;
}