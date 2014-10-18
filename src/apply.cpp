#include <iostream>
#include "rubiks.h"
#include "rubiks-getopt.h"
using namespace std;

int main(int argc, char *argv[]) {
    rubiks::Getopt getopt;
    getopt.parse(argc, argv);

    if (getopt.get_errors() > 0) {
        cerr << "Try -h for help" << endl;
        exit(getopt.get_errors());
    } else if (getopt.has_io_option(rubiks::IO_PRINT_HELP)) {
        cerr << "Usage:" << endl;
        cerr << "  " << getopt.get_program_name() << " < INPUT_CUBE + INPUT_MOVE > OUTPUT_MOVE" << endl;
        cerr << "  " << getopt.get_program_name() << " -I < INPUT_MOVE > OUTPUT_MOVE" << endl;
        cerr << "  " << getopt.get_program_name() << " -h" << endl;
        exit(-1);
    }

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
