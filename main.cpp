#include <cmath>
#include <string>
#include "Logger.h"

#define PI 3.1415926535897932384626433832795

using namespace std;

long long numItem = 2; // the number of total items.
int numSelectedItem = 1; // the number of selected items.
int numSearch = 1; // the number of search, i.e., iteration count.
double ampI; // the amplitude of selected items.
double ampO; // the amplitude of unselected items.

void run() {
    for (int i = 0; i < numSearch; i++) {
        ampI = -ampI; // selective inversion

        // inversion about average
        double avg = (ampI * numSelectedItem + ampO * (numItem - numSelectedItem)) / numItem;
        ampI = 2.0 * avg - ampI;
        ampO = 2.0 * avg - ampO;

        Logger logger("../result" + to_string(int(numItem / 10000000)) + ".csv");
        logger.writeComma(numItem);
        logger.writeComma(ampI);
        logger.writeComma(ampO);
        logger.writeComma(i + 1);
        if (abs(ampO * (numItem - numSelectedItem)) <= 0.0000000000000001)
            logger.writeLine(1); // found
        else
            logger.writeLine(0); // not found
    }
}

int main() {
    long long max = pow(2, 31);

    while (numItem < max) {
        ampI = 1.0 / sqrt(numItem);
        ampO = 1.0 / sqrt(numItem);
        double deg = asin(1.0 / sqrt(numItem)) * 180.0 / PI;
        numSearch = ceil((90.0 - deg) / (2.0 * deg));
        if (numItem % 100000 == 0)
            cout << "N = " << numItem << endl;
        run();
        numItem++;
    }
    return 0;
}
