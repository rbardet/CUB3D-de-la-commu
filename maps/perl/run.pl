#!/usr/bin/perl
use strict;
use warnings;
use Term::ANSIColor;
use POSIX qw(strftime);

#######################################################
#                 PRESETS CONFIGURABLES               #
#######################################################

my %presets = (
    # 1. Petit labyrinthe classique
    1 => {
        name => "Labyrinthe classique",
        description => "Petit labyrinthe avec couloirs étroits et nombreuses intersections",
        map_width      => [30, 50],
        map_height     => [30, 50],
        rooms         => [8, 12],
        room_width    => [3, 5],
        room_height   => [3, 5],
        corridor_size => 1,
        colors        => {
            floor => [100, 150],   # Tons terreux
            ceil  => [180, 220]    # Tons clairs
        }
    },

    # 2. Donjon médiéval
    2 => {
        name => "Donjon médiéval",
        description => "Salles carrées reliées par des couloirs droits",
        map_width      => [40, 60],
        map_height     => [40, 60],
        rooms         => [5, 8],
        room_width    => [5, 8],
        room_height   => [5, 8],
        corridor_size => 2,
        colors        => {
            floor => [80, 120],    # Pierre grise
            ceil  => [40, 80]      # Pierre sombre
        }
    },

    # 3. Caverne naturelle
    3 => {
        name => "Caverne naturelle",
        description => "Formes organiques avec couloirs sinueux",
        map_width      => [50, 80],
        map_height     => [50, 80],
        rooms         => [6, 10],
        room_width    => [4, 10],
        room_height   => [4, 10],
        corridor_size => 3,
        colors        => {
            floor => [60, 100],    # Terre brune
            ceil  => [30, 60]      # Roche noire
        }
    },

    # 4. Fort militaire
    4 => {
        name => "Fort militaire",
        description => "Structure symétrique avec couloirs larges",
        map_width      => [60, 80],
        map_height     => [60, 80],
        rooms         => [8, 12],
        room_width    => [6, 10],
        room_height   => [6, 10],
        corridor_size => 4,
        colors        => {
            floor => [120, 160],   # Béton clair
            ceil  => [80, 120]     # Métal
        }
    },

    # 5. Ruines anciennes
    5 => {
        name => "Ruines anciennes",
        description => "Salles irrégulières avec murs partiellement effondrés",
        map_width      => [70, 100],
        map_height     => [70, 100],
        rooms         => [10, 15],
        room_width    => [4, 8],
        room_height   => [4, 8],
        corridor_size => 2,
        colors        => {
            floor => [100, 140],   # Pierre usée
            ceil  => [60, 100]     # Pierre moussue
        }
    },

    # 6. Vaisseau spatial
    6 => {
        name => "Vaisseau spatial",
        description => "Couloirs très étroits et nombreuses petites salles",
        map_width      => [40, 60],
        map_height     => [40, 60],
        rooms         => [15, 20],
        room_width    => [2, 4],
        room_height   => [2, 4],
        corridor_size => 1,
        colors        => {
            floor => [30, 70],    # Métal sombre
            ceil  => [150, 200]   # Lumière bleutée
        }
    },

    # 7. Temple antique
    7 => {
        name => "Temple antique",
        description => "Grandes salles monumentales avec longs couloirs",
        map_width      => [80, 120],
        map_height     => [80, 120],
        rooms         => [4, 6],
        room_width    => [10, 15],
        room_height   => [10, 15],
        corridor_size => 3,
        colors        => {
            floor => [150, 190],  # Marbre
            ceil  => [120, 160]   # Or
        }
    },

    # 8. Mines abandonnées
    8 => {
        name => "Mines abandonnées",
        description => "Couloirs très longs et salles rectangulaires",
        map_width      => [100, 150],
        map_height     => [30, 50],
        rooms         => [8, 12],
        room_width    => [5, 15],
        room_height   => [3, 6],
        corridor_size => 2,
        colors        => {
            floor => [40, 80],    # Charbon
            ceil  => [20, 40]     # Noir profond
        }
    },

    # 9. Jardin mystique
    9 => {
        name => "Jardin mystique",
        description => "Salles circulaires avec chemins sinueux",
        map_width      => [50, 70],
        map_height     => [50, 70],
        rooms         => [6, 9],
        room_width    => [6, 9],
        room_height   => [6, 9],
        corridor_size => 2,
        colors        => {
            floor => [80, 120],   # Herbe
            ceil  => [180, 220]   # Ciel
        }
    },

    # 10. Catacombes
    10 => {
        name => "Catacombes",
        description => "Réseau dense de petites salles et couloirs",
        map_width      => [60, 90],
        map_height     => [60, 90],
        rooms         => [20, 30],
        room_width    => [2, 4],
        room_height   => [2, 4],
        corridor_size => 1,
        colors        => {
            floor => [50, 90],    # Terre humide
            ceil  => [10, 30]     # Noir absolu
        }
    },
    # 11. Donjon
    11 => {
        name => "carte vraiment géante",
        description => "Grande structure avec salles rectangulaires",
        map_width      => [300, 500],
        map_height     => [300, 500],
        rooms         => [15, 20],
        room_width    => [5, 10],
        room_height   => [5, 10],
        corridor_size => 3,
        colors        => {
            floor => [100, 140],   # Pierre grise
            ceil  => [60, 100]     # Pierre sombre
        }
    }
);

