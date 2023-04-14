#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
using namespace std;

class Employee
{
private:
    int id;
    string name;
    int age;
    string level;

public:
    Employee(int i, string n, int a, string l)
    {
        id = i;
        name = n;
        age = a;
        level = l;
    }
};
class WorkingHour
{
private:
    int employeeId;
    int day;
    pair<int, int> workingInterval;

public:
    WorkingHour(int e, int d, pair<int, int> w)
    {
        employeeId = e;
        day = d;
        workingInterval = w;
    }
};
class Team
{
private:
    int teamId;
    int teamHeadId;
    vector<int> memberIds;
    double bonusWorkingHoursMaxVariance;
    int bonusMinWorkingHours;

public:
    Team(int ti, int hi, vector<int> mi,
         double b, int bm = 0)
    {
        teamId = ti;
        teamHeadId = hi;
        memberIds = mi;
        bonusWorkingHoursMaxVariance = b;
        bonusMinWorkingHours = bm;
    }
};
class SalaryConfig
{
private:
    string level;
    int baseSalary;
    int salaryPerHour;
    int salaryPerExtraHour;
    int officialWorkingHours;
    int taxPercentage;

public:
    SalaryConfig(string l, int b, int s, int se, int o, int t)
    {
        level = l;
        baseSalary = b;
        salaryPerHour = s;
        salaryPerExtraHour = se;
        officialWorkingHours = o;
        taxPercentage = t;
    }
    string get_level() { return level; }
    void show_config()
    {
        cout << "Base Salary: " << baseSalary << endl;
        cout << "Salary Per Hour: " << salaryPerHour << endl;
        cout << "Salary Per Extra Hour: " << salaryPerExtraHour << endl;
        cout << "Official Working Hours: " << officialWorkingHours << endl;
        cout << "Tax: " << taxPercentage << '%' << endl;
    }
    void update_config(string b, string s, string se, string o, string t)
    {
        if (b != "-")
            baseSalary = stoi(b);
        if (s != "-")
            salaryPerHour = stoi(s);
        if (se != "-")
            salaryPerExtraHour = stoi(se);
        if (o != "-")
            officialWorkingHours = stoi(o);
        if (t != "-")
            taxPercentage = stoi(t);
        cout << "OK" << endl;
    }
};

int main(int argc, char *argv[])
{

    return 0;
}