#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<conio.h>
#include<Windows.h>
#include<map>
#include<ctime>
#include<iomanip>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

const std::map<int, std::string> CRIMES =
{
	std::pair<int, std::string>(1, "Проезд на красный.             "),
	std::pair<int, std::string>(2, "Превышение скорости.           "),
	std::pair<int, std::string>(3, "Езда по встречной полосе.      "),
	std::pair<int, std::string>(4, "Дрифт на перекрестке.          "),
	std::pair<int, std::string>(5, "Парковка в неположенном месте. "),
	std::pair<int, std::string>(6, "Оскорбление офицера.           "),
	std::pair<int, std::string>(7, "Вождение в нетрезвом состоянии."),
	std::pair<int, std::string>(8, "Вождение без документов.       "),
};

class DateCrime
{
	int year;
	int month;
	int day;
public:
	int get_year() const { return year; }
	int get_month() const { return month; }
	int get_day() const { return day; }
	DateCrime()
	{
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		this->year = 1900 + now->tm_year;
		this->month = 1 + now->tm_mon;
		this->day = now->tm_mday;
	}
	DateCrime(int year, int month, int day):year(year), month(month), day(day) {}
	DateCrime(const DateCrime& other): year(other.year), month(other.month), day(other.day) {}
	~DateCrime(){}

	bool operator==(const DateCrime& other)
	{
		return (year == other.year && month == other.month && day == other.day);
	}
	bool operator!=(const DateCrime& other)
	{
		return (year != other.year && month != other.month && day != other.day);
	}

	void print() const
	{
		cout << year << "-" << month << "-" << day;
	}
};

std::ostream& operator<<(std::ostream& os, const DateCrime& obj)
{
	return os << obj.get_year() << "-" << obj.get_month() << "-" << obj.get_day();
}
std::ofstream& operator<<(std::ofstream& ofs, const DateCrime& obj)
{
	ofs << obj.get_year() << "-" << obj.get_month() << "-" << obj.get_day();
	return ofs;
}

class Crime
{
	int id;
	std::string place;
	DateCrime crime_date;
public:
	int get_id() const { return id; }
	const std::string get_place() const { return place; }
	DateCrime get_crime_date() const { return crime_date; }
	Crime(int id, std::string place):id(id), place(place), crime_date(DateCrime()) {}
	Crime(int id, std::string place, DateCrime crime_date):id(id), place(place), crime_date(crime_date) {}
	Crime(const Crime& other) :id(other.get_id()), place(other.get_place()), crime_date(other.get_crime_date()) {}
	~Crime(){}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << std::setw(20) << CRIMES.at(obj.get_id()) << 
		std::setw(3) << " | " << 
		std::setw(20) << obj.get_place() << 
		std::setw(4) << " | " << 
		std::setw(12) << obj.get_crime_date();
}
std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_id() << obj.get_place() << "[" << obj.get_crime_date() << "]";
	return ofs;
}

