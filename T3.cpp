#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cmath>
#include <math.h>

using namespace std;

const string NOT_FOUND = "";
const int FOLDER_PATH_INDEX = 1;
const int EMPLOYEE_PROPERTIES_COUNT = 4;
const int DEFAULT = 0;
const int ONE_MONTH_DAYS = 30;
const int ONE_DAY_HOURS = 24;
const int NOTFOUND = -1;

void error(string message)
{
    cout << message << endl;
}

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
    int get_period_len() { return periodEnd - periodStart; }
    pair<int, int> get_period() { return {periodStart, periodEnd}; }
};
class SetOfWorkingHours
{
private:
    vector<WorkingHour *> workingHours;
    bool are_valid_days(int startDay, int endDay)
    {
        if (startDay > ONE_MONTH_DAYS || startDay < 1 ||
            endDay > ONE_MONTH_DAYS || endDay < 1 ||
            endDay < startDay)
        {
            return false;
        }
        return true;
    }
    bool are_valid_hours(int startHour, int endHour)
    {
        if (startHour > ONE_DAY_HOURS || startHour < 0 ||
            endHour > ONE_DAY_HOURS || endHour < 0 ||
            endHour < startHour)
        {
            return false;
        }
        return true;
    }

public:
    SetOfWorkingHours(vector<WorkingHour *> wHours) { workingHours = wHours; }
    SetOfWorkingHours() {}

    vector<WorkingHour *> get_periods() { return workingHours; }

    void add_new_period(WorkingHour *wHour) { workingHours.push_back(wHour); }
    void delete_periods_by_day_and_emp(int employeeId, int day);

    int find_total_working_hours();
    int find_total_working_hours_by_day(int day);
    double find_avg_emps_by_start_hour(int startHour);
    void show_indexes_with_max_value(vector<pair<string, string>> indexAndValue);
    void show_indexes_with_min_value(vector<pair<string, string>> indexAndValue);
    void show_total_hours_per_day(int startDay, int endDay);
    void show_employee_per_hour(int startHour, int endHour);

    void printt()
    {
        for (WorkingHour *o : workingHours)
        {
            cout << o->get_employee_id() << " " << o->get_day() << "   " << o->get_period().first << " " << o->get_period().second
                 << endl;
        }
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
    SalaryConfig(string l, int b = DEFAULT, int s = DEFAULT,
                 int se = DEFAULT, int o = DEFAULT, int t = DEFAULT)
    {
        level = l;
        baseSalary = b;
        salaryPerHour = s;
        salaryPerExtraHour = se;
        officialWorkingHours = o;
        taxPercentage = t;
    }

    string get_level() { return level; }
    int get_tax_percentage() { return taxPercentage; }

    int find_init_earning(int totalWHours);
    void show_config();
    void update_config(string b, string s, string se, string o, string t);
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

    void set_team_member(Employee *employee) { members.push_back(employee); }
    void set_bonus_percentage(int bPercentage) { bonusPercentage = bPercentage; }
    void show_members_info();
    int find_team_total_working_hours();
    double find_avg_member_working_hour();
    double find_emps_working_hours_variance();
    bool is_worthy_to_bonus();
};
class Employee
{
private:
    int id;
    string name;
    int age;
    string level;

    SetOfWorkingHours workingPeriods;
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

    int get_id() { return id; }
    int get_age() { return age; }
    string get_name() { return name; }
    string get_level() { return level; }
    string get_emp_team_id();
    SalaryConfig *get_salary_config() { return salaryConfig; }
    SetOfWorkingHours get_working_periods() { return workingPeriods; }

    void set_working_periods(SetOfWorkingHours workingHours) { workingPeriods = workingHours; }
    void add_working_period(WorkingHour *workingHour) { workingPeriods.add_new_period(workingHour); }
    void set_salary_config(SalaryConfig *sConfig) { salaryConfig = sConfig; }
    void set_team(Team *empTeam) { team = empTeam; }

