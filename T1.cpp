#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

const int FILE_PATH_INDEX = 1;
const int EMPLOYEE_PROPERTIES_COUNT = 4;
const int DEFAULT = 0;
const int ONE_MONTH_DAYS = 30;
const string NOT_FOUND = "";
const int NOTFOUND = -1;

void error(string message)
{
    cout << message << endl;
}

// موجوديت ها
class Employee;
class WorkingHour
{
private:
    int employeeId;
    int day;
    int periodStart;
    int periodEnd;

public:
    WorkingHour(int e, int d, int ps, int pe)
    {
        employeeId = e;
        day = d;
        periodStart = ps;
        periodEnd = pe;
    }
    int get_employee_id() { return employeeId; }
    int get_day() { return day; }
    pair<int, int> get_period() { return {periodStart, periodEnd}; }
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
    SalaryConfig(string l, int b = DEFAULT, int s = DEFAULT,
                 int se = DEFAULT, int o = DEFAULT, int t = DEFAULT)
    {
        // if (l != "junior" && l != "senior" && l != "expert" && l != "team_lead")
        // {
        //     error("INVALID_LEVEL");
        //     level = "";
        // }
        // else
        // {
        level = l;
        baseSalary = b;
        salaryPerHour = s;
        salaryPerExtraHour = se;
        officialWorkingHours = o;
        taxPercentage = t;
        // }
    }

    string get_level() { return level; }
    int get_tax_percentage() { return taxPercentage; }
    int find_init_earning(int totalWHours)
    {
        int initialEarning = baseSalary, earningWithTax;
        if (totalWHours > officialWorkingHours)
        {
            int extraHours = totalWHours - officialWorkingHours;
            initialEarning += (officialWorkingHours * salaryPerHour);
            initialEarning += (extraHours * salaryPerExtraHour);
        }
        else
        {
            initialEarning += (totalWHours * salaryPerHour);
        }
        return initialEarning;
    }
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
class Team
{
private:
    int teamId;
    int teamHeadId;
    vector<int> memberIds;
    double bonusWorkingHoursMaxVariance;
    int bonusMinWorkingHours;
    int bonusPercentage;

    vector<Employee *> members;

public:
    Team(int ti, int hi, vector<int> mi, double b, int bm, int bp = 0)
    {
        teamId = ti;
        teamHeadId = hi;
        memberIds = mi;
        bonusWorkingHoursMaxVariance = b;
        bonusMinWorkingHours = bm;
        bonusPercentage = bp;
    }

    vector<int> get_member_ids() { return memberIds; }
    int get_team_id() { return teamId; }
    int get_bonus_percentage() { return bonusPercentage; }
    int get_head_id() { return teamHeadId; }

    int find_team_total_working_hours()
    {
        int result = 0;
        for (int i = 0; i < members.size(); i++)
        {
            result += members[i]->find_total_working_hours();
        }
        return result;
    }
    double find_avg_member_working_hour()
    {
        int totalHours = find_team_total_working_hours();
        double avgHours = totalHours / members.size();
        double roundedAvg = round(avgHours * 10) / 10;
        return roundedAvg;
    }
    void show_members_info()
    {
        for (int i = 0; i < members.size(); i++)
        {
            cout << "Member ID: " << members[i]->get_id() << endl
                 << "Total Earning: " << members[i]->find_total_earning() << endl
                 << "---" << endl;
        }
    }
    void set_team_member(Employee *employee) { members.push_back(employee); }
};
class Employee
{
private:
    int id;
    string name;
    int age;
    string level;

    vector<WorkingHour *> workingPeriods;
    SalaryConfig *salaryConfig;
    Team *team;

public:
    Employee(int i, string n, int a, string l)
    {
        id = i;
        name = n;
        age = a;
        level = l;
    }

    void set_working_period(WorkingHour *workingHour) { workingPeriods.push_back(workingHour); }
    void set_salary_config(SalaryConfig *sConfig) { salaryConfig = sConfig; }
    void set_team(Team *empTeam) { team = empTeam; }

