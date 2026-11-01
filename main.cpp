#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <chrono>
#include <vector>
#include <format>
#include <unordered_map>
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
vector<int> FindObjByFilter(const unordered_map<int, T>& group, Filter<T, T_param> f, T_param param)
{
    vector <int> res;
    res.reserve(group.size());
    for (auto& s : group)
    {
        if (f(s.second, param))
            res.push_back(s.first);//!!!!!
    }

    return res;
}

template<class T>
vector<int> GetObjId(const unordered_map<int, T>& group)
{
    vector<int> res;
    res.reserve(group.size());
    for (auto& s : group)
    {
        res.push_back(s.first);//!!!
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


int RedactPipes(unordered_map<int, Pipe>& m) { //редактировать трубы
    int task;
    task = GetCorrectNumber(1, 2, "Edit Pipe(s) - 1, Delete Pipe(s) - 2");
    if (task == 1) {
        task = GetCorrectNumber(0, 3, "Edit one Pipe - 1, multiple Pipes - 2; (0 - exit)");
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
            vector<int> new_list = FindObjByFilter(m, CheckByStatus, is_in_repair);
            cout << "Found Pipes:" << endl;
            for (int i : new_list)
            {
                cout << m[i].GetId() << "\t" << m[i].GetName() << endl;
            }
            int choose_amount = GetCorrectNumber(1, 2, "Edit all found Pipes - 1, edit one by ID - 2");
            if (choose_amount == 1)
            {
                for (int i : new_list)
                {
                    m[i].RedactPipe();
                    cout << "\nStatus of a Pipe named " << m[i].GetName() << " was changed to " << m[i].GetStatus() << "\n";
                }
            }
            else
            {
                int id_to_redact = GetCorrectNumber(0, Pipe::GetMaxId(), "Enter id:");
                if (m.contains(id_to_redact)) {
                    m[id_to_redact].RedactPipe();
                    cout << "\nStatus of a Pipe named " << m[id_to_redact].GetName() << " was changed to " << m[id_to_redact].GetStatus() << "\n";
                }
                else { cout << "No such id" << endl; }
            }
        }
    }
    else {
        task = GetCorrectNumber(0, 3, "Delete one Pipe - 1, multiple Pipes - 2; (0 - exit)");
        if (task == 0) { return 0; }
        else if (task == 1)
        {
            string name_input = GetString("Enter name (0 - exit): \n");
            if (name_input == "0") {
                return 0;
            }
            else {
                for (int i : FindObjByFilter(m, CheckByName, name_input)) {
                    m.erase(i);
                    cout << "a Pipe named " << name_input << " was deleted" << endl;
                }
            }
        }
        else if (task == 2) {
            bool is_in_repair = GetCorrectNumber(false, true, "Enter Pipes' status: 1 - in repair, 0 - not: ");
            vector<int> new_list = FindObjByFilter(m, CheckByStatus, is_in_repair);
            cout << "Found Pipes:" << endl;
            for (int i : new_list)
            {
                cout << m[i].GetId() << "\t" << m[i].GetName() << endl;
            }
            int choose_amount = GetCorrectNumber(1, 2, "Deleete all found Pipes - 1, delete one by ID - 2");
            if (choose_amount == 1)
            {
                for (int i : new_list)
                {
                    cout << "Pipe named " << m[i].GetName() << " was deleted" << endl;
                    m.erase(i);
                }
            }
            else
            {
                int id_to_redact = GetCorrectNumber(0, Pipe::GetMaxId(), "Enter id:");
                if (m.contains(id_to_redact)) {
                    cout << "Pipe named " << m[id_to_redact].GetName() << " was deleted" << endl;
                    m.erase(id_to_redact);

                }
                else { cout << "No such id" << endl; }
            }
        }
    }
}


int RedactCSs(unordered_map<int, CS> &m) { //редактировать КС
    int task;
    task = GetCorrectNumber(1, 2, "Edit CS(s) - 1, Delete CS(s) - 2");
    if (task == 1) {
        task = GetCorrectNumber(0, 3, "Edit one CS - 1, multiple CSs - 2; (0 - exit)");
        if (task == 0) { return 0; }
        else if (task == 1)
        {
            string name_input = GetString("Enter name (0 - exit): \n");
            if (name_input == "0") {
                return 0;
            }
            else {
                for (int i : FindObjByFilter(m, CheckByName, name_input)) {
                    m[i].RedactCS();
                    cout << "CS named " << name_input << " had its workshop amount changed to " << m[i] << "\n";
                }
            }
        }
        else if (task == 2) {
            int ws = GetCorrectNumber(0, 1000, "Enter CS' workshop in work percent: ");
            vector<int> new_list = FindObjByFilter(m, CheckByWorkingWorkshopsPercent, ws);
            cout << "Found CSs:" << endl;
            for (int i : new_list)
            {
                cout << m[i].GetId() << "\t" << m[i].GetName() << endl;
            }
            int choose_amount = GetCorrectNumber(1, 2, "Edit all found CSs - 1, edit one by ID - 2");
            if (choose_amount == 1)
            {
                for (int i : new_list)
                {
                    m[i].RedactCS();
                }
            }
            else
            {
                int id_to_redact = GetCorrectNumber(0, Pipe::GetMaxId(), "Enter id:");
                if (m.contains(id_to_redact)) {
                    m[id_to_redact].RedactCS();
                }
                else { cout << "No such id" << endl; }
            }
        }
    }
    else {
        task = GetCorrectNumber(0, 3, "Delete one CS - 1, multiple CSs - 2; (0 - exit)");
        if (task == 0) { return 0; }
        else if (task == 1)
        {
            string name_input = GetString("Enter name (0 - exit): \n");
            if (name_input == "0") {
                return 0;
            }
            else {
                for (int i : FindObjByFilter(m, CheckByName, name_input)) {
                    m.erase(i);
                    cout << "a CS named " << name_input << " was deleted" << endl;
                }
            }
        }
        else if (task == 2) {
            int ws = GetCorrectNumber(0, 1000, "Enter CS' workshop in work percent: ");
            vector<int> new_list = FindObjByFilter(m, CheckByWorkingWorkshopsPercent, ws);
            cout << "Found CSs:" << endl;
            for (int i : new_list)
            {
                cout << m[i].GetId() << "\t" << m[i].GetName() << endl;
            }
            int choose_amount = GetCorrectNumber(1, 2, "Deleete all found CSs - 1, delete one by ID - 2");
            if (choose_amount == 1)
            {
                for (int i : new_list)
                {
                    cout << "CS named " << m[i].GetName() << " was deleted" << endl;
                    m.erase(i);
                }
            }
            else
            {
                int id_to_redact = GetCorrectNumber(0, Pipe::GetMaxId(), "Enter id:");
                if (m.contains(id_to_redact)) {
                    cout << "CS named " << m[id_to_redact].GetName() << " was deleted" << endl;
                    m.erase(id_to_redact);
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
        int task = GetCorrectNumber(0, 7, "-----------------------------------------------\n1. Add a Pipe\n2. Add a CS \n3. Print all objects \n4. Edit/delete object(s)\n5. Save to a file\n6. Load from a file\n0. Exit\n-----------------------------------------------");
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
