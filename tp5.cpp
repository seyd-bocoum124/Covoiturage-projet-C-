#include "carte.h"

#include <fstream>
#include <iostream>
#include <list>
#include <cmath>

int main(int argc, char** argv)
{
    Carte carte;

    // chargement de la carte
    std::ifstream fichier_carte(argv[1]);
    fichier_carte >> carte;

    // fichier des requêtes
    std::ifstream fichier_requetes(argv[2]);

    std::string origine_str;
    while (fichier_requetes >> origine_str) {
        long origine = std::stol(origine_str.substr(1));

        char separateur;
        fichier_requetes >> separateur; // ':'

        std::list<long> destinations;
        std::string token;
        while (fichier_requetes >> token && token != ";")
            destinations.push_back(std::stol(token.substr(1)));

        std::list<long> noeuds;
        std::list<std::string> routes;

        double distance =
            carte.calculer_trajet(origine,
                                  destinations,
                                  noeuds,
                                  routes);

        // affichage des noeuds parcourus
        for (long n : noeuds)
            std::cout << "n" << n << " ";
        std::cout << "\n";

        // affichage des routes (sans répétition)
        std::string derniere_route = "";
        for (const auto& r : routes) {
            if (r != derniere_route) {
                std::cout << r << " ";
                derniere_route = r;
            }
        }
        std::cout << "\n";

        // distance arrondie
        std::cout << std::llround(distance) << " m\n";
    }
}