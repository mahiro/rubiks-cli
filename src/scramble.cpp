#include <iostream>
#include "rubiks.h"
#include "rubiks-getopt.h"

using namespace std;

int main(int argc, char *argv[]) {
    rubiks::Getopt getopt;
    getopt.set_default_min_depth(20);
    getopt.set_default_max_depth(20);
    getopt.parse(argc, argv);

    if (getopt.get_errors() > 0) {
        cerr << "Try -h for help" << endl;
        exit(getopt.get_errors());
    } else if (getopt.has_io_option(rubiks::IO_PRINT_HELP)) {
        cerr << "Usage:" << endl;
        cerr << "  " << getopt.get_program_name() << " [-n|-N NUM] [-prlsmdt] < INPUT_CUBE > OUTPUT_MOVE" << endl;
        cerr << "  " << getopt.get_program_name() << " [-n|-N NUM] [-prlsmdt] -I > OUTPUT_MOVE" << endl;
        cerr << "  " << getopt.get_program_name() << " -h" << endl;
        exit(-1);
    }

    bool read_cube = getopt.has_io_option(rubiks::IO_READ_INITIAL_CUBE);
    size_t depth = getopt.get_min_depth();

    bool show_cube = getopt.has_io_option(rubiks::IO_PRINT_CUBE);
    bool show_procedure = getopt.has_io_option(rubiks::IO_PRINT_PROCEDURE);
    bool show_solution = getopt.has_io_option(rubiks::IO_PRINT_REVERSE_PROCEDURE);

    rubiks::Cube cube;

    if (read_cube) {
        cin >> cube;
    }

    rubiks::Scramble scramble(cube);
    scramble.set_turn_option(getopt.get_turn_option());
    scramble.set_slice_option(getopt.get_slice_option());
    scramble.scramble(depth);

    if (show_cube) {
        cout << cube;
    }

    if (show_procedure) {
        cout << scramble.get_procedure();
    }

    if (show_solution) {
        rubiks::Procedure solution;
        rubiks::reverse(scramble.get_procedure(), solution);
        cout << solution;
    }

    return 0;
}
