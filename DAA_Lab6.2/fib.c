#include <stdio.h>

int dp[100];

int fibonacci(int n){
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    if (dp[n] != -1)
        return dp[n];

    dp[n] = fibonacci(n - 1) + fibonacci(n - 2);

    return dp[n];
}

int main(){
    int n, i;
    printf("Enter n: ");
    scanf("%d", &n);

    for (i = 0; i < 100; i++)
        dp[i] = -1;

    printf("The %dth Fibonacci number is %d\n", n, fibonacci(n));
    return 0;
}