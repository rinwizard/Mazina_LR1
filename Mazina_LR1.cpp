#include <iostream>
#include <string>
#include <fstream>
#include <vector>



struct Pipe
{
    std::string KilometerMarker;
    float Length;
    int Diameter;
    bool InRepair;
};

struct Compressor_Station
{
    std::string Name;
    int WorkshopAmount;
    int WorkshopInWorkAmount;
    std::string StationClass;

};


Pipe Pipe1;
Compressor_Station CS1;
bool is_pipe = false;
bool is_cs = false;


void task1() // добавить трубу
{
    is_pipe = true;
    std::string KilometerMarker1;
    std::cout << "Добавление трубы...\nВведите километровый маркер: \n";
    std::cin >> KilometerMarker1;
    Pipe1.KilometerMarker = KilometerMarker1;

    float Length1;
    while (true)
    {
        std::cout << "Введите длину трубы (км):\n";
        std::cin >> Length1;
        if (Length1 > 0)
        {
            Pipe1.Length = Length1;
            break;
        }
        else
        {
            std::cout << "Некорректное значение. \n";
        }
    }

    int Diameter1;
    while (true)
    {
        std::cout << "Введите  диаметр трубы (мм):\n";
        std::cin >> Diameter1;
        if (Diameter1 > 0)
        {
            Pipe1.Diameter = Diameter1;
            break;
        }
        else
        {
            std::cout << "Некорректное значение. \n";
        }
    }

    Pipe1.InRepair = false;
}

void task2() // добавить КС
{
    std::string Name1;
    std::cout << "Добавление КС...\nВведите название: \n";
    std::cin >> Name1;
    CS1.Name = Name1;
    is_cs = true;

    int WorkshopAmount1;
    while (true)
    {
        std::cout << "Введите  количество цехов:\n";
        std::cin >> WorkshopAmount1;
        if (WorkshopAmount1 > 0)
        {
            CS1.WorkshopAmount = WorkshopAmount1;
            break;
        }
        else
        {
            std::cout << "Некорректное значение. \n";
        }
    }

    int WorkshopInWorkAmount1;
    while (true)
    {
        std::cout << "Введите  количество цехов в работе:\n";
        std::cin >> WorkshopInWorkAmount1;
        if (0 < WorkshopInWorkAmount1 <= WorkshopAmount1)
        {
            CS1.WorkshopAmount = WorkshopInWorkAmount1;
            break;
        }
        else
        {
            std::cout << "Некорректное значение. \n";
        }
    }
    std::string StationClass1;
    std::cout << "Введите класс КС: \n";
    std::cin >> StationClass1;
    CS1.StationClass = StationClass1;

}

void task3() // просмотр всех объектов
{
    std::cout << "Просмотр  всех объектов:\n";
    if (is_pipe)
    {
        std::cout << "Труба\nКилометровый маркер: " << Pipe1.KilometerMarker << "\nДлина (км): " << Pipe1.Length << "\nДиаметр (мм): " << Pipe1.Diameter << "\nВ ремонте (1 - да, 0 - нет): " << int(Pipe1.InRepair) << "\n";
    }
    if (is_cs)
    {
        std::cout << "Компрессионная станция\nНазвание: " << CS1.Name << "\nКоличество цехов: " << CS1.WorkshopAmount << "\nКоличество цехов в работе: " << CS1.WorkshopInWorkAmount << "Класс станции: " << CS1.StationClass << "\n";
    }
    if (is_pipe == false and is_cs == false)
    {
        std::cout << "Объектов нет!\n";
    }
}

void task4() // редактировать трубу
{
    if (is_pipe == false)
    { 
        std::cout << "Труб нет.\n";
        return; 
    }
    std::cout << "Редактирование трубы. Выберите параметр:\n1 - километровый маркер; 2 - длина;\n3 - диаметр; 4 - состояние в ремонте:\n";
    int redactpipe = 0;
    std::cin >> redactpipe;
    if (redactpipe == 1)
    {
        std::cout << "Введите новый километровый маркер: \n";
        std::cin >> Pipe1.KilometerMarker;
    }
    else if (redactpipe == 2)
    {
        float Length1;
        while (true)
        {
            std::cout << "Введите новую длину трубы (км):\n";
            std::cin >> Length1;
            if (Length1 > 0)
            {
                Pipe1.Length = Length1;
                break;
            }
            else
            {
                std::cout << "Некорректное значение. \n";
            }
        }
    }
    else if (redactpipe == 3)
    {
        int Diameter1;
        while (true)
        {
            std::cout << "Введите новый диаметр трубы (мм):\n";
            std::cin >> Diameter1;
            if (Diameter1 > 0)
            {
                Pipe1.Diameter = Diameter1;
                break;
            }
            else
            {
                std::cout << "Некорректное значение. \n";
            }
        }
    }
    else if (redactpipe == 4)
    {
        int inrepair = -1;
        while (true)
        {   
            std::cout << "Введите состояние трубы: 1 - в ремонте 0 - не в ремонте: \n";
            std::cin >> inrepair;
            if (inrepair == 0 or inrepair == 1)
            {
                Pipe1.InRepair = inrepair;
                break;
            }
            else {
                std::cout << "\nНекорректный ввод\n";
            }
        }
    }
}

