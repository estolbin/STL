#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<list>
#include<Windows.h>

using namespace std;

const std::string FILENAME = "base.txt";

typedef std::map<std::string, std::list<std::string>> base_list;

void add_to_tree(base_list& GaiMap, std::string numbera, std::string hhhh);
void list_all(base_list& GaiMap);
void read_from_file(base_list& GaiMap);
void add_record(base_list& GaiMap);
void save_file(base_list& GaiMap);
void list_for_number(base_list& GaiMap, std::string number);
void partial_list(base_list& GaiMap);
void main_menu();

void main()
{
    //setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    base_list GaiMap;

    read_from_file(GaiMap);
    int choice;
    std::string car_num;
    do
    {
        main_menu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            list_all(GaiMap);
            break;
        case 2:
            add_record(GaiMap);
            break;
        case 3:
            partial_list(GaiMap);
            break;
        case 4:
            cin.ignore();
            cout << "Номер для поиска: ";
            getline(cin, car_num);
            list_for_number(GaiMap, car_num);
            break;
        case 5:
            cout << "Bye!";
            break;
        default:
            main_menu();
            cin >> choice;
        }

    } while (choice != 5);
}
void add_to_tree(base_list& GaiMap, std::string numbera, std::string hhhh)
{
    auto it = GaiMap.find(numbera);
    if (it == GaiMap.end())
    {
        list<std::string> l;
        l.push_back(hhhh);
        GaiMap.insert(make_pair(numbera, l));
    }
    else
        it->second.push_back(hhhh);
}
void list_all(base_list& GaiMap)
{
    cout << "Номер" << "\t\t" << "Нарушения";
    cout << "\n----------------------------\n";
    for (auto p : GaiMap)
    {
        cout << p.first;
        list<std::string> get = p.second;
        for (auto it = get.begin(); it != get.end(); ++it)
            cout << "\t\t" << (*it) << '\n';
        cout << endl;
    }
}
void read_from_file(base_list& GaiMap)
{
    ifstream fin(FILENAME);
    int n = 0;
    if (fin.is_open())
    {
        std::string buffer;
        while (!fin.eof())
        {
            std::getline(fin, buffer);
            if (buffer.size())
            {
                std::string number = buffer.substr(0, buffer.find(">>"));
                std::string hhh = buffer.substr(buffer.find(">>") + 2);

                add_to_tree(GaiMap, number, hhh);
            }
        }
        fin.close();
    }
}
void add_record(base_list& GaiMap)
{
    std::string number;
    cin.ignore();
    cout << "Введите номер машины: ";
    getline(cin, number);

    std::string hhhh;
    cin.ignore();
    cout << "Введите нарушение: ";
    getline(cin, hhhh);

    add_to_tree(GaiMap, number, hhhh);
    save_file(GaiMap);
}
void save_file(base_list& GaiMap)
{
    ofstream fout;
    fout.open(FILENAME);
    if (!fout) return;

    for (auto p : GaiMap)
    {
        list<std::string> get = p.second;
        for (auto it = get.begin(); it != get.end(); ++it)
            fout << p.first << ">>" << (*it) << '\n';
        fout << endl;
    }
    fout.close();
}
void main_menu()
{
    cout << "\nБаза данных\n";
    cout << "-----------\n";
    cout << "Выберите один из пунктов\n";
    cout << "1 - Вывести весь список\n";
    cout << "2 - Добавить запись\n";
    cout << "3 - Частичный вывод (с..по)\n";
    cout << "4 - Вывод по номеру\n";
    cout << "5 - Выход\n";
    cout << "Выбранное значение: ";
}
void list_for_number(base_list& GaiMap, std::string number)
{
    auto it = GaiMap.find(number);
    if (it == GaiMap.end())
    {
        cout << "Номер \"чист\". Отличный водитель :)" << endl;
    }
    else
    {
        list<std::string> get = it->second;
        cout << "Список нарушений по номеру " << number << endl << endl;
        int count = 0;
        for (auto i = get.begin(); i != get.end(); ++i)
            cout << (++count) << ". " << *i << endl;
    }
}

void partial_list(base_list& GaiMap)
{
    std::string str_itlow, str_itupper;
    base_list::iterator itlow, itupper;

    cin.ignore();
    cout << "Введите начальный номер для вывода: "; getline(cin, str_itlow);
    itlow = GaiMap.lower_bound(str_itlow);
    cin.ignore();
    cout << "Введите конечный номер для вывода: "; getline(cin, str_itupper);
    itupper = GaiMap.upper_bound(str_itupper);

    cout << "Номер" << "\t\t" << "Нарушения";
    cout << "\n----------------------------\n";

    for (base_list::iterator car_it = itlow; car_it != itupper; car_it++)
    {
        cout << car_it->first;
        list<std::string> get = car_it->second;
        for (auto it = get.begin(); it != get.end(); ++it)
            cout << "\t\t" << (*it) << '\n';
        cout << endl;
    }

}