#include <iostream>
#include "rubiks.h"
#include "rubiks-getopt.h"
using namespace std;

int main(int argc, char *argv[]) {
    rubiks::Getopt getopt;
    getopt.set_default_min_depth(1);
    getopt.set_default_max_depth(1);
    getopt.parse(argc, argv);

    if (getopt.has_io_option(rubiks::IO_PRINT_HELP)) {
        cerr << "Usage:" << endl;
        cerr << "  " << getopt.get_program_name() << " [-n|-N NUM] [-prlsmdt] > OUTPUT_MOVE" << endl;
        cerr << "  " << getopt.get_program_name() << " -h" << endl;
        exit(-1);
    }

    size_t min_depth = getopt.get_min_depth();
    size_t max_depth = getopt.get_max_depth();

    for (size_t d = min_depth; d <= max_depth; d++) {
        rubiks::Enumerate enumerate(d);
        enumerate.set_turn_option(getopt.get_turn_option());
        enumerate.set_slice_option(getopt.get_slice_option());
        enumerate.search();
    }

    return 0;
}
