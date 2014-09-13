#include <iostream>
#include <sstream>
#include <cstring>
#include "rubiks.h"

namespace rubiks {
    using namespace std;

    /*
     *          -------
     *         |       |
     *         |   U   |
     *         |  [0]  |
     *  ------- ------- ------- -------
     * |       |       |       |       |
     * |   L   |   F   |   R   |   B   |
     * |  [3]  |  [1]  |  [2]  |  [4]  |
     *  ------- ------- ------- -------
     *         |       |
     *         |   D   |
     *         |  [5]  |
     *          -------
     * 
     *          -------
     *         | 0 1 2 |
     *         | 3 4 5 |
     *         | 6 7 8 |
     *  ------- ------- ------- -------
     * | 0 1 2 | 0 1 2 | 0 1 2 | 0 1 2 |
     * | 3 4 5 | 3 4 5 | 3 4 5 | 3 4 5 |
     * | 6 7 8 | 6 7 8 | 6 7 8 | 6 7 8 |
     *  ------- ------- ------- -------
     *         | 0 1 2 |
     *         | 3 4 5 |
     *         | 6 7 8 |
     *          -------
     * 
     */
    static const size_t rotation_patterns[9][5][8] = {
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

    inline void Cube::inner_rotate_QT(const size_t *r) {
        char tmp = table[r[0]][r[1]];
        table[r[0]][r[1]] = table[r[6]][r[7]];
        table[r[6]][r[7]] = table[r[4]][r[5]];
        table[r[4]][r[5]] = table[r[2]][r[3]];
        table[r[2]][r[3]] = tmp;
    }

    inline void Cube::inner_rotate_HT(const size_t *r) {
        char tmp = table[r[0]][r[1]];
        table[r[0]][r[1]] = table[r[4]][r[5]];
        table[r[4]][r[5]] = tmp;
        tmp = table[r[2]][r[3]];
        table[r[2]][r[3]] = table[r[6]][r[7]];
        table[r[6]][r[7]] = tmp;
    }

    inline void Cube::inner_rotate_RT(const size_t *r) {
        char tmp = table[r[0]][r[1]];
        table[r[0]][r[1]] = table[r[2]][r[3]];
        table[r[2]][r[3]] = table[r[4]][r[5]];
        table[r[4]][r[5]] = table[r[6]][r[7]];
        table[r[6]][r[7]] = tmp;
    }

    void Cube::rotate(Slice slice, Turn turn) {
        if (turn >= 4) {
            turn %= 4;
        }

        if (turn == NT) {
            return;
        }

        const size_t (*rot)[8] = rotation_patterns[slice];
        size_t num_rotate = is_single_face(slice) ? 5 : 3;

        if (is_single_slice(slice)) {
            if (turn == QT) {
                for (size_t i = 0; i < num_rotate; i++) {
                    inner_rotate_QT(rot[i]);
                }
            } else if (turn == HT) {
                for (size_t i = 0; i < num_rotate; i++) {
                    inner_rotate_HT(rot[i]);
                }
            } else if (turn == RT) {
                for (size_t i = 0; i < num_rotate; i++) {
                    inner_rotate_RT(rot[i]);
                }
            }
        } else if (is_double_slice(slice)) {
            switch (slice) {
                case W_u: rotate(U, turn); rotate(E, reverse(turn)); break;
                case W_f: rotate(F, turn); rotate(S, turn); break;
                case W_r: rotate(R, turn); rotate(M, reverse(turn)); break;
                case W_l: rotate(L, turn); rotate(M, turn); break;
                case W_b: rotate(B, turn); rotate(S, reverse(turn)); break;
                case W_d: rotate(D, turn); rotate(E, turn); break;
            }
        } else if (is_triple_slice(slice)) {
            switch (slice) {
                case T_x:
                    rotate(R, turn);
                    rotate(M, reverse(turn));
                    rotate(L, reverse(turn));
                    break;
                case T_y:
                    rotate(U, turn);
                    rotate(E, reverse(turn));
                    rotate(D, reverse(turn));
                    break;
                case T_z:
                    rotate(F, turn);
                    rotate(S, turn);
                    rotate(B, reverse(turn));
                    break;
            }
        }
    }

    void Cube::rotate(const Rotation &rotation) {
        rotate(rotation.slice, rotation.turn);
    }

    void Cube::scramble(size_t times) {
        Procedure procedure;
        scramble(times, procedure);
    }

    void Cube::scramble(size_t times, Procedure &procedure) {
        size_t count = 0;
        srand(time(0));

        while (count < times) {
            Slice slice = rand() % 6;

            if (procedure.size() > 0) {
                Slice prev_slice = procedure.back().get_slice();

                if (should_skip(prev_slice, slice)) {
                    continue;
                }
            }

            Turn turn = rand() % 3 + 1;
            rotate(slice, turn);
            procedure.push_back(Rotation(slice, turn));
            count++;
        }
    }

    bool Cube::operator==(const Cube &other) const {
        for (size_t i = 0; i < 6; i++) {
            for (size_t j = 0; j < 9; j++) {
                if (table[i][j] != other.table[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    istream &operator>>(istream &in, Cube &cube) {
        for (size_t r = 0; r < 3; r++) {
            for (size_t i = 0; i < 3; i++) in >> cube.table[U][3 * r + i];
        }

        for (size_t r = 0; r < 3; r++) {
            for (size_t i = 0; i < 3; i++) in >> cube.table[L][3 * r + i];
            for (size_t i = 0; i < 3; i++) in >> cube.table[F][3 * r + i];
            for (size_t i = 0; i < 3; i++) in >> cube.table[R][3 * r + i];
            for (size_t i = 0; i < 3; i++) in >> cube.table[B][3 * r + i];
        }

        for (size_t r = 0; r < 3; r++) {
            for (size_t i = 0; i < 3; i++) in >> cube.table[D][3 * r + i];
        }

        return in;
    }

    ostream &operator<<(ostream &out, const Cube &cube) {
        for (size_t r = 0; r < 3; r++) {
            for (size_t i = 0; i < 3; i++) out << "  ";
            out << " ";
            for (size_t i = 0; i < 3; i++) out << cube.table[U][3 * r + i] << (i == 2 ? "" : " ");
            out << endl;
        }

        out << endl;

        for (size_t r = 0; r < 3; r++) {
            for (size_t i = 0; i < 3; i++) out << cube.table[L][3 * r + i] << " ";
            out << " ";
            for (size_t i = 0; i < 3; i++) out << cube.table[F][3 * r + i] << " ";
            out << " ";
            for (size_t i = 0; i < 3; i++) out << cube.table[R][3 * r + i] << " ";
            out << " ";
            for (size_t i = 0; i < 3; i++) out << cube.table[B][3 * r + i] << (i == 2 ? "" : " ");
            out << endl;
        }

        out << endl;

        for (size_t r = 0; r < 3; r++) {
            for (size_t i = 0; i < 3; i++) out << "  ";
            out << " ";
            for (size_t i = 0; i < 3; i++) out << cube.table[D][3 * r + i] << (i == 2 ? "" : " ");
            out << endl;
        }

        out << endl;
        return out;
    }

    istream &operator>>(istream &in, Rotation &rotation) {
        string word;
        in >> word;

        if (!in) {
            return in;
        }

        switch (word[0]) {
            case 'U': rotation.slice = U; break;
            case 'F': rotation.slice = F; break;
            case 'R': rotation.slice = R; break;
            case 'L': rotation.slice = L; break;
            case 'B': rotation.slice = B; break;
            case 'D': rotation.slice = D; break;
            case 'M': rotation.slice = M; break;
            case 'S': rotation.slice = S; break;
            case 'E': rotation.slice = E; break;
            case 'u': rotation.slice = W_u; break;
            case 'f': rotation.slice = W_f; break;
            case 'r': rotation.slice = W_r; break;
            case 'l': rotation.slice = W_l; break;
            case 'b': rotation.slice = W_b; break;
            case 'd': rotation.slice = W_d; break;
            case 'x': rotation.slice = T_x; break;
            case 'y': rotation.slice = T_y; break;
            case 'z': rotation.slice = T_z; break;
            default: rotation = Rotation(); // TODO: handle error?
        }

        if (word.length() >= 2) {
            switch (word[1]) {
                case '\'': rotation.turn = RT; break;
                case '2': rotation.turn = HT; break;
                default: rotation.turn = NT; // TODO: handle error?
            }
        } else {
            rotation.turn = QT;
        }

        return in;
    }

    istream &operator>>(istream &in, Procedure &procedure) {
        string line;
        getline(in, line);

        if (!in) {
            return in;
        }

        stringstream ss;
        ss.str(line);

        while (true) {
            Rotation rotation;
            ss >> rotation;

            if (!ss) {
                break;
            }

            procedure.push_back(rotation);
        }

        return in;
    }

    ostream &operator<<(ostream &out, const Rotation &rotation) {
        if (rotation.turn == NT) {
            out << "  ";
        } else {
            out << Slices[rotation.slice] << Turns[rotation.turn];
        }

        return out;
    }

    ostream &operator<<(ostream &out, const Procedure &procedure) {
        bool first = true;

        for (Procedure::const_iterator it = procedure.begin();
                it != procedure.end(); ++it) {
            if (first) {
                first = false;
            } else {
                out << ' ';
            }

            out << *it;
        }

        out << endl;
        return out;
    }

    bool Search::inner_search_turns(Procedure &stack, Slice slice) {
        bool found = false;

        if (option & OPT_QUARTER_TURN) {
            // QT
            cube.rotate(slice, QT);
            if (inner_search(stack)) {found = true;}

            if (option & OPT_REVERSE_TURN) {
                // RT
                cube.rotate(slice, HT); // QT + HT => RT
                stack.back().turn = RT;
                if (inner_search(stack)) {found = true;}

                if (option & OPT_HALF_TURN) {
                    // HT
                    cube.rotate(slice, RT); // RT + RT => HT
                    stack.back().turn = HT;
                    if (inner_search(stack)) {found = true;}
                    // Restore
                    cube.rotate(slice, HT);
                } else {
                    // Restore
                    cube.rotate(slice, QT);
                }
            } else {
                if (option & OPT_HALF_TURN) {
                    // HT
                    cube.rotate(slice, QT); // QT + QT => HT
                    stack.back().turn = HT;
                    if (inner_search(stack)) {found = true;}
                    // Restore
                    cube.rotate(slice, HT);
                } else {
                    // Restore
                    cube.rotate(slice, RT);
                }
            }
        } else {
            if (option & OPT_REVERSE_TURN) {
                // RT
                cube.rotate(slice, RT);
                stack.back().turn = RT;
                if (inner_search(stack)) {found = true;}

                if (option & OPT_HALF_TURN) {
                    // HT
                    cube.rotate(slice, RT); // RT + RT => HT
                    stack.back().turn = HT;
                    if (inner_search(stack)) {found = true;}
                    // Restore
                    cube.rotate(slice, HT);
                } else {
                    // Restore
                    cube.rotate(slice, QT);
                }
            } else if (option & OPT_HALF_TURN) {
                // HT
                cube.rotate(slice, HT);
                stack.back().turn = HT;
                if (inner_search(stack)) {found = true;}
                // Restore
                cube.rotate(slice, HT);
            }
        }

        return found;
    }

    bool Search::inner_search(Procedure &stack) {
        size_t depth = stack.size();

        if (depth >= target_depth) {
            if (match()) {
                result(stack);
                return true;
            } else {
                return false;
            }
        }

        bool found = false;
        char prev_slice = depth > 0 ? stack.back().slice : -1;

        Slice slice_begin = (option & OPT_SINGLE_FACE) ? 0 : 6;
        Slice slice_end = (option & OPT_MIDDLE_SLICE) ? 9 : 6;

        for (Slice slice = slice_begin; slice < slice_end; slice++) {
            if (depth > 0 && should_skip(prev_slice, slice)) {
                continue;
            }

            stack.push_back(Rotation(slice, QT));

            if (inner_search_turns(stack, slice)) {
                found = true;
            }

            stack.pop_back();
        }

        return found;
    }

    bool Search::search() {
        Procedure stack;
        return inner_search(stack);
    }

    inline bool Search::match() const {
        return cube == goal;
    }

    inline void Search::result(const Procedure &procedure) const {
        out << procedure;
    }

    Cube enumerate_cube;

    Enumerate::Enumerate(size_t _depth) :
        Search(enumerate_cube, enumerate_cube, _depth) {};

    Enumerate::Enumerate(size_t _depth, ostream &_out) :
        Search(enumerate_cube, enumerate_cube, _depth, _out) {};

    inline bool Enumerate::match() const {
        return true;
    }

    inline void Enumerate::result(const Procedure &procedure) const {
        cout << procedure;
    }

    void reverse(const Procedure &source, Procedure &destination) {
        for (Procedure::const_reverse_iterator it = source.rbegin();
                it != source.rend(); ++it) {
            destination.push_back(it->reverse());
        }
    }

    void mirror(const Procedure &source, Procedure &destination) {
        for (Procedure::const_iterator it = source.begin();
                it != source.end(); ++it) {
            destination.push_back(it->mirror());
        }
    }
}
