#include <iostream>
#include "rubiks.h"
#include "rubiks-getopt.h"
using namespace std;

int main(int argc, char *argv[]) {
    rubiks::Getopt getopt;
    getopt.parse(argc, argv);

    while (true) {
        rubiks::Procedure input;
        cin >> input;

        if (!cin) {
            break;
        }

        rubiks::Procedure output;
        rubiks::mirror(input, output);

        cout << output;
    }

    return 0;
}
