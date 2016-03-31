/*============================================================================
  排序：
http://blog.csdn.net/hguisu/article/details/7776068
http://blog.csdn.net/jnu_simba/article/details/9705111
============================================================================*/
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int  n = 10;
//几个工具函数
void create(int a[])
{
    srand((unsigned)time(NULL));
    for(int i =0;i<10;i++)
        a[i] = rand()%9+1;
}
void print(int s[])
{
    for(int i =0;i<n;i++)
        cout<<s[i]<<" ";
}
void swap(int a,int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}
//交换排序 --- 冒泡 O(n) -> O(n^2)
void bubbleSort(int s[],int len)
{
    int i ,j;
    for(i=0; i<len; i++ )
    {
        for( j =0; j<i; j++)
        {
            if( s[i] < s[j] )
            {
                int tmp = s[j];
                s[j] = s[i];
                s[i] = tmp;
            }
        }
    }
}
//交换排序 --- 快排 O(nlogn)(平均情况)
void quickSort1(int *a,int left,int right)
{
    int i,j,t,temp;
    if(left>right)
        return;
    temp=a[left];
    i=left;
    j=right;
    while(i!=j)
    {
        //顺序很重要，要先从右边开始找
        while(a[j]>=temp && i<j)
            j--;
        while(a[i]<=temp && i<j)
            i++;
        if(i<j)
        {
            t=a[i];
            a[i]=a[j];
            a[j]=t;
        }
    }
    //最终将基准数归位
    a[left]=a[i];
    a[i]=temp;
    quickSort1(a,left,i-1);
    quickSort1(a,i+1,right);
}
void quickSort2(int a[],int l,int r)
{
    int i=l,j=r;
    if(l>=r)
        return ;
    int temp=a[i];
    while(i!=j)
    {
        while(i<j && a[j]>=temp)
            j--;
        if(i<j)
            a[i++]=a[j];
        while(i<j && a[i]<=temp)
            i++;
        if(i<j)
            a[j--]=a[i];
    }
    a[i]=temp;
    quickSort2(a,l,i-1);
    quickSort2(a,i+1,r);
}
//选择排序 --- 直接选择排序 O(n) -> O(n^2)
void chooseSort(int s[],int len)
{
    //每次循环找出最小的值min，min与 s[i] 交换。i++, 如此循环。O(n^2)
    int i,j,minIndex,tmp;
    for (i=0; i<len ; i++)
    {
        minIndex = i;
        //找出未排序种最小元素的下标
        for (j=i+1; j<len ; j++)
        {
            if (s [j]< s[minIndex])
                minIndex = j;
        }
        //交换最小元素和s[j];
        if (minIndex != i)
        {
            tmp=s [minIndex];
            s [minIndex]=s [i];
            s [i]=tmp;
        }
    }
}
//-----------------------------------------------------------------------------
//选择排序 --- 堆排序 O(nlogn)
void sink(int *a,int m,int k){
    while(2*k<=m){
        int j=2*k;
        if(j<m && a[j]<a[j+1]) j++;
        //if(a[j]<a[j+1]) j=j+1;
        if(a[k] > a[j]) break;
        swap(a[j],a[k]);
        k = j;
    }
}
void heapSort(int *a,int len){
    for(int k=len/2;k>=1;k--)
        sink(a,len,k);
    for(;len>1;){
        swap(a[1],a[len]);
        len--;
        sink(a,len,1);
    }
}
//-----------------------------------------------------------------------------
//插入排序 --- 直接插入排序 O(n) -> O(n^2)
void insertSort1(int s[],int len)
{
    int tmp,i,j;
    for (i = 1; i <len; i++)
    {
        tmp = s[i];    //将要插入的元素
        for (j = i-1; j >= 0 && s[j] >tmp;j--)
            s[j+1] = s[j];    //数组元素往后移
        //上面的for里j往前试探了一下是否要>temp,所以这里+1就是正确的位置。
        s[j+1] = tmp;
    }
}
void insertSort2(int a[], int len)
{
    for(int i= 1; i<len; i++){
        if(a[i] < a[i-1]){     //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入  
            int j= i-1;
            int x = a[i];      //复制为哨兵，即存储待排序元素
            a[i] = a[i-1];    //先后移一个元素
            while(x < a[j]){  //查找在有序表的插入位置
                a[j+1] = a[j];
                j--;          //元素后移
            }
            a[j+1] = x;       //插入到正确位置
        }
    }
}
//插入排序 --- 希尔排序(缩小增量法) O(n3/2)
void shellSort1(int a[], int len)
{
    //d：n/2、n/4、n/8、、1
    int i, j, gap;
    for (gap = len / 2; gap > 0; gap /= 2) //步长
        for (i = 0; i < gap; i++)        //直接插入排序
        {
            for (j = i + gap; j < len; j += gap)
                if (a[j] < a[j - gap])
                {
                    int temp = a[j];
                    int k = j - gap;
                    while (k >= 0 && a[k] > temp)
                    {
                        a[k + gap] = a[k];
                        k -= gap;
                    }
                    a[k + gap] = temp;
                }
        }
}
//归并排序 --- 归并排序 O(nlogn)
void merge(int *a,int start,int mid,int end)
{
    if(start>mid || mid >end ) return;
    int i=start,j=mid+1,k=0;
    int *L=(int *)malloc((end-start+1)*sizeof(int));
    while(i<=mid && j<=end)
    {
        if(a[i]<a[j])
        {
            L[k++]=a[i++];
        }else
        {
            L[k++]=a[j++];
        }
    }
    while(i<=mid)
        L[k++]=a[i++];
    while(j<=end)
        L[k++]=a[j++];
    for(i=start,j=0;i<=end;i++,j++)
    {
        a[i]=L[j];
    }
    free(L);
}
void mergeSort(int *a, int start,int end)
{
    if(start<end)
    {
        int mid=(start+end)/2;
        mergeSort(a,start,mid);
        mergeSort(a,mid+1,end);
        merge(a,start,mid,end);
    }
}
int main()
{
    int *s = new int [n];
    create(s);

    cout<<"1\\sort by bubbleSort"<<endl;
    bubbleSort(s,n);
    print(s);
    cout<<endl;

    cout<<"2\\sort by insertSort1"<<endl;
    insertSort1(s,n);
    print(s);
    cout<<endl;

    cout<<"3\\sort by quickSort1"<<endl;
    quickSort1(s,0,n);
    print(s);
    cout<<endl;

    cout<<"4\\sort by heapSort"<<endl;
    heapSort(s,n);
    print(s);
    cout<<endl;

    cout<<"5\\sort by shellSort1"<<endl;
    shellSort1(s,n);
    print(s);
    cout<<endl;

    cout<<"6\\sort by mergeSort"<<endl;
    mergeSort(s,0,n);
    print(s);
    cout<<endl;

    cout<<"7\\sort by chooseSort"<<endl;
    chooseSort(s,n);
    print(s);
    cout<<endl;

    return 0;
}
