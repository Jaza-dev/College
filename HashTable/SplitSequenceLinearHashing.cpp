#include "SplitSequenceLinearHashing.h"

int SplitSequenceLinearHashing::getAddress(string& key, int mAddress, int attemptCount, int tableCap, int compareValue) { 
    //neophnodno je bilo proslediti ili celu tablu ili samo vrednost koju koristim za porednjenje kako bij odredio gde idem dalje
    int s1 = 41, s2 = 167;
    int keyInt = atoi(&key[0]);
    if (keyInt > compareValue) {
        return mAddress + s1*attemptCount;
    }
    else {
        return mAddress + s2 * attemptCount;
    }
}
