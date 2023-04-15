#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>
#include <climits>
#include <cmath>
#include <algorithm>
using namespace std;
struct SALARY_CONFIG
{
    string level;
    int base_salary;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hour;
    int tax_persrntage;
};
class Teams;
class Employees
{
public:
    void set_employee_informations(string str, Employees &new_employee);
    void printname();
    void set_work_intervals_for_employees(string str, vector<Employees> &all_employees);
    void function_for_report_salaries(vector<Employees> all_employees, vector<Teams> all_teams);
    void function_for_report_employee_salary(int employee_id_want_to_be_found, vector<Employees> all_employee, vector<Teams> all_teams);
    void report_total_hours_per_day(int start_day, int end_day);
    void set_employees_salaries(vector<SALARY_CONFIG> salary_config, vector<Employees> &all_employees);
    int evaluate_employee_salary(int employee_id_from_stdin, int command_choicer, vector<Employees> all_employees, vector<Teams> all_teams);
    string find_team_head_name(string team_head_id, vector<Employees> all_employees);
    int evaluate_all_team_memebers_working_hours(vector<Employees> all_employee, vector<string> team_memebrs_ids);
    void function_to_evaluate_sum_employee_hours_between_days(vector<Employees> all_employees, int start_day, int end_day, vector<int> Total_working_hours);
    void Update_employee_salary_struct_after_updating_salaries(vector<Employees> &all_employees, string salary_level, vector<SALARY_CONFIG> all_salaries);
    void delete_working_hours(vector<Employees> &all_employees, string employee_id_want_to_find, string day);
    void add_working_hour_for_employee(vector<Employees> &all_employees, string employee_number_want_to_find, string day, int period_start, int period_end);
    bool check_for_function_report_employee_salary(vector<Employees> all_employees, string employee_id_want_to_find);
    bool check_for_function_report_total_hours_per_day(vector<Employees> all_employees, int start_day, int end_day);
    bool check_for_function_deleting_hours(vector<Employees> all_employees, string employee_number_want_to_find, int day);
    bool check_for_function_add_working_hours(vector<Employees> all_employees, string employee_id_want_to_find, string day, string time_interval);
    void function_for_report_employee_per_hour(vector<Employees> all_employees, int start_hour, int end_hour);
    int get_whole_team_work(vector<string> all_ids, vector<Employees> all_employees);
    double want_to_find_average_square(vector<Employees> all_employees, vector<string> team_members, string team_id, int team_size);
    int get_employee_id()
    {
        return stoi(employee_id);
    }
    int total_working_hour() //------------------------------------------------------------------------------------------------------------------------------------------------
    {
        int sum_of_work_hours = 0;
        for (int i = 0; i < employee_workdays.size(); i++)
        {
            for (int j = 1; j < employee_workdays[i].size(); j++)
            {
                int pos = employee_workdays[i][j].find("-");
                int num1 = stoi(employee_workdays[i][j].substr(0, pos));
                int num2 = stoi(employee_workdays[i][j].substr(pos + 1));
                int difference = num2 - num1;
                sum_of_work_hours += difference;
            }
        }
        return sum_of_work_hours;
    }
    void return_hame_chi()
    {
        cout << employee_name << endl;
        cout << employee_age << endl;
        cout << employee_id << endl;
        cout << employee_level << endl;
        cout << employee_salary.base_salary << employee_salary.level << employee_salary.tax_persrntage << endl;
        for (int i = 0; i < employee_workdays.size(); i++)
        {
            for (int j = 0; j < employee_workdays[i].size(); j++)
            {
                cout << employee_workdays[i][j];
            }
            cout << endl;
        }
    }

private:
    string employee_id; // az int dareshavordam
    string employee_name;
    string employee_age; // az int dareshavordam
    string employee_level;
    vector<vector<string>> employee_workdays;
    vector<string> employee_working_intervals;
    int all_employee_work_hours;
    SALARY_CONFIG employee_salary;
};
class Teams
{
public:
    void set_teams_informations(string str, Teams &new_team);
    void printname();
    int finding_employee_team_id_and_team_bonus(string employee_id_want_to_find, vector<Teams> all_teams, int command_choicer);
    void function_to_report_team_salary(vector<Teams> all_teams, vector<Employees> all_employees, string team_id_want_to_find);
    void Update_team_bonus(vector<Teams> &all_teams, string team_number_want_to_find, int new_team_bonus);
    bool check_for_function_report_team_salary(vector<Teams> all_teams, string team_id_want_to_find);
    bool check_for_function_update_team_bonus(vector<Teams> all_teams, string team_id_want_to_find, int bonus_percentage);
    void find_team_for_bonus(vector<Employees> all_employess, vector<Teams> all_teams);
    void add_num(string num)
    {
        team_members_id.push_back(num);
    }
    void sort_nums()
    {
        sort(team_members_id.begin(), team_members_id.end(), [](string &a, string &b)
             { return stoi(a) < stoi(b); });
    }

private:
    string team_id;                          // az int dareshavordam
    string team_head_id;                     // az int dareshavordam
    vector<string> team_members_id;          // az int dareshavordam
    int team_bonus = 0;                      // az int dareshavordam
    string bonus_min_working_hours;          // az int dareshavordam
    string bonus_working_hours_max_variance; // az double dareshavordam
};

