# 动态规划

##### 1 斐波纳契

> 跳台阶问题 ： n个台阶，每次能跳一层或两层，到达第n层，有多少种跳法？ （达到第n层时，有两种跳法，从第n-1层跳一层，或从n-2层跳两层）

- 递归实现

  ```c++
  int fib(n){
      return n < 2 ? n : f(n-1) + f(n-2);
  }
  ```

  ![image-20211020202042693](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20211020202042693.png)

- 递归实现

  1. 将已计算过实例的结果制表备查

     ```c++
     
     ```

  2. 动态规划法，由自顶而下递归，转化为自底而上迭代

     ```c++
     int fib(n){
     	int f = 0; int g = 1; 
         while(0 < n--){
             g = g + f;
             f = g - f;
         }
         return g;
     }
     ```


  ##### 2 最长公共子序列（longest common sequence）

  ![image-20211021192309668](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20211021192309668.png)

- 递归实现

    对于序列A[0，n]和B[0，m]，LCS(A，B)有三种情况

  - 若n == -1 或 m == -1，则取作空序列
  - 当A[n] == B[m]时，则取作：LCS(A[0，n-1]，B[0，m-1]) + 1   （减而治之思想）
  
  ![image-20211021200946913](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20211021200946913.png)
  
  - 当A[n] ！= B[m]时，则取作：LCS(A[0，n-1]，B[0，m])与LCS(A[0，n]，B[0，m-1])中**取最长者** （分而治之思想）
  
    ![image-20211021201002720](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20211021201002720.png)
  
    ```c++
    /* Utility function to get max of 2 integers */
    int max(int a, int b)
    {
        return (a > b)? a : b;
    }
    
    /* Returns length of LCS for X[0..m-1], Y[0..n-1] */
    int lcs( char *X, char *Y, int m, int n )
    {
        if (m == 0 || n == 0)
            return 0;
        if (X[m-1] == Y[n-1])
            return 1 + lcs(X, Y, m-1, n-1);
        else
            return max(lcs(X, Y, m, n-1), lcs(X, Y, m-1, n));
    }
    ```
  
    ![image-20211027190826448](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20211027190826448.png)
  
  ![image-20211027191128521](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20211027191128521.png)
  
- 动态规划（打表）

  ```c++
  
  ```
  
  
  
  
