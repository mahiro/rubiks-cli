#include <iostream>
#include "rubiks.h"
using namespace std;

int main(int argc, char *argv[]) {
    int min_depth = 1;
    int max_depth = 8;

    if (argc > 1) {
        min_depth = atoi(argv[1]);
        max_depth = min_depth;
    }

    if (argc > 2) {
        max_depth = atoi(argv[2]);
    }

    rubiks::Cube cube;
    rubiks::Cube goal;

    cin >> cube;
    cin >> goal;

    for (int d = min_depth; d <= max_depth; d++) {
        rubiks::Search search(cube, goal);
        cerr << "# Depth: " << d << endl;

        if (search.search(d)) {
            break;
        }
    }

    return 0;
}
