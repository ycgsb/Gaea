#ifndef LONGESTCOMMONSUBSEQUENCE_H
#define LONGESTCOMMONSUBSEQUENCE_H

#include "../../util/Array1D.h"

namespace ycg {

template <class T>
class LongestCommonSubsequence {
public:
    int computeLength(const Array1D<T> &a, const Array1D<T> &b);
//    void constructSolution();
};

template <class T>
int LongestCommonSubsequence<T>::computeLength(const Array1D<T> &a, const Array1D<T> &b) {
    int n = a.length(), m = b.length();
    int *dp[2];
    dp[0] = new int[m + 1];
    dp[1] = new int[m + 1];
    int flag = 0;
    for(int j = 0; j <= m; ++j) {
        dp[flag][j] = 0;
    }
    for(int i = 0; i < n; ++i) {
        flag = 1 - flag;
        dp[flag][0] = 0;
        for(int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                dp[flag][j+1] = dp[1-flag][j] + 1;
            } else if (dp[1-flag][j+1] < dp[flag][j]) {
                dp[flag][j+1] = dp[flag][j];
            } else {
                dp[flag][j+1] = dp[1-flag][j+1];
            }
        }
    }
    int result = dp[flag][m];
    delete []dp[0];
    delete []dp[1];
    return result;
}

} //~ namespace ycg


#endif // LONGESTCOMMONSUBSEQUENCE_H
