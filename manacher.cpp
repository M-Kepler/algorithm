/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-03-31 09:47:55
* Filename     : manacher.cpp
* Description  : test_file

===================== manacher�㷨 ========================
  ˼��:
  ������,ż���Ļ��Ĵ�һ������,ÿ���������ַ��м����
  һ���������ֵķָ��ַ�,�������Ĵ����ȾͶ���������.
  ����һ����������P[id]����¼��str[id]Ϊ���ĵĻ��Ĵ�����
  ��ĳ���(����P[i]).
  ԭ��: 12212321
  �´�: # 1 # 2 # 2 # 1 # 2 # 3 # 2 # 1 #
  P[i]: 1 2 1 2 5 2 1 4 1 2 1 6 1 2 1 2 1
  P[id]-1 �Ǹû����Ӵ���ԭ���еĳ���(����'#'),��������
  P[id]-1 ��Ϊ����
  ����:
  ��ô��P[i],��ô����P[i]����һ��P[i]?
  ����������������:id(��չ����Ԫ���±�) �� mx=id+P[id]
  mx ����idΪ���ĵ���Ӵ��ı߽�(������mx),
  �ؼ���:
  ��� mx>i ��ô P[i] >= min(P[2*id-i], mx-i)
  .......................�������ô�õ�����?......................
  if mx-i>P[j] then ����֪��,�ֱ���P[i]��P[j]Ϊ���ĵĴ�
  һ����������P[id]Ϊ���ĵĻ��Ĵ���,�������������

  elif mx-i<P[i] then ��s[j]Ϊ���ĵĻ��Ĵ��Ѿ�������s[id]
  Ϊ���ĵĻ��Ĵ�����,���ǿ���֪��j��mx��һ�ΰ뾶�Ļ��Ĵ�
  �ǰ����������,����������ֻ������ʵʵȥƥ����.

  elif mx<i ����޷�ȥ��P[i]��������,ֻ��P[i]=1.
  fi
  j = 2*id-i;��j��i����id�ĶԳƵ�
  ���Ӷ�:
  O(n)
  ===========================================================*/

#include <iostream>
using namespace std;
char s[200002];
char str[400010];
int p[400010];
int min(int a, int b)
{
    return a < b ? a : b;
}
//�����´�
int pre()
{
    int i, j = 0;
    str[j++] = '$';
    for (i = 0; s[i]; i++)
    {
        str[j++] = '#';
        str[j++] = s[i];
    }
    //��ĩβ����#����˸�\0
    str[j++] = '#';
    str[j] = '\0';
    return j;
}
void longestPald_manacher(int n)
{
    int mx = 0, id, i;
    p[0] = 0;
    for (i = 1; i < n; i++)
    {
        if (mx > i)
            p[i] = min(mx - i, p[2 * id - i]);
        else
            p[i] = 1;
        while (str[i - p[i]] == str[i + p[i]])
            p[i]++;
        if (p[i] + i > mx) {
            mx = p[i] + i;
            id = i;
        }
    }
}
int main(int argc, char const *argv[])
{
    while (cin >> s)
    {
        int n = pre();
        longestPald_manacher(n);
        int ans = 0, i;
        for (i = 1; i < n; i++)
            if (p[i] > ans)
                ans = p[i];
        cout << ans - 1 << endl;
    }
    return 0;
}
