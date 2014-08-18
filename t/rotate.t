#!/usr/bin/perl
use strict;
use warnings;

use Test::More tests => 27;
use FindBin;
use IPC::Open2;

my $orig = <<END;
       A B C
       D E F
       G H I

a b c  J K L  S T U  j k l
d e f  M N O  V W X  m n o
g h i  P Q R  Y Z !  p q r

       s t u
       v w x
       y z ?

END

sub test {
    my ($proc, $expected) = @_;

    open2(my $in, my $out, "$FindBin::Bin/../bin/rubiks-apply");
    print $out $orig;
    print $out $proc;
    close $out;

    my $actual = join('', <$in>);
    close $in;

    local $Test::Builder::Level = $Test::Builder::Level + 1;
    is($actual, $expected);
}

test("U", <<END);
       G D A
       H E B
       I F C

J K L  S T U  j k l  a b c
d e f  M N O  V W X  m n o
g h i  P Q R  Y Z !  p q r

       s t u
       v w x
       y z ?

END

test("U2", <<END);
       I H G
       F E D
       C B A

S T U  j k l  a b c  J K L
d e f  M N O  V W X  m n o
g h i  P Q R  Y Z !  p q r

       s t u
       v w x
       y z ?

END

test("U'", <<END);
       C F I
       B E H
       A D G

j k l  a b c  J K L  S T U
d e f  M N O  V W X  m n o
g h i  P Q R  Y Z !  p q r

       s t u
       v w x
       y z ?

END

test("F", <<END);
       A B C
       D E F
       i f c

a b s  P M J  G T U  j k l
d e t  Q N K  H W X  m n o
g h u  R O L  I Z !  p q r

       Y V S
       v w x
       y z ?

END

test("F2", <<END);
       A B C
       D E F
       u t s

a b Y  R Q P  i T U  j k l
d e V  O N M  f W X  m n o
g h S  L K J  c Z !  p q r

       I H G
       v w x
       y z ?

END

test("F'", <<END);
       A B C
       D E F
       S V Y

a b I  L O R  u T U  j k l
d e H  K N Q  t W X  m n o
g h G  J M P  s Z !  p q r

       c f i
       v w x
       y z ?

END

test("R", <<END);
       A B L
       D E O
       G H R

a b c  J K u  Y V S  I k l
d e f  M N x  Z W T  F n o
g h i  P Q ?  ! X U  C q r

       s t p
       v w m
       y z j

END

test("R2", <<END);
       A B u
       D E x
       G H ?

a b c  J K p  ! Z Y  R k l
d e f  M N m  X W V  O n o
g h i  P Q j  U T S  L q r

       s t C
       v w F
       y z I

END

test("R'", <<END);
       A B p
       D E m
       G H j

a b c  J K C  U X !  ? k l
d e f  M N F  T W Z  x n o
g h i  P Q I  S V Y  u q r

       s t L
       v w O
       y z R

END

test("L", <<END);
       r B C
       o E F
       l H I

g d a  A K L  S T U  j k y
h e b  D N O  V W X  m n v
i f c  G Q R  Y Z !  p q s

       J t u
       M w x
       P z ?

END

test("L2", <<END);
       s B C
       v E F
       y H I

i h g  r K L  S T U  j k P
f e d  o N O  V W X  m n M
c b a  l Q R  Y Z !  p q J

       A t u
       D w x
       G z ?

END

test("L'", <<END);
       J B C
       M E F
       P H I

c f i  s K L  S T U  j k G
b e h  v N O  V W X  m n D
a d g  y Q R  Y Z !  p q A

       r t u
       o w x
       l z ?

END

test("B", <<END);
       U X !
       D E F
       G H I

C b c  J K L  S T ?  p m j
B e f  M N O  V W z  q n k
A h i  P Q R  Y Z y  r o l

       s t u
       v w x
       a d g

END

test("B2", <<END);
       ? z y
       D E F
       G H I

! b c  J K L  S T g  r q p
X e f  M N O  V W d  o n m
U h i  P Q R  Y Z a  l k j

       s t u
       v w x
       C B A

END

test("B'", <<END);
       g d a
       D E F
       G H I

y b c  J K L  S T A  l o r
z e f  M N O  V W B  k n q
? h i  P Q R  Y Z C  j m p

       s t u
       v w x
       ! X U

END

test("D", <<END);
       A B C
       D E F
       G H I

a b c  J K L  S T U  j k l
d e f  M N O  V W X  m n o
p q r  g h i  P Q R  Y Z !

       y v s
       z w t
       ? x u

END

test("D2", <<END);
       A B C
       D E F
       G H I

a b c  J K L  S T U  j k l
d e f  M N O  V W X  m n o
Y Z !  p q r  g h i  P Q R

       ? z y
       x w v
       u t s

END

test("D'", <<END);
       A B C
       D E F
       G H I

a b c  J K L  S T U  j k l
d e f  M N O  V W X  m n o
P Q R  Y Z !  p q r  g h i

       u x ?
       t w z
       s v y

END

test("M", <<END);
       A q C
       D n F
       G k I

a b c  J B L  S T U  j z l
d e f  M E O  V W X  m w o
g h i  P H R  Y Z !  p t r

       s K u
       v N x
       y Q ?

END

test("M2", <<END);
       A t C
       D w F
       G z I

a b c  J q L  S T U  j Q l
d e f  M n O  V W X  m N o
g h i  P k R  Y Z !  p K r

       s B u
       v E x
       y H ?

END

test("M'", <<END);
       A K C
       D N F
       G Q I

a b c  J t L  S T U  j H l
d e f  M w O  V W X  m E o
g h i  P z R  Y Z !  p B r

       s q u
       v n x
       y k ?

END

test("S", <<END);
       A B C
       h e b
       G H I

a v c  J K L  S D U  j k l
d w f  M N O  V E X  m n o
g x i  P Q R  Y F !  p q r

       s t u
       Z W T
       y z ?

END

test("S2", <<END);
       A B C
       x w v
       G H I

a Z c  J K L  S h U  j k l
d W f  M N O  V e X  m n o
g T i  P Q R  Y b !  p q r

       s t u
       F E D
       y z ?

END

test("S'", <<END);
       A B C
       T W Z
       G H I

a F c  J K L  S x U  j k l
d E f  M N O  V w X  m n o
g D i  P Q R  Y v !  p q r

       s t u
       b e h
       y z ?

END

test("E", <<END);
       A B C
       D E F
       G H I

a b c  J K L  S T U  j k l
m n o  d e f  M N O  V W X
g h i  P Q R  Y Z !  p q r

       s t u
       v w x
       y z ?

END

test("E2", <<END);
       A B C
       D E F
       G H I

a b c  J K L  S T U  j k l
V W X  m n o  d e f  M N O
g h i  P Q R  Y Z !  p q r

       s t u
       v w x
       y z ?

END

test("E'", <<END);
       A B C
       D E F
       G H I

a b c  J K L  S T U  j k l
M N O  V W X  m n o  d e f
g h i  P Q R  Y Z !  p q r

       s t u
       v w x
       y z ?

END
