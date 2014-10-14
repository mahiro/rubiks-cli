#include <iostream>
#include <stddef.h>
#include "rubiks.h"
#include "rubiks-getopt.h"
using namespace std;

int main(int argc, char *argv[]) {
    rubiks::Getopt getopt;
    getopt.set_default_min_depth(1);
    getopt.set_default_max_depth(8);
    getopt.parse(argc, argv);

    if (getopt.has_io_option(rubiks::IO_PRINT_HELP)) {
        cerr << "Usage:" << endl;
        cerr << "  " << getopt.get_program_name() << " [-n|-N NUM] [-prlsmdt] < INITIAL_CUBE + TARGET_CUBE > OUTPUT_MOVE" << endl;
        cerr << "  " << getopt.get_program_name() << " -h" << endl;
        exit(-1);
    }

    bool read_initial_cube = getopt.has_io_option(rubiks::IO_READ_INITIAL_CUBE);
    bool read_target_cube = getopt.has_io_option(rubiks::IO_READ_TARGET_CUBE);

    size_t min_depth = getopt.get_min_depth();
    size_t max_depth = getopt.get_max_depth();

    rubiks::Cube cube;
    rubiks::Cube goal;

    if (read_initial_cube) {
        cin >> cube;
    }

    if (read_target_cube) {
        cin >> goal;
    }

    bool show_progress = !getopt.has_io_option(rubiks::IO_QUIET_PROGRESS);

    for (size_t d = min_depth; d <= max_depth; d++) {
        rubiks::Search search(cube, goal, d);
        search.set_option(getopt.get_option());

        if (show_progress) {
            cerr << "# Depth: " << d << endl;
        }

        if (search.search()) {
            break;
        }
    }

    return 0;
}
