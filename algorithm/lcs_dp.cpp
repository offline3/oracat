#include <string.h>
#include <stdio.h>

int a = 10;
int array[a] = {0};

int max(int l, int r){
    return l < r ? r : l;
}

int lcs(char* a, char*b, int n, int m){
    int dp[n+1][m+1];
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if(i == 0 || j == 0){
                dp[i][j] = 0;
            }
            else if(a[i-1] == b[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[n][m];
}
int main()
{
char X[] = "AGGTAB";
char Y[] = "GXTXAYB";
 
int m = strlen(X);
int n = strlen(Y);
 
printf("Length of LCS is %d", lcs( X, Y, m, n ) );
 
return 0;
}