# Textures communes à tous les presets
my @textures = (
    "NO      ./graphic/NO.png",
    "SO      ./graphic/SO.png",
    "WE      ./graphic/WE.png",
    "EA      ./graphic/EA.png",
    "DO      ./graphic/DO.png"
);

my @start_directions = ('N', 'S', 'E', 'W');

#######################################################
#                 FONCTIONS UTILITAIRES               #
#######################################################

sub show_menu {
    print color('bold green') . "\n=== GENERATEUR DE CARTE CUB3D ===\n" . color('reset');
    print "Choisissez un preset de configuration:\n";

    foreach my $key (sort keys %presets) {
        printf "[%d] %-20s (Salles: %d-%d, Taille: %d-%dx%d-%d)\n",
               $key, $presets{$key}{name},
               $presets{$key}{rooms}[0], $presets{$key}{rooms}[1],
               $presets{$key}{map_width}[0], $presets{$key}{map_width}[1],
               $presets{$key}{map_height}[0], $presets{$key}{map_height}[1];
    }

    print "\nVotre choix [1-" . scalar(keys %presets) . "]: ";
    my $choice = <STDIN>;
    chomp $choice;

    return $choice if exists $presets{$choice};
    return 1; # Default si mauvais choix
}

sub dig_room {
    my ($map, $width, $height, $x1, $y1, $x2, $y2) = @_;
    for my $y ($y1..$y2) {
        for my $x ($x1..$x2) {
            $map->[$y][$x] = '0' if $x > 0 && $x < $width-1 && $y > 0 && $y < $height-1;
        }
    }
}

sub dig_corridor {
    my ($map, $width, $height, $corridor_size, $x1, $y1, $x2, $y2) = @_;
    my $offset = int($corridor_size / 2);

    if ($x1 < $x2) {
        for my $x ($x1..$x2) {
            for my $dy (-$offset..$offset) {
                my $ny = $y1 + $dy;
                $map->[$ny][$x] = '0' if $x > 0 && $x < $width-1 && $ny > 0 && $ny < $height-1;
            }
        }
    } else {
        for my $x ($x2..$x1) {
            for my $dy (-$offset..$offset) {
                my $ny = $y1 + $dy;
                $map->[$ny][$x] = '0' if $x > 0 && $x < $width-1 && $ny > 0 && $ny < $height-1;
            }
        }
    }

    if ($y1 < $y2) {
        for my $y ($y1..$y2) {
            for my $dx (-$offset..$offset) {
                my $nx = $x2 + $dx;
                $map->[$y][$nx] = '0' if $nx > 0 && $nx < $width-1 && $y > 0 && $y < $height-1;
            }
        }
    } else {
        for my $y ($y2..$y1) {
            for my $dx (-$offset..$offset) {
                my $nx = $x2 + $dx;
                $map->[$y][$nx] = '0' if $nx > 0 && $nx < $width-1 && $y > 0 && $y < $height-1;
            }
        }
    }
}

