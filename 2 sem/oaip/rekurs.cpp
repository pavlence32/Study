#include <iostream>
#include <string.h>
using namespace std;
int kolnechet(int a, int i)
{
    if (a < 10 && a % 2 != 0)
        return i + 1;
    else if (a < 10)
        return i;
    else if ((a % 10) % 2 != 0)
        return kolnechet(a / 10, i + 1);
    else
        return kolnechet(a / 10, i);
}
int maxinch(int a, int max)
{
    if (a < 10)
        return a > max ? a : max;
    if (max < a % 10)
        return maxinch(a / 10, a % 10);
    else
        return maxinch(a / 10, max);
}
int sumnechet(int a)
{
    if (a < 10)
        return (a % 2 != 0) ? a : 0;
    if ((a % 10) % 2 != 0)
        return a % 10 + sumnechet(a / 10);
    else
        return sumnechet(a / 10);
}
int maxArr(int a[], int n)
{
    if (n == 1)
        return a[0];
    int m = maxArr(a, n - 1);
    return a[n - 1] > m ? a[n - 1] : m;
}
bool palindrom(const char *a, int l, int r)
{
    if (l >= r)
        return true;
    else if (a[l] == a[r])
        return palindrom(a, l + 1, r - 1);
    else
        return false;
}
int main()
{
    char a[20];
    cin.getline(a, 20);
    cout << palindrom(a, 0, strlen(a) - 1);
}