void task5()
{
    if (is_cs == false)
    {
        std::cout << "КС нет.\n";
        return;
    }
    std::cout << "Редактирование параметров КС. Выберите параметр:\n1 - название; 2 - количество цехов;\n3 - количество цехов в работе; 4 - класс станции: \n";
    int redactcs = -1;
    std::cin >> redactcs;
    if (redactcs == 1)
    {
        std::cout << "Введите новое название КС: \n";
        std::cin >> CS1.Name;
    }
    else if (redactcs == 2)
    {
        int WorkshopAmount1;
        while (true)
        {
            std::cout << "Введите новое количество цехов:\n";
            std::cin >> WorkshopAmount1;
            if (WorkshopAmount1 > 0)
            {
                CS1.WorkshopAmount = WorkshopAmount1;
                break;
            }
            else
            {
                std::cout << "Некорректное значение. \n";
            }
        }
    }
    else if (redactcs == 3)
    {
        int WorkshopInWorkAmount1;
        while (true)
        {
            std::cout << "Введите новое количество цехов в работе:\n";
            std::cin >> WorkshopInWorkAmount1;
            if (0 < WorkshopInWorkAmount1 <= CS1.WorkshopAmount)
            {
                CS1.WorkshopAmount = WorkshopInWorkAmount1;
                break;
            }
            else
            {
                std::cout << "Некорректное значение. \n";
            }
        }
    }
    else if (redactcs == 4)
    {
        std::cout << "Введите новый класс КС: \n";
        std::cin >> CS1.StationClass;
    }
}

void task6()
{
    
    std::ofstream file("data.txt");
    if (is_pipe)
    {
        file << "Pipe:\n";
        file << "KilometerMarker=" << Pipe1.KilometerMarker << "\n";
        file << "Length=" << Pipe1.Length << "\n";
        file << "Diameter=" << Pipe1.Diameter << "\n";
        file << "InRepair=" << Pipe1.InRepair << "\n";
    }

    if (is_cs)
    {
        file << "Compressor Station:" << "\n";
        file << "Name=" << CS1.Name << "\n";
        file << "WorkshopAmount=" << CS1.WorkshopAmount << "\n";
        file << "WorkshopInWorkAmount=" << CS1.WorkshopInWorkAmount << "\n";
        file << "StationClass=" << CS1.StationClass << "\n";
    }
}

void task7() // загрузить
{
    is_cs = true;
    is_pipe = true;
    std::string filename = "data.txt";
    std::ifstream file(filename);

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();

    Pipe1.KilometerMarker = lines[1].substr(lines[1].find("=") + 1);
    std::cout << "Загрузка...\nТруба\nКилометровая метка: " << Pipe1.KilometerMarker << "\n";
    Pipe1.Length = std::stof(lines[2].substr(lines[2].find("=") + 1));
    std::cout << "Длина: " << Pipe1.Length << "\n";
    Pipe1.Diameter = std::stoi(lines[3].substr(lines[3].find("=") + 1));
    std::cout << "Диаметр: " << Pipe1.Diameter << "\n";
    Pipe1.InRepair = std::stoi(lines[4].substr(lines[4].find("=") + 1));
    std::cout << "В ремонте (1 - да, 0 - нет): " << Pipe1.InRepair << "\n";

    CS1.Name = lines[6].substr(lines[6].find("=") + 1);
    std::cout << "Компрессионная Станция\nНазвание: " << CS1.Name << "\n";
    CS1.WorkshopAmount = std::stoi(lines[7].substr(lines[7].find("=") + 1));
    std::cout << "Количество цехов: " << CS1.WorkshopAmount << "\n";
    CS1.WorkshopInWorkAmount = std::stoi(lines[8].substr(lines[8].find("=") + 1));
    std::cout << "Количество цехов в работе: " << CS1.WorkshopInWorkAmount << "\n";
    CS1.StationClass = lines[9].substr(lines[9].find("=") + 1);
    std::cout << "Класс Станции: " << CS1.StationClass << "\n";
    std::cout << "Дата загружена.\n";
}

int main()
{   
    setlocale(LC_ALL, "Russian");
    std::string task = "-1";
    while (task != "0")
    {   
        std::cout << "\n-----------------------------------------------\n"
                  << "1. Добавить трубу 2. Добавить КС \n"
                  << "3. Просмотр всех объектов 4. Редактировать трубу \n"
                  << "5. Редактировать КС 6. Сохранить\n"
                  << "7. Загрузить 0. Выход \n";
        std::cin >> task;
        if (task == "1")
        {
            task1();
        }
        else if (task == "2")
        {
            task2();
        }
        else if (task == "3")
        {
            task3();
        }
        else if (task == "4")
        {
            task4();
        }
        else if (task == "5")
        {
            task5();
        }
        else if (task == "6")
        {
            task6();
        }
        else if (task == "7")
        {
            task7();
        }
        else
        {
            std::cout << "Введите корректную комманду.\n";
        }
    }   
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
