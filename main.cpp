#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include "Logger.h"

#define PI 3.1415926535897932384626433832795

using namespace std;

int nWire = 1;
int inverseBit = 1;
int nRuns = 1;

bool isMatch(vector<double> &amp) {
    for (int i = amp.size() - 1; i >= nWire - inverseBit; i--) {
//        if (abs(amp[i]) > 0)
        if (abs(amp[i]) > 0.0000000000000001)
            return false;
    }
    return true;
}

void prtSum(vector<double> &amp) {
    double sum = 0.0;
    for (int i = 0; i < inverseBit; i++) {
        sum += amp[i] * amp[i];
    }
    cout << sum * 100.0 << endl;
}

void run(vector<double> &amp, int count) {
    if (count == nRuns)
        return;
    else {
        // selective inversion
        for (int i = 0; i < inverseBit; i++)
            amp[i] = -amp[i];

        // inversion about average
        double avg = 0.0;
        for (auto it:amp)
            avg += it;
        avg /= nWire;
        for (auto &it :amp)
            it = 2.0 * avg - it;
        if (isMatch(amp)) {
            Logger logger("../match.csv");
            logger.writeComma(nWire);
            logger.writeLine(count + 1);
            cout << nWire << "," << count + 1 << endl;
        }
        run(amp, count + 1);
    }
}

int main() {
    cout << fixed << setprecision(10);
    cout << "input nWire and maxWire" << endl;
    int maxWire;
    cin >> nWire >> maxWire;
    if (nWire < inverseBit)
        return -9999;
    while (nWire <= maxWire) {
        vector<double> amp(nWire, 1.0 / sqrt(nWire));
//        cout << nWire << ',';
        nRuns = ceil((PI / 2.0 - 1.0 / sqrt(nWire)) / (2.0 / sqrt(nWire)));
        run(amp, 0);
        nWire++;
    }
    return 0;
}
