/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-08 08:00:23
* Filename     : sort.cpp
* Description  : test_file
**********************************************************/

/*============================================================================
排序：
http://blog.csdn.net/hguisu/article/details/7776068
非常详细http://blog.csdn.net/jnu_simba/article/details/9705111
============================================================================*/
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
using namespace std;
const int  n = 10;
void create(int a[])
{
    srand((unsigned)time(NULL));
    for(int i =0;i<10;i++)
        a[i] = rand()%100+1;
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
/*
 * 比较相邻的两个元素，然后考虑是否交换
 */
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
/*
 *找一个数key，作为参照, 从序列两端开始扫，
 *找出右边第一个比key小的数a，
 *左边第一个比key大的数b，交换a b
 *j往←，i往→，当i=j时，交换a[i]和key
 *交换之后，肯定是key_left < key < key_right
 *然后就像二分法那样递归地对左右两边同样的操作
 */
void quickSort(int *a,int left,int right)
{
    int i,j,t,temp;
    if(left>right)
        return;
    temp=a[left];
    i=left;
    j=right;
    while(i!=j)
    {
        //顺序很重要,先让j往左走
        //因为当i=j的时候是要交换s[j]和key的
        //所以必须j的方向必须是寻找<key的方向
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
    quickSort(a,left,i-1);
    quickSort(a,i+1,right);
}

//选择排序 --- 直接选择排序 O(n) -> O(n^2)
/*
 * 每趟都从未排序的序列b中和b序列的第一个数b.1做比较，
 * 如果比它小，就更新minIndex，循环后，肯定是最小元素的index，
 * 然后b[minindex]和b.1交换
 */
void chooseSort(int s[],int len)
{
    int i,j,minIndex,tmp;
    for (i=0; i<len ; i++)
    {
        minIndex = i;
        //找出未排序中最小元素的下标
        for (j=i+1; j<len ; j++)
        {
            if (s [j]< s[minIndex])
                minIndex = j;
        }
        //交换最小元素和s[j];
        if (minIndex != i)
            swap(s[minIndex], s[i]);
    }
}

//选择排序 --- 堆排序 O(nlogn)
/*
 * 大根堆:每个节点的值都>=左右孩子节点的值o
 *
 * 将待排序的序列构造成一个大顶堆.此时,整个序列
 * 的最大值就是堆顶 的根结点.将它移走(其实就是将其
 * 与堆数组的末尾元素交换, 此时末尾元素就是最大值),
 * 然后将剩余的n-1个序列重新构造成一个堆,这样就会得到
 * n个元素的次大值.如此反复执行,便能得到一个有序序列了。
 * 时间复杂度为 O(nlogn),好于冒泡,简单选择,直接插入的O(n^2)
 *
 */
void sink(int *a,int m,int k)
{
    while(2*k<=m)
    {
        int j=2*k;
        if(j<m && a[j]<a[j+1])
            j++;
        if(a[k] > a[j]) break;
        swap(a[j],a[k]);
        k = j;
    }
}
void heapSort(int *a,int len)
{
    for(int k=len/2;k>=1;k--)
        sink(a,len,k);
    for(;len>1;){
        swap(a[1],a[len]);
        len--;
        sink(a,len,1);
    }
}

//插入排序 --- 直接插入排序 O(n) -> O(n^2)
/*
 * 已排序的序列为A,初始只有一个元素，从s中将元素插入到a中
 * 只要将A中所有小与S[0]的元素后移一位，然后把S[0]放入就行了
 */
void insertSort1(int s[],int len)
{
    int tmp,i,j;
    for (i = 1; i <len; i++)
    {
        //1 2 3 5 6 4 9
        tmp = s[i];    //要插入的元素
        // 先将s[i]存入tmp，在元素后移时不必多次存入tmp
        for (j = i-1; j >= 0 && s[j]>tmp; j--)
            s[j+1] = s[j];
        //for里j往前试探了一下是否要>temp,所以这里+1就是正确的位置。
        s[j+1] = tmp;
    }
}
void insertSort2(int a[], int len)
{
    for(int i= 1; i<len; i++)
    {
        if(a[i] < a[i-1])
        {     //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入
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

//插入排序 --- 希尔排序(缩小增量法) O(n^(3/2))
/*
 * 从S中每隔gap取一次数，在这些数中进行分组insertsort
 * 并不是实实在在地抽取数据出来,
 * gap的选取一般是 n/2、n/4、n/8、.... 、1
 */
void shellSort(int a[], int len)
{
    // 6 2 9 1 5 4
    // 6 1 \ 2 5 \ 9 4    3
    // 1 2 4 6 5 9
    int i, j, gap;
    for (gap = len / 2; gap > 0; gap /= 2) //步长
    {
        //循环gap次，这样取过的元素不会重复被取
        for (i = 0; i < gap; i++)        //直接插入排序
        {
            for (j = i + gap; j < len; j += gap)
            {
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
    }
}

//归并排序 --- 归并排序 O(nlogn)
/*
 * 假设初始序列含有n个记录,则可以看成n个有序的子序列,每个子序列的长度为1,然后
 * 两两归并,得到(不小于n/2的最小整数)个长度为2或1的有序子序列,再两两归并,...
 * 如此重复,直至得到一个长度为n的有序序列为止,这种排序方法称为2路归并排序
 * 时间复杂度为O(nlogn),空间复杂度为O(n+logn),如果非递归实现归并,则避免了递归时深度为logn的栈空间
 * 空间复杂度为O(n)
 */
void merge(int *a,int start,int mid,int end)
{
    if(start>mid || mid >end )
        return;
    int i=start,j=mid+1,k=0;
    int *L=(int *)malloc((end-start+1)*sizeof(int));
    while(i<=mid && j<=end)
    {
        if(a[i]<a[j])
            L[k++]=a[i++];
        else
            L[k++]=a[j++];
    }
    //将剩下部分复制到L
    while(i<=mid)
        L[k++]=a[i++];
    while(j<=end)
        L[k++]=a[j++];
    //将排序好的序列从临时L重新复制到a中
    for(i=start,j=0;i<=end;i++,j++)
        a[i]=L[j];
    //free(L);
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

//煎饼排序
/*
 * 1. 找到数组里最大的数 max，把arr[0,max]反转，这样 max 就到最上面了
 * 2. 然后再把整个数组arr 反转，这样 max 就到达最后面了
 * 3. 再对去掉 max 后的数组进行 1和2 的操作
 */
void flip(int*arr, int i)
{
    // 逆置数组 arr[0..i]
    int temp, start = 0;
    while(start <i)
    {
        temp = arr[start];
        arr[start]=arr[i];
        arr[i]=temp;
        start++;
        i--;
    }
}
int findMax(int*arr, int n)
{
    // 找出 arr[0..n-1] 内最大的元素的下标
    int mi, i;
    for (mi = 0, i = 0; i < n; ++i)
        if (arr[i] > arr[mi])
            mi = i;
    return mi;
}
void pancakeSort(int *arr, int n)
{
    for (int curr_size = n; curr_size > 1; --curr_size)
    {
        int mi = findMax(arr, curr_size);
        if (mi != curr_size-1)
        {
            flip(arr, mi);
            flip(arr, curr_size-1);
        }
    }
}

int main()
{
    int *s = new int [n];
    create(s);

    cout<<"bubbleSort"<<endl;
    bubbleSort(s,n);
    print(s);
    cout<<endl;

    cout<<"insertSort1"<<endl;
    insertSort1(s,n);
    print(s);
    cout<<endl;

    cout<<"quickSort"<<endl;
    quickSort(s,0,n);
    print(s);
    cout<<endl;

    cout<<"heapSort"<<endl;
    heapSort(s,n);
    print(s);
    cout<<endl;

    cout<<"shellSort"<<endl;
    shellSort(s,n);
    print(s);
    cout<<endl;

    cout<<"mergeSort"<<endl;
    mergeSort(s,0,n);
    print(s);
    cout<<endl;

    cout<<"chooseSort"<<endl;
    chooseSort(s,n);
    print(s);
    cout<<endl;

    cout<<"pancakeSort"<<endl;
    pancakeSort(s,n);
    print(s);
    cout<<endl;

    return 0;
}
