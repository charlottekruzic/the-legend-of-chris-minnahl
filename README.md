# The Legend Of Chris Minnahl

**Jeu d'infiltration stratégique développé en Licence 3 Informatique à l'Université de Franche-Comté, encadré par Julien Bernard, maître de conférences.**

## Description
The Legend Of Chris Minnahl est un jeu vidéo d'infiltration stratégique où le joueur doit naviguer discrètement à travers un musée pour voler des diamants tout en évitant les gardes. Le jeu est développé en C++ et utilise la bibliothèque [GameDev Framework](https://gamedevframework.github.io/).

## Membres de l'équipe
- Gurnaud Jade
- Turan Baturay
- Kruzic Charlotte

## Fonctionnalités
- Déplacement du joueur à travers diverses salles du musée.
- Éviter les gardes en utilisant des gadgets et des transformations en statue.
- Collecte de diamants pour compléter chaque niveau.
- Visualisation via une mini-carte, sans révéler la position des gardes.

## Architecture du jeu
- GameManager : Gère les transitions entre les différentes scènes du jeu et le cycle de vie global de l'application.
- Scènes : Multiples scènes comme la scène du jeu, la scène de pause, et la scène de visualisation de la mini-carte.
- ResourceManager : Gestion optimisée des ressources telles que textures, sons et polices.
- Classes spécifiques : Player, Guard, Wall et d'autres classes modélisant les éléments interactifs du jeu.

## Installation
Pour jouer à The Legend Of Chris Minnahl, suivez ces étapes :

1. Clonez le dépôt GitHub :
   ```bash
   git clone https://github.com/charlottekruzic/TheLegendOfChrisMinnahl.git
   ```
2. Naviguez dans le dossier du projet et compilez le code :
   ```bash
   cd TheLegendOfChrisMinnahl
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Exécutez le jeu :
   ```bash
   ./TheLegendOfChrisMinnahl
   ```

## Utilisation
Utilisez les touches directionnelles pour déplacer le joueur. Appuyez sur la touche `Espace` pour vous transformer en statue et sur `M` pour afficher la mini-carte.

## Documentation additionnelle
Pour plus de détails sur la conception et l'architecture du jeu, veuillez consulter le rapport complet fourni dans les ressources du projet ou accessible via [ce lien](https://github.com/charlottekruzic/TheLegendOfChrisMinnahl/blob/main/rapport_gurnaud_turan_kruzic.pdf).