sub generate_map {
    my $preset = shift;

    # Récupération des paramètres du preset
    my ($min_width, $max_width) = @{$preset->{map_width}};
    my ($min_height, $max_height) = @{$preset->{map_height}};
    my ($min_rooms, $max_rooms) = @{$preset->{rooms}};
    my ($min_room_w, $max_room_w) = @{$preset->{room_width}};
    my ($min_room_h, $max_room_h) = @{$preset->{room_height}};
    my $corridor_size = $preset->{corridor_size};
    my ($floor_min, $floor_max) = @{$preset->{colors}{floor}};
    my ($ceil_min, $ceil_max) = @{$preset->{colors}{ceil}};

    # Génération des dimensions aléatoires
    my $width  = $min_width  + int(rand($max_width  - $min_width  + 1));
    my $height = $min_height + int(rand($max_height - $min_height + 1));
    my $num_rooms = $min_rooms + int(rand($max_rooms - $min_rooms + 1));

    # Génération des couleurs
    my $floor_color = sprintf("%d,%d,%d",
        $floor_min + int(rand($floor_max - $floor_min + 1)),
        $floor_min + int(rand($floor_max - $floor_min + 1)),
        $floor_min + int(rand($floor_max - $floor_min + 1)));

    my $ceiling_color = sprintf("%d,%d,%d",
        $ceil_min + int(rand($ceil_max - $ceil_min + 1)),
        $ceil_min + int(rand($ceil_max - $ceil_min + 1)),
        $ceil_min + int(rand($ceil_max - $ceil_min + 1)));

    # Initialisation de la carte
    my @map;
    for my $y (0..$height-1) {
        for my $x (0..$width-1) {
            $map[$y][$x] = ' ';
        }
    }

    # Génération des salles
    my @rooms;
    for (1..$num_rooms) {
        my $w = $min_room_w + int(rand($max_room_w - $min_room_w + 1));
        my $h = $min_room_h + int(rand($max_room_h - $min_room_h + 1));
        my $x = 1 + int(rand($width - $w - 2));
        my $y = 1 + int(rand($height - $h - 2));
        dig_room(\@map, $width, $height, $x, $y, $x+$w, $y+$h);
        push @rooms, { x => $x+int($w/2), y => $y+int($h/2) };
    }

    # Connexion des salles avec des couloirs
    for my $i (0..$#rooms-1) {
        dig_corridor(\@map, $width, $height, $corridor_size,
                    $rooms[$i]{x}, $rooms[$i]{y},
                    $rooms[$i+1]{x}, $rooms[$i+1]{y});
    }

    # Placement du point de départ et de la sortie
    $map[$rooms[0]{y}][$rooms[0]{x}] = $start_directions[int(rand(@start_directions))];
    $map[$rooms[-1]{y}][$rooms[-1]{x}] = 'D';

    # Ajout des murs autour des zones creusées
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

    # Nettoyage des murs isolés
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

    # Retourne les données de la carte
    return {
        textures => \@textures,
        floor    => $floor_color,
        ceiling  => $ceiling_color,
        map      => \@map
    };
}

sub save_to_file {
    my ($map_data, $filename) = @_;

    open(my $fh, '>', $filename) or die "Impossible d'écrire dans le fichier $filename: $!";

    print $fh join("\n", @{$map_data->{textures}}) . "\n\n";
    print $fh "F $map_data->{floor}\n";
    print $fh "C $map_data->{ceiling}\n\n";

    for my $row (@{$map_data->{map}}) {
        print $fh join('', @$row) . "\n";
    }

    close($fh);
}

#######################################################
#                 PROGRAMME PRINCIPAL                 #
#######################################################

# Affiche le menu et récupère le choix
my $preset_choice = show_menu();
my $preset = $presets{$preset_choice};

print color('yellow') . "\nGénération d'une carte avec le preset: " .
      color('bold cyan') . "$preset->{name}\n" . color('reset');

# Génère la carte
my $map_data = generate_map($preset);

# Crée un nom de fichier avec timestamp
my $timestamp = strftime("%Y%m%d_%H%M%S", localtime);
my $filename = "$timestamp.cub";

# Sauvegarde dans le fichier
save_to_file($map_data, $filename);

print color('bold green') . "\nCarte générée avec succès dans le fichier: $filename\n" . color('reset');
