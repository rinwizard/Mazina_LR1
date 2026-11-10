#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <chrono>
#include <vector>
#include <algorithm>
#include <format>
#include <unordered_map>
#include <unordered_set>
#include "utils.h"
#include "Pipe.h"
#include "CS.h"

using namespace std;
using namespace chrono;

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
unordered_set<int> FindObjByFilter(const unordered_map<int, T>& group, Filter<T, T_param> f, T_param param)
{
    unordered_set<int> res;
    res.reserve(group.size());
    for (auto& s : group)
    {
        if (f(s.second, param))
            res.emplace(s.first, s.second);
    }

    return res;
}


void ShowAll(unordered_map<int, Pipe> pipes, unordered_map<int, CS> css) // просмотр всех объектов
{
    if (pipes.size() != 0) {
        for (const auto& x : pipes) 
        { 
            cout << x.second << endl; 
        }
    }
    else { cout << "There are no pipes yet" << endl; }

    if (css.size() != 0) {
        for (const auto x : css) { cout << x.second << endl; }
    }
    else { cout << "There are no CSs yet" << endl; }
}


void RedactPipes(unordered_map<int, Pipe>& pipes) { //редактировать трубы
    int task;
    int action;
    action = GetCorrectNumber(1, 2, "Edit Pipe(s) - 1, Delete Pipe(s) - 2 (0 -  exit)");
    if (action == 0) 
        return; 

    task = GetCorrectNumber(0, 3, "One Pipe - 1, Multiple Pipes - 2;");
    if (task == 1)
    {
        int ID_input = GetCorrectNumber(-1, Pipe::GetMaxId(), "Enter ID: \n");
        if (pipes.contains(ID_input)) 
            if (action == 1)
                pipes[ID_input].RedactPipe(); 
            else 
                pipes.erase(ID_input); 
        else 
            cout << "No such ID!" << endl;
        
        return;
    }
    else if (task == 2) {
        task = GetCorrectNumber(1, 2, "Sort by Name - 1, by Status - 2");
        unordered_set<int> new_list;
        if (task == 1)
        {
            string name = GetString("Enter name:");
            new_list = FindObjByFilter(pipes, CheckByName, name);
        }
        else {
            bool is_in_repair = GetCorrectNumber(0, 1, "Enter Pipes' status: 1 - in repair, 0 - not: "); // + by name
            new_list = FindObjByFilter(pipes, CheckByStatus, is_in_repair);
        }
        cout << "Found Pipes:" << endl;
        for (int i: new_list)
        {
            cout << pipes[i].GetId() << "\t" << pipes[i].GetName() << endl;
        }
        int choose_amount = GetCorrectNumber(1, 2, "all found Pipes - 1, by ID - 2"); //while
        if (choose_amount == 1)
        {
            for (int i: new_list)
            {
                if (action == 1) { pipes[i].RedactPipe(); }
                else { pipes.erase(i); }
            }
        }
        else
        {
            while (true)
            {
                int ID_input = GetCorrectNumber(0, Pipe::GetMaxId(), "Enter id: (-1 - exit)");
                if (ID_input == -1)
                    return;
                else if (new_list.contains(ID_input)) {
                    if (action == 1) { pipes[ID_input].RedactPipe(); }
                    else { pipes.erase(ID_input); }
                }
                else { cout << "No such id" << endl; }
            }
            
            
        }
    }
}


void RedactCSs(unordered_map<int, CS>& css) { //редактировать кс
    int task;
    int action;
    action = GetCorrectNumber(1, 2, "Edit Pipe(s) - 1, Delete Pipe(s) - 2 (0 -  exit)");
    if (action == 0)
        return;

    task = GetCorrectNumber(0, 3, "One Pipe - 1, Multiple Pipes - 2;");
    if (task == 1)
    {
        int ID_input = GetCorrectNumber(-1, Pipe::GetMaxId(), "Enter ID: \n");
        if (css.contains(ID_input))
            if (action == 1)
                css[ID_input].RedactCS();
            else
                css.erase(ID_input);
        else
            cout << "No such ID!" << endl;

        return;
    }
    else if (task == 2) {
        task = GetCorrectNumber(1, 2, "Sort by Name - 1, by Percent of workshops in work - 2");
        unordered_set<int> new_list;
        if (task == 1)
        {
            string name = GetString("Enter name:");
            new_list = FindObjByFilter(css, CheckByName, name);
        }
        else {
            int percent = GetCorrectNumber(false, true, "Enter CS' workshop in work percent:");
            new_list = FindObjByFilter(css, CheckByWorkingWorkshopsPercent, percent);
        }
        cout << "Found Pipes:" << endl;
        for (int i : new_list)
        {
            cout << css[i].GetId() << "\t" << css[i].GetName() << endl;
        }
        int choose_amount = GetCorrectNumber(1, 2, "all found CSs - 1, by ID - 2"); //while
        if (choose_amount == 1)
        {
            for (int i : new_list)
            {
                if (action == 1) { css[i].RedactCS(); }
                else { css.erase(i); }
            }
        }
        else
        {
            while (true)
            {
                int ID_input = GetCorrectNumber(0, Pipe::GetMaxId(), "Enter id: (-1 - exit)");
                if (ID_input == -1)
                    return;
                else if (css.contains(ID_input)) {
                    if (action == 1) { css[ID_input].RedactCS(); }
                    else { css.erase(ID_input); }
                }
                else { cout << "No such id" << endl; }
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
        Pipe::SetMaxId(pipes);
        CS::SetMaxId(css);
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
    fout << Pipe::GetMaxId();
    fout << CS::GetMaxId();
}


int main()
{
    redirect_output_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
    ofstream logfile("log_" + time + ".txt");
    cerr_out.redirect(logfile);
    unordered_map<int, Pipe> Pipes;
    unordered_map<int, CS> CSs;

    while (true) {
        int task = GetCorrectNumber(0, 7, "---------------------------\n|1. Add a Pipe            |\n|2. Add a CS              |\n|3. Print all objects     |\n|4. Edit/delete object(s) |\n|5. Save to a file        |\n|6. Load from a file      |\n|0. Exit                  |\n---------------------------");
        switch (task)
        {
        case 0: { //выход
            cout << "Exit...";
            return 0;
        }
        case 1: { //добавить трубу
            //int id = Pipe::MaxID + 1;
            Pipe p;
            cin >> p;
            Pipes.emplace(p.GetId(),p);
            break;
        }
        case 2: { //добавить кс
            CS cs;
            cin >> cs;
            CSs.emplace(cs.GetId(), cs);
            break;
        }
        case 3: { //просмотр всех объектов
            ShowAll(Pipes, CSs);
            break;
        }
        case 4: { //редактировать/удалить объект
            int task = GetCorrectNumber(1, 2, "Redact/delete: Pipe - 1, CS - 2");
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
            string filename = GetString("Enter filename to save (ends with .txt): ");
            ofstream fout;
            fout.open(filename, ios::out);
            if (fout.is_open())
            {
                Save(fout, Pipes, CSs);
                fout.close();
                cout << "\nДанные сохранены.\n";
            }
            else
            {
                cout << "\nCannot open file.\n";
            }
            break;
        }
        case 6: { //загрузить из файла
            string filename = GetString("Enter filename to load (ends with .txt): ");
            ifstream fin;
            fin.open(filename, ios::in);
            if (fin.is_open())
            {
                Load(fin, Pipes, CSs);
                fin.close();
                cout << "\nData was successfully loaded.\n";
            }
            else
            {
                cout << "\nCannot open file.\n";
            }
            break;
        }
        }
    }
}