bool compare_employees(Employees &emp1, Employees &emp2)
{
    return emp1.get_employee_id() < emp2.get_employee_id();
}
void sort_employees(vector<Employees> &all_employees)
{
    sort(all_employees.begin(), all_employees.end(), compare_employees);
}
void Employees::printname()
{
    cout << employee_name << " " << employee_id << endl;
    for (int i = 0; i < employee_workdays.size(); i++)
    {
        for (int j = 0; j < employee_workdays[i].size(); j++)
        {
            cout << employee_workdays[i][j] << " ";
        }
        cout << endl;
    }
}
void Teams::printname()
{
    cout << team_id;
}
vector<string> split_by_commas(string str)
{
    vector<string> result;
    int start_pos = 0;
    while (start_pos < str.length())
    {
        int comma_pos = str.find(",", start_pos);
        if (comma_pos == string::npos)
        {
            result.push_back(str.substr(start_pos));
            break;
        }
        result.push_back(str.substr(start_pos, comma_pos - start_pos));
        start_pos = comma_pos + 1;
    }
    return result;
}
void Employees::set_employee_informations(string str, Employees &new_employee)
{
    vector<string> fields = split_by_commas(str);
    new_employee.employee_id = fields[0];
    new_employee.employee_name = fields[1];
    new_employee.employee_age = fields[2];
    new_employee.employee_level = fields[3];
}
vector<Employees> read_from_employees_file(string filename) // kar mikone
{
    vector<Employees> all_employees;
    ifstream input_csv(filename);
    Employees new_employee;

    string line;
    getline(input_csv, line); // skip the header row in the CSV file

    while (getline(input_csv, line))
    {
        new_employee.set_employee_informations(line, new_employee);
        all_employees.push_back(new_employee);
    }
    sort_employees(all_employees);
    input_csv.close();
    return all_employees;
}
vector<Teams> read_from_Teams_file(string filename)
{
    vector<Teams> all_teams;
    ifstream input_csv(filename);
    Teams new_team;

    string line;
    getline(input_csv, line); // skip the header row in the CSV file

    while (getline(input_csv, line))
    {
        new_team.set_teams_informations(line, new_team);
        all_teams.push_back(new_team);
    }
    for (int i = 0; i < all_teams.size(); i++)
    {
        all_teams[i].sort_nums();
    }
    input_csv.close();
    return all_teams;
}
void mergeRows(vector<vector<string>> &data)
{
    map<string, vector<string>> rowMap;
    for (const auto &row : data)
    {
        const string &firstcolumn = row[0];
        vector<string> &secondcolumn = rowMap[firstcolumn];
        secondcolumn.insert(secondcolumn.end(), row.begin() + 1, row.end());
    }
    data.clear();
    for (const auto &pair : rowMap)
    {
        vector<string> newRow = {pair.first};
        newRow.insert(newRow.end(), pair.second.begin(), pair.second.end());
        data.push_back(newRow);
    }
}
vector<string> get_third_to_end(vector<string> all_strings)
{
    vector<string> result_vector_of_strings;
    for (int size = 2; size < all_strings.size(); size++)
    {
        result_vector_of_strings.push_back(all_strings[size]);
    }
    return result_vector_of_strings;
}
vector<string> get_second_to_end(vector<string> all_strings)
{
    vector<string> result_vector_of_strings;
    for (int size = 1; size < all_strings.size(); size++)
    {
        result_vector_of_strings.push_back(all_strings[size]);
    }
    return result_vector_of_strings;
}
int evaluate_working_hours_of_employee(vector<string> input_vector_of_strings)
{
    vector<int> result_vector;
    for (const auto &str : input_vector_of_strings)
    {
        istringstream iss(str);
        string numstr1, numstr2;
        getline(iss, numstr1, '-');
        getline(iss, numstr2, '-');
        int num1 = stoi(numstr1);
        int num2 = stoi(numstr2);
        int diff = num2 - num1;
        result_vector.push_back(diff);
    }
    int sum_all_diffs = 0;
    for (int i = 0; i < result_vector.size(); i++)
    {
        sum_all_diffs = sum_all_diffs + result_vector[i];
    }
    return sum_all_diffs;
}
vector<vector<string>> create_2d_vector_for_working_intervals(vector<string> input_strings_for_2d_vector)
{
    vector<vector<string>> result_2d_vector_of_strings;
    vector<string> first_row;

    first_row.push_back(input_strings_for_2d_vector.front());
    result_2d_vector_of_strings.push_back(first_row);
    for (int size = 1; size < input_strings_for_2d_vector.size(); size++)
    {
        result_2d_vector_of_strings[0].push_back(input_strings_for_2d_vector[size]);
    }
    return result_2d_vector_of_strings;
}
vector<vector<string>> working_interval_2d_vector_need_to_be_saved_in_class(vector<vector<string>> vector1, vector<vector<string>> vector2)
{
    vector<vector<string>> result_2d_vec;
    for (const auto &row : vector1)
    {
        result_2d_vec.push_back(row);
    }
    for (const auto &row : vector2)
    {
        result_2d_vec.push_back(row);
    }
    return result_2d_vec;
}
void Employees::set_work_intervals_for_employees(string filename, vector<Employees> &all_employees)
{
    ifstream input_csv(filename);
    string line;
    string emp_id;
    string emp_work_day;
    vector<string> working_intervals_for_evaluate;
    vector<string> working_intervals_for_2d_vector;
    vector<vector<string>> working_intervals_need_to_be_added;
    getline(input_csv, line); // skip the header row in the CSV file

    while (getline(input_csv, line))
    {
        vector<string> fields = split_by_commas(line);
        emp_id = fields[0];

        for (int number_of_employees = 0; number_of_employees < all_employees.size(); number_of_employees++)
        {
            if (all_employees[number_of_employees].employee_id == emp_id)
            {
                emp_work_day = fields[1];

                working_intervals_for_evaluate = get_third_to_end(fields);

                working_intervals_for_2d_vector = get_second_to_end(fields);
                for (int i = 0; i < working_intervals_for_evaluate.size(); i++)
                {
                    all_employees[number_of_employees].employee_working_intervals.push_back(working_intervals_for_evaluate[i]);
                }

                working_intervals_need_to_be_added = create_2d_vector_for_working_intervals(working_intervals_for_2d_vector);

                all_employees[number_of_employees].employee_workdays.insert(all_employees[number_of_employees].employee_workdays.end(), working_intervals_need_to_be_added.begin(), working_intervals_need_to_be_added.end());
                all_employees[number_of_employees].all_employee_work_hours = all_employees[number_of_employees].total_working_hour();
                mergeRows(all_employees[number_of_employees].employee_workdays);
            }
        }
    }
    input_csv.close();
}
void read_from_working_hours_file(vector<Employees> &all_employees, string folder_name)
{
    vector<Employees> All_of_employees = all_employees;
    Employees new_Employee;
    new_Employee.set_work_intervals_for_employees(folder_name + "/working_hours.csv", all_employees);
}
void Employees::set_employees_salaries(vector<SALARY_CONFIG> salary_config, vector<Employees> &all_employees)
{
    for (int all_salary = 0; all_salary < salary_config.size(); all_salary++)
    {

        for (int all_employee_numbers = 0; all_employee_numbers < all_employees.size(); all_employee_numbers++)
        {
            if (all_employees[all_employee_numbers].employee_level == salary_config[all_salary].level)
            {
                all_employees[all_employee_numbers].employee_salary = salary_config[all_salary];
            }
        }
    }
}
SALARY_CONFIG set_new_salary(string line)
{
    SALARY_CONFIG new_salary_config;
    vector<string> fields = split_by_commas(line);
    new_salary_config.level = fields[0];
    new_salary_config.base_salary = stoi(fields[1]);
    new_salary_config.salary_per_hour = stoi(fields[2]);
    new_salary_config.salary_per_extra_hour = stoi(fields[3]);
    new_salary_config.official_working_hour = stoi(fields[4]);
    new_salary_config.tax_persrntage = stoi(fields[5]);
    return new_salary_config;
}
void read_from_salary_configs_file(vector<SALARY_CONFIG> &salary_config, string file_name, vector<Employees> &all_employees)
{
    ifstream input_csv(file_name);
    string line;
    SALARY_CONFIG new_salary_config;
    Employees new_employee;
    getline(input_csv, line); // skip the header row in the CSV file
    while (getline(input_csv, line))
    {
        salary_config.push_back(set_new_salary(line));
    }
    new_employee.set_employees_salaries(salary_config, all_employees);
    input_csv.close();
}
vector<string> find_team_memebers_id_in_dollar_signed_string(string string_with_dollar_sign)
{
    vector<string> extrected_numbers;
    string current_number = "";
    for (char &c : string_with_dollar_sign)
    {
        if (c == '$')
        {
            extrected_numbers.push_back(current_number);
            current_number = "";
        }
        else
        {
            current_number += c;
        }
    }
    if (current_number != "")
    {
        extrected_numbers.push_back(current_number);
    }
    return extrected_numbers;
}
void Teams::set_teams_informations(string str, Teams &new_team)
{
    vector<string> fields = split_by_commas(str);
    new_team.team_id = fields[0];
    new_team.team_head_id = fields[1];
    new_team.team_members_id = find_team_memebers_id_in_dollar_signed_string(fields[2]);
    new_team.bonus_min_working_hours = fields[3];
    new_team.bonus_working_hours_max_variance = fields[4];
}
void Employees::report_total_hours_per_day(int start_day, int end_day)
{
    vector<int> vector_of_working_hours_between_days;
    int sum = 0;
    for (int from = start_day; from <= end_day; from++)
    {
        sum = 0;
        for (int size = 0; size < employee_workdays.size(); size++)
        {
            if (employee_workdays[size][0] == to_string(from))
            { // Function is in gallery screenshot
            }
        }
    }
}
int Teams::finding_employee_team_id_and_team_bonus(string employee_id_want_to_find, vector<Teams> all_teams, int command_choicer)
// command choicer -->> 1 for employee team id / 2 for team bonus
{
    int flag = 1;
    int finded_team_bonus = -1;
    int finded_employee_team_id = -1;
    for (int all_team_numbers = 0; all_team_numbers < all_teams.size(); all_team_numbers++)
    {
        for (int all_members_in_a_team = 0; all_members_in_a_team < all_teams[all_team_numbers].team_members_id.size(); all_members_in_a_team++)
        {
            if ((employee_id_want_to_find) == all_teams[all_team_numbers].team_members_id[all_members_in_a_team])
            {
                finded_employee_team_id = stoi(all_teams[all_team_numbers].team_id);
                finded_team_bonus = all_teams[all_team_numbers].team_bonus;
            }
        }
    }
    if (command_choicer == 1)
    {
        if (finded_employee_team_id == -1)
            return 0;
        else
            return finded_employee_team_id;
    };
    if (command_choicer == 2)
    {
        if (finded_employee_team_id != -1)
            return finded_team_bonus;
        else if (finded_employee_team_id == -1)
            return 0;
    }
    return 0;
}
int bonus_evaluator(int salary, int bonus_per)
{
    double bonus_multi = (double)bonus_per / 100.0;
    int result = (int)round(salary * bonus_multi);
    result = (int)round(result / 10.0) * 10;
    return result;
}
int tax_evaluator(int salary, int tax_per)
{
    double tax_milti = (double)tax_per / 100.0;
    int result = (int)round(salary * tax_milti);
    return result;
}
int round_up_floats_2(vector<float> numbers)
{
    float rounded_num = roundf(numbers[0] * (numbers[1] / 100));
    return (int)rounded_num;
}
float round_up_floats_3(float numbers)
{
    float rounded_num = roundf(numbers / 30);
    return rounded_num;
}
int Employees::evaluate_employee_salary(int employee_id_from_stdin, int command_choicer, vector<Employees> all_employees, vector<Teams> all_teams)
// Command choice is like this ->> 1 for Salary / 2 for Total Earning / 3 for value of bonus / 4 for Tax value
{
    int Total_salary_with_tax;
    int Total_salary;
    float team_bonus;
    float Tax;
    int Salary_with_tax;
    vector<float> float_nums;
    Teams employee_team_id;
    int employee_team_bonus_percentage = 0;
    for (int number_of_employee = 0; number_of_employee < all_employees.size(); number_of_employee++)
    {
        if (all_employees[number_of_employee].employee_id == to_string(employee_id_from_stdin))
        {
            Total_salary = all_employees[number_of_employee].employee_salary.base_salary;

            int extra_working_hours = all_employees[number_of_employee].total_working_hour() - all_employees[number_of_employee].employee_salary.official_working_hour;

            if (extra_working_hours > 0)
            {
                Total_salary = Total_salary + all_employees[number_of_employee].employee_salary.official_working_hour * all_employees[number_of_employee].employee_salary.salary_per_hour;

                Total_salary = Total_salary + extra_working_hours * (all_employees[number_of_employee].employee_salary.salary_per_extra_hour);
            }
            else
            {
                Total_salary = Total_salary + all_employees[number_of_employee].total_working_hour() * all_employees[number_of_employee].employee_salary.salary_per_hour;
            }
            employee_team_bonus_percentage = employee_team_id.finding_employee_team_id_and_team_bonus(all_employees[number_of_employee].employee_id, all_teams, 2);

            if (employee_team_bonus_percentage != 0)
            {

                float_nums.push_back((float)Total_salary);
                float_nums.push_back(float(employee_team_bonus_percentage));
                team_bonus = round_up_floats_2(float_nums);
                Total_salary = team_bonus + Total_salary;
            }
            else
            {
                Total_salary = Total_salary;
                team_bonus = 0;
            }
            float_nums.clear();
            float_nums.push_back((float)Total_salary);
            float_nums.push_back((float)all_employees[number_of_employee].employee_salary.tax_persrntage);
            Tax = round_up_floats_2(float_nums);
            Total_salary_with_tax = Total_salary - Tax;
        }
    }
    if (command_choicer == 1)
        return Total_salary - team_bonus;
    if (command_choicer == 2)
        return Total_salary_with_tax;
    if (command_choicer == 3)
        return team_bonus;
    if (command_choicer == 4)
        return Tax;
    return 0;
}

