#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

int nWire = 16;
int inverseBit = 5;
int nRuns = 3;

void prt(vector<double> &amp) {
//    cout << "Amp:\t";
//    for (auto it:amp) {
//        cout << it << '\t';
//    }
//    cout << endl;
    cout << "Prob:\t";
    for (auto it:amp) {
        cout << it * it << '\t';
    }
    cout << endl;
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
            it = avg - (it - avg);
        run(amp, count + 1);
    }
}

int main() {
    cout << fixed << setprecision(10);

    while (nWire < 17) {
        vector<double> amp(nWire, 1.0 / sqrt(nWire));
        cout << nWire << ',';
        run(amp, 0);
        prtSum(amp);
        nWire++;
    }

    return 0;
}
