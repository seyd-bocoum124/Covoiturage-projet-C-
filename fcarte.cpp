/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Automne 2025
 *  TP5 - Livreur de pizza
 */

#include "carte.h"

#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <cctype>

// convertit "n123" en 123
static long lire_noeud(const std::string& texte)
{
    // format supposé : n<number>
    return std::stol(texte.substr(1));
}

std::istream& operator>>(std::istream& is, Carte& carte)
{
    std::string ligne;

    // lecture des noeuds
    while (std::getline(is, ligne)) {
        if (ligne == "---")
            break;

        if (ligne.empty())
            continue;

        // exemple : n17 (45.508382,-73.568744) ;
        std::stringstream flux(ligne);

        std::string nom_noeud;
        flux >> nom_noeud;

        long idNoeud = lire_noeud(nom_noeud);

        char c;
        double latitude, longitude;

        flux >> c;          // '('
        flux >> latitude;
        flux >> c;          // ','
        flux >> longitude;
        flux >> c;          // ')'

        carte.ajouter_noeud(idNoeud, PointST(latitude, longitude));
    }

    // lecture des routes
    while (std::getline(is, ligne)) {
        if (ligne.empty())
            continue;

        // exemple : UQAM5 : n15 n17 n19 ;
        std::stringstream flux(ligne);

        std::string nom_route;
        flux >> nom_route;

        char c;
        flux >> c; // ':'

        std::list<long> noeuds;

        std::string token;
        while (flux >> token) {
            if (token == ";")
                break;

            noeuds.push_back(lire_noeud(token));
        }

        carte.ajouter_route(nom_route, noeuds);
    }

    return is;
}