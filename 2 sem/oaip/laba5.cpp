#include <iostream>
using namespace std;
struct Pole
{
    char punnaz[15];
    int nomer;
    char vremya[6];
};
bool unique(Pole a[10], int i)
{
    return a[i].nomer == 0;
}
int makehash(int a, Pole j[10])
{
    int i = a % 10;
    int c;
    if (unique(j, i))
        return i;
    else
    {
        c = 1 + (a % (10 - 2));
        while (true)
        {
            i -= c;
            if (i < 0)
                i += 10;
            if (unique(j, i))
                break;
        }
        return i;
    }
}
void prosm(Pole arr[8])
{
    for (int i = 0; i < 8; i++)
        cout << arr[i].punnaz << " " << arr[i].nomer << " " << arr[i].vremya << "\n";
}
void prostohash(Pole hassh[20])
{
    for (int i = 0; i < 10; i++)
    {
        cout << "[" << i << "] ";
        if (hassh[i].nomer == 0)
            cout << "empty\n";
        else
            cout << hassh[i].punnaz << " " << hassh[i].nomer << " " << hassh[i].vremya << "\n";
    }
}
void poiskr(Pole hassh[10])
{
    cout << "Enter nomer\n";
    int key;
    cin >> key;

    int n = key % 10;
    int c = 1 + (key % 8);

    for (int j = 0; j < 10; j++)
    {
        if (hassh[n].nomer == key)
        {
            cout << "Found: " << hassh[n].punnaz << " "
                 << hassh[n].nomer << " " << hassh[n].vremya << "\n";
            return;
        }
        n -= c;
        if (n < 0)
            n += 10;
    }
    cout << "Not found\n";
}
int main()
{
    Pole arr[8];
    Pole hassh[10] = {};
    int c;
    cout << "Enter elements\n";
    for (int i = 0; i < 8; i++)
    {
        cout << "Destination\n";
        cin.getline(arr[i].punnaz, 15);
        cout << "Nomer\n";
        cin >> arr[i].nomer;
        cin.ignore();
        cout << "Time\n";
        cin.getline(arr[i].vremya, 6);
    }
    for (int i = 0; i < 8; i++)
    {
        c = makehash(arr[i].nomer, hassh);
        hassh[c] = arr[i];
    }
    poiskr(hassh);
    prosm(arr);
    prostohash(hassh);
    return 0;
}