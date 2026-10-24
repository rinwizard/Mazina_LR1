#include <iostream>
#include <string>
#include <fstream>
#include <set>

#include <vector>
#include <unordered_map>
#include "utils.h"
#include "Pipe.h"
#include "CS.h"

using namespace std;

// поиск по фильтрам

//template<class T, typename T_param>
//using Filter = bool(*)(const T& s, T_param param);
//id GetId(const unordered_map<T, int>& group, string name)
//{
//    int i = 0;
//    for (auto& s : group)
//    {
//        if (s.GetName() == name)
//            res.push_back(i);
//        i++;
//    }
//
//    return res;
//}
template<class T, typename T_param>
using Filter = bool(*)(const T& s, T_param param);

bool CheckByStatus(const Pipe& s, bool param)
{
    return s.GetStatus() == param;
}
bool CheckByName(const Pipe& s, string param)
{
    return s.GetName() == param;
}
bool CheckByName(const CS& s, string param)
{
    return s.GetName() == param;
}

bool CheckByWorkingWorkshopsPercent(const CS& cs, int param)
{
    return cs.GetWorkshopWorkingPercent() == param;
}

template<class T, typename T_param>
vector<int> FindObjByFilter(const unordered_map<int, T>& group, Filter<T, T_param> f, T_param param)
{
    vector <int> res;
    int i = 0;
    for (auto& s : group)
    {
        if (f(s.second, param))
            res.push_back(s.first);
        i++;
    }

    return res;
}


void ShowAll(unordered_map<int, Pipe> pipes, unordered_map<int, CS> css) // просмотр всех объектов
{
    if (pipes.size() != 0) {
        for (const auto& x : pipes) { cout << x.second << endl; }
    }
    else { cout << "There are no pipes yet" << endl; }

    if (css.size() != 0) {
        for (const auto x : css) { cout << x.second << endl; }
    }
    else { cout << "There are no CSs yet" << endl; }
}


int RedactPipes(unordered_map<int, Pipe>& m) { //редактировать трубы
    int task;
    cout << "\nEdit Pipe(s) - 1, Delete Pipe(s) - 2\n";
    task = GetCorrectNumber(1, 2);
    if (task == 1) {
        cout << "Edit one Pipe - 1, multiple Pipes - 2; (0 - exit)\n";
        task = GetCorrectNumber(0, 2);
        if (task == 0) { return 0; }
        else if (task == 1)
        {
            string name_input = GetString("Enter name (0 - exit): \n");
            if (name_input == "0") {
                return 0;
            }
            else {
                for (int i : FindObjByFilter(m, CheckByName, name_input)) {
                    m[i].RedactPipe();
                    cout << "\nStatus of a Pipe named " << name_input << " was changed to " << m[i].GetStatus() << "\n";
                }
            }
        }
        else if (task == 2) {
            cout << "\nEnter Pipes' status: 1 - in repair, 0 - not: ";
            bool is_in_repair = GetCorrectNumber(false, true);
            for (int i : FindObjByFilter(m, CheckByStatus, is_in_repair)) {
                m[i].RedactPipe();
                cout << "\nStatus of a Pipe named " << m[i].GetName() << " was changed to " << m[i].GetStatus() << "\n";
            }
        }
    }
    else {
        cout << "Delete one Pipe - 1, multiple Pipes - 2; (0 - exit)\n";
        task = GetCorrectNumber(0, 2);
        if (task == 0) { return 0; }
        if (task == 1)
        {
            string name_input = GetString("Enter name: \n");
            for (int i : FindObjByFilter(m, CheckByName, name_input)) {
                cout << "Pipe named " << name_input << " deleted.\n";
                m.erase(i);
            }
        }
        else if (task == 2) {
            cout << "\nEnter status: 1 - in_repair, 0 - not: ";
            bool is_in_repair = GetCorrectNumber(false, true);
            for (int i : FindObjByFilter(m, CheckByStatus, is_in_repair)) {
                cout << "Pipe named " << m[i].GetName() << " deleted.\n";
                m.erase(i);
            }
        }
    }
}