    int find_emp_total_working_hours();
    int find_absent_days();
    int find_initial_earning();
    int find_bonus_amount();
    int find_tax_amount();
    int find_total_earning();
    bool is_allowed_period_to_add(int day, int periodStart, int periodEnd);
};

int Employee::find_absent_days()
{
    set<int> nonRepWorkDays;
    for (WorkingHour *workperiod : workingPeriods.get_periods())
    {
        nonRepWorkDays.insert(workperiod->get_day());
    }
    return ONE_MONTH_DAYS - nonRepWorkDays.size();
}
int Employee::find_emp_total_working_hours()
{
    return workingPeriods.find_total_working_hours();
}
int Employee::find_initial_earning()
{
    return salaryConfig->find_init_earning(find_emp_total_working_hours());
}
int Employee::find_bonus_amount()
{
    if (team != NULL)
    {
        int initialEarning = find_initial_earning();
        return round((team->get_bonus_percentage() * initialEarning) / 100.0);
    }
    return 0;
}
int Employee::find_tax_amount()
{
    int initialEarning = find_initial_earning() + find_bonus_amount();
    return round((get_salary_config()->get_tax_percentage() * initialEarning) / 100.0);
}
int Employee::find_total_earning()
{
    return find_initial_earning() + find_bonus_amount() - find_tax_amount();
}
bool Employee::is_allowed_period_to_add(int day, int periodStart, int periodEnd)
{
    for (int i = 0; i < workingPeriods.get_periods().size(); i++)
    {
        WorkingHour *curPeriod = workingPeriods.get_periods()[i];
        if (curPeriod->get_day() == day &&
            curPeriod->get_period().first < periodEnd && curPeriod->get_period().second > periodStart)
        {
            error("INVALID_INTERVAL");
            return false;
        }
    }
    return true;
}
string Employee::get_emp_team_id()
{
    if (team != NULL)
        return to_string(team->get_team_id());
    else
        return "N/A";
}

int Team ::find_team_total_working_hours()
{
    int result = 0;
    for (int i = 0; i < members.size(); i++)
    {
        result += members[i]->find_emp_total_working_hours();
    }
    return result;
}
double Team ::find_avg_member_working_hour()
{
    int totalHours = find_team_total_working_hours();
    double avgHours = totalHours / members.size();
    return avgHours;
}
double Team ::find_emps_working_hours_variance()
{
    double sumOfSquaredDiffs = 0;
    for (int i = 0; i < members.size(); i++)
    {
        double wHourDiff = find_avg_member_working_hour() - members[i]->find_emp_total_working_hours();
        sumOfSquaredDiffs += pow(wHourDiff, 2);
    }
    double variance = sumOfSquaredDiffs / members.size();
    return variance;
}
bool Team ::is_worthy_to_bonus()
{
    if (bonusMinWorkingHours < find_team_total_working_hours() && bonusWorkingHoursMaxVariance > find_emps_working_hours_variance())
    {
        return true;
    }
    return false;
}
void Team ::show_members_info()
{
    for (int i = 0; i < members.size(); i++)
    {
        cout << "Member ID: " << members[i]->get_id() << endl
             << "Total Earning: " << members[i]->find_total_earning() << endl
             << "---" << endl;
    }
}

int SalaryConfig::find_init_earning(int totalWHours)
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
void SalaryConfig::show_config()
{
    cout << "Base Salary: " << baseSalary << endl;
    cout << "Salary Per Hour: " << salaryPerHour << endl;
    cout << "Salary Per Extra Hour: " << salaryPerExtraHour << endl;
    cout << "Official Working Hours: " << officialWorkingHours << endl;
    cout << "Tax: " << taxPercentage << '%' << endl;
}
void SalaryConfig::update_config(string b, string s, string se, string o, string t)
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

int SetOfWorkingHours::find_total_working_hours()
{
    int result = 0;
    for (int i = 0; i < workingHours.size(); i++)
    {
        result += workingHours[i]->get_period_len();
    }
    return result;
}
int SetOfWorkingHours::find_total_working_hours_by_day(int day)
{
    int total = 0;
    for (int i = 0; i < workingHours.size(); i++)
    {
        if (workingHours[i]->get_day() == day)
        {
            total += workingHours[i]->get_period_len();
        }
    }
    return total;
}
double SetOfWorkingHours::find_avg_emps_by_start_hour(int startHour)
{
    int endHour = startHour + 1;
    int sumOfEmps = 0;
    for (int day = 0; day < ONE_MONTH_DAYS; day++)
    {
        set<int> workingEmpIds;
        for (int i = 0; i < workingHours.size(); i++)
        {
            int startOfWorkPeriod = workingHours[i]->get_period().first;
            int endOfWorkPeriod = workingHours[i]->get_period().second;
            if (startOfWorkPeriod <= startHour && endOfWorkPeriod >= endHour &&
                workingHours[i]->get_day() == day)
            {
                workingEmpIds.insert(workingHours[i]->get_employee_id());
            }
        }
        sumOfEmps += workingEmpIds.size();
    }
    return round((double)sumOfEmps / ONE_MONTH_DAYS * 10) / 10;
}
void SetOfWorkingHours::delete_periods_by_day_and_emp(int employeeId, int day)
{
    for (int i = 0; i < workingHours.size(); i++)
    {
        if (workingHours[i]->get_day() == day && workingHours[i]->get_employee_id() == employeeId)
        {
            workingHours.erase(workingHours.begin() + i);
            delete workingHours[i];
        }
    }
}
void SetOfWorkingHours::show_indexes_with_max_value(vector<pair<string, string>> indexAndValue)
{
    double max = stof(indexAndValue[0].second);
    for (pair<string, string> dayAndTot : indexAndValue)
    {
        if (stof(dayAndTot.second) > max)
        {
            max = stof(dayAndTot.second);
        }
    }
    for (pair<string, string> dayAndTot : indexAndValue)
    {
        if (stof(dayAndTot.second) == max)
        {
            cout << " " << dayAndTot.first;
        }
    }
    cout << endl;
}
void SetOfWorkingHours::show_indexes_with_min_value(vector<pair<string, string>> indexAndValue)
{
    double min = stof(indexAndValue[0].second);
    for (pair<string, string> dayAndTot : indexAndValue)
    {
        if (stof(dayAndTot.second) < min)
        {
            min = stof(dayAndTot.second);
        }
    }
    for (pair<string, string> dayAndTot : indexAndValue)
    {
        if (stof(dayAndTot.second) == min)
        {
            cout << " " << dayAndTot.first;
        }
    }
    cout << endl;
}
void SetOfWorkingHours::show_total_hours_per_day(int startDay, int endDay)
{
    if (are_valid_days(startDay, endDay) == true)
    {
        vector<pair<string, string>> dayAndTotalHours;
        for (int i = startDay; i <= endDay; i++)
        {
            cout << "Day #" << i << ": " << find_total_working_hours_by_day(i) << endl;
            dayAndTotalHours.push_back({to_string(i), to_string(find_total_working_hours_by_day(i))});
        }
        cout << "---" << endl;
        cout << "Day(s) with Max Working Hours:";
        show_indexes_with_max_value(dayAndTotalHours);
        cout << "Day(s) with Min Working Hours:";
        show_indexes_with_min_value(dayAndTotalHours);
    }
    else
    {
        error("INVALID_ARGUMENTS");
    }
}
void SetOfWorkingHours::show_employee_per_hour(int startHour, int endHour)
{
    if (are_valid_hours(startHour, endHour) == true)
    {
        vector<pair<string, string>> hourAndAvgEmps;
        for (int i = startHour; i < endHour; i++)
        {
            cout << i << "-" << i + 1 << ": " << find_avg_emps_by_start_hour(i) << endl;
            string timePeriod = to_string(i) + '-' + to_string(i + 1);
            hourAndAvgEmps.push_back({timePeriod, to_string(find_avg_emps_by_start_hour(i))});
        }
        cout << "---" << endl;
        cout << "Period(s) with Max Working Employees:";
        show_indexes_with_max_value(hourAndAvgEmps);
        cout << "Period(s) with Min Working Employees:";
        show_indexes_with_min_value(hourAndAvgEmps);
    }
    else
    {
        error("INVALID_ARGUMENTS");
    }
}

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

