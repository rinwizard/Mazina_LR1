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
    char StationClass;

};


Pipe New_Pipe;
Compressor_Station New_CS;
bool is_pipe = false;
bool is_cs = false;
int pipe_amount = 1;
int cs_amount = 1;


void AddPipe() // добавить трубу
{
    std::cout << "Добавление трубы...\nВведите километровый маркер: \n";
    std::cin >> New_Pipe.KilometerMarker;//!!!!!!!

    while (true)
    {
        std::cout << "Введите длину трубы (км):\n";
        std::cin >> New_Pipe.Length;
        if (New_Pipe.Length > 0)
            break;
        else
            std::cout << "Некорректное значение. \n";
    }

    while (true)
    {
        std::cout << "Введите  диаметр трубы (мм):\n";
        std::cin >> New_Pipe.Diameter;
        if (New_Pipe.Diameter > 0)
        {
            break;
        }
        else
        {
            std::cout << "Некорректное значение. \n";
        }
    }

    New_Pipe.InRepair = false;
    is_pipe = true;
}

void AddCS() // добавить КС
{
    std::string Name1;
    std::cout << "Добавление КС...\nВведите название: \n";
    std::cin >> Name1;
    New_CS.Name = Name1;
    is_cs = true;

    while (true)
    {
        std::cout << "Введите  количество цехов:\n";
        std::cin >> New_CS.WorkshopAmount;
        if (New_CS.WorkshopAmount > 0)
        {
            break;
        }
        else
        {
            std::cout << "Некорректное значение. \n";
        }
    }

    while (true)
    {
        std::cout << "Введите количество цехов в работе:\n";
        std::cin >> New_CS.WorkshopInWorkAmount;
        if (0 < New_CS.WorkshopInWorkAmount <= New_CS.WorkshopAmount)
        {
            break;
        }
        else
        {
            std::cout << "Некорректное значение. \n";
        }
    }
    std::cout << "Введите класс КС: \n";
    std::cin >> New_CS.StationClass;
}

void ShowAll() // просмотр всех объектов
{
    std::cout << "Просмотр  всех объектов:\n";
    if (is_pipe)
    {
        std::cout << "Труба\nКилометровый маркер: " << New_Pipe.KilometerMarker << "\nДлина (км): " << New_Pipe.Length << "\nДиаметр (мм): " << New_Pipe.Diameter << "\nВ ремонте (1 - да, 0 - нет): " << New_Pipe.InRepair << "\n";
    }
    if (is_cs)
    {
        std::cout << "Компрессионная станция\nНазвание: " << New_CS.Name << "\nКоличество цехов: " << New_CS.WorkshopAmount << "\nКоличество цехов в работе: " << New_CS.WorkshopInWorkAmount << "\nКласс станции: " << New_CS.StationClass << "\n";
    }
    if (!is_pipe && !is_cs)
    {
        std::cout << "Объектов нет!\n";
    }
}

void RedactPipe() // редактировать трубу
{
    if (is_pipe == false)
    { 
        std::cout << "Труб нет.\n";
        return; 
    }
    std::cout << "Редактирование трубы. Состояние трубы в данный момент (1 - в ремонте; 0 - нет): " << New_Pipe.InRepair << "\n";

    while (true)
    {   
        std::cout << "Введите состояние трубы: (1 - в ремонте; 0 - нет): \n";
        std::cin >> New_Pipe.InRepair;
        if (New_Pipe.InRepair == 0 or New_Pipe.InRepair == 1)
        {
            break;
        }
        else {
            std::cout << "\nНекорректный ввод.\n";
        }
    }
}

void RedactCS() //редактировать КС
{
    if (is_cs == false)
    {
        std::cout << "КС нет.\n";
        return;
    }
    std::cout << "Редактирование КС. Введите новое количество цехов в работе: \n";
    while (true)
    {
        std::cin >> New_CS.WorkshopInWorkAmount;
        if (0 < New_CS.WorkshopInWorkAmount <= New_CS.WorkshopAmount)
        {
            break;
        }
        else
        {
            std::cout << "Некорректное значение. Введите новое количество цехов в работе:\n";
        }
    }
}

