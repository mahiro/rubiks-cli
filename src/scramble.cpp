#include <iostream>
#include "rubiks.h"
using namespace std;

int main(int argc, char *argv[]) {
    bool show_cube = true;
    bool show_procedure = false;
    bool show_solution = false;

    int times = 20;

    if (argc > 1) {
        times = atoi(argv[1]);
    }

    rubiks::Procedure procedure;
    rubiks::Cube cube;
    cube.reset();
    cube.scramble(times, procedure);

    if (show_cube) {
        cout << cube;
    }

    if (show_procedure) {
        cout << procedure;
    }

    if (show_solution) {
        rubiks::Procedure solution;
        rubiks::reverse(procedure, solution);
        cout << solution;
    }

    return 0;
}