    void sort_by_total_working_hours(vector<Team *> teams)
    {
        for (int i = 0; i < teams.size(); i++)
        {
            for (int j = i; j < teams.size(); j++)
            {
                if (teams[i]->find_team_total_working_hours() > teams[j]->find_team_total_working_hours())
                {
                    Team *temp = teams[i];
                    teams[i] = teams[j];
                    teams[j] = temp;
                }
            }
        }
    }
    void set_emp_w_hours(Employee *emp)
    {
        vector<WorkingHour *> wPeriods;
        for (int j = 0; j < workingHours.get_periods().size(); j++)
        {
            if (workingHours.get_periods()[j]->get_employee_id() == emp->get_id())
            {
                wPeriods.push_back(workingHours.get_periods()[j]);
            }
        }
        emp->set_working_periods(wPeriods);
    }
    void set_emp_s_config(Employee *emp)
    {
        emp->set_salary_config(find_salary_by_level(emp->get_level()));
    }
    void set_emp_team(Employee *emp)
    {
        emp->set_team(find_team_by_member_id(emp->get_id()));
    }

    vector<string> read_file(string filePath)
    {
        vector<string> readFile;
        ifstream inputFile(filePath);
        string lineOfFile;
        while (getline(inputFile, lineOfFile))
        {
            istringstream line(lineOfFile);
            string fileElement;
            while (getline(line, fileElement, ','))
                readFile.push_back(fileElement);
        }
        inputFile.close();
    }
    
