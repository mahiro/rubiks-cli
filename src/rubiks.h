#ifndef RUBIKS_CUBE_H
#define RUBIKS_CUBE_H

#include <iostream>
#include <vector>

namespace rubiks {
    using namespace std;

    class Cube;
    class Rotation;
    class Search;
    typedef size_t Slice;
    typedef size_t Turn;
    typedef vector<Rotation> Procedure;

    const Slice U = 0; // Up
    const Slice F = 1; // Front
    const Slice R = 2; // Right
    const Slice L = 3; // Left
    const Slice B = 4; // Back
    const Slice D = 5; // Down
    const Slice M = 6; // Middle  (Up-to-Front)
    const Slice S = 7; // Side    (Up-to-Right)
    const Slice E = 8; // Equator (Front-to-Right)
    const char Slices[] = {'U', 'F', 'R', 'L', 'B', 'D', 'M', 'S', 'E'};

    const Turn NT = 0; // No turn
    const Turn QT = 1; // Quarter turn
    const Turn HT = 2; // Half turn
    const Turn RT = 3; // Reverse quarter turn
    const char Turns[] = {'?', ' ', '2', '\''};

    const char DefaultTable[6][9] = {
        /*U*/ {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
        /*F*/ {'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
        /*R*/ {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
        /*L*/ {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        /*B*/ {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},
        /*D*/ {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'},
    };

    class Cube {
      private:
        char table[6][9];
        void inner_rotate_QT(const size_t *rotation_pattern);
        void inner_rotate_HT(const size_t *rotation_pattern);
        void inner_rotate_RT(const size_t *rotation_pattern);
      public:
        Cube() {reset();}
        Cube(const Cube &other) {
            *this = other;
        }
        inline void reset() {
            memcpy(table, DefaultTable, sizeof table);
        }
        void rotate(Slice slice, Turn turn);
        void rotate(const Rotation &rotation);
        void scramble(int times);
        void scramble(int times, Procedure &rotations);
        inline Cube &operator=(const Cube &other) {
            memcpy(table, other.table, sizeof table);
            return *this;
        }
        bool operator==(const Cube &other) const;
        friend istream &operator>>(istream &in, Cube &cube);
        friend ostream &operator<<(ostream &out, const Cube &cube);
    };

    class Rotation {
      private:
        Slice slice;
        Turn turn;
      public:
        Rotation() : slice(U), turn(NT) {}
        Rotation(Slice _slice, Turn _turn) : slice(_slice), turn(_turn) {}
        inline Slice get_slice() const {return slice;}
        inline Turn get_turn() const {return turn;}
        Rotation reverse() const;
        bool operator==(const Rotation &other) const;
        friend class Cube;
        friend class Search;
        friend class Enumerate;
        friend istream &operator>>(istream &in, Rotation &rotation);
        friend ostream &operator<<(ostream &out, const Rotation &rotation);
        friend istream &operator>>(istream &out, Procedure &rotations);
        friend ostream &operator<<(ostream &out, const Procedure &rotations);
    };

    class Search {
      private:
        Cube &cube;
        const Cube &goal;
        Procedure stack;
        ostream &out;
      public:
        Search(Cube &_cube, const Cube &_goal) : cube(_cube), goal(_goal), out(cout) {}
        Search(Cube &_cube, const Cube &_goal, ostream &_out) : cube(_cube), goal(_goal), out(_out) {}
        bool search(int target_depth);
      protected:
        void handle_result(const Procedure &stack) const;
    };

    class Enumerate {
      private:
        Procedure stack;
        ostream &out;
      public:
        Enumerate() : out(cout) {}
        Enumerate(ostream &_out) : out(_out) {}
        void enumerate(int target_depth);
      protected:
        void handle_result(const Procedure &procedure) const;
    };

    inline bool should_skip(Slice prev_slice, Slice current_slice) {
        if (prev_slice == current_slice) {
            return true;
        } else if (prev_slice == D && current_slice == U) {
            return true;
        } else if (prev_slice == B && current_slice == F) {
            return true;
        } else if (prev_slice == L && current_slice == R) {
            return true;
        } else if (prev_slice == M && (current_slice == R || current_slice == L)) {
            return true;
        } else if (prev_slice == S && (current_slice == F || current_slice == B)) {
            return true;
        } else if (prev_slice == E && (current_slice == U || current_slice == D)) {
            return true;
        }

        return false;
    }

    void reverse_procedure(const Procedure &source, Procedure &destination);
}

#endif
