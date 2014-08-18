#!/usr/bin/perl
use strict;
use warnings;

use Test::More tests => 5;
use FindBin;
use IPC::Open2;

sub test {
    my ($input, $expected) = @_;

    open2(my $in, my $out, "$FindBin::Bin/../bin/rubiks-reverse");
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
test("R  S' R' U  R  S  R'\n", "R  S' R' U' R  S  R'\n");

test(<<INPUT, <<OUTPUT);
F2 M' U  B2 S' U' F 
D  E  B' F' M2 D 

S  L' S2

INPUT
F' U  S  B2 U' M  F2
D' M2 F  B  E' D'

S2 L  S'

OUTPUT
