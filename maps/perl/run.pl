#!/usr/bin/perl
#for i in {1..20}; do perl run.pl > "$i.cub"; done
use strict;
use warnings;

# Configuration
my $corridor_thickness = 4;  # 1 = couloirs étroits, 3 = couloirs larges

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
# Initialiser avec des espaces
for my $y (0..$height-1) {
    for my $x (0..$width-1) {
        $map[$y][$x] = ' ';
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

    # Élargir les couloirs selon la variable $corridor_thickness
    my $offset = int($corridor_thickness / 2);

    if ($x1 < $x2) {
        for my $x ($x1..$x2) {
            for my $dy (-$offset..$offset) {
                my $ny = $y1 + $dy;
                $map[$ny][$x] = '0' if $x > 0 && $x < $width-1 && $ny > 0 && $ny < $height-1;
            }
        }
    } else {
        for my $x ($x2..$x1) {
            for my $dy (-$offset..$offset) {
                my $ny = $y1 + $dy;
                $map[$ny][$x] = '0' if $x > 0 && $x < $width-1 && $ny > 0 && $ny < $height-1;
            }
        }
    }

    if ($y1 < $y2) {
        for my $y ($y1..$y2) {
            for my $dx (-$offset..$offset) {
                my $nx = $x2 + $dx;
                $map[$y][$nx] = '0' if $nx > 0 && $nx < $width-1 && $y > 0 && $y < $height-1;
            }
        }
    } else {
        for my $y ($y2..$y1) {
            for my $dx (-$offset..$offset) {
                my $nx = $x2 + $dx;
                $map[$y][$nx] = '0' if $nx > 0 && $nx < $width-1 && $y > 0 && $y < $height-1;
            }
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

# Ajouter seulement les murs nécessaires
for my $y (1..$height-2) {
    for my $x (1..$width-2) {
        if ($map[$y][$x] eq '0') {
            $map[$y-1][$x] = '1' if $map[$y-1][$x] eq ' ';
            $map[$y+1][$x] = '1' if $map[$y+1][$x] eq ' ';
            $map[$y][$x-1] = '1' if $map[$y][$x-1] eq ' ';
            $map[$y][$x+1] = '1' if $map[$y][$x+1] eq ' ';
        }
    }
}

# Nettoyer les '1' isolés qui ne bordent aucun '0'
for my $y (1..$height-2) {
    for my $x (1..$width-2) {
        if ($map[$y][$x] eq '1') {
            my $has_adjacent_zero = 0;
            $has_adjacent_zero ||= ($map[$y-1][$x] eq '0');
            $has_adjacent_zero ||= ($map[$y+1][$x] eq '0');
            $has_adjacent_zero ||= ($map[$y][$x-1] eq '0');
            $has_adjacent_zero ||= ($map[$y][$x+1] eq '0');
            $map[$y][$x] = ' ' unless $has_adjacent_zero;
        }
    }
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
