#ifndef RUBIKS_GETOPT_H
#define RUBIKS_GETOPT_H

#include "rubiks.h"

namespace rubiks {
    typedef unsigned int IOOption;

    const IOOption IO_READ_INITIAL_CUBE       = 0x01;
    const IOOption IO_READ_TARGET_CUBE        = 0x02;
    const IOOption IO_PRINT_CUBE              = 0x04;
    const IOOption IO_PRINT_PROCEDURE         = 0x08;
    const IOOption IO_PRINT_REVERSE_PROCEDURE = 0x10;
    const IOOption IO_QUIET_PROGRESS          = 0x20;
    const IOOption IO_PRINT_HELP              = 0x40;

    const IOOption DefaultIOOption = IO_READ_INITIAL_CUBE | IO_READ_TARGET_CUBE | IO_PRINT_CUBE;

    const int DEPTH_UNSET = -1;

    class Getopt {
      public:
        Getopt() :
            default_min_depth(DEPTH_UNSET), default_max_depth(DEPTH_UNSET),
            min_depth(DEPTH_UNSET), max_depth(DEPTH_UNSET),
            turn_option(0), slice_option(0), io_option(0),
            errors(0) {}
        void parse(int argc, char *argv[]);
        string get_program_path() const {return program_path;}
        string get_program_name() const {return program_name;}
        void set_default_min_depth(size_t _default_min_depth) {default_min_depth = (int)_default_min_depth;}
        void set_default_max_depth(size_t _default_max_depth) {default_max_depth = (int)_default_max_depth;}

        void add_turn_option(TurnOption _turn_option) {
            turn_option |= _turn_option;
        }

        void remove_turn_option(TurnOption _turn_option) {
            if (!turn_option) {
                turn_option |= DefaultTurnOption;
            }

            turn_option &= ~_turn_option;
        }

        void add_slice_option(SliceOption _slice_option) {
            slice_option |= _slice_option;
        }

        void remove_slice_option(SliceOption _slice_option) {
            if (!slice_option) {
                slice_option |= DefaultSliceOption;
            }

            slice_option &= ~_slice_option;
        }

        void add_io_option(IOOption _io_option) {
            io_option |= _io_option;
        }

        void remove_io_option(IOOption _io_option) {
            if (!io_option) {
                io_option |= DefaultIOOption;
            }

            io_option &= ~_io_option;
        }

        size_t get_min_depth() const {
            return (size_t)(min_depth == DEPTH_UNSET ? default_min_depth : min_depth);
        }

        size_t get_max_depth() const {
            return (size_t)(max_depth == DEPTH_UNSET ? default_max_depth : max_depth);
        }

        TurnOption get_turn_option() const {
            return !turn_option ? DefaultTurnOption : turn_option;
        }

        SliceOption get_slice_option() const {
            return !slice_option ? DefaultSliceOption : slice_option;
        }

        IOOption get_io_option() const {
            return !io_option ? DefaultIOOption : io_option;
        }

        bool has_turn_option(TurnOption _turn_option) const {return (get_turn_option() & _turn_option) != 0;}
        bool has_slice_option(SliceOption _slice_option) const {return (get_slice_option() & _slice_option) != 0;}
        bool has_io_option(IOOption _io_option) const {return (get_io_option() & _io_option) != 0;}
        size_t get_errors() const {return errors;}

      private:
        string program_path;
        string program_name;
        int default_min_depth;
        int default_max_depth;
        int min_depth;
        int max_depth;
        TurnOption turn_option;
        SliceOption slice_option;
        IOOption io_option;
        size_t errors;
    };
}

#endif

