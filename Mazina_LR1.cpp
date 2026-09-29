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

struct Compressing_Station
{
    std::string Name;
    int WorkshopAmount;
    int WorkshopInWorkAmount;
    char StationClass;
};


bool is_int(std::string num)
{
    if (num.empty()) return false;

    try {
        size_t l_num = 0;
        std::stod(num, &l_num);
        return l_num == num.length();
    }
    catch (...) {
        return false;
    }
}


bool is_float(std::string num)
{
    if (num.empty()) return false;
    try
    {
        size_t l_num = 0;
        float f = std::stof(num, &l_num);
        return l_num == num.length();
    }
    catch (...) {
        return false;
    }
}



void AddPipe(Pipe& Object) // добавить трубу
{
    std::cout << "Добавление трубы...\nВведите километровый маркер: \n";
    std::string marker;
    std::getline(std::cin, marker);
    Object.KilometerMarker = marker;

    while (true)
    {
        std::cout << "Введите длину трубы (км):\n";
        std::string length;
        std::getline(std::cin, length);
        if (is_float(length) && std::stof(length) > 0)
        {
            Object.Length = std::stof(length);
            break;
        }
        else
            std::cout << "Некорректное значение. \n";
    }

    while (true)
    {
        std::cout << "Введите  диаметр трубы (мм):\n";
        std::string diameter;
        std::getline(std::cin, diameter);
        if (is_int(diameter) && std::stoi(diameter) > 0)
        {
            Object.Diameter = std::stoi(diameter);
            break;
        }
        else
        {
            std::cout << "Некорректное значение. \n";
        }
    }

    Object.InRepair = false;
}

