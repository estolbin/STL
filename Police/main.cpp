#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<conio.h>
#include<Windows.h>
#include<map>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

const std::map<int, std::string> CRIMES =
{
	std::pair<int, std::string>(1, "Проезд на красный."),
	std::pair<int, std::string>(2, "Превышение скорости."),
	std::pair<int, std::string>(3, "Езда по встречной полосе."),
	std::pair<int, std::string>(4, "Дрифт на перекрестке."),
	std::pair<int, std::string>(5, "Парковка в неположенном месте."),
	std::pair<int, std::string>(6, "Оскорбление офицера."),
	std::pair<int, std::string>(7, "Вождение в нетрезвом состоянии."),
	std::pair<int, std::string>(8, "Вождение без документов."),
};

class Crime
{
	int id;
	std::string place;
public:
	int get_id() const { return id; }
	const std::string get_place() const { return place; }
	Crime(int id, std::string place):id(id), place(place) {}
	~Crime(){}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << CRIMES.at(obj.get_id()) << " - " << obj.get_place();
}

std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_id() << obj.get_place();
	return ofs;
}

void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
void load(std::map<std::string, std::list<Crime>>& base, const std::string filename);;
int check_crime();
std::string input_place();
std::string input_plate();
void menu(std::map<std::string, std::list<Crime>>& base, const std::string& filename);

//#define ADDITION_TO_BASE

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::map<std::string, std::list<Crime>> base;
	load(base, "base.txt");
	print(base);

#ifdef ADDITION_TO_BASE
	std::string licence_plate;	
	int id;
	std::string place;
	cout << "Введите номер автомобиля: "; cin >> licence_plate;
	/*cout << "Выберите правонарушение:  "; cin >> id;
	id = check_crime();
	cout << "Введите место происшествия:";
	cin.ignore();
	std::getline(std::cin, place);*/
	//base[licence_plate].push_back(Crime(id, place));

	base[licence_plate].push_back(Crime(check_crime(), input_place()));
	print(base);
#endif // ADDITION_TO_BASE

	menu(base, "base.txt");

	print(base);
	save(base, "base.txt");
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	system("CLS");	
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		cout << it->first << ":\n";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			cout << *jt << ";\n";
		}
		cout << "\n-----------------------------------------------\n";
	}
	system("PAUSE");
}
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		fout << it->first << ":";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			fout << *jt << ",";
		}
		fout.seekp(-1, std::ios::cur);
		fout << ";\n";
	}
	fout.close();
	std::string command = "notepad ";
	command += filename;
	system(command.c_str());
}
void load(std::map<std::string, std::list<Crime>>& base, const std::string filename)
{
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		//TODO: read file
		while (!fin.eof())
		{
			std::string licence_plate;
			std::string all_crimes;
			std::getline(fin, licence_plate, ':');
			std::getline(fin, all_crimes);
			if (licence_plate.empty() || all_crimes.empty())continue;
			all_crimes.erase(all_crimes.find_last_of(';'));
			for (int start = -1, end = 0; end != std::string::npos; start = end)
			{
				start++;	
				end = all_crimes.find(',', start);
				std::string place = all_crimes.substr(start, end - start);
				int id = std::stoi(place, 0, 10);
				place.erase(0, 1);
				//place.erase(place.find_last_of(';'));
				base[licence_plate].push_back(Crime(id, place));
			}
		}

		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
}
int check_crime()
{
	system("CLS");
	for (std::pair<int, std::string> i : CRIMES)
	{
		cout << i.first << tab << i.second << endl;
	}
	int id;
	cout << "Выбор правонарушения: "; cin >> id;
	return id;
}
std::string input_place()
{
	std::string place;
	cout << "Введите место происшествия:";
	cin.ignore();
	std::getline(std::cin, place);
	return place;
}
std::string input_plate()
{
	std::string licence_plate;	
	std::string place;
	cout << "Введите номер автомобиля: "; cin >> licence_plate;
	return licence_plate;
}
void menu(std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	char key;
	do
	{
		system("CLS");
		cout << "1. Вывод всей базы;" << endl;
		cout << "2. Вывод по номерному знаку;" << endl;
		cout << "3. Вывод по диапазону номеров;" << endl;
		cout << "4. Выборка по шаблону;" << endl;
		cout << "5. Выборка по правонарушению;" << endl;
		cout << "6. Выборка по адресам;" << endl;
		cout << "7. Сохранение базы;" << endl;
		cout << "8. Загрузка базы;" << endl;
		cout << "9. Добавление записи;" << endl;
		cout << "Esc - Выход из программы;" << endl;
		key = _getch();
		switch (key)
		{
		case '1': print(base); break;
		case '2': 
		case '3': 
		case '4': 
		case '5': 
		case '6': cout << "Эта опция еще не добавлена. Ожидается в следующем релизе\n";
			system("PAUSE");
			break;
		case '7': save(base, filename); break;
		case '8': load(base, filename); break;
		case '9': base[input_plate()].push_back(Crime(check_crime(), input_place())); break;
		}
	} while (key != 27);
}