    vector<Employee *> build_emps_vec(vector<string> readFile)
    {
    }
    SetOfWorkingHours build_working_hours_vec(vector<string> readFile)
    {
    }
    vector<Team *> build_teams_vec(vector<string> readFile)
    {
    }
    vector<SalaryConfig *> build_salary_configs_vec(vector<string> readFile)
    {
    }
    
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
    }

    bool is_valid_day(int day)
    {
        if (day < 1 || day > 30)
        {
            error("INVALID_ARGUMENTS");
            return false;
        }
        return true;
    }
    bool is_valid_period_time(int periodStart, int periodEnd)
    {
        if (periodStart >= periodEnd ||
            periodStart < 0 || periodStart > 24 || periodEnd < 0 || periodEnd > 24)
        {
            error("INVALID_ARGUMENTS");
            return false;
        }
        return true;
    }

    vector<Employee *> employees;
    SetOfWorkingHours workingHours;
    vector<Team *> teams;
    vector<SalaryConfig *> salaryConfigs;

public:
    // Program(vector<Employee *> e, vector<WorkingHour *> w,
    //         vector<Team *> t, vector<SalaryConfig *> s)
    // {
    //     employees = e;
    //     workingHours = w;
    //     teams = t;
    //     salaryConfigs = s;
    // }
    Program(string FolderPath)
    {
        // Program program (
        //     {new Employee(1, "AzadehZahedi", 28, "junior"),
        //      new Employee(2, "MehranAmiri", 32, "expert"),
        //      new Employee(3, "ParvinKarami", 45, "senior"),
        //      new Employee(4, "BehzadAbbasi", 26, "junior"),
        //      new Employee(5, "GolnazEmadi", 39, "team_lead"),
        //      new Employee(6, "HatefJahangiri", 50, "junior"),
        //      new Employee(7, "DonyaMohammadi", 31, "team_lead")},
        //     {new WorkingHour(2, 16, 9, 16),
        //      new WorkingHour(7, 22, 8, 17),
        //      new WorkingHour(5, 7, 8, 12),
        //      new WorkingHour(4, 21, 14, 17),
        //      new WorkingHour(6, 30, 14, 21),
        //      new WorkingHour(7, 9, 14, 20),
        //      new WorkingHour(3, 12, 13, 17),
        //      new WorkingHour(5, 7, 14, 18),
        //      new WorkingHour(1, 18, 7, 11),
        //      new WorkingHour(6, 25, 13, 19),
        //      new WorkingHour(7, 9, 9, 10),
        //      new WorkingHour(1, 18, 13, 17),
        //      new WorkingHour(2, 18, 9, 17)},
        //     {new Team(1, 2, {2, 4}, 410, 22.837),
        //      new Team(2, 3, {3, 1}, 450, 31.416)},
        //     {new SalaryConfig("junior", 13000, 60, 48, 210, 15),
        //      new SalaryConfig("senior", 21500, 100, 75, 215, 28),
        //      new SalaryConfig("expert", 31000, 140, 112, 215, 25),
        //      new SalaryConfig("team_lead", 40000, 180, 134, 220, 32)});
        // program.connectObjects();
        string employeesFPath = FolderPath + "/employees.csv", workingHoursFPath = FolderPath + "/working_hours.csv",
               teamsFPath = FolderPath + "/teams.csv", salaryConfigsFPath = FolderPath + "/salary_configs.csv";

        vector<string> empsFile = read_file(employeesFPath);
        vector<string> wHoursFile = read_file(workingHoursFPath);
        vector<string> teamsFile = read_file(teamsFPath);
        vector<string> salConfigsFile = read_file(salaryConfigsFPath);

        employees = build_emps_vec(empsFile);
        workingHours = build_working_hours_vec(empsFile);
        teams = build_teams_vec(empsFile);
        salaryConfigs = build_salary_configs_vec(empsFile);

        connectObjects();
    }

    // *1*
    void report_salaries()
    {
        for (Employee *employee : employees)
        {
            cout << "ID: " << employee->get_id() << endl
                 << "Name: " << employee->get_name() << endl
                 << "Total Working Hours: " << employee->find_emp_total_working_hours() << endl
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
                 << "Total Working Hours: " << selectedEmp->find_emp_total_working_hours() << endl
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
                 << "Average Member Working Hour: " << round(selectedTeam->find_avg_member_working_hour() * 10) / 10 << endl
                 << "Bonus: " << selectedTeam->get_bonus_percentage() << endl
                 << "---" << endl;
            selectedTeam->show_members_info();
        }
    }
    // *4*
    void report_total_hours_per_day(int startDay, int endDay)
    {
        // SetOfWorkingHours selectedWorkingHours;
        // for (int i = 0; i < workingHours.get_periods().size(); i++)
        // {
        //     for (int day = startDay; day <= endDay; day++)
        //     {
        //         if (workingHours.get_periods()[i]->get_day() == day)
        //         {
        //             selectedWorkingHours.add_new_period(workingHours.get_periods()[i]);
        //         }
        //     }
        // }
        // selectedWorkingHours.show_total_hours_per_day(startDay, endDay);
        // cout<<"poloooooooooo\n";
        workingHours.show_total_hours_per_day(startDay, endDay);
    }
    // *5*
    void report_employee_per_hour(int startHour, int endHour)
    {
        workingHours.show_employee_per_hour(startHour, endHour);
    }
    // *6*
    void show_salary_config(string level)
    {
        SalaryConfig *selectedSalary = find_salary_by_level(level);
        if (selectedSalary != NULL)
            selectedSalary->show_config();
    }
    // *7*
    void update_salary_config(string level, string baseSalary, string salaryPerHour,
                              string salaryPerExtraHour, string officialWorkingHours, string taxPercentage)
    {
        SalaryConfig *selectedSalary = find_salary_by_level(level);
        if (selectedSalary != NULL)
            selectedSalary->update_config(baseSalary, salaryPerHour,
                                          salaryPerExtraHour, officialWorkingHours, taxPercentage);
    }
    // *8*
    void add_working_hours(int employeeId, int day, int periodStart, int periodEnd)
    {
        Employee *selectedEmp = find_employee_by_id(employeeId);
        if (selectedEmp != NULL && is_valid_day(day) && is_valid_period_time(periodStart, periodEnd))
        {
            if (selectedEmp->is_allowed_period_to_add(day, periodStart, periodEnd) == true)
            {
                WorkingHour *newWorkingHour = new WorkingHour(employeeId, day, periodStart, periodEnd);

                workingHours.add_new_period(newWorkingHour);
                selectedEmp->add_working_period(newWorkingHour);
                cout << "OK\n";
            }
        }
    }
    // *9*
    void delete_working_hours(int employeeId, int day)
    {
        Employee *selectedEmp = find_employee_by_id(employeeId);
        if (selectedEmp != NULL && is_valid_day(day))
        {
            workingHours.delete_periods_by_day_and_emp(employeeId, day);
            selectedEmp->get_working_periods().delete_periods_by_day_and_emp(employeeId, day);
            cout << "OK\n";
        }
    }
    // *10*
    void update_team_bonus(int teamId, int bonusPercentage)
    {
        Team *selectedTeam = find_team_by_id(teamId);
        if (selectedTeam != NULL)
        {
            if (bonusPercentage < 0 || bonusPercentage > 100)
            {
                error("INVALID_ARGUMENTS");
            }
            else
            {
                selectedTeam->set_bonus_percentage(bonusPercentage);
                cout << "OK\n";
            }
        }
    }
    // *11*
    void find_teams_for_bonus()
    {
        vector<Team *> worthyTeams;
        for (int i = 0; i < teams.size(); i++)
        {
            if (teams[i]->is_worthy_to_bonus())
            {
                worthyTeams.push_back(teams[i]);
            }
        }
        if (worthyTeams.size() != 0)
        {
            sort_by_total_working_hours(worthyTeams);
            for (int i = 0; i < worthyTeams.size(); i++)
            {
                cout << "Team ID: " << worthyTeams[i]->get_team_id() << endl;
            }
        }
        else
        {
            cout << "NO_BONUS_TEAMS\n";
        }
    }

    // --12--
    void handle_commands()
    {
        string command;
        while (cin >> command)
        {
            if (command == "report_salaries")
            {
                report_salaries();
            }
            else if (command == "report_employee_salary")
            {
                int employeeId;
                cin >> employeeId;
                report_employee_salary(employeeId);
            }
            else if (command == "report_team_salary")
            {
                int teamId;
                cin >> teamId;
                report_team_salary(teamId);
            }
            else if (command == "report_total_hours_per_day")
            {
                int startDay, endDay;
                cin >> startDay >> endDay;
                report_total_hours_per_day(startDay, endDay);
            }
            else if (command == "report_employee_per_hour")
            {
                int startHour, endHour;
                cin >> startHour >> endHour;
                report_employee_per_hour(startHour, endHour);
            }
            else if (command == "show_salary_config")
            {
                string level;
                cin >> level;
                show_salary_config(level);
            }
            else if (command == "update_salary_config")
            {
                string level, baseSalary, salaryPerHour, salaryPerExtraHour, officialWorkingHours, taxPercentage;
                cin >> level >> baseSalary >> salaryPerHour >> salaryPerExtraHour >> officialWorkingHours >> taxPercentage;
                update_salary_config(level, baseSalary, salaryPerHour, salaryPerExtraHour,
                                     officialWorkingHours, taxPercentage);
            }
            else if (command == "add_working_hours")
            {
                int employeeId, day, periodStart, periodEnd;
                cin >> employeeId >> day >> periodStart >> periodEnd;
                add_working_hours(employeeId, day, periodStart, periodEnd);
            }
            else if (command == "delete_working_hours")
            {
                int employeeId, day;
                cin >> employeeId >> day;
                delete_working_hours(employeeId, day);
            }
            else if (command == "update_team_bonus")
            {
                int teamId, bonusPercentage;
                cin >> teamId >> bonusPercentage;
                update_team_bonus(teamId, bonusPercentage);
            }
            else if (command == "find_teams_for_bonus")
            {
                find_teams_for_bonus();
            }
            else
            {
                error("unknown command\n");
            }
        }
    }
    // --13--
    void delete_everything()
    {
        for (Employee *employee : employees)
            delete employee;
        for (WorkingHour *workingHour : workingHours.get_periods())
            delete workingHour;
        for (Team *team : teams)
            delete team;
        for (SalaryConfig *salaryConfig : salaryConfigs)
            delete salaryConfig;
    }
};

int main(int argc, char *argv[])
{
    Program program(argv[FOLDER_PATH_INDEX]);

    program.handle_commands();

    program.delete_everything();

    return 0;
}