INF3105 — TP5 : Le Livreur de pizza
Description
Ce projet correspond au TP5 du cours INF3105 – Structures de données et algorithmes (UQAM). Il
consiste à implémenter un programme C++ permettant de calculer des chemins optimaux pour un
livreur de pizza sur une carte représentée sous forme de graphe orienté.
Le programme lit : - un fichier de carte (noeuds et routes), - un fichier de requêtes (origine +
destinations),
et produit pour chaque requête : 1. la séquence de noeuds du chemin optimal, 2. la liste des routes
empruntées, 3. la distance totale du trajet (en mètres).
Compilation
Le programme est conçu pour être compilé avec g++ (version 13) sur le serveur
java2.ens.uqam.ca.
make
Exécution
./tp5 carte.txt requete.txt
ou
./tp5 carte.txt < requetes.txt
Structure du projet
- tp5.cpp : point d’entrée du programme
- carte.{h,cpp} : représentation de la carte (graphe)
- pointst.{h,cpp} : représentation des points géographiques
- Makefile : compilation du projet
- VisionneuseTP5.jar : outil de visualisation (optionnel)
Structures et algorithmes
- Conteneurs STL (map, vector, etc.)
- Algorithme de Dijkstra
- Graphe orienté
- Calcul précis des distances
À propos des fichiers de test volumineux
Les fichiers de test volumineux ne sont pas inclus dans ce dépôt Git afin de respecter la limite de
100 Mo imposée par GitHub. Ils sont disponibles séparément via l’énoncé officiel.
Environnement
- Linux (java2.ens.uqam.ca)
- g++ 13
Auteur
Seydina Bocoum — UQAM — INF3105
Remarque
directives du TP.
Le dépôt contient uniquement les fichiers nécessaires à la compilation, conformément aux
