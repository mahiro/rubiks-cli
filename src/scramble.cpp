#include <iostream>
#include "rubiks.h"
using namespace std;

int main(int argc, char *argv[]) {
    bool show_procedure = false;
    bool show_solution = false;

    rubiks::Cube cube;
    cube.reset();

    srand(time(0));
    rubiks::Procedure procedure;

    while (procedure.size() < 20) {
        rubiks::Slice slice = rand() % 6;

        if (procedure.size() > 0) {
            rubiks::Slice prev_slice = procedure.back().get_slice();

            if (rubiks::should_skip(prev_slice, slice)) {
                continue;
            }
        }

        rubiks::Turn turn = rand() % 3 + 1;
        cube.rotate(slice, turn);
        procedure.push_back(rubiks::Rotation(slice, turn));
    }

    cout << cube;

    if (show_procedure) {
        cout << procedure;
    }

    if (show_solution) {
        rubiks::Procedure solution;
        rubiks::reverse_procedure(procedure, solution);
        cout << solution;
    }

    return 0;
}
