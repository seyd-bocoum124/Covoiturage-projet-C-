# Makefile pour INF3105 / TP5
OPTIONS = -Wall
# Choisir l'une des deux configurations : -g -O0 pour débogage et -O2 pour la remise.
#OPTIONS = -g -O0 -Wall
OPTIONS = -O2 -Wall

# Syntaxe : cible : dépendance1 dépendance2 ...
# Ensuite, la ou les ligne(s) débutant par une tabulation (\t) donne les commandes pour construire une cible

tp5 :  tp5.cpp carte.o pointst.o fcarte.o
	g++ ${OPTIONS} -o tp5 tp5.cpp carte.o pointst.o fcarte.o

carte.o: carte.cpp carte.h pointst.h
	g++ ${OPTIONS} -c carte.cpp

fcarte.o: fcarte.cpp carte.h pointst.h
	g++ ${OPTIONS} -c fcarte.cpp

pointst.o: pointst.h pointst.cpp
	g++ ${OPTIONS} -c pointst.cpp

clean:
	rm -rf tp5 *.o

