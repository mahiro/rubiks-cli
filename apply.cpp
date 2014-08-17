#include <iostream>
#include "rubiks.h"
using namespace std;

int main(int argc, char *argv[]) {
    rubiks::Cube cube;
    cin >> cube;

    while (true) {
        rubiks::Procedure input;
        cin >> input;

        if (!cin) {
            break;
        }

        if (input.size() > 0) {
            for (rubiks::Procedure::iterator it = input.begin();
                    it != input.end(); ++it) {
                cube.rotate(*it);
            }

            cout << cube;
        }
    }

    return 0;
}
