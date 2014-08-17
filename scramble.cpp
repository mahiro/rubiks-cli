#include <iostream>
#include "rubiks.h"
using namespace std;

int main(int argc, char *argv[]) {
    rubiks::Cube cube;
    cube.reset();

    srand(time(0));

    for (int i = 0; i < 20; i++) {
        rubiks::Slice face = rand() % 6;
        rubiks::Turn turn = rand() % 3 + 1;
        cube.rotate(face, turn);
    }

    cout << cube;
    return 0;
}
