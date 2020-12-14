
#include<iostream>
#include<stack>
#include<algorithm>
#include<string>
#include<map>

using namespace std;

map  <string, string> PDA;
stack <char> magazin;

// Заполняем наш МП автомат
void automataFilling() {
	PDA["00Z"] = "00Z";
	PDA["000"] = "000";
	PDA["01Z"] = "11Z";
	PDA["010"] = "110";

	PDA["111"] = "111";

	PDA["101"] = "21";
	PDA["201"] = "1E";

	PDA["100"] = "30";
	PDA["300"] = "4E";
	PDA["400"] = "30";
	PDA["4Z"] = "5Z";
};


//функция проверки входной цепочки символов
string CheckExpression(string &input) {

	string mistakePosition;
	// инициализация начального состояния 
	string currentCondition = "0"; 

	
	string nextStr; nextStr.reserve(4);

	//устанавливаем маркер дна
	magazin.push('Z');

	int len = input.length();
	string key; key.reserve(4);

	string currentSymbol;
	string result; result.reserve(30);

	//просто проходимся по строке  посимвольно 
	int i;
	for ( i = 0; i != len; ++i) {
		
		//запоминаем текущий символ
		currentSymbol = input[i];
	
		//создаем ключ: текущее состояние + текущий символ + верхний символ на стеке 
		key = currentCondition + currentSymbol + magazin.top();

		//далее будем искать этот ключ в нашем автомате
		nextStr = PDA[key];
		int nextStr_len = nextStr.length();
		if (nextStr_len == 0) {
			static string mistakePosition(to_string(i + 1));
			result = string("Ошибка в позиции " + mistakePosition  + string(" Неожиданный символ ") + currentSymbol);
			return result;
		}
		else {
			//переходим в следующее состояние по таблице переходов
			currentCondition = nextStr[0];
			
			//смотрим, нужно ли что-то извлечь из стека
			if (nextStr.back() == 'E') {
				magazin.pop();
			}
			
			//добавляем символы в стек ,если это нужно
			if (nextStr_len == 3) {
				char temp = nextStr[1];
				magazin.push(temp);
			}
		}
	}
	if (magazin.top() == 'Z')
		return string("данная строка принадлежит языку");
	else
		return string("Ошибка в позиции " + to_string((i  + 1)) + string(" Неожиданный символ ") + currentSymbol); 
}


int main() {
	setlocale(LC_ALL, "Russian");

	//инициализируем наш автомат
	automataFilling();

	// вводим строку 
	string input; input.reserve(100);
	cout << "Введите строку: ";
	getline(cin, input);

	// проверяем цепочку, которую нам подали на ввод
	cout << CheckExpression(input);
	
	return 0;
}
