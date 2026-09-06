#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	const int SIZE = 10;
	int arr[SIZE], summa = 0;
	int choice_vod;
	int i=0;
	cout << "�������� ���� �������� �������" << endl;
	cout << "1-keyboard" << endl;
	cout << "2-random" << endl; 
	cin >> choice_vod;
	switch (choice_vod)
	{
	case 1: cout << "������� �������� ���������" << endl; 
		for (int i = 0; i < SIZE; i++)
		{
			cin >> arr[i]; 
		}
		for (int i = 0; i < SIZE; i++)              // rand() % (�������� - ������� + 1) + �������
		{
			cout << arr[i] << " ";
		}
		break;
	case 2:
		for (int i = 0; i < SIZE; i++)
		{
			arr[i] = rand() % 101-30;
		}
		for (int i = 0; i < SIZE; i++)
		{
			cout << arr[i] << " " ;
		}
		break;
	default:
		cout << "GG";
		return 0;
	}
	cout << endl;
	int polozindex=-1 ;
	for (int i = 0; i < SIZE; i++)
	{
		if (arr[i] > 0)
		{
			polozindex = i;
			break;
		}
	}
		if (polozindex == -1) {
			cout << "��� ������������� ���������" << endl;
			return 0;
		}
		int negaindex = -1;

		for (int g = 0; g < SIZE; g++)
		{
			if (arr[g] < 0)
			{
				negaindex = g;
				break;
			}
		}
				switch (negaindex)
				{
				case -1:
					cout << "��� ������������� ��������� " << endl;
					return 0;
				case 0:
					cout << "������������� ������" << endl;
					return 0;
				}
			if (negaindex == polozindex + 2)
			{
				summa = arr[1 + polozindex];
				cout << "����� ����� " << summa << endl;
				return 0;
			}
			 if (negaindex == polozindex + 1)
			{
				cout << "���� ����� ����� ����������" << endl;
				return 0;
			}
			 for (int i = polozindex + 1; i < negaindex; i++) {
				 summa += arr[i];
			 }
			 cout << "����� ����� " << summa << endl;
			 return 0;
}




	