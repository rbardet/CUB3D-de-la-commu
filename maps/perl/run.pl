#!/usr/bin/perl
use strict;
use warnings;

my @textures = (
    "NO      ./graphic/NO.xpm",
    "SO      ./graphic/SO.xpm",
    "WE      ./graphic/WE.xpm",
    "EA      ./graphic/EA.xpm",
    "DO      ./graphic/DO.xpm"
);

my $floor_color = sprintf("%d,%d,%d", int(rand(128)) + 64, int(rand(128)) + 64, int(rand(128)) + 64);
my $ceiling_color = sprintf("%d,%d,%d", int(rand(128)) + 128, int(rand(128)) + 128, int(rand(128)) + 128);
my $width = 20 + int(rand(181));
my $height = 20 + int(rand(181));

my @map;
for my $y (0..$height-1) {
    for my $x (0..$width-1) {
        $map[$y][$x] = '1';
    }
}

sub dig_room {
    my ($x1, $y1, $x2, $y2) = @_;
    for my $y ($y1..$y2) {
        for my $x ($x1..$x2) {
            $map[$y][$x] = '0' if $x > 0 && $x < $width-1 && $y > 0 && $y < $height-1;
        }
    }
}

sub dig_corridor {
    my ($x1, $y1, $x2, $y2) = @_;
    if ($x1 < $x2) {
        for my $x ($x1..$x2) {
            $map[$y1][$x] = '0' if $x > 0 && $x < $width-1;
        }
    } else {
        for my $x ($x2..$x1) {
            $map[$y1][$x] = '0' if $x > 0 && $x < $width-1;
        }
    }
    if ($y1 < $y2) {
        for my $y ($y1..$y2) {
            $map[$y][$x2] = '0' if $y > 0 && $y < $height-1;
        }
    } else {
        for my $y ($y2..$y1) {
            $map[$y][$x2] = '0' if $y > 0 && $y < $height-1;
        }
    }
}

my @rooms;
for (1..8) {
    my $w = 3 + int(rand(8));
    my $h = 3 + int(rand(6));
    my $x = 1 + int(rand($width - $w - 2));
    my $y = 1 + int(rand($height - $h - 2));
    dig_room($x, $y, $x+$w, $y+$h);
    push @rooms, { x => $x+int($w/2), y => $y+int($h/2) };
}

for my $i (0..$#rooms-1) {
    dig_corridor($rooms[$i]{x}, $rooms[$i]{y}, $rooms[$i+1]{x}, $rooms[$i+1]{y});
}

my @directions = ('N', 'W', 'E', 'S');
$map[$rooms[0]{y}][$rooms[0]{x}] = $directions[int(rand(@directions))];
$map[$rooms[-1]{y}][$rooms[-1]{x}] = 'D';

for (1..30) {
    my $x = 1 + int(rand($width-2));
    my $y = 1 + int(rand($height-2));
    $map[$y][$x] = '1' if $map[$y][$x] eq '0';
}

print "NO      ./graphic/NO.xpm\n";
print "SO      ./graphic/SO.xpm\n";
print "WE      ./graphic/WE.xpm\n";
print "EA      ./graphic/EA.xpm\n";
print "DO      ./graphic/DO.xpm\n\n";

print "F $floor_color\n";
print "C $ceiling_color\n\n";

for my $row (@map) {
    print join('', @$row) . "\n";
}
