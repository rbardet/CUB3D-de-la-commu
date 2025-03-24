# cub3D – 42 School Project

![cub3D Screenshot](assets/screenshot.png) <!-- Ajoute une image si possible -->

**Développez un jeu de type « labyrinthe 3D » en raycasting, inspiré de Wolfenstein 3D.**

---

## 📝 Table des matières
- [Introduction](#-introduction)
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [Contrôles](#-contrôles)
- [Approche Technique](#-approche-technique)
- [Crédits](#-crédits)

---

## 🚀 Introduction

**cub3D** est un projet de la branche graphique de 42, où vous recréez un moteur 3D simplifié en utilisant la technique du **raycasting**.
L'objectif est de générer dynamiquement une vue 3D à partir d'une carte 2D, avec des textures, des sprites, et une gestion de la lumière.

---

## ✨ Features

- **Rendu 3D en temps réel** avec textures muraux personnalisables.
- **Gestion des sprites** pour des éléments dynamiques (ex: objets, ennemis).
- **Mouvements fluides** : déplacements avant/arrière, rotations, strafing.
- **Système de collision** avec les murs.
- **Parsing de carte** au format `.cub` avec validation des erreurs.
- **Support de la souris** pour une rotation intuitive.
- **Effets de lumière** : ombres, couleurs de plafond/sol.

---

## 🔧 Installation

### Prérequis
- **macOS** (testé sur Big Sur et versions ultérieures).
- **MiniLibX** (bibliothèque graphique de 42).
- **Compilateur C** (gcc/clang).

### Étapes
1. Clone le dépôt :
   ```bash
   git clone https://github.com/tonusername/cub3D.git && cd cub3D
   ```
2. Compile le projet :
   ```bash
   make
   ```
3. Lance le jeu avec une carte :
   ```bash
   ./cub3D maps/map1.cub
   ```

---

## 🕹️ Usage

### Format de la carte (`.cub`)
- Définit les textures, couleurs, et la structure du labyrinthe.
- Exemple :
  ```
  NO ./textures/north_wall.xpm
  SO ./textures/south_wall.xpm
  F 220,100,0
  C 135,206,250
  11111
  10001
  1N 01
  11111
  ```

### Commandes
```bash
./cub3D [--save] <fichier.cub>  # --save génère un screenshot BMP
```

---

## 🎮 Contrôles

| **Action**         | **Touche**       |
|--------------------|------------------|
| Avancer           | `W` ou `↑`       |
| Reculer           | `S` ou `↓`       |
| Rotation gauche   | `A` ou `←`       |
| Rotation droite   | `D` ou `→`       |
| Quitter           | `ESC` ou `Croix` |

---

## 🧠 Approche Technique

### Raycasting
- **Algorithme DDA** (Digital Differential Analyzer) pour détecter les murs.
- **Calculs optimisés** : précalcul des distances, gestion des angles.
- **Textures mappées** avec interpolation pour éviter les distortions.

### Structure du Code
- **Parsing** : Validation syntaxique/sémantique des fichiers `.cub`.
- **Gestion des erreurs** : Messages clairs et sortie propre.
- **Architecture** :
  ```
  cub3D/
  ├── includes/         # Headers
  ├── srcs/             # Code source
  │   ├── raycasting/   # Raycasting
  │   ├── rendering/    # Rendering
  │   └── parsing/      # Lecture de carte
  └── textures/         # Fichiers XPM
  ```

---

## 👥 Crédits

- **Auteur** : [rbardet](https://github.com/rbardet-) [throbert](https://github.com/throbert) [hdelacou](https://github.com/M-U-C-K-A)

---

🛠️ **Fait avec** : C, MiniLibX, et passion.
📜 **Conforme à la Norme 42** : Pas de fonctions interdites, code `-Wall -Wextra -Werror`.
