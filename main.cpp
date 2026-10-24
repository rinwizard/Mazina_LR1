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
    task = GetCorrectNumber(1, 2, "Edit Pipe(s) - 1, Delete Pipe(s) - 2");
    if (task == 1) {
        task = GetCorrectNumber(0, 3, "Edit one Pipe - 1, multiple Pipes - 2; all Pipes - 3 (0 - exit)");
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
            bool is_in_repair = GetCorrectNumber(false, true, "Enter Pipes' status: 1 - in repair, 0 - not: ");
            for (int i : FindObjByFilter(m, CheckByStatus, is_in_repair)) {
                m[i].RedactPipe();
                cout << "\nStatus of a Pipe named " << m[i].GetName() << " was changed to " << m[i].GetStatus() << "\n";
            }
        }
        else
        {
            cout << "Editing all Pipes' statuses....\n";
            for (int i=0; i<=Pipe::MaxID; i++)
            {
                m[i].RedactPipe();
                cout << "\nStatus of a Pipe named " << m[i].GetName() << " was changed to " << m[i].GetStatus() << "\n";
            }
        }
    }
    else {
        task = GetCorrectNumber(0, 2, "Delete one Pipe - 1, multiple Pipes - 2; 3 - all Pipes (0 - exit)");
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
            bool is_in_repair = GetCorrectNumber(false, true, "Enter status: 1 - in_repair, 0 - not: ");
            for (int i : FindObjByFilter(m, CheckByStatus, is_in_repair)) {
                cout << "Pipe named " << m[i].GetName() << " deleted.\n";
                m.erase(i);
            }
        }
        else
        {
            cout << "Deleting all Pipes...\n";
            for (int i = 0; i <= Pipe::MaxID; i++)
            {
                cout << "Pipe named " << m[i].GetName() << " deleted.\n";
                m.erase(i);
            }
        }
    }
}



int RedactCSs(unordered_map<int, CS>& cs) { //редактировать трубы
    int task;
    task = GetCorrectNumber(1, 2, "Edit CS(s) - 1, Delete CS(s) - 2");
    if (task == 1) {
        task = GetCorrectNumber(0, 2, "Edit one CS - 1, multiple CSs - 2; all CSs - 3 (0 - exit)");
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
            int percent = GetCorrectNumber(0, 10000, "Enter percent of workstations in work: ");
            for (int i : FindObjByFilter(cs, CheckByWorkingWorkshopsPercent, percent)) {
                cs[i].RedactCS();
                cout << "\nCS named " << cs[i].GetName() << " had its workshops in work amount changed to " << cs[i].GetWorkshopWorkingAmount() << "\n";
            }
        }
        else
        {
            for (int i = 0; i <= CS::MaxID; i++)
            {
                cs[i].RedactCS();
                cout << "\nCS named " << cs[i].GetName() << " had its workshops in work amount changed to " << cs[i].GetWorkshopWorkingAmount() << "\n";
            }
        }
    }
    else {
        task = GetCorrectNumber(0, 2, "Delete one - 1, multiple - 2; 3 - all CSs (0 - exit)");
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
            int percent = GetCorrectNumber(false, true, "Enter percent of workstations in work: ");
            for (int i : FindObjByFilter(cs, CheckByWorkingWorkshopsPercent, percent)) {
                cout << "CS named " << cs[i].GetName() << " deleted.\n";
                cs.erase(i);
            }
        }
        else
        {
            cout << "Deleting all CSs....\n";
            for (int i = 0; i <= CS::MaxID; i++)
            {
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


int main()
{
    unordered_map<int, Pipe> Pipes;
    unordered_map<int, CS> CSs;

    while (true) {
        int task = GetCorrectNumber(0, 7, "-----------------------------------------------\n1. Add a Pipe 2. Add a CS \n3. Print all objects 4. Edit/delete object(s)\n5. Save to a file 6. Load from a file\n0. Exit");
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
                cout << "\nДанные загружены.\n";
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