int RedactCSs(unordered_map<int, CS>& cs) { //редактировать трубы
    int task;
    cout << "\nEdit CS(s) - 1, Delete CS(s) - 2\n";
    task = GetCorrectNumber(1, 2);
    if (task == 1) {
        cout << "Edit one CS - 1, multiple CSs - 2; (0 - exit)\n";
        task = GetCorrectNumber(0, 2);
        if (task == 0) { return 0; }
        else if (task == 1)
        {
            string name_input = GetString("Enter name (0 - exit): \n");
            if (name_input == "0") {
                return 0;
            }
            else {
                for (int i : FindObjByFilter(cs, CheckByName, name_input)) {
                    cs[i].RedactCS();
                    cout << "\nCS named " << name_input << " had its workshops in work amount changed to " << cs[i].GetWorkshopWorkingAmount() << "\n";
                }
            }
        }
        else if (task == 2) {
            cout << "\nEnter percent of workstations in work: ";
            int percent = GetCorrectNumber(0, 10000);
            for (int i : FindObjByFilter(cs, CheckByWorkingWorkshopsPercent, percent)) {
                cs[i].RedactCS();
                cout << "\nStatus of a Pipe named " << cs[i].GetName() << " was changed to " << cs[i].GetWorkshopWorkingPercent() << "\n";
            }
        }
    }
    else {
        cout << "Delete one - 1, multiple - 2; (0 - exit)\n";
        task = GetCorrectNumber(0, 2);
        if (task == 0) { return 0; }
        if (task == 1)
        {
            string name_input = GetString("Enter name: \n");
            for (int i : FindObjByFilter(cs, CheckByName, name_input)) {
                cout << "CS named " << name_input << " deleted.\n";
                cs.erase(i);
            }
        }
        else if (task == 2) {
            cout << "\nEnter percent of workstations in work: ";
            int percent = GetCorrectNumber(false, true);
            for (int i : FindObjByFilter(cs, CheckByWorkingWorkshopsPercent, percent)) {
                cout << "CS named " << cs[i].GetName() << " deleted.\n";
                cs.erase(i);
            }
        }
    }
}


void Load(ifstream& fin, unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css)
{
    int pipe_amount;
    int cs_amount;
    fin >> pipe_amount;
    fin >> cs_amount;
    if (pipe_amount > 0 || cs_amount > 0) {
        pipes.clear();
        css.clear();
        for (int i = 0; i < pipe_amount; ++i) {
            Pipe pipe;
            fin >> pipe;
            pipes[pipe.GetId()] = pipe;
        }
        for (int i = 0; i < cs_amount; ++i) {
            CS cs;
            fin >> cs;
            css[cs.GetId()] = cs;
        }
        fin >> Pipe::MaxID;
        fin >> CS::MaxID;
    }
}

void Save(ofstream& fout, const unordered_map<int, Pipe>& pipes, const unordered_map<int, CS>& css)
{
    fout << pipes.size() << endl;
    fout << css.size() << endl;

    if (pipes.size() != 0) {
        for (const auto& x : pipes) {
            fout << x.second;
        }
    }
    if (css.size() != 0) {
        for (const auto& x : css) {
            fout << x.second;
        }
    }
    fout << Pipe::MaxID << endl;
    fout << CS::MaxID << endl;
}

