#!/usr/bin/perl
use strict;
use warnings;

use Test::More tests => 5;
use FindBin;
use IPC::Open2;

sub test {
    my ($input, $expected) = @_;

    open2(my $in, my $out, "$FindBin::Bin/../bin/rubiks-mirror");
    print $out $input;
    close $out;

    my $actual = join('', <$in>);
    close $in;

    local $Test::Builder::Level = $Test::Builder::Level + 1;
    is($actual, $expected);
}

test("U \n", "U'\n");
test("U'\n", "U \n");
test("U2\n", "U2\n");
test("R  S' R' U  R  S  R'\n", "F' M' F  U' F' M  F \n");

test(<<INPUT, <<OUTPUT);
F2 M' U  B2 S' U' F 
D  E  B' F' M2 D 

S  L' S2

INPUT
R2 S' U' L2 M' U  R'
D' E' L  R  S2 D'

M  B  M2

OUTPUT