    int get_id() { return id; }
    int get_age() { return age; }
    string get_name() { return name; }
    string get_level() { return level; }
    SalaryConfig *get_salary_config() { return salaryConfig; }
    string get_emp_team_id()
    {
        if (team != NULL)
            return to_string(team->get_team_id());
        else
            return "N/A";
    }

    int find_absent_days()
    {
        set<int> nonRepWorkDays;
        for (WorkingHour *workperiod : workingPeriods)
        {
            nonRepWorkDays.insert(workperiod->get_day());
        }
        return ONE_MONTH_DAYS - nonRepWorkDays.size();
    }
    int find_total_working_hours()
    {
        int result = 0;
        for (WorkingHour *workperiod : workingPeriods)
        {
            result += (workperiod->get_period().second - workperiod->get_period().first);
        }
        return result;
    }
    int find_initial_earning()
    {
        return salaryConfig->find_init_earning(find_total_working_hours());
    }
    int find_bonus_amount()
    {
        if (team != NULL)
        {
            int initialEarning = find_initial_earning();
            return (team->get_bonus_percentage() * initialEarning) / 100.0 + 0.5;
        }
        return 0;
    }
    int find_tax_amount()
    {
        int initialEarning = find_initial_earning() + find_bonus_amount();
        return (get_salary_config()->get_tax_percentage() * initialEarning) / 100.0 + 0.5;
    }
    int find_total_earning()
    {
        return find_initial_earning() + find_bonus_amount() - find_tax_amount();
    }

    void koko()
    {
        for (WorkingHour *w : workingPeriods)
        {
            cout << w->get_period().first << "  " << w->get_period().second << endl;
        }
        salaryConfig->show_config();
        cout << endl

             << endl;
    }
};

// كل برنامه
class Program
{
private:
    SalaryConfig *find_salary_by_level(string level)
    {
        for (int i = 0; i < salaryConfigs.size(); i++)
            if (salaryConfigs[i]->get_level() == level)
                return salaryConfigs[i];
        error("INVALID_LEVEL");
        return NULL;
    }
    Team *find_team_by_member_id(int id)
    {
        for (int i = 0; i < teams.size(); i++)
        {
            vector<int> memberIds = teams[i]->get_member_ids();
            for (int j = 0; j < memberIds.size(); j++)
            {
                if (id == memberIds[j])
                {
                    return teams[i];
                }
            }
        }
        return NULL;
    }
    Employee *find_employee_by_id(int id)
    {
        for (int i = 0; i < employees.size(); i++)
        {
            if (id == employees[i]->get_id())
            {
                return employees[i];
            }
        }
        error("EMPLOYEE_NOT_FOUND");
        return NULL;
    }
    Team *find_team_by_id(int teamId)
    {
        for (int i = 0; i < teams.size(); i++)
        {
            if (teamId == teams[i]->get_team_id())
            {
                return teams[i];
            }
        }
        error("TEAM_NOT_FOUND");
        return NULL;
    }

    void set_emp_w_hours(Employee *emp)
    {
        for (int j = 0; j < workingHours.size(); j++)
        {
            if (workingHours[j]->get_employee_id() == emp->get_id())
            {
                emp->set_working_period(workingHours[j]);
            }
        }
    }
    void set_emp_s_config(Employee *emp)
    {
        emp->set_salary_config(find_salary_by_level(emp->get_level()));
    }
    void set_emp_team(Employee *emp)
    {
        emp->set_team(find_team_by_member_id(emp->get_id()));
    }

