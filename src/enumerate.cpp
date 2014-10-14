#include <iostream>
#include "rubiks.h"
#include "rubiks-getopt.h"
using namespace std;

int main(int argc, char *argv[]) {
    rubiks::Getopt getopt;
    getopt.set_default_min_depth(1);
    getopt.set_default_max_depth(1);
    getopt.parse(argc, argv);

    size_t min_depth = getopt.get_min_depth();
    size_t max_depth = getopt.get_max_depth();

    for (size_t d = min_depth; d <= max_depth; d++) {
        rubiks::Enumerate enumerate(d);
        enumerate.set_option(getopt.get_option());
        enumerate.search();
    }

    return 0;
}
