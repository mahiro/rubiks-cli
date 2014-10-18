#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "rubiks-getopt.h"

namespace rubiks {
    using namespace std;

    void Getopt::parse(int argc, char *argv[]) {
        program_path = argv[0];
        program_name = program_path.substr(program_path.find_last_of('/') + 1);

        int opt;

        while ((opt = getopt(argc, argv, "n:N:pPrRlLsSmMdDtTiIjJoOuUvVqQhH")) != -1) {
            switch (opt) {
                case 'n':
                    min_depth = atoi(optarg);
                    if (max_depth == DEPTH_UNSET || min_depth > max_depth) max_depth = min_depth;
                    break;
                case 'N':
                    max_depth = atoi(optarg);
                    if (min_depth != DEPTH_UNSET && min_depth > max_depth) min_depth = max_depth;
                    break;

                case 'p':
                    add_turn_option(OPT_QUARTER_TURN);
                    break;
                case 'P':
                    remove_turn_option(OPT_QUARTER_TURN);
                    break;

                case 'r':
                    add_turn_option(OPT_REVERSE_TURN);
                    break;
                case 'R':
                    remove_turn_option(OPT_REVERSE_TURN);
                    break;

                case 'l':
                    add_turn_option(OPT_HALF_TURN);
                    break;
                case 'L':
                    remove_turn_option(OPT_HALF_TURN);
                    break;

                case 's':
                    add_slice_option(OPT_SINGLE_FACE);
                    break;
                case 'S':
                    remove_slice_option(OPT_SINGLE_FACE);
                    break;

                case 'm':
                    add_slice_option(OPT_MIDDLE_SLICE);
                    break;
                case 'M':
                    remove_slice_option(OPT_MIDDLE_SLICE);
                    break;

                case 'd':
                    add_slice_option(OPT_DOUBLE_SLICE);
                    break;
                case 'D':
                    remove_slice_option(OPT_DOUBLE_SLICE);
                    break;

                case 't':
                    add_slice_option(OPT_TRIPLE_SLICE);
                    break;
                case 'T':
                    remove_slice_option(OPT_TRIPLE_SLICE);
                    break;

                case 'i':
                    add_io_option(IO_READ_INITIAL_CUBE);
                    break;
                case 'I':
                    remove_io_option(IO_READ_INITIAL_CUBE);
                    break;

                case 'j':
                    add_io_option(IO_READ_TARGET_CUBE);
                    break;
                case 'J':
                    remove_io_option(IO_READ_TARGET_CUBE);
                    break;

                case 'o':
                    add_io_option(IO_PRINT_CUBE);
                    break;
                case 'O':
                    remove_io_option(IO_PRINT_CUBE);
                    break;

                case 'u':
                    add_io_option(IO_PRINT_PROCEDURE);
                    break;
                case 'U':
                    remove_io_option(IO_PRINT_PROCEDURE);
                    break;

                case 'v':
                    add_io_option(IO_PRINT_REVERSE_PROCEDURE);
                    break;
                case 'V':
                    remove_io_option(IO_PRINT_REVERSE_PROCEDURE);
                    break;

                case 'q':
                    add_io_option(IO_QUIET_PROGRESS);
                    break;
                case 'Q':
                    remove_io_option(IO_QUIET_PROGRESS);
                    break;

                case 'h':
                    add_io_option(IO_PRINT_HELP);
                    break;
                case 'H':
                    remove_io_option(IO_PRINT_HELP);
                    break;

                default:
                    errors++;
            }
        }
    }
}
