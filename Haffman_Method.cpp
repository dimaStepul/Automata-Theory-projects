#include<iostream>
#include<string>
#include<map>


using namespace std;

map <pair<char, int>, int> DKA; //таблица состояний нашего ДКА

////заполняем наш ДКА
void fillingAutomaton() {
	DKA[make_pair('a', 1)] = 7;
	DKA[make_pair('b', 1)] = 7;
	DKA[make_pair('c', 1)] = 7;
	DKA[make_pair('+', 1)] = 2;

	DKA[make_pair('a', 2)] = 7;
	DKA[make_pair('b', 2)] = 3;
	DKA[make_pair('c', 2)] = 7;
	DKA[make_pair('+', 2)] = 2;

	DKA[make_pair('a', 3)] = 4;
	DKA[make_pair('b', 3)] = 7;
	DKA[make_pair('c', 3)] = 7;
	DKA[make_pair('+', 3)] = 7;

	DKA[make_pair('a', 4)] = 4;
	DKA[make_pair('b', 4)] = 5;
	DKA[make_pair('c', 4)] = 7;
	DKA[make_pair('+', 4)] = 7;

	DKA[make_pair('a', 5)] = 4;
	DKA[make_pair('b', 5)] = 8;
	DKA[make_pair('c', 5)] = 7;
	DKA[make_pair('+', 5)] = 7;

	DKA[make_pair('a', 6)] = 7;
	DKA[make_pair('b', 6)] = 7;
	DKA[make_pair('c', 6)] = 7;
	DKA[make_pair('+', 6)] = 7;

	DKA[make_pair('a', 7)] = 7;
	DKA[make_pair('b', 7)] = 7;
	DKA[make_pair('c', 7)] = 7;
	DKA[make_pair('+', 7)] = 7;

	DKA[make_pair('a', 8)] = 4;
	DKA[make_pair('b', 8)] = 8;
	DKA[make_pair('c', 8)] = 7;
	DKA[make_pair('+', 8)] = 6;
}


bool check_RegularExpr(string& substring) {
	int	currentCondition = 1; // по умолчанию начальное состояние = 1
	int len = substring.length();
	for (int i = 0; i != len; ++i) {
		if (currentCondition == 7)
			return false; //если дьявольское , то сразу возвращаем false
		currentCondition = DKA[make_pair(substring[i], currentCondition)];
		/*
		смотрим, какому состоянию соответствует пара(символ,текущее состояние)
		*/
	}
	return (currentCondition == 6);//проверяем, было ли достигнуто финальное состояние
}


int main() {
	fillingAutomaton();  //заполняем наш ДКА

	ios_base::sync_with_stdio(false); //ускоряем наш ввод\вывод
	cin.tie(nullptr);
	cout.tie(nullptr);

	//вводим количество тестов
	cout << "Input numbers of tests: ";
	int testAmount;
	cin >> testAmount; cin.ignore();
	string input; input.reserve(100);
	string temp = "";
	temp.reserve(30);

	bool isAnyStringFound = false; //флаг, который помогает нам понять, была ли хотя бы одна подходящая цепочка 
	for (int i = 0; i != testAmount; ++i) {
		getline(cin, input);
		bool flagStartCheck = false;
		int startIndex; //индекс начала правильной цепочки
		int lengthInput = input.length();
		for (int j = 0; j != lengthInput; ++j) {
			if (flagStartCheck) // если до этого был символ '+', добавляем в substring 
				temp.push_back(input[j]);
			if (input[j] == '+' && flagStartCheck) {// если встретился + второй раз, проверяем, удовлетворяет ли строка нашему ДКА
				if (check_RegularExpr(temp)) {
					cout << startIndex + 1 << ": " << temp << endl;
					isAnyStringFound = true;
					temp = "";
				}
				else {  /*
						если не удовлетворяет, обнуляем temp  и, так как нам встретился символ '+',
						запоминаем начало (возможно правильной) подстроки
						*/
					startIndex = j;
					temp = "";
				}
			}
			if (input[j] == '+') { // если встретился '+', запоминаем индекс 
				flagStartCheck = true;
				temp.push_back(input[j]);	
				startIndex = j;
			}
		}
	}
	if (!isAnyStringFound) { // если не найдено ни одной подходящей цепочки
		cout << "Strings don't find" << endl;
	}
	return 0;
}
