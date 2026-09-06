#include <iostream>
using namespace std;
int main()
{
  setlocale(LC_ALL, "ru_RU.UTF-8");
  int strok;
  int colon;
  cout << "Введите кол-во строк " << endl;
  cin >> strok;
  cout << "Введите кол-во столбцов " << endl;
  cin >> colon;
  int** arr = new int*[strok];
  for (int i = 0; i < strok; i++)
  {
    arr[i] = new int[colon];
  }
  cout << "Введите элементы" << endl;
  for (int i = 0; i < strok; i++)
  {
    for (int j = 0; j < colon; j++)
    {
      cin >> arr[i][j];
    }
  }
  cout<<endl;
  for (int i = 0; i < strok-1; i++)
  {
    for (int j = 0; j < strok - 1; j++)
    {
      if (arr[j][0]>arr[j+1][0])
      {
        int* temp = arr[j];
        arr[j ]  = arr[j+1];
        arr[j + 1] = temp;
      }
    }
  }
  for (int i = 0; i < strok; i++)
  {
    for (int j = 0; j < colon; j++)
    {
      cout << arr[i][j]<<" ";
    }
    cout << endl;
  }
  for (int i = 0; i < strok; i++)
  {
    delete [] arr[i];
  }
  delete[] arr;
  return 0;
}