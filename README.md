# Chasse_au_tresor

On se propose de créer un jeu de chasse au trésor multijoueur.
Dans une grille de jeu de 20x20, un trésor est caché.
Chaque joueur est placé de façon aléatoire sur la grille en début du jeu.
Il ne possède comme information que la distance le séparant du trésor.
Les déplacements possibles sont: haut, bas, gauche et droite.Les bords de la grille sont particuliers : si le joueur est sur le bord gauche et qu'il essaye d'aller à gauche, cela le fera reculer d'une case à droite.
Si le joueur est sur le bord haut et qu'il essaye d'aller en haut, cela le fera reculer d'une case vers le bas.
Si le joueur est sur le bord droit et qu'il essaye d'aller à droite, cela l'amènera sur le bord gauche.
Si le joueur est sur le bord bas et qu'il essaye d'aller en bas, cela l'amènera sur le bord haut.
Si le joueur rencontre un autre joueur, les deux joueurs sont renvoyés à despositions aléatoires.
Le jeu se termine lorsqu'un joueur a trouvé le trésor.
