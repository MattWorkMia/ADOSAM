# A Dance of Sun and Moon

### Identifiant du projet: 33817

## Auteurs
- Marius Henriksen (P2202226)
- Matteo Miali (P2205226)

## Commandes de Compilation et d'Exécution
1. Faites en sorte d'avoir les libraires SDL2, SDL2_Image, SDL2_TTF, SDL2_Mixer d'installés sur votre systeme
2. Naviguez jusqu'au répertoire `adosam`. 
3. Exécutez `make clean` pour nettoyer les fichiers objets et l'exécutable `adosam`. (ceux deja existants ont ete compiles sur mac, si vous etes sur linux veuillez recompiler)
4. Exécutez `make` ou `make all` pour compiler.
5. Exécutez `make doc` pour générer la documentation.
6. Lancez l'application en exécutant `bin/adosam`.

## Utilisation de l'Application
- Appuyez sur la touche **Échap** pour quitter le jeu à tout moment.
- Dans le menu :
  - Cliquez sur les boutons **LEVEL 1**, **LEVEL 2** ou **QUITTER** (porte de sortie en haut à gauche de l'écran) avec la souris.
- Dans le jeu :
  - Appuyez sur **P** pour mettre en pause.
  - Appuyez sur n'importe quelle autre touche clavier pour passer d'une case à la suivante (*e.g. **ESPACE***).

- Dans le menu pause :
  - Appuyez sur **P** pour reprendre le niveau.
  - Cliquez sur le bouton **QUITTER** (porte de sortie, à gauche de l'icône Pause) pour revenir au menu principal.
  - Cliquez sur le bouton **RECOMMENCER** (flèche retour en arrière, à droite de l'icône Pause) pour recommencer le niveau.

## Comment joue-t-on ?
- Le nombre de vies est affiché en haut à gauche, à côté du coeur.
- Le score est affiché en haut à droite. 

- Le but est d'abord d'arriver jusqu'à la fin du niveau, puis de faire le meilleur score possible à la fin du niveau. 
- A chaque fois que l'astre en rotation (le Soleil ou la Lune) est pile au-dessus de la prochaine case, c'est l'autre qui devient l'astre en rotation. 
    - A ce moment, le joueur doit appuyer sur une touche clavier.
    - S'il appuie au même moment que le centre de rotation change, ou s'il a très peu de délai, le joueur gagne des points sans perdre de vie.
    -  Cependant, s'il appuie au trop tôt ou trop tard et que le délai entre l'input et le moment du changement de rotation est trop grand, le joueur perd une vie. 
    - Un texte apparaît lui annonçant s'il est en rythme ou non. 

- Si le joueur perd toutes ses vies, le niveau se termine. 

- Ecoutez bien le rythme de la musique pour rester en rythme dans le jeu !

## Liste des fonctionnalités
- **2 niveaux**. Possibilité d'en ajouter plus en ajoutant les données du niveau dans `data/` et en initialisant ce nouveau niveau et son bouton correctement dans le code.

- **Creation niveau**. Pour creer un niveau, le dossier map lie doit etre situé dans data/maps, il doit contenir un audio correspondant a la musique du niveau en .wav, un audio correspondant a l'effet sonore en .wav et enfin un fichier texte. Dans ce fichier texte, la premiere ligne doit etre le bpm du niveau, et pour chaque nouvelle case un retour a la ligne est demandé. La derniere case doit forcement etre un end. Pour ce qui est de l'ordre des cases celui-ci se doit d'etre logique (prenez exemple sur les niveaux deja existants), si l'odre n'est pas bon, la génération du niveau ne sera pas bonne. 

- **Possibilité de mettre le jeu en pause**, et de revenir au menu principal ou bien de recommencer le niveau.

- **Gestion du score**: Le score est basé sur une simple différence entre le BPM du niveau et le délai entre le moment d'input du joueur et le moment de changement de rotation. Une formule de score plus complexe pour remplacer ce système est possible en changeant une seule ligne de code (dans `level.cpp`).

- **Effets Sonores et Musique**: Effets sonores à chaque compte à rebours pour que le joueur comprenne le rythme de la musique et du niveau. Musique tout au long du niveau, en rythme avec la vitesse du joueur. Important pour une bonne expérience mais non-nécessaire (peut jouer sans le son).

- **Tuiles spéciales**: 3 tuiles ont un effet sur le joueur: les tuiles d'accélération, de ralentissement, et de changement de sens de rotation, pour éviter la répétitivité. Ces tuiles s'ajoutent aux tuiles classiques horizontales et verticales et aux tuiles de changement de direction (tuiles comportant un 'coin'). 

## Organisation de l'archive

- `a-dance-of-sun-and-moon/` : Le répertoire principal du projet.

  - `.vscode/` : Répertoire contenant la configuration de Visual Studio Code.

  - `readme.md` : Le fichier readme du projet.
  
  - `adosam/` : Répertoire contenant le code source et tous les fichiers nécessaires au projet.

    - `bin/` : Répertoire contenant l'exécutable `adosam` après compilation.
    - `obj/` : Répertoire contenant les fichiers objets après compilation.
    - `doc/` : Répertoire contenant la documentation générée, ainsi que la présentation pour la soutenance et le diagramme des classes UML.
    - `data/` : Répertoire contenant toutes les données nécessaires au projet.
    - `include/` : Répertoire contenant tous les fichiers d'en-tête (.h).
    - `src/` : Répertoire contenant tous les fichiers source (.cpp).

    - `Makefile` : Fichier de configuration pour la compilation du projet, qui redirige soit vers `LinuxMakefile` soit vers `MacMakefile` selon l'OS.

    - `LinuxMakefile` : Fichier de configuration spécifique pour la compilation sur Linux.

    - `MacMakefile` : Fichier de configuration spécifique pour la compilation sur Mac.
