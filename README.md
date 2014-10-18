# Rubik's Cube CLI

Command References:

* [rubiks-search](#rubiks-search)
* [rubiks-enumerate](#rubiks-enumerate)
* [rubiks-scramble](#rubiks-scramble)
* [rubiks-apply](#rubiks-apply)
* [rubiks-reverse](#rubiks-reverse)
* [rubiks-mirror](#rubiks-mirror)

Appendix:

* [Cube Notation](#cube-notation)
* [Move Notation](#move-notation)

## rubiks-search

Given initial and target Rubik's cube placements as input, the command finds steps that will turn the initial cube into
the target cube.

This is based on a brute-force algorithm that attempts all the combinations of steps to match the cube with the target,
where a simple optimization with parallel slices is applied so that obviously unnecessary steps are omitted.

The maximum search depth is set to 8 by default, which already takes a long time (possibly several hours).
On the other hand, the number of steps required to solve an arbitrary Rubik's cube is known to be 20.
Thus, this program is not useful to solve a generic cube.
In fact, there appear to be no known perfectly optimal algorithm to solve a generic cube.

This program is rather intended to be a simple utility to discover optimal steps for a particular part of practical
methods, such as the LBL method.

### Usage

    $ rubiks-search <<END
    
           W Y W
           Y W Y
           W Y W
    
    R O R  B G B  O R O  G B G
    R O R  B G B  O R O  G B G
    R O R  B G B  O R O  G B G
    
           Y W Y
           W Y W
           Y W Y
    
    
           W W W
           W W W
           W W W
    
    O O O  G G G  R R R  B B B
    O O O  G G G  R R R  B B B
    O O O  G G G  R R R  B B B
    
           Y Y Y
           Y Y Y
           Y Y Y
    
    END

Output:

    # Depth: 1
    #  0 result(s)
    # Depth: 2
    #  0 result(s)
    # Depth: 3
    #  0 result(s)
    # Depth: 4
    F2 B2 R2 L2
    R2 L2 F2 B2
    #  2 result(s)

Note: Sample input data files are found in the `data` directory.

### Default Options

    $ rubiks-search -n1 -N8 -i -j -p -r -l -s -m

### Depth Options

    -n DEPTH   Set minimum depth (default = 1) and maximum depth (unless -N is given)
    -N DEPTH   Set maximum depth (default = 8)

### Input Options

    -i/-j   Read STDIN for the initial/target cube (default)
    -I/-J   Use the default cube as the initial/target input instead of reading STDIN

### Output Options

    -q/-Q   Enable/disable quiet mode to suppress printing progress in STDERR

### Turn Options

    -p/-P   Enable/disable primary (clockwise) quarter turns         | U F R L B D
    -r/-R   Enable/disable reverse (counter-clockwise) quarter turns | U' F' R' L' B' D'
    -l/-L   Enable/disable half (180 degrees) turns                  | U2 F2 R2 L2 B2 D2

### Slice Options

    -s/-S   Enable/disable single face turns                         | U F R L B D
    -m/-M   Enable/disable middle slice turns                        | M S E
    -d/-D   Enable/disable double-slice turns                        | u f r l b d
    -t/-T   Enable/disable cube rotations (triple-slice turns)       | x y z



## rubiks-enumerate

Enumerates all the combinations of steps that are used by `rubiks-search` algorithm.

### Usage

    $ rubiks-enumerate

Output:

    U 
    U'
    U2
    F 
    F'
    F2
    R 
    R'
    R2
    L 
    L'
    L2
    B 
    B'
    B2
    D 
    D'
    D2
    M 
    M'
    M2
    S 
    S'
    S2
    E 
    E'
    E2

### Default Options

    $ rubiks-enumerate -n1 -N1 -p -r -l -s -m

### Depth Options

    -n DEPTH   Set minimum depth (default = 1) and maximum depth (unless -N is given)
    -N DEPTH   Set maximum depth (default = 1)

### Turn Options

    -p/-P   Enable/disable primary (clockwise) quarter turns         | U F R L B D
    -r/-R   Enable/disable reverse (counter-clockwise) quarter turns | U' F' R' L' B' D'
    -l/-L   Enable/disable half (180 degrees) turns                  | U2 F2 R2 L2 B2 D2

### Slice Options

    -s/-S   Enable/disable single face turns                         | U F R L B D
    -m/-M   Enable/disable middle slice turns                        | M S E
    -d/-D   Enable/disable double-slice turns                        | u f r l b d
    -t/-T   Enable/disable cube rotations (triple-slice turns)       | x y z



## rubiks-scramble

Scrambles a Rubik's cube given as STDIN with random rotations.

### Usage

    $ rubiks-scramble <<END
    
           W W W
           W W W
           W W W
    
    O O O  G G G  R R R  B B B
    O O O  G G G  R R R  B B B
    O O O  G G G  R R R  B B B
    
           Y Y Y
           Y Y Y
           Y Y Y
    
    END

Alternative form to start with a default Rubik's cube:

    $ rubiks-scramble -I

Output:

           Y O O
           B W Y
           Y Y G
    
    R O O  B O W  O B W  B G B
    R O Y  G G W  B R B  R B G
    R Y W  R W R  W O G  Y W G
    
           G G B
           R Y W
           Y R O

### Default Options

    $ rubiks-scramble -n20 -i -o -p -r -l -s -m

### Depth Options

    -n DEPTH   Set the number of turns (default = 20)

### Input Options

    -i   Read STDIN for the initial cube (default)
    -I   Use the default cube as the initial input instead of reading STDIN

### Output Options

    -o/-O   Print the scrambled cube (default)
    -u/-U   Print the rotation steps used to scramble the cube
    -v/-V   Print the reverse steps to solve the scrambled cube

### Turn Options

    -p/-P   Enable/disable primary (clockwise) quarter turns         | U F R L B D
    -r/-R   Enable/disable reverse (counter-clockwise) quarter turns | U' F' R' L' B' D'
    -l/-L   Enable/disable half (180 degrees) turns                  | U2 F2 R2 L2 B2 D2

### Slice Options

    -s/-S   Enable/disable single face turns                         | U F R L B D
    -m/-M   Enable/disable middle slice turns                        | M S E
    -d/-D   Enable/disable double-slice turns                        | u f r l b d
    -t/-T   Enable/disable cube rotations (triple-slice turns)       | x y z



## rubiks-apply

Applies a given Rubik's cube with a given list of rotation steps. A result cube is printed per input line.

### Usage

    $ rubiks-apply <<END
    
           W W W
           W W W
           W W W
    
    O O O  G G G  R R R  B B B
    O O O  G G G  R R R  B B B
    O O O  G G G  R R R  B B B
    
           Y Y Y
           Y Y Y
           Y Y Y
    
    F2 B2 R2 L2
    
    END

Alternative form to start with a default Rubik's cube:

    $ rubiks-apply -I <<END
    
    F2 B2 R2 L2
    
    END

Output:

           W Y W
           Y W Y
           W Y W
    
    R O R  B G B  O R O  G B G
    R O R  B G B  O R O  G B G
    R O R  B G B  O R O  G B G
    
           Y W Y
           W Y W
           Y W Y

### Default Options

    $ rubiks-apply -i

### Input Options

    -i   Read STDIN for the initial cube (default)
    -I   Use the default cube as the initial input instead of reading STDIN



## rubiks-reverse

Reverses a given list of rotation steps in such a way that the reverse steps can be used to revert the cube after
applying the steps.

### Usage

    $ rubiks-reverse <<END
    
    R  L' M2 U' F  S2
    
    END

Output:

    S2 F' U  M2 L  R'



## rubiks-mirror

Generates mirrored steps of given rotation steps. A mirror is based on a perspective view from the direction at the
corner of `U`, `F` and `R` where the left and right hand sides (`F` and `R`) are inverted.

### Usage

    $ rubiks-mirror <<END
    
    R  L' M2 U' F  S2
    
    END

Output:

    F' B  S2 U  R' M2



## Cube Notation

A Rubik's cube is represented by 54 characters in the order of the projected diagram depicted as below:

           W W W
           W W W
           W W W
    
    O O O  G G G  R R R  B B B
    O O O  G G G  R R R  B B B
    O O O  G G G  R R R  B B B
    
           Y Y Y
           Y Y Y
           Y Y Y

The above example intentionally uses color code, `W` for white, `G` for green, `R` for red, `O` for orange,
`B` for blue, and `Y` for yellow.
However, all the CLI commands are designed in a way that any arbitrary characters are accepted for any squares,
even without checking the physically possible configurations.

For example, some other character (`.` in the below) can represent yet unknown or variable square:

           W W W
           W W W
           W W W
    
    O O O  G G G  R R R  B B B
    . O .  . G .  . R .  . B .
    . . .  . . .  . . .  . . .
    
           . . .
           . . .
           . . .

Below is another example that represents unique squares to keep track of all the places distinctively:

           A B C
           D E F
           G H I
    
    a b c  J K L  S T U  j k l
    d e f  M N O  V W X  m n o
    g h i  P Q R  Y Z !  p q r
    
           s t u
           v w x
           y z ?

When a program (such as `rubiks-search`) reads a cube notation from STDIN, it simply picks up 54 characters,
excluding whitespaces.
Thus, the input can alternatively be as compact as below:

    WWWWWWWWW
    OOOGGGRRRBBB
    OOOGGGRRRBBB
    OOOGGGRRRBBB
    YYYYYYYYY

Note this is *not* the same order as listing the characters face by face.

    W W W W W W W W W
    O O O O O O O O O
    G G G G G G G G G
    R R R R R R R R R
    B B B B B B B B B
    Y Y Y Y Y Y Y Y Y
    # This does not work as intended.

The actual face orientations are interpreted as below:

              -------
             |       |
             |   U   |
             |  [0]  |
      ------- ------- ------- -------
     |       |       |       |       |
     |   L   |   F   |   R   |   B   |
     |  [3]  |  [1]  |  [2]  |  [4]  |
      ------- ------- ------- -------
             |       |
             |   D   |
             |  [5]  |
              -------

where `U` is for Up, `F` is for Front, `R` is for Right, `L` is for Left, `B` is for Back, and `D` is for Down.
The index subscripts indicate the order of the internal data structure.

Further broken down, each square in a face is indexed as below:

              -------
             | 0 1 2 |
             | 3 4 5 |
             | 6 7 8 |
      ------- ------- ------- -------
     | 0 1 2 | 0 1 2 | 0 1 2 | 0 1 2 |
     | 3 4 5 | 3 4 5 | 3 4 5 | 3 4 5 |
     | 6 7 8 | 6 7 8 | 6 7 8 | 6 7 8 |
      ------- ------- ------- -------
             | 0 1 2 |
             | 3 4 5 |
             | 6 7 8 |
              -------



## Move Notation

Single-face turns are represented by the faces that are rotated:

    U - Up
    F - Front
    R - Right
    L - Left
    B - Back
    D - Down

The direction of the turn is *clockwise* unless the notations are annotated:

    U  - Clockwise quarter turn
    U' - Counter-clockwise quarter turn
    U2 - Half turn

Middle-slice turns are represented by additional three characters:

    M - Middle   (the layer between L and R; turn direction as L)
    S - Standing (the layer between F and B; turn direction as F)
    E - Equator  (the layer between U and D; turn direction as D)

Double-slice turns are represented by lower case letters:

    u - Up    (U + E')
    f - Front (F + S)
    r - Right (R + M')
    l - Left  (L + M)
    b - Back  (B + S')
    d - Down  (D + E)

Triple-slice turns (cube rotations) are represented by x,y,z-axis characters:

    x - Rotate the entire cube on R
    y - Rotate the entire cube on U
    z - Rotate the entire cube on F

A sequence of move steps are represented by multiple turn symbols, separated by white-spaces:

    U F' M2 u y' L
