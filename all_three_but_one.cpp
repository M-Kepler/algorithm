/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-03-31 09:45:01
* Filename     : all_three_but_one.cpp
* Description  : 其他数字都出现了3次，唯有一个数字只出现了一次
***********************************************************/

#include <iostream>
using namespace std;
int singleNumber(int A[], int n);
int main()
{
    //int len =sizeof(s)/sizeof(s[0]);
    int s1[]={2,2,4,5,2,8,7,7,8,7,8,4,4};
    cout<<"s1=2,2,4,5,2,8,7,7,8,7,8,4,4"<<endl;
    int len =sizeof(s1)/sizeof(s1[0]);
    cout<<singleNumber(s1,len)<<endl;
    return 0;
}

int singleNumber(int A[], int n)
{
    int ones = 0, twos = 0, xthrees = 0;
    for(int i = 0; i < n; ++i)
    {
        twos |= (ones & A[i]);
        ones ^= A[i];
        xthrees = ~(ones & twos);
        ones &= xthrees;
        twos &= xthrees;
    }
    return ones;
}



