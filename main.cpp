#include <iostream>
#include <vector>
#include <cstdlib>
#include <cctype>
using namespace std;

// Faces
const char U = 0; // Up
const char F = 1; // Front
const char R = 2; // Right
const char L = 3; // Left
const char B = 4; // Back
const char D = 5; // Down
const char M = 6; // Up-to-Front middle
const char S = 7; // Up-to-Right middle
const char E = 8; // Front-to-Right middle
const char faces[] = {'U', 'F', 'R', 'L', 'B', 'D', 'M', 'S', 'E'};

// Turns
const char QT = 0; // Quarter turn
const char HT = 1; // Half turn
const char RT = 2; // Reverse quarter turn
const char turns[] = {' ', '2', '\''};

// Positions
//  0 1 2
//  3 4 5
//  6 7 8

//    U
//  L F R B
//    D

char complete_cube[6][9] = {
    /*U*/ {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
    /*F*/ {'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
    /*R*/ {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
    /*L*/ {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
    /*B*/ {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},
    /*D*/ {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'},
};

char main_cube[6][9] = {
    /*U*/ {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
    /*F*/ {'G', 'O', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
    /*R*/ {'R', 'G', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
    /*L*/ {'O', 'R', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
    /*B*/ {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},
    /*D*/ {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'},
};

char goal_cube[6][9] = {
    /*U*/ {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
    /*F*/ {'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
    /*R*/ {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
    /*L*/ {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
    /*B*/ {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},
    /*D*/ {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'},
};

char rotation[9][5][8] = {
    /*U*/ {
        {U, 0, U, 2, U, 8, U, 6},
        {U, 1, U, 5, U, 7, U, 3},
        {B, 2, R, 2, F, 2, L, 2},
        {B, 1, R, 1, F, 1, L, 1},
        {B, 0, R, 0, F, 0, L, 0},
    },
    /*F*/ {
        {F, 0, F, 2, F, 8, F, 6},
        {F, 1, F, 5, F, 7, F, 3},
        {U, 6, R, 0, D, 2, L, 8},
        {U, 7, R, 3, D, 1, L, 5},
        {U, 8, R, 6, D, 0, L, 2},
    },
    /*R*/ {
        {R, 0, R, 2, R, 8, R, 6},
        {R, 1, R, 5, R, 7, R, 3},
        {U, 8, B, 0, D, 8, F, 8},
        {U, 5, B, 3, D, 5, F, 5},
        {U, 2, B, 6, D, 2, F, 2},
    },
    /*L*/ {
        {L, 0, L, 2, L, 8, L, 6},
        {L, 1, L, 5, L, 7, L, 3},
        {U, 0, F, 0, D, 0, B, 8},
        {U, 3, F, 3, D, 3, B, 5},
        {U, 6, F, 6, D, 6, B, 2},
    },
    /*B*/ {
        {B, 0, B, 2, B, 8, B, 6},
        {B, 1, B, 5, B, 7, B, 3},
        {U, 2, L, 0, D, 6, R, 8},
        {U, 1, L, 3, D, 7, R, 5},
        {U, 0, L, 6, D, 8, R, 2},
    },
    /*D*/ {
        {D, 0, D, 2, D, 8, D, 6},
        {D, 1, D, 5, D, 7, D, 3},
        {F, 6, R, 6, B, 6, L, 6},
        {F, 7, R, 7, B, 7, L, 7},
        {F, 8, R, 8, B, 8, L, 8},
    },
    /*M*/ {
        {U, 7, F, 7, D, 7, B, 1},
        {U, 4, F, 4, D, 4, B, 4},
        {U, 1, F, 1, D, 1, B, 7},
    },
    /*S*/ {
        {U, 3, R, 1, D, 5, L, 7},
        {U, 4, R, 4, D, 4, L, 4},
        {U, 5, R, 7, D, 3, L, 1},
    },
    /*E*/ {
        {F, 3, R, 3, B, 3, L, 3},
        {F, 4, R, 4, B, 4, L, 4},
        {F, 5, R, 5, B, 5, L, 5},
    },
};

inline void rotate_QT(char *r) {
    char tmp = main_cube[r[0]][r[1]];
    main_cube[r[0]][r[1]] = main_cube[r[6]][r[7]];
    main_cube[r[6]][r[7]] = main_cube[r[4]][r[5]];
    main_cube[r[4]][r[5]] = main_cube[r[2]][r[3]];
    main_cube[r[2]][r[3]] = tmp;
}

inline void rotate_HT(char *r) {
    char tmp = main_cube[r[0]][r[1]];
    main_cube[r[0]][r[1]] = main_cube[r[4]][r[5]];
    main_cube[r[4]][r[5]] = tmp;
    tmp = main_cube[r[2]][r[3]];
    main_cube[r[2]][r[3]] = main_cube[r[6]][r[7]];
    main_cube[r[6]][r[7]] = tmp;
}

inline void rotate_RT(char *r) {
    char tmp = main_cube[r[0]][r[1]];
    main_cube[r[0]][r[1]] = main_cube[r[2]][r[3]];
    main_cube[r[2]][r[3]] = main_cube[r[4]][r[5]];
    main_cube[r[4]][r[5]] = main_cube[r[6]][r[7]];
    main_cube[r[6]][r[7]] = tmp;
}

void rotate(char face, char turn) {
    char (*rot)[8] = rotation[face];
    int num_rotate = face < 6 ? 5 : 3;

    if (turn == QT) {
        for (char i = 0; i < num_rotate; i++) {
            rotate_QT(rot[i]);
        }
    } else if (turn == HT) {
        for (char i = 0; i < num_rotate; i++) {
            rotate_HT(rot[i]);
        }
    } else if (turn == RT) {
        for (char i = 0; i < num_rotate; i++) {
            rotate_RT(rot[i]);
        }
    }
}

inline char color_at(char face, char pos) {
    return main_cube[face][pos];
}

void print() {
    for (int r = 0; r < 3; r++) {
        for (int i = 0; i < 3; i++) cout << "  ";
        cout << " ";
        for (int i = 0; i < 3; i++) cout << color_at(U, 3 * r + i) << " ";
        cout << endl;
    }

    cout << endl;

    for (int r = 0; r < 3; r++) {
        for (int i = 0; i < 3; i++) cout << color_at(L, 3 * r + i) << " ";
        cout << " ";
        for (int i = 0; i < 3; i++) cout << color_at(F, 3 * r + i) << " ";
        cout << " ";
        for (int i = 0; i < 3; i++) cout << color_at(R, 3 * r + i) << " ";
        cout << " ";
        for (int i = 0; i < 3; i++) cout << color_at(B, 3 * r + i) << " ";
        cout << endl;
    }

    cout << endl;

    for (int r = 0; r < 3; r++) {
        for (int i = 0; i < 3; i++) cout << "  ";
        cout << " ";
        for (int i = 0; i < 3; i++) cout << color_at(D, 3 * r + i) << " ";
        cout << endl;
    }

    cout << endl;
}

long long match_count = 0L;

bool match() {
    match_count++;

//    if (match_count % 10000 == 0) {
//        cout << "\r" << match_count << flush;
//    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 9; j++) {
            if (main_cube[i][j] != goal_cube[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool should_skip(char prev_face, char current_face) {
    if (prev_face == current_face) {
        return true;
    } else if (prev_face == D && current_face == U) {
        return true;
    } else if (prev_face == B && current_face == F) {
        return true;
    } else if (prev_face == L && current_face == R) {
        return true;
    } else if (prev_face == M && (current_face == R || current_face == L)) {
        return true;
    } else if (prev_face == S && (current_face == F || current_face == B)) {
        return true;
    } else if (prev_face == E && (current_face == U || current_face == D)) {
        return true;
    }

    return false;
}

vector<char> face_stack;
vector<char> turn_stack;

void print_steps() {
    for (int i = 0; i < face_stack.size(); i++) {
        cout << faces[face_stack[i]] << turns[turn_stack[i]] << " ";
    }

    cout << endl;
}

int min_depth = 1;
int max_depth = 9;

int target_depth = 1;

bool traverse() {
    int depth = face_stack.size();

    if (depth == target_depth) {
        if (match()) {
            print_steps();
            return true;
        }
    }

    if (depth >= target_depth) {
        return false;
    }

    bool found = false;
    int num_faces = 6 + 3; // faces + middles
    char prev_face = depth > 0 ? face_stack.back() : -1;

    for (int face = 0; face < num_faces; face++) {
        if (depth > 0) {
            if (should_skip(prev_face, face)) {
                continue;
            }
        }

        face_stack.push_back(face);
        {
            rotate(face, QT);
            turn_stack.push_back(QT);
            {
                if (traverse()) {found = true;}
            }
            turn_stack.pop_back();
            rotate(face, HT);
            turn_stack.push_back(RT);
            {
                if (traverse()) {found = true;}
            }
            turn_stack.pop_back();
            rotate(face, RT);
            turn_stack.push_back(HT);
            {
                if (traverse()) {found = true;}
            }
            turn_stack.pop_back();
            rotate(face, HT);
        }
        face_stack.pop_back();
    }

    return found;
}

char read_color() {
    char ch;

    while (1) {
        cin >> ch;
        return ch;
    }

    return '.';
}

void read_cube(char (*cube)[9]) {
    for (int r = 0; r < 3; r++) {
        for (int i = 0; i < 3; i++) {
            cube[U][3 * r + i] = read_color();
        }
    }

    for (int r = 0; r < 3; r++) {
        for (int i = 0; i < 3; i++) {
            cube[L][3 * r + i] = read_color();
        }

        for (int i = 0; i < 3; i++) {
            cube[F][3 * r + i] = read_color();
        }

        for (int i = 0; i < 3; i++) {
            cube[R][3 * r + i] = read_color();
        }

        for (int i = 0; i < 3; i++) {
            cube[B][3 * r + i] = read_color();
        }
    }

    for (int r = 0; r < 3; r++) {
        for (int i = 0; i < 3; i++) {
            cube[D][3 * r + i] = read_color();
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        min_depth = atoi(argv[1]);
        max_depth = min_depth;
    }

    if (argc > 2) {
        max_depth = atoi(argv[2]);
    }

    read_cube(main_cube);
    read_cube(goal_cube);

    for (int d = min_depth; d <= max_depth; d++) {
        target_depth = d;
        cerr << "# Depth: " << target_depth << endl;

        if (traverse()) {
            break;
        }
    }

//    cout << "\r" << match_count << endl;

    return 0;
}
