#include <iostream>
#include "rubiks.h"
#include "rubiks-getopt.h"
using namespace std;

int main(int argc, char *argv[]) {
    rubiks::Getopt getopt;
    getopt.parse(argc, argv);

    if (getopt.has_io_option(rubiks::IO_PRINT_HELP)) {
        cerr << "Usage:" << endl;
        cerr << "  " << getopt.get_program_name() << " < INPUT_MOVE > OUTPUT_MOVE" << endl;
        cerr << "  " << getopt.get_program_name() << " -h" << endl;
        exit(-1);
    }

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