void Save() // сохранить
{   
    std::cout << "1 - сохранить трубу; 2 - сохранить КС; 3 - сохранить всё: \n";
    std::string task;
    std::cin >> task;
    if (task == "1" && is_pipe)
    {   

        std::ofstream file("data.txt");
        pipe_amount = 1;
        cs_amount = 0;
        file << "1\n0\n";
        file << New_Pipe.KilometerMarker << "\n";
        file << New_Pipe.Length << "\n";
        file << New_Pipe.Diameter << "\n";
        file << New_Pipe.InRepair << "\n";
    }
    
    else if (task == "2" && is_cs)
    {
        std::ofstream file("data.txt");
        pipe_amount = 0;
        cs_amount = 1;
        file << "0\n1\n";
        file << New_CS.Name << "\n";
        file << New_CS.WorkshopAmount << "\n";
        file << New_CS.WorkshopInWorkAmount << "\n";
        file << New_CS.StationClass << "\n";
    }
    else if (task == "3" && is_pipe && is_cs)
    {
        std::ofstream file("data.txt");
        pipe_amount = 1;
        cs_amount = 1;
        file << "1\n1\n";
        file << New_Pipe.KilometerMarker << "\n";
        file << New_Pipe.Length << "\n";
        file << New_Pipe.Diameter << "\n";
        file << New_Pipe.InRepair << "\n";
        file << New_CS.Name << "\n";
        file << New_CS.WorkshopAmount << "\n";
        file << New_CS.WorkshopInWorkAmount << "\n";
        file << New_CS.StationClass << "\n";
    }
    else
    {
        std::cout << "Некорректный ввод/нет данных.\n";
    }
}

void Load() // загрузить
{
    while (true)
    {
       // std::cout << "1 - загрузить трубу; 2 - загрузить КС, 3 - загрузить всё:\n";
        std::string task;
        std::cin >> task;
        if (task == "1" && pipe_amount == 1)
        {
            is_pipe = true;
            std::string filename = "data.txt";
            std::ifstream file(filename);

            std::vector<std::string> lines;
            std::string line;

            while (std::getline(file, line)) {
                lines.push_back(line);
            }

            file.close();

            New_Pipe.KilometerMarker = lines[2];
            New_Pipe.Length = std::stof(lines[3]);
            New_Pipe.Diameter = std::stoi(lines[4]);
            New_Pipe.InRepair = std::stoi(lines[5]);
            std::cout << "Данные загружены.\n";
            break;
        }
        else if (task == "2" && cs_amount == 1)
        {
            is_cs = true;
            std::string filename = "data.txt";
            std::ifstream file(filename);

            std::vector<std::string> lines;
            std::string line;

            while (std::getline(file, line)) {
                lines.push_back(line);
            }

            file.close();

            New_CS.Name = lines[6];
            New_CS.WorkshopAmount = std::stoi(lines[7]);
            New_CS.WorkshopInWorkAmount = std::stoi(lines[8]);
            New_CS.StationClass = lines[9][0];
            std::cout << "Данные загружены.\n";
            break;
        }
        else if (task == "3" && cs_amount == 1 && pipe_amount == 1)
        {
            is_pipe = true;
            is_cs = true;
            std::string filename = "data.txt";
            std::ifstream file(filename);

            std::vector<std::string> lines;
            std::string line;

            while (std::getline(file, line)) {
                lines.push_back(line);
            }

            file.close();

            New_Pipe.KilometerMarker = lines[2];
            New_Pipe.Length = std::stof(lines[3]);
            New_Pipe.Diameter = std::stoi(lines[4]);
            New_Pipe.InRepair = std::stoi(lines[5]);
            New_CS.Name = lines[6];
            New_CS.WorkshopAmount = std::stoi(lines[7]);
            New_CS.WorkshopInWorkAmount = std::stoi(lines[8]);
            New_CS.StationClass = lines[9][0];
            std::cout << "Данные загружены.\n";
            break;
        }
        else
        {
            std::cout << "Некорректный ввод.\n";
        }
    }


}

int main()
{   
    setlocale(LC_ALL, "Russian");
    std::string task = "-1";
    while (true)
    {   
        std::cout << "\n-----------------------------------------------\n"
                  << "1. Добавить трубу 2. Добавить КС \n"
                  << "3. Просмотр всех объектов 4. Редактировать трубу \n"
                  << "5. Редактировать КС 6. Сохранить\n"
                  << "7. Загрузить 0. Выход \n";
        std::cin >> task;
        if (task == "1")
        {
            AddPipe();
        }
        else if (task == "2")
        {
            AddCS();
        }
        else if (task == "3")
        {
            ShowAll();
        }
        else if (task == "4")
        {
            RedactPipe();
        }
        else if (task == "5")
        {
            RedactCS();
        }
        else if (task == "6")
        {
            Save();
        }
        else if (task == "7")
        {
            Load();
        }
        else if (task == "0")
        {
            std::cout << "Выход...";
            return 0;
        }
        else
        {
            std::cout << "Введите корректную комманду.\n";
        }
    }   
}