#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

struct Candle {
    double timestamp;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

int main() {
    // === ПАРАМЕТР: размер новой свечи в секундах ===
    // 60 * 5 = 5 минут, 60 * 60 * 2 = 2 часа
    const int newCandleSize = 60 * 5;

    string inputFile = "btcusd_1-min_data.csv";
    string outputFile = "bitusd_" + to_string(newCandleSize / 60) + "-min_data.csv";

    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть входной файл!" << endl;
        return 1;
    }

    vector<Candle> candles;
    string line;
    getline(fin, line);

    while (getline(fin, line)) {
        stringstream ss(line);
        Candle c;
        char comma;
        ss >> c.timestamp >> comma >> c.open >> comma >> c.high >> comma >> c.low >> comma >> c.close >> comma >> c.volume;
        candles.push_back(c);
    }
    fin.close();

    if (candles.empty()) {
        cerr << "Файл пуст или неверный формат." << endl;
        return 1;
    }

    ofstream fout(outputFile);
    fout << "Timestamp,Open,High,Low,Close,Volume\n";
    fout << fixed << setprecision(2);

    double startTime = candles.front().timestamp;
    double currentWindowStart = startTime;
    double currentWindowEnd = currentWindowStart + newCandleSize;

    Candle agg{};
    bool firstInWindow = true;

    for (const auto& c : candles) {
        if (c.timestamp >= currentWindowEnd) {

            fout << agg.timestamp << "," << agg.open << "," << agg.high << ","
                 << agg.low << "," << agg.close << "," << agg.volume << "\n";

            currentWindowStart = currentWindowEnd;
            currentWindowEnd += newCandleSize;

            agg = {}; 
            firstInWindow = true;
        }

        if (firstInWindow) {
            agg.timestamp = currentWindowStart;
            agg.open = c.open;
            agg.high = c.high;
            agg.low = c.low;
            agg.close = c.close;
            agg.volume = c.volume;
            firstInWindow = false;
        } else {
            agg.high = max(agg.high, c.high);
            agg.low = min(agg.low, c.low);
            agg.close = c.close;
            agg.volume += c.volume;
        }
    }

    if (!firstInWindow) {
        fout << agg.timestamp << "," << agg.open << "," << agg.high << ","
             << agg.low << "," << agg.close << "," << agg.volume << "\n";
    }

    fout.close();
    cout << "Готово! Файл сохранен как " << outputFile << endl;
    return 0;
}