//
//void SavePipe(Pipe& PipeObject, ofstream &file)
//{
//    file << PipeObject.KilometerMarker << "\n";
//    file << PipeObject.Length << "\n";
//    file << PipeObject.Diameter << "\n";
//    file << PipeObject.InRepair << "\n";
//}
//
//void SaveCS(Compressing_Station& CSObject, ofstream &file)
//{
//    file << CSObject.Name << "\n";
//    file << CSObject.WorkshopAmount << "\n";
//    file << CSObject.WorkshopInWorkAmount << "\n";
//    file << CSObject.StationClass << "\n";
////}
//
//void Save(Pipe& PipeObject, Compressing_Station& CSObject, bool is_pipe, bool is_cs) // сохранить
//{
//    ofstream file("data.txt");
//    file << is_pipe << "\n";
//    file << is_cs << "\n";
//    if (is_pipe)
//    {
//        SavePipe(PipeObject, file);
//        cout << "Труба сохранена.\n";
//    }
//    if (is_cs)
//    {
//        SaveCS(CSObject, file);
//        cout << "КС сохранена.\n";
//    }
//    else
//    {
//        cout << "нет данных.\n";
//    }
//    file.close();
//}
//
//
//int LoadPipe(Pipe& PipeObject, ifstream &file)
//{
//    string line = "";
//    getline(file, line);
//    PipeObject.KilometerMarker = line;
//
//    getline(file, line);
//    if (is_float(line))
//    {
//        PipeObject.Length = stof(line);
//    }
//    else
//    {
//        cout << "Битый файл.";
//        return 1;
//    }
//
//    getline(file, line);
//    if (is_int(line))
//    {
//        PipeObject.Diameter = stoi(line);
//    }
//    else
//    {
//        cout << "Битый файл.";
//        return 1;
//    }
//
//    getline(file, line);
//    if (is_int(line))
//    {
//        PipeObject.InRepair = stoi(line);
//    }
//    else
//    {
//        cout << "Битый файл.";
//        return 1;
//    }
//    cout << "Данные трубы загружены.\n";
//    return 0;
//}
//
//int LoadCS(Compressing_Station& CSObject, ifstream &file)
//{
//    string line = "";
//    getline(file, line);
//    CSObject.Name = line;
//
//    getline(file, line);
//    if (is_int(line))
//    {
//        CSObject.WorkshopAmount = stoi(line);
//    }
//    else
//    {
//        cout << "Битый файл.";
//        return 1;
//    }
//
//    getline(file, line);
//    if (is_int(line))
//    {
//        CSObject.WorkshopAmount = stoi(line);
//    }
//    else
//    {
//        cout << "Битый файл.";
//        return 1;
//    }
//
//    getline(file, line);
//    CSObject.StationClass = line[0];
//    file.close();
//
//    cout << "Данные КС загружены.\n";
//    return 0;
//}
//
//void Load(Pipe& PipeObject, Compressing_Station& CSObject, bool& is_pipe, bool& is_cs) // загрузить
//{
//    string filename = "data.txt";
//    ifstream file(filename);
//
//    string line;
//
//    getline(file, line);
//    is_pipe = line == "1";
//    
//    getline(file, line);
//    is_cs = line == "1";
//
//    if (is_pipe)
//        LoadPipe(PipeObject, file);
//    else { cout << "Трубы нет."; }
//    if (is_cs)
//        LoadCS(CSObject, file);
//    else { cout << "КС нет."; }
//
//    file.close();
//}

int main()
{
    unordered_map<int, Pipe> Pipes;
    unordered_map<int, CS> CSs;

    while (true) {
        std::cout << "\n-----------------------------------------------\n"
            << "1. Add a Pipe 2. Add a CS \n"
            << "3. Print all objects 4. Edit/delete object(s) \n"
            << "5. Save to a file 6. Load from a file\n"
            << "0. Exit \n" << std::endl;

        int task = GetCorrectNumber(0, 7);
        switch (task)
        {
        case 0: { //выход
            cout << "Exit...";
            return 0;
        }
        case 1: { //добавить трубу
            int id = Pipe::MaxID + 1;
            Pipes.emplace(id, Pipe());
            cin >> Pipes[id];
            break;
        }
        case 2: { //добавить кс
            int id = CS::MaxID + 1;
            CSs.emplace(id, CS());
            cin >> CSs[id];
            break;
        }
        case 3: { //просмотр всех объектов
            ShowAll(Pipes, CSs);
            break;
        }
        case 4: { //редактировать/удалить объект
            cout << "\nRedact/delete pipe - 1, CS - 2?\n";
            int task = GetCorrectNumber(1, 2);
            if (task == 1)
            {
                RedactPipes(Pipes);
            }
            else
            {
                RedactCSs(CSs);
            }
            break;
        }
        case 5: { //сохранить в файл
            ofstream fout;
            fout.open("data.txt", ios::out);
            if (fout.is_open())
            {
                Save(fout, Pipes, CSs);
                fout.close();
            }
            break;
        }
        case 6: { //загрузить из файла
            ifstream fin;
            fin.open("data.txt", ios::in);
            if (fin.is_open())
            {
                Load(fin, Pipes, CSs);
                fin.close();
            }
            break;
        }
        }
    }
}
