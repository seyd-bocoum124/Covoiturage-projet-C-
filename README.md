# INF3105 — TP5 : Le Livreur de pizza
## Description
Ce projet correspond au **TP5 du cours INF3105 – Structures de données et algorithmes (UQAM)**
Il consiste à implémenter un programme en **C++** permettant de calculer des **chemins optimau
pour un livreur de pizza sur une carte représentée sous forme de **graphe orienté**.
Le programme :
- lit un fichier de **carte** (nœuds et routes),
- lit un fichier de **requêtes** (origine + destinations),
- produit pour chaque requête :
1. la séquence de nœuds du chemin optimal,
2. la liste des routes empruntées,
3. la distance totale du trajet (en mètres).
---
## Compilation
Le programme est conçu pour être compilé avec **g++ (version 13)** sur le serveur `java2.ens.u
```bash
make
```
---
## Exécution
```bash
./tp5 carte.txt requete.txt
```
ou en utilisant l’entrée standard :
```bash
./tp5 carte.txt < requetes.txt
```
---
## Structure du projet
- `tp5.cpp` : point d’entrée du programme
- `carte.{h,cpp}` : représentation de la carte (graphe)
- `pointst.{h,cpp}` : représentation des points géographiques
- `Makefile` : compilation du projet
- `VisionneuseTP5.jar` : outil de visualisation (optionnel)
---
## Structures et algorithmes
- Conteneurs de la STL (`map`, `vector`, etc.)
- Algorithme de **Dijkstra**
- Graphe orienté
- Calcul précis des distances (sans arrondi intermédiaire)
---
## Fichiers de test volumineux
Les fichiers de test volumineux fournis avec l’énoncé **ne sont pas inclus dans ce dépôt Git**
**Raison :**
- GitHub impose une limite stricte de **100 Mo par fichier**.
- Ces fichiers sont disponibles séparément via l’énoncé officiel du TP.
- Ils ne sont pas requis pour la remise du code source.
Ils sont donc volontairement ignorés via `.gitignore`.
---
## Environnement
- Système : Linux (`java2.ens.uqam.ca`)
- Compilateur : `g++ 13`
---
## Auteur
**Seydina Bocoum**
UQAM — INF3105
---
## Remarque
Ce dépôt contient uniquement les fichiers nécessaires à la compilation,
conformément aux directives du TP.