void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
void load(std::map<std::string, std::list<Crime>>& base, const std::string filename);;
int check_crime();
std::string input_place();
std::string input_plate();
void menu(std::map<std::string, std::list<Crime>>& base, const std::string& filename);
void print_for_number(const std::map<std::string, std::list<Crime>>& base);
void print_for_range(const std::map<std::string, std::list<Crime>>& base);
void print_for_crime(const std::map<std::string, std::list<Crime>>& base);
void print_for_address(const std::map<std::string, std::list<Crime>>& base);
void print_for_date(const std::map<std::string, std::list<Crime>>& base);
std::string date_string(std::string s, int start);
DateCrime input_date();
//#define ADDITION_TO_BASE

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::map<std::string, std::list<Crime>> base;
	load(base, "base.txt");
	//print(base);

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

	//print(base);
	save(base, "base.txt");
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	system("cls");	
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		cout << it->first << ":\n";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			cout << *jt << ";\n";
		}
		cout << "------------------------------------------------------------------------------\n";
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
				//end = all_crimes.find('[', start);
				std::string place = all_crimes.substr(start, end - start);

				// parse date
				//size_t endPos = all_crimes.find("]") - (all_crimes.find("[") + 1) + all_crimes.size();
				std::string date_crime = date_string(all_crimes, start);//all_crimes.substr(all_crimes.find("[")+1, endPos);
				int year = std::stoi(date_crime.substr(0, 4), 0, 10);
				int month = std::stoi(date_crime.substr(5, date_crime.find("-")), 0, 10);
				int day = std::stoi(date_crime.substr(date_crime.find_last_of("-")+1), 0, 10);


				int id = std::stoi(place, 0, 10);
				place.erase(0, 1);
				place.erase(place.find("["));
				//place.erase(place.find_last_of(';'));
				base[licence_plate].push_back(Crime(id, place, DateCrime(year, month, day)));
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
	cin.ignore();
	cout << "Введите место происшествия: ";
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
		system("cls");
		cout << "1. Вывод всей базы;" << endl;
		cout << "2. Вывод по номерному знаку;" << endl;
		cout << "3. Вывод по диапазону номеров;" << endl;
		cout << "4. Выборка по шаблону (на дату);" << endl;
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
		case '2': print_for_number(base); break;
		case '3': print_for_range(base); break;
		case '4': print_for_date(base); break;
		case '5': print_for_crime(base); break;
		case '6': print_for_address(base); break;
		case '7': save(base, filename); break;
		case '8': load(base, filename); break;
		case '9': base[input_plate()].push_back(Crime(check_crime(), input_place(), DateCrime())); break;
		}
	} while (key != 27);
}
void print_for_number(const std::map<std::string, std::list<Crime>>& base)
{
	std::string number;
	cout << "Введите номер для печати: "; getline(cin, number);
	std::map<std::string, std::list<Crime>>::const_iterator it = base.find(number);
	if (it == base.cend())
	{
		cout << "Ничего не найдено";
		return;
	}
	else
	{
		system("cls");
		cout << it->first << ":\n";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			cout << *jt << ";\n";
		}
		cout << "\n-----------------------------------------------\n";
	}
	system("pause");

}
void print_for_range(const std::map<std::string, std::list<Crime>>& base)
{
	system("cls");
	std::string number_beg, number_end;
	cin.ignore();
	cout << "Введите начало диапазона: "; getline(cin, number_beg);
	cin.ignore();
	cout << "Введите конец диапазона: "; getline(cin, number_end);

	std::map<std::string, std::list<Crime>> temp_map;
	temp_map.insert(base.lower_bound(number_beg), base.upper_bound(number_end));
	if (!temp_map.empty())
		print(temp_map);
	else
	{
		cout << "Диапазон задан неверно.";
		system("pause");
	}

}
void print_for_crime(const std::map<std::string, std::list<Crime>>& base)
{
	system("cls");
	int crime = check_crime();
	std::map<std::string, std::list<Crime>> temp_map;

	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end();++it)
	{
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			if (jt->get_id() == crime)
			{
				temp_map[it->first].push_back(Crime(*jt));
			}
		}
	}
	if (!temp_map.empty())
		print(temp_map);
	else
	{
		cout << "По данному нарушению нет зарегистрированных \"протоколов\"";
		system("pause");
	}
	
}
void print_for_address(const std::map<std::string, std::list<Crime>>& base)
{
	system("cls");
	std::string addr = input_place();
	std::map<std::string, std::list<Crime>> temp_map;

	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			if (jt->get_place().find(addr) != std::string::npos)
			{
				temp_map[it->first].push_back(Crime(*jt));
			}
		}
	}
	if (!temp_map.empty())
		print(temp_map);
	else
	{
		cout << "По данному адресу нет зарегистированных протоколов.";
		system("pause");
	}
}
void print_for_date(const std::map<std::string, std::list<Crime>>& base)
{
	system("cls");
	DateCrime date_for_search = input_date();
	std::map<std::string, std::list<Crime>> temp_map;

	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			if (jt->get_crime_date() == date_for_search)
				temp_map[it->first].push_back(Crime(*jt));
		}
	}
	if (!temp_map.empty())
		print(temp_map);
	else
	{
		cout << "На данную дату не было зарегистировано нарушений.";
		system("pause");
	}
}
std::string date_string(std::string s, int start)
{
	size_t start_pos = s.find("[", start);
	size_t end_pos = s.find("]", start_pos);

	if ((end_pos != std::string::npos) && start_pos < end_pos)
	{
		start_pos += 1;
		return s.substr(start_pos, end_pos - start_pos);
	}
	return "";
}
DateCrime input_date()
{
	system("cls");
	int year, month, day;
	cout << "Год: "; cin >> year;
	cout << "Месяц: "; cin >> month;
	cout << "Число: "; cin >> day;

	return DateCrime(year, month, day);
}