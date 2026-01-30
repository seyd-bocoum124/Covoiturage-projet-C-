#ifndef CARTE_H
#define CARTE_H

#include <map>
#include <vector>
#include <list>
#include <string>
#include <istream>

#include "pointst.h"

class Carte {
public:
    // ajoute un noeud avec sa position
    void ajouter_noeud(long idNoeud, const PointST& position);

    // ajoute une route définie par une suite de noeuds
    void ajouter_route(const std::string& nomRoute,
                       const std::list<long>& noeuds);

    // plus court chemin simple entre deux noeuds
    double calculer_chemin(long origine, long destination,
                           std::list<long>& noeuds,
                           std::list<std::string>& routes) const;

    // trajet complet passant par toutes les destinations
    double calculer_trajet(long origine,
                           const std::list<long>& destinations,
                           std::list<long>& noeuds_sortie,
                           std::list<std::string>& routes_sortie) const;

private:
    struct Arc {
        long vers;
        std::string route;
        double dist;
    };

    // positions des noeuds
    std::map<long, PointST> points;

    // liste d’adjacence
    std::map<long, std::vector<Arc> > adj;

    // dijkstra interne (signature identique au .cpp)
    void dijkstra(long source,
                  std::map<long,double>& distances,
                  std::map<long,long>& parent,
                  std::map<long,std::string>& parentRoute) const;
};

// chargement depuis un flux (utilisé ailleurs)
std::istream& operator>>(std::istream& is, Carte& carte);

#endif