void AddCS(Compressing_Station& Object) // добавить КС
{
    std::cout << "Добавление КС...\nВведите название: \n";
    std::string Name1;
    std::getline(std::cin, Name1);
    Object.Name = Name1;

    while (true)
    {
        std::cout << "Введите  количество цехов:\n";
        std::string amount;
        std::getline(std::cin, amount);
        if (is_int(amount) && std::stoi(amount) > 0)
        {
            Object.WorkshopAmount = std::stoi(amount);
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
        std::string amount;
        std::getline(std::cin, amount);
        if (is_int(amount) && std::stoi(amount) >= 0 && std::stoi(amount) <= Object.WorkshopAmount)
        {
            Object.WorkshopInWorkAmount = std::stoi(amount);
            break;
        }
        else
        {
            std::cout << "Некорректное значение. \n";
        }
    }
    while (true)
    {
        std::cout << "Введите класс КС (1 символ): \n";
        std::string statclass;
        std::getline(std::cin, statclass);
        if (!statclass.empty() && statclass.length() == 1)
        {
            Object.StationClass = statclass[0];
            break;
        }
        else { std::cout << "Некорректное значение. \n"; }
    }
}

void ShowAll(Pipe& PipeObj, Compressing_Station& CSObj) // просмотр всех объектов
{
    bool is_pipe = 0;
    bool is_cs = 0;
    if (PipeObj.Diameter != -1 && PipeObj.KilometerMarker != "-1" && PipeObj.Length != -1) { is_pipe = 1; }
    if (CSObj.StationClass != -1 && CSObj.WorkshopAmount != -1 && CSObj.Name != "-1") { is_cs = 1; }

    std::cout << "Просмотр  всех объектов:\n";
    if (is_pipe)
    {
        std::cout << "----Труба----\nКилометровый маркер: " << PipeObj.KilometerMarker << "\nДлина (км): " << PipeObj.Length << "\nДиаметр (мм): " << PipeObj.Diameter << "\nВ ремонте (1 - да, 0 - нет): " << PipeObj.InRepair << "\n";
    }
    if (is_cs)
    {
        std::cout << "----Компрессионная станция----\nНазвание: " << CSObj.Name << "\nКоличество цехов: " << CSObj.WorkshopAmount << "\nКоличество цехов в работе: " << CSObj.WorkshopInWorkAmount << "\nКласс станции: " << CSObj.StationClass << "\n";
    }
    if (!is_pipe && !is_cs)
    {
        std::cout << "Объектов нет!\n";
    }
}

void RedactPipe(Pipe& Object, bool is_pipe) // редактировать трубу
{
    if (is_pipe == false)
    {
        std::cout << "Труб нет.\n";
        return;
    }
    std::cout << "Редактирование трубы. Состояние трубы в данный момент (1 - в ремонте; 0 - нет): " << Object.InRepair << "\n";

    while (true)
    {
        std::cout << "Введите состояние трубы: (1 - в ремонте; 0 - нет): \n";
        std::string input;
        std::getline(std::cin, input);
        if (is_int(input) && (std::stoi(input) == 0 || std::stoi(input) == 1))
        {
            Object.InRepair = std::stoi(input);
            break;
        }
        else {
            std::cout << "\nНекорректный ввод.\n";
        }
    }
}

void RedactCS(Compressing_Station& Object, bool is_cs) //редактировать КС
{
    if (is_cs == false)
    {
        std::cout << "КС нет.\n";
        return;
    }
    std::cout << "Редактирование КС. Введите новое количество цехов в работе: \n";
    while (true)
    {
        std::string amount;
        std::getline(std::cin, amount);
        if (is_int(amount))
        {
            int val = std::stoi(amount);
            if (val >= 0 && val <= Object.WorkshopAmount)
            {
                Object.WorkshopInWorkAmount = val;
                break;
            }
            else
            {
                std::cout << "Некорректное значение. Введите новое количество цехов в работе:\n";
            }
        }
        else
        {
            std::cout << "Некорректное значение. Введите новое количество цехов в работе:\n";
        }
    }
}

void SavePipe(Pipe& PipeObject, std::ofstream &file)
{
    file << PipeObject.KilometerMarker << "\n";
    file << PipeObject.Length << "\n";
    file << PipeObject.Diameter << "\n";
    file << PipeObject.InRepair << "\n";
}

void SaveCS(Compressing_Station& CSObject, std::ofstream &file)
{
    file << CSObject.Name << "\n";
    file << CSObject.WorkshopAmount << "\n";
    file << CSObject.WorkshopInWorkAmount << "\n";
    file << CSObject.StationClass << "\n";
}

void Save(Pipe& PipeObject, Compressing_Station& CSObject, bool is_pipe, bool is_cs) // сохранить
{
    std::ofstream file("data.txt");
    file << is_pipe << "\n";
    file << is_cs << "\n";
    if (is_pipe)
    {
        SavePipe(PipeObject, file);
        std::cout << "Труба сохранена.\n";
    }
    if (is_cs)
    {
        SaveCS(CSObject, file);
        std::cout << "КС сохранена.\n";
    }
    else
    {
        std::cout << "нет данных.\n";
    }
    file.close();
}


void LoadPipe(Pipe& PipeObject, std::ifstream &file)
{
    std::string line = "";
    std::getline(file, line);
    PipeObject.KilometerMarker = line;

    std::getline(file, line);
    PipeObject.Length = std::stof(line);

    std::getline(file, line);
    PipeObject.Diameter = std::stoi(line);

    std::getline(file, line);
    PipeObject.InRepair = std::stoi(line);

}

void LoadCS(Compressing_Station& CSObject, std::ifstream &file)
{
    std::string line = "";
    std::getline(file, line);
    CSObject.Name = line;

    std::getline(file, line);
    CSObject.WorkshopAmount = std::stoi(line);

 
    std::getline(file, line);
    CSObject.WorkshopAmount = std::stoi(line);

    std::getline(file, line);
    CSObject.StationClass = line[0];
    file.close();
}

void Load(Pipe& PipeObject, Compressing_Station& CSObject, bool& is_pipe, bool& is_cs) // загрузить
{
    std::string filename = "data.txt";
    std::ifstream file(filename);

    std::string line;

    std::getline(file, line);
    is_pipe = line == "1";
    
    std::getline(file, line);
    is_cs = line == "1";

    if (is_pipe)
    {
        LoadPipe(PipeObject, file);
        std::cout << "Данные загружены.\n";

        if (is_cs)
        {
            LoadCS(CSObject, file);
            std::cout << "Данные КС загружены.\n";
        }
    }
    else if (is_cs)
    {
        LoadCS(CSObject, file);
        std::cout << "Данные трубы загружены.\n";
    }

    else
    { std::cout << "В файле нет данных.\n";}
    file.close();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Pipe New_Pipe;
    New_Pipe.Diameter = -1;
    New_Pipe.KilometerMarker = "-1";
    New_Pipe.Length = -1;
    New_Pipe.InRepair = 0;
    Compressing_Station New_CS;
    New_CS.Name = "-1";
    New_CS.StationClass = -1;
    New_CS.WorkshopAmount = -1;
    New_CS.WorkshopInWorkAmount = 0;
    bool is_pipe = false;
    bool is_cs = false;
    int pipe_amount = 0;
    int cs_amount = 0;


    std::string task = "-1";
    while (true)
    {
        std::cout << "\n-----------------------------------------------\n"
            << "1. Добавить трубу 2. Добавить КС \n"
            << "3. Просмотр всех объектов 4. Редактировать трубу \n"
            << "5. Редактировать КС 6. Сохранить\n"
            << "7. Загрузить 0. Выход \n";
        std::getline(std::cin, task);
        if (task == "1")
        {
            AddPipe(New_Pipe);
            is_pipe = true;
        }
        else if (task == "2")
        {
            AddCS(New_CS);
            is_cs = true;
        }
        else if (task == "3")
        {
            ShowAll(New_Pipe, New_CS);
        }
        else if (task == "4")
        {
            RedactPipe(New_Pipe, is_pipe);
        }
        else if (task == "5")
        {
            RedactCS(New_CS, is_cs);
        }
        else if (task == "6")
        {
            Save(New_Pipe, New_CS, is_pipe, is_cs);
        }
        else if (task == "7")
        {
            Load(New_Pipe, New_CS, is_pipe, is_cs);
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