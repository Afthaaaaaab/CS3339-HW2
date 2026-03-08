#include <iostream>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

// Convert float to bitset
bitset<32> floatToBits(float value)
{
    uint32_t temp;
    memcpy(&temp, &value, sizeof(value));
    return bitset<32>(temp);
}

// Print IEEE format: sign exponent fraction
void printIEEE(bitset<32> bits)
{
    cout << bits[31] << " ";

    for (int i = 30; i >= 23; i--)
        cout << bits[i];

    cout << " ";

    for (int i = 22; i >= 0; i--)
        cout << bits[i];
}

// Extract exponent (remove bias)
int getExponent(bitset<32> bits)
{
    bitset<8> exponent;

    for (int i = 0; i < 8; i++)
        exponent[7 - i] = bits[30 - i];

    return (int)exponent.to_ulong() - 127;
}

int main(int argc, char* argv[])
{
    // Check argument count
    if (argc != 3)
    {
        cout << "usage: ./fp_overflow_checker loop_bound loop_counter\n\n";
        cout << "loop_bound is a positive floating-point value\n";
        cout << "loop_counter is a positive floating-point value\n";
        return 0;
    }

    float loop_bound = stof(argv[1]);
    float loop_counter = stof(argv[2]);

    bitset<32> boundBits = floatToBits(loop_bound);
    bitset<32> counterBits = floatToBits(loop_counter);

    cout << "Loop bound:   ";
    printIEEE(boundBits);
    cout << endl;

    cout << "Loop counter: ";
    printIEEE(counterBits);
    cout << endl;

    int expBound = getExponent(boundBits);
    int expCounter = getExponent(counterBits);

    int exponentDifference = expBound - expCounter;

    if (exponentDifference > 23)
    {
        cout << endl;
        cout << "Warning: Possible overflow!" << endl;
        cout << "Overflow threshold:" << endl;

        float threshold = pow(2, exponentDifference);

        cout << threshold << endl;

        bitset<32> thresholdBits = floatToBits(threshold);
        printIEEE(thresholdBits);
        cout << endl;
    }
    else
    {
        cout << endl;
        cout << "There is no overflow!" << endl;
    }

    return 0;
}
