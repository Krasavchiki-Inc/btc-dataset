#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<sstream>
#include<iomanip>

using namespace std;

string convertDate(string line){
    int k = 0;
    int date_unix = 0;
    while (line[k] != '.'){
        date_unix = date_unix * 10 + (line[k] - '0');
        ++k;
    }
    time_t unix_time = date_unix;
    tm* time_info = localtime(&unix_time);

    ostringstream oss;
    oss << (time_info->tm_year + 1900) << "-"
        << setw(2) << setfill('0') << (time_info->tm_mon + 1) << "-"
        << setw(2) << setfill('0') << time_info->tm_mday << " "
        << setw(2) << setfill('0') << time_info->tm_hour << ":"
        << setw(2) << setfill('0') << time_info->tm_min << ":"
        << setw(2) << setfill('0') << time_info->tm_sec;
    
    string formatted_time = oss.str();

    return formatted_time;
}

int main(){
    string path = "btcusd_1-min_data.csv";
    ifstream input(path);
    ofstream output("bts-usdt_1min_dataConv.csv");

    if (!input.is_open()) {
        cerr << "Не удалось открыть файл: " << path << endl;
        return 1; 
    }

    string line;
    getline(input, line);
    string header = line;
    output << header << endl;

    string normalDate;
    string otherPart;
    string new_line;
    int i = 0;
    while (getline(input, line)) {
        normalDate = convertDate(line);
        //cout << normalDate << endl;
        otherPart = line.substr(12);
        new_line = normalDate + otherPart;
        output << new_line <<endl;
        //printf("%d\n", i );
        ++i;
    }
    
    cout << "complete";
    return 0;
}