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

class Sol {
public:
    double numItem = {0};
    double numSearch = {0};
    double ampI = {0};
    double ampO = {0};
    double probI = {0};
    double probO = {0};

    Sol &operator=(const Sol &t) = default;

    bool operator!=(const Sol &t) const {
        return this->ampI != t.ampI || this->ampO != t.ampO
               || this->probO != t.probO || this->probI != t.probI
               || this->numItem != t.numItem || this->numSearch != t.numSearch;
    }
};


Sol best;

void run() {
    for (int i = 0; i < numSearch; i++) {
        ampI = -ampI; // selective inversion

        // inversion about average
        double avg = (ampI * numSelectedItem + ampO * (numItem - numSelectedItem)) / numItem;
        ampI = 2.0 * avg - ampI;
        ampO = 2.0 * avg - ampO;

        // update best
        if (abs(1 - best.ampI) > abs(1 - ampI) && numItem != 4) {
            best.ampI = ampI;
            best.ampO = ampO;
            best.numSearch = numSearch;
            best.numItem = numItem;
            best.probI = ampI * ampI;
            best.probO = ampO * ampO;
        }

        // output
        if (i >= numSearch - 2) {
            Logger logger("../result" + to_string(int(numItem / 100000)) + ".csv");
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
}

int main() {
    long long max = pow(2, 31);
    Sol tmp;
    while (numItem < max) {
        ampI = 1.0 / sqrt(numItem);
        ampO = 1.0 / sqrt(numItem);
        double deg = asin(1.0 / sqrt(numItem)) * 180.0 / PI;
        numSearch = ceil((90.0 - deg) / (2.0 * deg));
        if (numItem % 100000 == 0)
            cout << "N = " << numItem << endl;
        run();
        numItem++;

        // if best has changed, print best
        if (best != tmp) {
            Logger logger("../best.csv");
            logger.writeComma(best.numItem);
            logger.writeComma(best.ampI);
            logger.writeComma(best.ampO);
            logger.writeComma(best.probI);
            logger.writeComma(best.probO);
            logger.writeLine(best.numSearch + 1);
            tmp = best;
        }
    }
    return 0;
}
