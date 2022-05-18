#include <iostream>
#include <math.h>
using namespace std;

/**
 * Count the number of arithmetic sequences from 12:00 to 12:00 plus [duration] minutes
 * 
 * @param duration Number of minutes past 12:00 to count sequences for
 * @return number of arithmetic sequences in the time
 */
int count_sequences(int duration) {
    int clock[4] = { 1, 2, 0, 0 };
    int difference;
    int sequences = 0;

    for (int i = 0; i <= duration; i++) {
        // increment sequences if clock is a sequence
        if (clock[0] == 0) {
            difference = clock[2] - clock[1];
            if (clock[3] - clock[2] == difference) {
                sequences++;
            }
        } else {
            difference = clock[1] - clock[0];
            if (clock[2] - clock[1] == difference && clock[3] - clock[2] == difference) {
                sequences++;
            }
        }

        // increment the clock
        if (clock[3] != 9) {
            clock[3]++;
        } else if (clock[2] != 5) {
            clock[3] = 0;
            clock[2]++;
        } else if (clock[1] != 9) {
            clock[2] = 0;
            clock[3] = 0;
            if (clock[0] == 1 && clock[1] == 2) {
                clock[0] = 0;
                clock[1] = 1;
            } else {
                clock[1]++;
            }
        } else {
            clock[0] = 1;
            clock[1] = 0;
            clock[2] = 0;
            clock[3] = 0;
        }
    }

    return sequences;
}

int main() {
    int sequences = 0;
    int duration;
    cin >> duration;
    // 1440 minutes in a day
    const int minutes_in_half_day = 720;

    // if duration longer than 12 hours, only need to calculate 12 hours to find all the days
    if (duration >= minutes_in_half_day) {
        // could be set as constant value if desired
        int seq_in_half_day = count_sequences(minutes_in_half_day);
        int half_days = floor(duration / minutes_in_half_day);
        sequences += seq_in_half_day * half_days;
        duration -= minutes_in_half_day * half_days;
    }

    sequences += count_sequences(duration);

    cout << sequences << endl;
}