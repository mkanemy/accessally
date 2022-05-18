#include <iostream>
using namespace std;

/**
 * Distribute as much blood as possible from available[j] to patients[i]
 * 
 * @param patients Array of patients needing blood
 * @param i Index of patient we will supply blood to
 * @param available Array of available blood
 * @param j Index of type of blood we will distribute from
 * @return Number of patients that received blood
 */
int distribute_blood(int patients[8], int i, int available[8], int j) {
    int received;

    if (patients[i] <= available[j]) {
        available[j] -= patients[i];
        received = patients[i];
        patients[i] = 0;
    } else {
        patients[i] -= available[j];
        received = available[j];
        available[j] = 0;
    }

    return received;
}

int main() {
    // read the input and store into available and patients arrays
    int oneg, opos, aneg, apos, bneg, bpos, abneg, abpos;
    cin >> oneg >> opos >> aneg >> apos >> bneg >> bpos >> abneg >> abpos;
    int available[8] = { oneg, opos, aneg, apos, bneg, bpos, abneg, abpos };
    cin >> oneg >> opos >> aneg >> apos >> bneg >> bpos >> abneg >> abpos;
    int patients[8] = { oneg, opos, aneg, apos, bneg, bpos, abneg, abpos };

    int received = 0;
    int j;

    for (int i = 0; i < 8; i++) {
        // firstly take as many as possible from same blood and Rh type
        if (available[i] != 0 && patients[i] != 0) {
            received += distribute_blood(patients, i, available, i);
        }

        // skip rest if no patients of this type need blood anymore
        if (patients[i] == 0) {
            continue;
        }

        // negative blood types
        if (i % 2 == 0) {
            // go back and check all higher negative types 
            j = i;
            while (j >= 2) {
                j -= 2;
                // check to ensure not giving A type to B type
                if (j == 2 && i == 4) {
                    continue;
                }
                received += distribute_blood(patients, i, available, j);
            } 

        // positive blood types
        } else {
            // go back and check all higher positive types first (so we do not take from negative types when not needed)
            j = i;
            while (j >= 1) {
                j -= 2;
                // check to ensure not giving A type to B type
                if (j == 3 && i == 5) {
                    continue;
                }
                received += distribute_blood(patients, i, available, j);
            } 
            // if still patients that need blood, now we can take from negative types
            if (patients[i] != 0) {
                j = i + 1;
                while (j >= 2) {
                    j -= 2;
                    // check to ensure not giving A type to B type
                    if (j == 2 && i == 5) {
                        continue;
                    }
                    received += distribute_blood(patients, i, available, j);
                } 
            }
        }
        
    }

    cout << received << endl;
}