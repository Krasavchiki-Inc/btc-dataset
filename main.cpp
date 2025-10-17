#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

struct candle
{
    double open;
    double high;
    double low;
    double close;
    double volume;
};

int convertToInt(string line)
{
    int k = 0;
    int date_unix = 0;
    while (line[k] != '.')
    {
        date_unix = date_unix * 10 + (line[k] - '0');
        ++k;
    }
    return date_unix;
}

void parsString(string line, candle *cur_cand)
{
    string date_s, open_s, high_s, low_s, close_s, volume_s;
    string *fields[] = {&date_s, &open_s, &high_s, &low_s, &close_s, &volume_s};
    int fields_index = 0;
    for (char ch : line)
    {
        if (ch == ',')
        {
            fields_index++;
            if (fields_index >= 6)
                break;
        }
        else
        {
            *fields[fields_index] += ch;
        }
    }

    try
    {
        cur_cand->open = stod(open_s);
        cur_cand->high = stod(high_s);
        cur_cand->low = stod(low_s);
        cur_cand->close = stod(close_s);
        cur_cand->volume = stod(volume_s);
    }
    catch (const std::exception &e)
    {
        cerr << "Ошибка при парсинге строки: " << e.what() << "\n";
        cerr << "Исходная строка:  " << line << endl;
        cur_cand->open = cur_cand->high = cur_cand->low = cur_cand->close = cur_cand->volume = 0;
    }
}

int main()
{
    string path = "bts-usdt_1min_dataConv.csv";
    ifstream BTCdata(path);

    if (!BTCdata.is_open())
    {
<<<<<<< HEAD
        cerr << "Не удалось открыть файл: " << path << endl;
=======
        cerr << "Не удалось  открыть файл: " << path << endl;
>>>>>>> 984838a9b6cb7ddaf058d9b08449289fb0f53f11
        return 1;
    }

    string line;
    getline(BTCdata, line);
    string header = line;

    vector<candle> all_data;
    candle cur_cand;
    int startDate = 1596722040;
    while (getline(BTCdata, line))
    {
        if (convertToInt(line) > startDate)
        {
            parsString(line, &cur_cand);
            all_data.push_back(cur_cand);
        }
    }

    for (int i = 0; i + 200 <= all_data.size(); i += 200)
    {
        vector<candle> segment = vector<candle>(
            all_data.begin() + i,
            all_data.begin() + min(i + 200, (int)all_data.size()));
        // тут в перспективе дописать функции анализ и создавать массив со свечами и аналитическими данными
    }
    return 0;
}