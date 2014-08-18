#include <iostream>
#include "rubiks.h"
using namespace std;

int main(int argc, char *argv[]) {
    while (true) {
        rubiks::Procedure input;
        cin >> input;

        if (!cin) {
            break;
        }

        rubiks::Procedure output;
        rubiks::reverse(input, output);

        cout << output;
    }

    return 0;
}
