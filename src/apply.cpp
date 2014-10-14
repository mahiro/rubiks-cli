#include <iostream>
#include "rubiks.h"
#include "rubiks-getopt.h"
using namespace std;

int main(int argc, char *argv[]) {
    rubiks::Getopt getopt;
    getopt.parse(argc, argv);

    bool read_cube = getopt.has_io_option(rubiks::IO_READ_INITIAL_CUBE);

    rubiks::Cube cube;

    if (read_cube) {
        cin >> cube;
    }

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
