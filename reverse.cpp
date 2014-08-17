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

        for (rubiks::Procedure::reverse_iterator it = input.rbegin();
                it != input.rend(); ++it) {
            output.push_back(it->reverse());
        }

        cout << output;
    }

    return 0;
}
