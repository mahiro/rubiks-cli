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
    typedef size_t Position;
    typedef vector<Rotation> Procedure;
    typedef unsigned int Option;

    const Slice U = 0; // Up
    const Slice F = 1; // Front
    const Slice R = 2; // Right
    const Slice L = 3; // Left
    const Slice B = 4; // Back
    const Slice D = 5; // Down
    const Slice M = 6; // Middle   (Up-to-Front)
    const Slice S = 7; // Standing (Up-to-Right)
    const Slice E = 8; // Equator  (Front-to-Right)
    const Slice W_u =  9; // Up 2 layers
    const Slice W_f = 10; // Front 2 layers
    const Slice W_r = 11; // Right 2 layers
    const Slice W_l = 12; // Left 2 layers
    const Slice W_b = 13; // Back 2 layers
    const Slice W_d = 14; // Down 2 layers
    const Slice T_x = 15; // x-axis rotation
    const Slice T_y = 16; // y-axis rotation
    const Slice T_z = 17; // z-axis rotation

    const Slice mirror_slice[] = {
        /*U*/ U,
        /*F*/ R,
        /*R*/ F,
        /*L*/ B,
        /*B*/ L,
        /*D*/ D,
        /*M*/ S,
        /*S*/ M,
        /*E*/ E,
        /*W_u*/ W_u,
        /*W_f*/ W_r,
        /*W_r*/ W_f,
        /*W_l*/ W_b,
        /*W_b*/ W_l,
        /*W_d*/ W_d,
        /*T_x*/ T_z,
        /*T_y*/ T_y,
        /*T_z*/ T_x,
    };

    const char Slices[] = {
        'U', 'F', 'R', 'L', 'B', 'D',
        'M', 'S', 'E',
        'u', 'f', 'r', 'l', 'b', 'd',
        'x', 'y', 'z',
    };

    inline bool is_single_face (Slice slice) {return  /* 0 <= slice && */ slice <  6;}
    inline bool is_middle_slice(Slice slice) {return  6 <= slice && slice <  9;}
    inline bool is_single_slice(Slice slice) {return  /* 0 <= slice && */ slice <  9;}
    inline bool is_double_slice(Slice slice) {return  9 <= slice && slice < 15;}
    inline bool is_triple_slice(Slice slice) {return 15 <= slice && slice < 18;}

    const Turn NT = 0; // No turn
    const Turn QT = 1; // Quarter turn
    const Turn HT = 2; // Half turn
    const Turn RT = 3; // Reverse quarter turn
    const char Turns[] = {'?', ' ', '2', '\''};

    inline Turn reverse(Turn turn) {return (4 - turn) & 0x03;}

    const char DefaultTable[6][9] = {
        /*U*/ {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
        /*F*/ {'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
        /*R*/ {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
        /*L*/ {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        /*B*/ {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},
        /*D*/ {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'},
    };

    const Option OPT_QUARTER_TURN  = 0x01;
    const Option OPT_REVERSE_TURN  = 0x02;
    const Option OPT_HALF_TURN     = 0x04;

    const Option OPT_SINGLE_FACE   = 0x10;
    const Option OPT_MIDDLE_SLICE  = 0x20;
    const Option OPT_DOUBLE_SLICES = 0x40;
    const Option OPT_CUBE_ROTATION = 0x80;

    const Option DefaultOption =
        OPT_QUARTER_TURN | OPT_HALF_TURN | OPT_REVERSE_TURN |
        OPT_SINGLE_FACE | OPT_MIDDLE_SLICE;

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
        inline char get(Slice slice, Position position) {
            return table[slice][position];
        }
        inline void reset() {
            memcpy(table, DefaultTable, sizeof table);
        }
        void rotate(Slice slice, Turn turn);
        void rotate(const Rotation &rotation);
        void scramble(size_t times);
        void scramble(size_t times, Procedure &rotations);
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
        inline Rotation reverse() const {
            return Rotation(slice, rubiks::reverse(turn));
        }
        inline Rotation mirror() const {
            return Rotation(mirror_slice[slice],
                    (slice == M || slice == S ? turn : rubiks::reverse(turn)));
        }
        inline bool operator==(const Rotation &other) const {
            return slice == other.slice && turn == other.turn;
        }
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
        bool inner_search(Procedure &stack);
        bool inner_search_turns(Procedure &stack, Slice slice);
      protected:
        Cube &cube;
        const Cube &goal;
        size_t target_depth;
        ostream &out;
        Option option;
      public:
        Search(Cube &_cube, const Cube &_goal, size_t _depth) :
            cube(_cube), goal(_goal), target_depth(_depth), out(cout), option(DefaultOption) {}
        Search(Cube &_cube, const Cube &_goal, size_t _depth, ostream &_out) :
            cube(_cube), goal(_goal), target_depth(_depth), out(_out), option(DefaultOption) {}
        bool search();
        void add_option(Option opt) {
            option |= opt;
        }
        void remove_option(Option opt) {
            option &= ~opt;
        }
        bool has_option(Option opt) {
            return option & opt;
        }
      protected:
        bool match() const;
        void result(const Procedure &stack) const;
    };

    class Enumerate : public Search {
      public:
        Enumerate(size_t _depth);
        Enumerate(size_t _depth, ostream &_out);
      protected:
        bool match() const;
        void result(const Procedure &stack) const;
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

    void reverse(const Procedure &source, Procedure &destination);
    void mirror(const Procedure &source, Procedure &destination);
}

#endif
