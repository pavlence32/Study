#include <iostream>
#include <string.h> 
#include <cstdlib>
using namespace std;
const int N = 30;
struct car {
	char marka[N];
	int max_speed;
	int year;
}massivcars[8];

struct spisok {
	car data;
	spisok* next;
}*table[10];

int getHash(int year) {
	return year % 10;
}

void insert(car newCar) {
	int index = getHash(newCar.year);

	spisok* newspisok = new spisok;
	newspisok->data = newCar;

	newspisok->next = table[index];
	table[index] = newspisok;
}


car* find(int searchYear) {
	int index = getHash(searchYear);
	spisok* current = table[index];

	while (current != nullptr) {
		if (current->data.year == searchYear) {
			return &(current->data);
		}
		current = current->next;
	}
	return nullptr;
}

void clearTable() {
	for (int i = 0; i < 10; i++) {
		spisok* current = table[i];
		while (current != nullptr) {
			spisok* toDelete = current;
			current = current->next;
			delete toDelete;
		}
		table[i] = nullptr;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");

	for (int i = 0; i < 10; i++) 
		table[i] = nullptr;
	
	for (int i = 0; i < 3; i++) {
		cout << "Введите данные для " << i + 1 << " автомобиля " << endl;
		cout << "Марка: ";
		char marka[N];
		cin >> marka;
		strcpy_s(massivcars[i].marka, marka);
		cout << "Максимальная скорость: ";
		int speed;
		cin >> speed;
		massivcars[i].max_speed = speed;
		cout << "Год выпуска: ";
		int year;
		cin >> year;
		massivcars[i].year = year;

		insert(massivcars[i]);
		cout << endl;
	}

	cout << "\n Исходный массив " << endl;
	for (int i = 0; i < 8; i++) {
		cout << i + 1 << ". " << massivcars[i].marka << " | "
			<< massivcars[i].max_speed << " км/ч | "
			<< massivcars[i].year << " год" << endl;
	}

	cout << "\n Хеш-таблица (Метод цепочек) " << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Ячейка [" << i << "]: ";
		if (table[i] != nullptr) {
			spisok* current = table[i];
			while (current != nullptr) {
				cout << current->data.marka << " (" << current->data.year << ")";
				if (current->next != nullptr) cout << " -> ";
				current = current->next;
			}
		}
		else cout << "пусто";
		
		cout << endl;
	}

	cout << "\nВведите год выпуска для поиска в таблице: ";
	int searchYear;
	cin >> searchYear;

	car* foundCar = find(searchYear);
	if (foundCar != nullptr) {
		int index = getHash(searchYear);
		cout << "\n[РЕЗУЛЬТАТ ПОИСКА]" << endl;
		cout << "Найдено в цепочке ячейки: " << index << endl;
		cout << "Марка: " << foundCar->marka << endl;
		cout << "Макс. скорость: " << foundCar->max_speed << endl;
		cout << "Год выпуска: " << foundCar->year << endl;
	}
	else cout << "\nАвтомобиль с таким годом выпуска не найден." << endl;
	
	clearTable();

	return 0;
}