    vector<Employee *> employees;
    vector<WorkingHour *> workingHours;
    vector<Team *> teams;
    vector<SalaryConfig *> salaryConfigs;

public:
    Program(vector<Employee *> e, vector<WorkingHour *> w,
            vector<Team *> t, vector<SalaryConfig *> s)
    {
        employees = e;
        workingHours = w;
        teams = t;
        salaryConfigs = s;
    }
    // *0*
    void connectObjects()
    {
        for (int i = 0; i < employees.size(); i++)
        {
            set_emp_w_hours(employees[i]);
            set_emp_s_config(employees[i]);
            set_emp_team(employees[i]);
        }
        for (int i = 0; i < teams.size(); i++)
        {
            vector<int> memberIds = teams[i]->get_member_ids();
            for (int j = 0; j < memberIds.size(); j++)
            {
                teams[i]->set_team_member(find_employee_by_id(memberIds[j]));
            }
        }

        // for (Employee *i : employees)
        // {
        //     cout << i->get_name() << endl;
        //     i->koko();
        // }
    }
    // *1*
    void report_salaries()
    {
        for (Employee *employee : employees)
        {
            cout << "ID: " << employee->get_id() << endl
                 << "Name: " << employee->get_name() << endl
                 << "Total Working Hours: " << employee->find_total_working_hours() << endl
                 << "Total Earning: " << employee->find_total_earning() << endl
                 << "---" << endl;
        }
    }
    // *2*
    void report_employee_salary(int employeeId)
    {
        Employee *selectedEmp = find_employee_by_id(employeeId);
        if (selectedEmp != NULL)
        {
            cout << "ID: " << selectedEmp->get_id() << endl
                 << "Name: " << selectedEmp->get_name() << endl
                 << "Age: " << selectedEmp->get_age() << endl
                 << "Level: " << selectedEmp->get_level() << endl
                 << "Team ID: " << selectedEmp->get_emp_team_id() << endl
                 << "Total Working Hours: " << selectedEmp->find_total_working_hours() << endl
                 << "Absent Days: " << selectedEmp->find_absent_days() << endl
                 << "Salary: " << selectedEmp->find_initial_earning() << endl
                 << "Bonus: " << selectedEmp->find_bonus_amount() << endl
                 << "Tax: " << selectedEmp->find_tax_amount() << endl
                 << "Total Earning: " << selectedEmp->find_total_earning() << endl;
        }
    }
    // *3*
    void report_team_salary(int teamId)
    {
        Team *selectedTeam = find_team_by_id(teamId);
        if (selectedTeam != NULL)
        {
            cout << "ID: " << selectedTeam->get_team_id() << endl
                 << "Head ID: " << selectedTeam->get_head_id() << endl
                 << "Head Name: " << find_employee_by_id(selectedTeam->get_head_id())->get_name() << endl
                 << "Team Total Working Hours: " << selectedTeam->find_team_total_working_hours() << endl
                 << "Average Member Working Hour: " << selectedTeam->find_avg_member_working_hour() << endl
                 << "Bonus: " << selectedTeam->get_bonus_percentage() << endl
                 << "---" << endl;
            selectedTeam->show_members_info();
        }
    }
    // *4*
    void report_total_hours_per_day(int startDay, int endDay)
    {
    }
    // *5*
    void report_employee_per_hour(int startHour, int endHour)
    {
    }
    // *6*
    void show_salary_config(string level)
    {
        SalaryConfig *selectedSalary = find_salary_by_level(level);
        // اگر لول داده شده معتبر بود،اپديت را انجام بده
        if (selectedSalary != NULL)
            selectedSalary->show_config();
    }
    // *7*
    void update_salary_config(string level, string baseSalary, string salaryPerHour,
                              string salaryPerExtraHour, string officialWorkingHours, string taxPercentage)
    {
        SalaryConfig *selectedSalary = find_salary_by_level(level);
        // اگر لول داده شده معتبر بود،اپديت را انجام بده
        if (selectedSalary != NULL)
            selectedSalary->update_config(baseSalary, salaryPerHour,
                                          salaryPerExtraHour, officialWorkingHours, taxPercentage);
    }
    // *8*
    void add_working_hours(int employeeId, int day, int periodStart, int periodEnd)
    {
    }
    // *9*
    void delete_working_hours(int employeeId, int day)
    {
    }
    // *10*
    void update_team_bonus(int teamId, int bonusPercentage)
    {
    }
    // *11*
    void find_teams_for_bonus()
    {
    }
    // *12*
    void delete_everything()
    {
        // زدي رو ديليت كن از هيپ new سرچ كن هر جا
        for (Employee *employee : employees)
            delete employee;
        for (WorkingHour *workingHour : workingHours)
            delete workingHour;
        for (Team *team : teams)
            delete team;
        for (SalaryConfig *salaryConfig : salaryConfigs)
            delete salaryConfig;
    }
};

int main(int argc, char *argv[])
{
    Program program(
        {new Employee(1, "AzadehZahedi", 28, "junior"),
         new Employee(2, "MehranAmiri", 32, "expert"),
         new Employee(3, "ParvinKarami", 45, "senior"),
         new Employee(4, "BehzadAbbasi", 26, "junior"),
         new Employee(5, "GolnazEmadi", 39, "team_lead"),
         new Employee(6, "HatefJahangiri", 50, "junior"),
         new Employee(7, "DonyaMohammadi", 31, "team_lead")},
        {new WorkingHour(2, 16, 9, 16),
         new WorkingHour(7, 22, 8, 17),
         new WorkingHour(5, 7, 8, 12),
         new WorkingHour(4, 21, 14, 17),
         new WorkingHour(6, 30, 14, 21),
         new WorkingHour(7, 9, 14, 20),
         new WorkingHour(3, 12, 13, 17),
         new WorkingHour(5, 7, 14, 18),
         new WorkingHour(1, 18, 7, 11),
         new WorkingHour(6, 25, 13, 19),
         new WorkingHour(7, 9, 9, 10),
         new WorkingHour(1, 18, 13, 17),
         new WorkingHour(2, 18, 9, 17)},
        {new Team(1, 7, {6, 7, 3}, 780, 12.712),
         new Team(2, 5, {5, 4, 2, 1}, 1030, 22.837)},
        {new SalaryConfig("junior", 10000, 60, 48, 168, 15),
         new SalaryConfig("senior", 17000, 100, 75, 176, 28),
         new SalaryConfig("expert", 26500, 140, 112, 176, 25),
         new SalaryConfig("team_lead", 33000, 180, 134, 184, 32)});
    program.connectObjects();

    string command;
    while (cin >> command)
    {
        if (command == "report_salaries")
        {
            program.report_salaries();
        }
        else if (command == "report_employee_salary")
        {
            int employeeId;
            cin >> employeeId;
            program.report_employee_salary(employeeId);
        }
        else if (command == "report_team_salary")
        {
            int teamId;
            cin >> teamId;
            program.report_team_salary(teamId);
        }
        else if (command == "report_total_hours_per_day")
        {
            int startDay, endDay;
            cin >> startDay >> endDay;
            program.report_total_hours_per_day(startDay, endDay);
        }
        else if (command == "report_employee_per_hour")
        {
            int startHour, endHour;
            cin >> startHour >> endHour;
            program.report_employee_per_hour(startHour, endHour);
        }
        else if (command == "show_salary_config")
        {
            string level;
            cin >> level;
            program.show_salary_config(level);
        }
        else if (command == "update_salary_config")
        {
            string level, baseSalary, salaryPerHour, salaryPerExtraHour, officialWorkingHours, taxPercentage;
            cin >> level >> baseSalary >> salaryPerHour >> salaryPerExtraHour >> officialWorkingHours >> taxPercentage;
            program.update_salary_config(level, baseSalary, salaryPerHour, salaryPerExtraHour,
                                         officialWorkingHours, taxPercentage);
        }
        else if (command == "add_working_hours")
        {
            int employeeId, day, periodStart, periodEnd;
            cin >> employeeId >> day >> periodStart >> periodEnd;
            program.add_working_hours(employeeId, day, periodStart, periodEnd);
        }
        else if (command == "delete_working_hours")
        {
            int employeeId, day;
            cin >> employeeId >> day;
            program.delete_working_hours(employeeId, day);
        }
        else if (command == "update_team_bonus")
        {
            int teamId, bonusPercentage;
            cin >> teamId >> bonusPercentage;
            program.update_team_bonus(teamId, bonusPercentage);
        }
        else if (command == "find_teams_for_bonus")
        {
            program.find_teams_for_bonus();
        }
        else
        {
            error("unknown command\n");
        }
    }

    program.delete_everything();
    return 0;
}