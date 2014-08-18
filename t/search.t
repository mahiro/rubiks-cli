#!/usr/bin/perl
use strict;
use warnings;

use Test::More tests => 3;
use FindBin;
use IPC::Open2;

sub test {
    my ($input, $expected) = @_;

    open2(my $in, my $out, "$FindBin::Bin/../bin/rubiks-search 2>/dev/null");
    print $out $input;
    close $out;

    my $actual = join('', <$in>);
    close $in;

    local $Test::Builder::Level = $Test::Builder::Level + 1;
    is($actual, $expected);
}

test(<<INPUT, <<OUTPUT);
       G . .
       . . .
       . . .

. . .  . G G  . . .  . . .
. . .  G G G  . . .  . . .
. . .  G G G  . . .  . . .

       . . .
       . . .
       . . .


       . . .
       . . .
       . . .

. . .  G G G  . . .  . . .
. . .  G G G  . . .  . . .
. . .  G G G  . . .  . . .

       . . .
       . . .
       . . .

INPUT
U  B  U'
OUTPUT

test(<<INPUT, <<OUTPUT);
       . . .
       . . .
       . . .

. . .  . . .  . . .  . . .
O O R  G G G  O R R  B B B
O O O  G G G  R R R  B B B

       Y Y Y
       Y Y Y
       Y Y Y


       . . .
       . . .
       . . .

. . .  . . .  . . .  . . .
O O O  G G G  R R R  B B B
O O O  G G G  R R R  B B B

       Y Y Y
       Y Y Y
       Y Y Y

INPUT
F2 U2 F2 U2 F2
B2 D2 F2 D2 B2
OUTPUT

test(<<INPUT, <<OUTPUT);
       W W W
       W W W
       W W W

O O R  B G G  R R O  G B B
. . .  . . .  . . .  . . .
. . .  . . .  . . .  . . .

       . . .
       . . .
       . . .


       W W W
       W W W
       W W W

O O O  G G G  R R R  B B B
. . .  . . .  . . .  . . .
. . .  . . .  . . .  . . .

       . . .
       . . .
       . . .

INPUT
F' B' D2 F  B 
F2 S' R2 F2 S 
R  L  D2 R' L'
R2 M' F2 R2 M 
L2 M  B2 L2 M'
B2 S  L2 B2 S'
OUTPUT
