#include <iostream>
#include "rubiks.h"
using namespace std;

int main(int argc, char *argv[]) {
    int target_depth = 1;

    if (argc > 1) {
        target_depth = atoi(argv[1]);
    }

    rubiks::Enumerate enumerate(target_depth);
    enumerate.search();

    return 0;
}