//-----------   AZ INJA DASTORA SHORO MISHAN BE TARTIB ----------
void Employees::function_for_report_salaries(vector<Employees> all_employees, vector<Teams> all_teams)
{
    for (int all_employee_numbers = 0; all_employee_numbers < all_employees.size(); all_employee_numbers++)
    {
        cout << "ID: " << all_employees[all_employee_numbers].employee_id << endl;
        cout << "Name: " << all_employees[all_employee_numbers].employee_name << endl;
        cout << "Total Working Hours: " << all_employees[all_employee_numbers].total_working_hour() << endl;
        cout << "Total Earning: " << all_employees[all_employee_numbers].evaluate_employee_salary(stoi(all_employees[all_employee_numbers].employee_id), 2, all_employees, all_teams) << endl;

        cout << "---" << endl;
    }
}
void Employees::function_for_report_employee_salary(int employee_id_want_to_be_found, vector<Employees> all_employee, vector<Teams> all_teams)
{
    Teams team_to_find_employee_team_id;
    for (int all_employee_numbers = 0; all_employee_numbers < all_employee.size(); all_employee_numbers++)
    {
        if (stoi(all_employee[all_employee_numbers].employee_id) == employee_id_want_to_be_found)
        {
            cout << "ID: " << all_employee[all_employee_numbers].employee_id << endl;
            cout << "Name: " << all_employee[all_employee_numbers].employee_name << endl;
            cout << "Age: " << all_employee[all_employee_numbers].employee_age << endl;
            cout << "Level: " << all_employee[all_employee_numbers].employee_level << endl;
            cout << "Team ID: ";
            if (team_to_find_employee_team_id.finding_employee_team_id_and_team_bonus(all_employee[all_employee_numbers].employee_id, all_teams, 1) == 0)
                cout << "N/A" << endl;
            else
                cout << team_to_find_employee_team_id.finding_employee_team_id_and_team_bonus(all_employee[all_employee_numbers].employee_id, all_teams, 1) << endl;

            cout << "Total Working Hours: " << all_employee[all_employee_numbers].total_working_hour() << endl;
            cout << "Absent Days: " << 30 - all_employee[all_employee_numbers].employee_workdays.size() << endl;
            cout << "Salary: " << all_employee[all_employee_numbers].evaluate_employee_salary(stoi(all_employee[all_employee_numbers].employee_id), 1, all_employee, all_teams) << endl;
            cout << "Bonus: " << all_employee[all_employee_numbers].evaluate_employee_salary(stoi(all_employee[all_employee_numbers].employee_id), 3, all_employee, all_teams) << endl;
            cout << "Tax: " << all_employee[all_employee_numbers].evaluate_employee_salary(stoi(all_employee[all_employee_numbers].employee_id), 4, all_employee, all_teams) << endl;
            cout << "Total Earning: " << all_employee[all_employee_numbers].evaluate_employee_salary(stoi(all_employee[all_employee_numbers].employee_id), 2, all_employee, all_teams) << endl;
        }
    }
}
string Employees::find_team_head_name(string team_head_id, vector<Employees> all_employees)
{
    for (int all_employee_numbers = 0; all_employee_numbers < all_employees.size(); all_employee_numbers++)
    {
        if (all_employees[all_employee_numbers].employee_id == team_head_id)
            return all_employees[all_employee_numbers].employee_name;
    }
    return "are";
}
int Employees::evaluate_all_team_memebers_working_hours(vector<Employees> all_employee, vector<string> team_memebrs_ids)
{
    int sum_of_all_working_hours = 0;
    for (int number_of_team_memebers = 0; number_of_team_memebers < team_memebrs_ids.size(); number_of_team_memebers++)
    {
        for (int employee_numbers = 0; employee_numbers < all_employee.size(); employee_numbers++)
        {
            if (all_employee[employee_numbers].employee_id == team_memebrs_ids[number_of_team_memebers])
            {
                sum_of_all_working_hours = sum_of_all_working_hours + all_employee[employee_numbers].total_working_hour();
            }
        }
    }
    return sum_of_all_working_hours;
}
float solve(float number, int place)
{
    cout << fixed;
    cout << setprecision(place);
    return number;
}
void Teams::function_to_report_team_salary(vector<Teams> all_teams, vector<Employees> all_employees, string team_id_want_to_find)
{
    Employees employee_for_functions;
    for (int number_of_teams = 0; number_of_teams < all_teams.size(); number_of_teams++)
    {
        if (all_teams[number_of_teams].team_id == team_id_want_to_find)
        {
            cout << "ID: " << all_teams[number_of_teams].team_id << endl;
            cout << "Head ID: " << all_teams[number_of_teams].team_head_id << endl;
            cout << "Head Name: " << employee_for_functions.find_team_head_name(all_teams[number_of_teams].team_head_id, all_employees) << endl;
            cout << "Team Total Working Hours: " << employee_for_functions.evaluate_all_team_memebers_working_hours(all_employees, all_teams[number_of_teams].team_members_id) << endl;
            cout << "Average Member Working Hours: " << solve(((double)employee_for_functions.evaluate_all_team_memebers_working_hours(all_employees, all_teams[number_of_teams].team_members_id) / (double)all_teams[number_of_teams].team_members_id.size()), 1) << endl;
            cout << "Bonus: " << all_teams[number_of_teams].team_bonus << endl;
            cout << "---" << endl;
            for (int number_of_member_in_team = 0; number_of_member_in_team < all_teams[number_of_teams].team_members_id.size(); number_of_member_in_team++)
            {
                cout << "Member ID: " << all_teams[number_of_teams].team_members_id[number_of_member_in_team] << endl;
                cout << "Total Earning: " << employee_for_functions.evaluate_employee_salary(stoi(all_teams[number_of_teams].team_members_id[number_of_member_in_team]), 2, all_employees, all_teams) << endl;
                cout << "---" << endl;
            }
        }
    }
}
int find_sum_of_employee_working_hours(vector<vector<string>> workdays)
{
    int Total_diff = 0;
    for (auto vector : workdays)
    {
        for (int i = 1; i < workdays.size(); i++)
        {
            int num1 = stoi(vector[i].substr(0, vector[i].find("-")));
            int num2 = stoi(vector[i].substr(vector[i].find("-") + 1));
            Total_diff = Total_diff + num2 - num1;
        }
    }
    return Total_diff;
}
void find_max_and_min_int(vector<int> nums, vector<int> all_days)
{
    int max_val = INT_MIN;
    int min_val = INT_MAX;
    vector<int> min_indices;
    vector<int> max_indices;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] > max_val)
        {
            max_val = nums[i];
            max_indices.clear();
            max_indices.push_back(i);
        }
        else if (nums[i] == max_val)
        {
            max_indices.push_back(i);
        }
        if (nums[i] < min_val)
        {
            min_val = nums[i];
            min_indices.clear();
            min_indices.push_back(i);
        }
        else if (nums[i] == min_val)
        {
            min_indices.push_back(i);
        }
    }
    cout << "Day(s) with Max Working Hours: ";
    for (int i = 0; i < max_indices.size(); i++)
    {
        if (i == max_indices.size() - 1)
        {

            cout << all_days[max_indices[i]] << endl;
            continue;
            ;
        }
        cout << all_days[max_indices[i]] << " ";
    }

    cout << "Day(s) with Min Working Hours: ";
    for (int i = 0; i < min_indices.size(); i++)
    {
        if (i == min_indices.size() - 1)
        {
            cout << all_days[min_indices[i]] << endl;
            continue;
        }
        cout << all_days[min_indices[i]] << " ";
    }
}
void find_max_and_min_float(vector<float> nums, vector<string> all_days)
{
    float max_val = INT_MIN;
    float min_val = INT_MAX;
    vector<int> min_indices;
    vector<int> max_indices;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] > max_val)
        {
            max_val = nums[i];
            max_indices.clear();
            max_indices.push_back(i);
        }
        else if (nums[i] == max_val)
        {

            max_indices.push_back(i);
        }
        if (nums[i] < min_val)
        {
            min_val = nums[i];
            min_indices.clear();
            min_indices.push_back(i);
        }
        else if (nums[i] == min_val)
        {

            min_indices.push_back(i);
        }
    }
    cout << "Period(s) with Max Working Employees: ";
    for (int i = 0; i < max_indices.size(); i++)
    {
        cout << all_days[max_indices[i]] << " ";
    }
    cout << endl;
    cout << "Period(s) with Min Working Employees: ";
    for (int i = 0; i < min_indices.size(); i++)
    {
        cout << all_days[min_indices[i]] << " ";
    }
    cout << endl;
}
int evaluate_string(string str)
{
    int pos = str.find("-");
    int num1 = stoi(str.substr(0, pos));
    int num2 = stoi(str.substr(pos + 1));
    int difference = num2 - num1;
    return num2 - num1;
}
void Employees::function_to_evaluate_sum_employee_hours_between_days(vector<Employees> all_employees, int start_day, int end_day, vector<int> Total_working_hours)
{
    int all_working_hours = 0;
    int new_working_hours = 0;
    vector<int> all_days;
    for (int from = start_day; from <= end_day; from++)
    {
        all_days.push_back(from);
    }
    for (int Days = start_day; Days <= end_day; Days++)
    {
        all_working_hours = 0;
        new_working_hours = 0;
        for (int employee_number = 0; employee_number < all_employees.size(); employee_number++)
        {
            for (int all_work_days = 0; all_work_days < all_employees[employee_number].employee_workdays.size(); all_work_days++)
            {
                if (all_employees[employee_number].employee_workdays[all_work_days][0] == to_string(Days))
                {
                    for (int i = 0; i < all_employees[employee_number].employee_workdays[all_work_days].size(); i++)
                    {
                        new_working_hours = evaluate_string(all_employees[employee_number].employee_workdays[all_work_days][i]);
                        all_working_hours += new_working_hours;
                    }
                }
            }
        }
        Total_working_hours.push_back(all_working_hours);
    }
    int between_days = end_day - start_day;
    for (int Days = start_day; Days <= end_day; Days++)
    {
        cout << "Day #" << Days << ": " << Total_working_hours[between_days - (end_day - Days)] << endl;
    }
    cout << "---" << endl;
    find_max_and_min_int(Total_working_hours, all_days);
}
void show_salary_config(string salary_level, vector<SALARY_CONFIG> all_salaries)
{
    for (int i = 0; i < all_salaries.size(); i++)
    {
        if (all_salaries[i].level == salary_level)
        {
            cout << "Base Salary: " << all_salaries[i].base_salary << endl;
            cout << "Salary Per Hour: " << all_salaries[i].salary_per_hour << endl;
            cout << "Salary Per Extra Hour: " << all_salaries[i].salary_per_extra_hour << endl;
            cout << "Official Working Hours: " << all_salaries[i].official_working_hour << endl;
            cout << "Tax: " << all_salaries[i].tax_persrntage << "%" << endl;
        }
    }
}
void Update_salary_config(vector<Employees> &all_employees, string salary_level, string base_salary, string salary_per_hour, string salary_per_extra_hour, string official_working_hours, string tax_percentage, vector<SALARY_CONFIG> &all_salaries)
{
    Employees employee_to_change;
    for (int i = 0; i < all_salaries.size(); i++)
    {
        if (all_salaries[i].level == salary_level)
        {
            if (base_salary == "-")
                all_salaries[i].base_salary = all_salaries[i].base_salary;
            else
                all_salaries[i].base_salary = stoi(base_salary);
            if (salary_per_hour == "-")
                all_salaries[i].salary_per_hour = all_salaries[i].salary_per_hour;
            else
                all_salaries[i].salary_per_hour = stoi(salary_per_hour);
            if (salary_per_extra_hour == "-")
                all_salaries[i].salary_per_extra_hour = all_salaries[i].salary_per_extra_hour;
            else
                all_salaries[i].salary_per_extra_hour = stoi(salary_per_extra_hour);
            if (official_working_hours == "-")
                all_salaries[i].official_working_hour = all_salaries[i].official_working_hour;
            else
                all_salaries[i].official_working_hour = stoi(official_working_hours);
            if (tax_percentage == "-")
                all_salaries[i].tax_persrntage = all_salaries[i].tax_persrntage;
            else
                all_salaries[i].tax_persrntage = stoi(tax_percentage);
        }
    }
    employee_to_change.Update_employee_salary_struct_after_updating_salaries(all_employees, salary_level, all_salaries);
    cout << "OK" << endl;
}
void Employees::Update_employee_salary_struct_after_updating_salaries(vector<Employees> &all_employees, string salary_level, vector<SALARY_CONFIG> all_salaries)
{
    for (int number_of_salary = 0; number_of_salary < all_salaries.size(); number_of_salary++)
    {
        for (int all_employees_numbers = 0; all_employees_numbers < all_employees.size(); all_employees_numbers++)
        {
            if (all_salaries[number_of_salary].level == all_employees[all_employees_numbers].employee_salary.level)
            {
                all_employees[all_employees_numbers].employee_salary = all_salaries[number_of_salary];
            }
        }
    }
}
void Teams::Update_team_bonus(vector<Teams> &all_teams, string team_number_want_to_find, int new_team_bonus)
{

    for (int number_of_team = 0; number_of_team < all_teams.size(); number_of_team++)
    {
        if (all_teams[number_of_team].team_id == team_number_want_to_find)
        {
            all_teams[number_of_team].team_bonus = new_team_bonus;
        }
    }
    cout << "OK" << endl;
}
vector<vector<string>> delete_specific_row_of_2d_vector(vector<vector<string>> all_workdays, int specific_row)
{
    vector<vector<string>> new_vec;
    for (int i = 0; i < all_workdays.size(); i++)
    {
        if (i == specific_row)
            continue;
        new_vec.push_back(all_workdays[i]);
    }
    if (new_vec.size() != all_workdays.size())
        cout << "OK" << endl;
    return new_vec;
}
void Employees::delete_working_hours(vector<Employees> &all_employees, string employee_id_want_to_find, string day)
{
    for (int number_of_employees = 0; number_of_employees < all_employees.size(); number_of_employees++)
    {
        if (all_employees[number_of_employees].employee_id == employee_id_want_to_find)
        {
            for (int all_work_days = 0; all_work_days < all_employees[number_of_employees].employee_workdays.size(); all_work_days++)
            {
                if (all_employees[number_of_employees].employee_workdays[all_work_days][0] == day)
                {
                    all_employees[number_of_employees].employee_workdays = delete_specific_row_of_2d_vector(all_employees[number_of_employees].employee_workdays, all_work_days);
                }
            }
        }
    }
}
void Employees::add_working_hour_for_employee(vector<Employees> &all_employees, string employee_number_want_to_find, string day, int period_start, int period_end)
{
    for (int number_for_employee = 0; number_for_employee < all_employees.size(); number_for_employee++)
    {
        if (all_employees[number_for_employee].employee_id == employee_number_want_to_find)
        {
            string date_range = to_string(period_start) + "-" + to_string(period_end);
            all_employees[number_for_employee].employee_workdays.push_back({day, date_range});
            mergeRows(all_employees[number_for_employee].employee_workdays);
        }
    }
}
bool Employees::check_for_function_report_employee_salary(vector<Employees> all_employees, string employee_id_want_to_find)
{
    int flag = 0;
    for (int number_of_employee = 0; number_of_employee < all_employees.size(); number_of_employee++)
    {
        if (all_employees[number_of_employee].employee_id == employee_id_want_to_find)
            flag = 1;
    }
    if (flag == 0)
    {
        cout << "EMPLOYEE_NOT_FOUND" << endl;
        return false;
    }
    if (flag == 1)
        return true;
    return true;
}
bool Teams::check_for_function_report_team_salary(vector<Teams> all_teams, string team_id_want_to_find)
{
    int flag = 0;
    for (int number_of_team = 0; number_of_team < all_teams.size(); number_of_team++)
    {
        if (all_teams[number_of_team].team_id == team_id_want_to_find)
            flag = 1;
    }
    if (flag == 0)
    {
        cout << "TEAM_NOT_FOUND" << endl;
        return false;
    }
    if (flag == 1)
    {
        return true;
    }
    return true;
}
bool Employees::check_for_function_report_total_hours_per_day(vector<Employees> all_employees, int start_day, int end_day)
{
    if (start_day > 30 || end_day > 30 || start_day < 1 || end_day < 1 || start_day > end_day)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return false;
    }
    return true;
}
bool check_for_function_show_salary_config(vector<SALARY_CONFIG> all_salaries, string salary_level)
{
    int flag = 0;
    for (int salary_num = 0; salary_num < all_salaries.size(); salary_num++)
    {
        if (all_salaries[salary_num].level == salary_level)
        {
            flag = 1;
        }
    }
    if (flag == 1)
    {
        return true;
    }
    if (flag == 0)
    {
        cout << "INVALID_LEVEL" << endl;
        return false;
    }
    return true;
}
bool check_for_function_update_salary_parameters(vector<SALARY_CONFIG> all_salaries, string salary_level)
{
    int flag = 0;
    for (int salary_num = 0; salary_num < all_salaries.size(); salary_num++)
    {
        if (all_salaries[salary_num].level == salary_level)
        {
            flag = 1;
        }
    }
    if (flag == 1)
    {
        return true;
    }
    if (flag == 0)
    {
        cout << "INVALID_LEVEL" << endl;
        return false;
    }
    return true;
}
bool Employees::check_for_function_deleting_hours(vector<Employees> all_employees, string employee_number_want_to_find, int day)
{
    int flag1 = 0;
    int flag2 = 0;
    for (int size_employee = 0; size_employee < all_employees.size(); size_employee++)
    {
        if (all_employees[size_employee].employee_id == employee_number_want_to_find)
            flag1 = 1;
    }
    if (day > 30 || day < 1)
        flag2 = -1;
    if (flag1 == 1 && flag2 == 0)
        return true;
    if (flag1 == 0)
    {
        cout << "EMPLOYEE_NOT_FOUND" << endl;
        return false;
    }
    if (flag1 == 1 && flag2 == -1)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return false;
    }
    if (flag1 == 0 && flag2 == 0)
    {
        cout << "EMPLOYEE_NOT_FOUND" << endl;
        return false;
    }
    return false;
    /*if (flag1 == 0 && flag2 == -1)
    {
        //// HERE NEED TO BE COMPLETED FIRST ASK THEN DO!!!!!!!!!!!
    }*/
}
bool Teams::check_for_function_update_team_bonus(vector<Teams> all_teams, string team_id_want_to_find, int bonus_percentage)
{
    int flag1 = 0;
    int flag2 = 0;
    for (int size = 0; size < all_teams.size(); size++)
    {
        if (all_teams[size].team_id == team_id_want_to_find)
            flag1 = 1;
    }
    if (bonus_percentage < 0 || bonus_percentage > 100)
        flag2 = -1;
    if (flag1 == 1 && flag2 == 0)
        return true;
    if (flag1 == 0)
    {
        cout << "TEAM_NOT_FOUND" << endl;
        return false;
    }
    if (flag1 == 1 && flag2 == -1)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return false;
    }
    if (flag1 == 0 && flag2 == 0)
    {
        cout << "TEAM_NOT_FOUND" << endl;
        return false;
    }
    return false;
    /*if (flag1 == 0 && flag2 == -1)
    {
        //// HERE NEED TO BE COMPLETED FIRST ASK THEN DO!!!!!!!!!!!
    }*/
}
bool Employees::check_for_function_add_working_hours(vector<Employees> all_employees, string employee_id_want_to_find, string day, string time_interval)
{
    int flag = 0;
    vector<vector<string>> employee_workdays_to_check;
    for (int all_employee_number = 0; all_employee_number < all_employees.size(); all_employee_number++)
    {
        if (all_employees[all_employee_number].employee_id == employee_id_want_to_find)
        {
            flag = 1;
            employee_workdays_to_check = all_employees[all_employee_number].employee_workdays;
        }
    }
    if (flag == 0)
    {
        cout << "EMPLOYEE_NOT_FOUND" << endl;
        return false;
    }
    int dayInt = stoi(day);
    if (dayInt < 1 || dayInt > 30)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return false;
    }
    stringstream ss(time_interval);
    string token;
    getline(ss, token, '-');
    int start_time = stoi(token);
    getline(ss, token, '-');
    int end_time = stoi(token);
    if (start_time < 0 || start_time > 24 || end_time < 0 || end_time > 24 || end_time <= start_time)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return false;
    }
    bool day_available;
    for (vector<string> schedule : employee_workdays_to_check)
    {
        if (schedule[0] == day)
        {
            for (int i = 1; i < schedule.size(); i++)
            {
                stringstream ss2(schedule[1]);
                string token2;
                getline(ss2, token2, '-');
                int start_schedule = stoi(token2);
                getline(ss2, token2, '-');
                int end_schedule = stoi(token2);
                if ((start_time >= start_schedule && start_time < end_schedule) || (end_time > start_schedule && end_time <= end_schedule))
                {
                    cout << "INVALID_INTERVAL" << endl;
                    return false;
                }
            }
            day_available = false;
            break;
        }
    }

    cout << "OK" << endl;
    return true;
}
bool check_for_function_report_employee_per_hour(int hour1, int hour2)
{
    if (hour1 > 24 || hour1 < 0 || hour2 > 24 || hour2 < 0 || hour2 <= hour1)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return false;
    }
    return true;
}
vector<string> parse_time_intervals_for_one_hour(string time_interval)
{
    vector<string> result;
    istringstream iss(time_interval);
    int start, end;
    char dash;
    iss >> start >> dash >> end;
    for (int i = start; i < +end; i++)
    {
        result.push_back(to_string(i) + "-" + to_string(i + 1));
    }
    return result;
}
float count_time_intervals(string interval, vector<vector<string>> intervals)
{
    float count = 0;
    for (vector<string> row : intervals)
    {
        string time_interval = row[1];
        int start_time = stoi(time_interval.substr(0, time_interval.find("-")));
        int end_time = stoi(time_interval.substr(time_interval.find("-") + 1));
        if (start_time <= stoi(interval.substr(0, interval.find("-"))) &&
            end_time >= stoi(interval.substr(interval.find("-") + 1)))
        {
            count++;
        }
    }
    return count;
}
vector<float> round_up_floats(vector<float> numbers)
{
    vector<float> rounded_numbers;
    {
        for (float num : numbers)
        {
            float rounded_num = roundf(num * 10) / 10;
            rounded_numbers.push_back(rounded_num);
        }
    }
    return rounded_numbers;
}
void Employees::function_for_report_employee_per_hour(vector<Employees> all_employees, int start_hour, int end_hour)
{
    vector<float> all_averages;
    vector<string> splited_times = parse_time_intervals_for_one_hour(to_string(start_hour) + "-" + to_string(end_hour));
    for (int number_of_splited_time = 0; number_of_splited_time < splited_times.size(); number_of_splited_time++)
    {
        float average_working_hour = 0;
        for (int number_of_employee = 0; number_of_employee < all_employees.size(); number_of_employee++)
        {
            average_working_hour = average_working_hour + count_time_intervals(splited_times[number_of_splited_time], all_employees[number_of_employee].employee_workdays);
        }

        all_averages.push_back(average_working_hour / 30);

        cout << splited_times[number_of_splited_time] << ": " << round_up_floats_3(average_working_hour) << endl;
    }
    cout << "---" << endl;
    all_averages = round_up_floats(all_averages);
    find_max_and_min_float(all_averages, splited_times);
}
int Employees::get_whole_team_work(vector<string> all_ids, vector<Employees> all_employees)
{
    int all_working_hours = 0;
    for (int i = 0; i < all_ids.size(); i++)
    {

        for (int j = 0; j < all_employees.size(); j++)
        {
            if (all_ids[i] == all_employees[j].employee_id)
                all_working_hours = all_working_hours + all_employees[j].total_working_hour();
        }
    }
    return all_working_hours;
}
double Employees::want_to_find_average_square(vector<Employees> all_employees, vector<string> team_members, string team_id, int team_size)
{
    Employees new_employee;
    float average;
    average = solve(((double)new_employee.evaluate_all_team_memebers_working_hours(all_employees, team_members) / (double)team_size), 1);
    float variance = 0;
    for (int i = 0; i < all_employees.size(); i++)
    {
        for (int j = 0; j < team_members.size(); j++)
        {
            if (all_employees[i].employee_id == team_members[j])
            {
                variance = variance + ((average - all_employees[i].total_working_hour()) * (average - all_employees[i].total_working_hour()));
            }
        }
    }
    variance = variance / team_size;
    return variance;
}
bool compare(pair<int, string> a, pair<int, string> b)
{
    int num1 = stoi(a.second);
    int num2 = stoi(b.second);
    if (a.first != b.first)
    {
        return a.first > b.first;
    }
    else
    {
        return num1 < num2;
    }
}
void Teams::find_team_for_bonus(vector<Employees> all_employess, vector<Teams> all_teams)
{
    vector<pair<int, string>> Possilbles;
    pair<int, string> new_pair;
    vector<string> all_ids;
    int all_working_hours;
    Employees employee_to_test;
    for (int i = 0; i < all_teams.size(); i++)
    {
        all_ids = all_teams[i].team_members_id;
        all_working_hours = employee_to_test.get_whole_team_work(all_ids, all_employess);
        if ((all_working_hours > stoi(all_teams[i].bonus_min_working_hours)) && (employee_to_test.want_to_find_average_square(all_employess, all_teams[i].team_members_id, all_teams[i].team_id, all_teams[i].team_members_id.size()) < stoi(all_teams[i].bonus_working_hours_max_variance)))
        {
            new_pair.first = all_working_hours;
            new_pair.second = all_teams[i].team_id;
            Possilbles.push_back(new_pair);
        }
    }
    if (Possilbles.size() == 0)
    {
        cout << "NO_BONUS_TEAMS" << endl;
        return;
    }
    sort(Possilbles.begin(), Possilbles.end(), compare);
    for (int i = 0; i < Possilbles.size(); i++)
    {
        cout << Possilbles[i].second << endl;
    }
}
void get_command_from_user(vector<Employees> &all_employees, vector<Teams> &all_teams, vector<SALARY_CONFIG> &all_salaries)
{
    string command;
    Employees employee_to_test;
    Teams team_to_test;
    while (cin >> command)
    {

        if (command == "report_salaries")
        {
            employee_to_test.function_for_report_salaries(all_employees, all_teams);
        }
        else if (command == "report_employee_salary")
        {
            int employee_want_to_find;
            cin >> employee_want_to_find;
            if (employee_to_test.check_for_function_report_employee_salary(all_employees, to_string(employee_want_to_find)))
                employee_to_test.function_for_report_employee_salary(employee_want_to_find, all_employees, all_teams);
        }
        else if (command == "report_team_salary")
        {
            int team_want_to_find;
            cin >> team_want_to_find;
            if (team_to_test.check_for_function_report_team_salary(all_teams, to_string(team_want_to_find)))
                team_to_test.function_to_report_team_salary(all_teams, all_employees, to_string(team_want_to_find));
        }
        else if (command == "report_total_hours_per_day")
        {
            int day1, day2;
            vector<int> All_hours;
            cin >> day1 >> day2;
            if (employee_to_test.check_for_function_report_total_hours_per_day(all_employees, day1, day2))
                employee_to_test.function_to_evaluate_sum_employee_hours_between_days(all_employees, day1, day2, All_hours);
        }
        else if (command == "report_employee_per_hour")
        {
            int hour1, hour2;
            cin >> hour1 >> hour2;
            if (check_for_function_report_employee_per_hour(hour1, hour2))
                employee_to_test.function_for_report_employee_per_hour(all_employees, hour1, hour2);
        }
        else if (command == "show_salary_config")
        {
            string salary_level;
            cin >> salary_level;
            if (check_for_function_show_salary_config(all_salaries, salary_level))
                show_salary_config(salary_level, all_salaries);
        }
        else if (command == "update_salary_config")
        {
            string salary_level;
            string base_salary, salary_per_hour, salary_per_extra_hour, official_working_hours, tax_percentage;
            cin >> salary_level >> base_salary >> salary_per_hour >> salary_per_extra_hour >> official_working_hours >> tax_percentage;
            if (check_for_function_update_salary_parameters(all_salaries, salary_level))
                Update_salary_config(all_employees, salary_level, (base_salary), (salary_per_hour), (salary_per_extra_hour), (official_working_hours), (tax_percentage), all_salaries);
        }
        else if (command == "add_working_hours")
        {
            string employee_if_want_to_find, day, period_start, period_end;
            cin >> employee_if_want_to_find >> day >> period_start >> period_end;
            if (employee_to_test.check_for_function_add_working_hours(all_employees, employee_if_want_to_find, day, (period_start + "-" + period_end)))
                employee_to_test.add_working_hour_for_employee(all_employees, employee_if_want_to_find, day, stoi(period_start), stoi(period_end));
        }
        else if (command == "delete_working_hours")
        {
            int employee_id_want_to_find, day;
            cin >> employee_id_want_to_find >> day;
            if (employee_to_test.check_for_function_deleting_hours(all_employees, to_string(employee_id_want_to_find), day))
                employee_to_test.delete_working_hours(all_employees, to_string(employee_id_want_to_find), to_string(day));
        }
        else if (command == "update_team_bonus")
        {
            int team_id_want_to_find, bonus_percentage;
            cin >> team_id_want_to_find >> bonus_percentage;
            if (team_to_test.check_for_function_update_team_bonus(all_teams, to_string(team_id_want_to_find), bonus_percentage))
                team_to_test.Update_team_bonus(all_teams, to_string(team_id_want_to_find), bonus_percentage);
        }
        else if (command == "find_teams_for_bonus")
        {
            team_to_test.find_team_for_bonus(all_employees, all_teams);
        }
        else
        {
            fflush(stdin);
            cout << "PLEASE ENTER A VALID COMMAND" << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    string folder = string(argv[1]);
    vector<Employees> all_employee;
    vector<string> all_files = {"/employees.csv", "/teams.csv", "/salary_configs.csv"};
    all_employee = read_from_employees_file(argv[1] + all_files[0]);
    Employees new_employee = all_employee[0];
    read_from_working_hours_file(all_employee, argv[1]);
    vector<Teams> all_teams;
    all_teams = read_from_Teams_file(argv[1] + all_files[1]);
    Teams new_team = all_teams[0];
    string command;
    vector<SALARY_CONFIG> Salary_config;
    read_from_salary_configs_file(Salary_config, argv[1] + all_files[2], all_employee);
    vector<int> all_hours;
    get_command_from_user(all_employee, all_teams, Salary_config);
}
