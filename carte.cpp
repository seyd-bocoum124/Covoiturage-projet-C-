#include "carte.h"

#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

// ajout d’un noeud dans la carte
void Carte::ajouter_noeud(long idNoeud, const PointST& position)
{
    points[idNoeud] = position;
    adj[idNoeud];
}

// ajoute une route définie par une suite de noeuds
void Carte::ajouter_route(const std::string& nomRoute,
                          const std::list<long>& noeuds)
{
    if (noeuds.size() < 2) return;

    std::list<long>::const_iterator it = noeuds.begin();
    long courant = *it++;

    for (; it != noeuds.end(); ++it) {
        long suivant = *it;
        double distance = points[courant].distance(points[suivant]);
        adj[courant].push_back(Arc{suivant, nomRoute, distance});
        courant = suivant;
    }
}

// dijkstra depuis une source
void Carte::dijkstra(long source,
                     std::map<long,double>& distances,
                     std::map<long,long>& parent,
                     std::map<long,std::string>& parentRoute) const
{
    const double INFINI = std::numeric_limits<double>::infinity();

    distances.clear();
    parent.clear();
    parentRoute.clear();

    for (std::map<long,PointST>::const_iterator it = points.begin();
         it != points.end(); ++it)
        distances[it->first] = INFINI;

    distances[source] = 0.0;

    typedef std::pair<double,long> Etat;
    std::priority_queue<Etat, std::vector<Etat>, std::greater<Etat> > file;
    file.push(std::make_pair(0.0, source));

    while (!file.empty()) {
        Etat etat = file.top(); file.pop();
        double distanceCourante = etat.first;
        long noeud = etat.second;

        if (distanceCourante > distances[noeud]) continue;

        std::map<long, std::vector<Arc> >::const_iterator itAdj = adj.find(noeud);
        if (itAdj == adj.end()) continue;

        const std::vector<Arc>& arcs = itAdj->second;
        for (size_t i = 0; i < arcs.size(); ++i) {
            const Arc& arc = arcs[i];
            double nouvelleDistance = distanceCourante + arc.dist;

            if (nouvelleDistance < distances[arc.vers]) {
                distances[arc.vers] = nouvelleDistance;
                parent[arc.vers] = noeud;
                parentRoute[arc.vers] = arc.route;
                file.push(std::make_pair(nouvelleDistance, arc.vers));
            }
        }
    }
}

// ajoute un segment src -> dst en remontant les parents
static void ajouter_segment(long source, long destination,
                            const std::map<long,long>& parent,
                            const std::map<long,std::string>& parentRoute,
                            std::list<long>& noeuds_sortie,
                            std::list<std::string>& routes_sortie,
                            bool inclure_source)
{
    std::vector<long> noeuds_inverse;
    std::vector<std::string> routes_inverse;

    long courant = destination;
    noeuds_inverse.push_back(courant);

    while (courant != source) {
        std::map<long,long>::const_iterator itP = parent.find(courant);
        if (itP == parent.end()) {
            noeuds_sortie.clear();
            routes_sortie.clear();
            return;
        }

        routes_inverse.push_back(parentRoute.find(courant)->second);
        courant = itP->second;
        noeuds_inverse.push_back(courant);
    }

    reverse(noeuds_inverse.begin(), noeuds_inverse.end());
    reverse(routes_inverse.begin(), routes_inverse.end());

    size_t debut = inclure_source ? 0 : 1;
    for (size_t i = debut; i < noeuds_inverse.size(); ++i)
        noeuds_sortie.push_back(noeuds_inverse[i]);

    for (size_t i = 0; i < routes_inverse.size(); ++i)
        routes_sortie.push_back(routes_inverse[i]);
}

// plus court chemin simple
double Carte::calculer_chemin(long origine, long destination,
                              std::list<long>& noeuds,
                              std::list<std::string>& routes) const
{
    std::map<long,double> distances;
    std::map<long,long> parent;
    std::map<long,std::string> parentRoute;

    dijkstra(origine, distances, parent, parentRoute);

    noeuds.clear();
    routes.clear();

    if (!std::isfinite(distances[destination])) {
        return std::numeric_limits<double>::infinity();
    }

    ajouter_segment(origine, destination,
                    parent, parentRoute,
                    noeuds, routes,
                    true);

    return distances[destination];
}

// trajet complet avec retour à l’origine
double Carte::calculer_trajet(long origine,
                              const std::list<long>& destinations,
                              std::list<long>& noeuds_sortie,
                              std::list<std::string>& routes_sortie) const
{
    noeuds_sortie.clear();
    routes_sortie.clear();

    if (destinations.empty()) {
        noeuds_sortie.push_back(origine);
        return 0.0;
    }

    if (destinations.size() == 1) {
        long d = destinations.front();

        std::list<long> n1, n2;
        std::list<std::string> r1, r2;

        double d1 = calculer_chemin(origine, d, n1, r1);
        double d2 = calculer_chemin(d, origine, n2, r2);

        noeuds_sortie = n1;
        n2.pop_front();
        noeuds_sortie.insert(noeuds_sortie.end(), n2.begin(), n2.end());

        routes_sortie = r1;
        routes_sortie.insert(routes_sortie.end(), r2.begin(), r2.end());

        return d1 + d2;
    }

    vector<long> points_cles;
    points_cles.push_back(origine);
    for (list<long>::const_iterator it = destinations.begin();
         it != destinations.end(); ++it)
        points_cles.push_back(*it);

    int nb_destinations = (int)points_cles.size() - 1;
    int tous_visites = (1 << nb_destinations) - 1;
    const double INFINI = numeric_limits<double>::infinity();

    vector< map<long,double> > toutes_distances(nb_destinations + 1);
    vector< map<long,long> > tous_parents(nb_destinations + 1);
    vector< map<long,string> > toutes_routes_parent(nb_destinations + 1);

    for (int i = 0; i <= nb_destinations; ++i)
        dijkstra(points_cles[i],
                 toutes_distances[i],
                 tous_parents[i],
                 toutes_routes_parent[i]);

    vector< vector<double> > matrice_distances(
        nb_destinations + 1,
        vector<double>(nb_destinations + 1, INFINI)
    );

    for (int i = 0; i <= nb_destinations; ++i)
        for (int j = 0; j <= nb_destinations; ++j)
            if (toutes_distances[i].count(points_cles[j]))
                matrice_distances[i][j] =
                    toutes_distances[i][points_cles[j]];

    vector< vector<double> > cout_min(
        1 << nb_destinations,
        vector<double>(nb_destinations, INFINI)
    );

    vector< vector<int> > precedent_dest(
        1 << nb_destinations,
        vector<int>(nb_destinations, -1)
    );

    for (int i = 0; i < nb_destinations; ++i)
        cout_min[1 << i][i] = matrice_distances[0][i + 1];

    for (int ensemble_visites = 1;
         ensemble_visites <= tous_visites;
         ++ensemble_visites)
    {
        for (int i = 0; i < nb_destinations; ++i) {
            if (!(ensemble_visites & (1 << i))) continue;

            double cout_actuel = cout_min[ensemble_visites][i];
            if (!isfinite(cout_actuel)) continue;

            for (int j = 0; j < nb_destinations; ++j) {
                if (ensemble_visites & (1 << j)) continue;

                int nouvel_ensemble =
                    ensemble_visites | (1 << j);

                double nouveau_cout =
                    cout_actuel +
                    matrice_distances[i + 1][j + 1];

                if (nouveau_cout <
                    cout_min[nouvel_ensemble][j])
                {
                    cout_min[nouvel_ensemble][j] =
                        nouveau_cout;
                    precedent_dest[nouvel_ensemble][j] =
                        i;
                }
            }
        }
    }

    double meilleur = INFINI;
    int dernier = -1;
    for (int i = 0; i < nb_destinations; ++i) {
        double v =
            cout_min[tous_visites][i] +
            matrice_distances[i + 1][0];

        if (v < meilleur) {
            meilleur = v;
            dernier = i;
        }
    }

    if (!isfinite(meilleur)) return INFINI;

    vector<int> ordre_destinations;
    int ensemble_visites = tous_visites;
    while (dernier != -1) {
        ordre_destinations.push_back(dernier);
        int p = precedent_dest[ensemble_visites][dernier];
        ensemble_visites ^= (1 << dernier);
        dernier = p;
    }
    reverse(ordre_destinations.begin(),
            ordre_destinations.end());

    noeuds_sortie.push_back(points_cles[0]);
    int indice_courant = 0;

    for (size_t t = 0; t < ordre_destinations.size(); ++t) {
        int indice_suivant =
            ordre_destinations[t] + 1;

        ajouter_segment(points_cles[indice_courant],
                        points_cles[indice_suivant],
                        tous_parents[indice_courant],
                        toutes_routes_parent[indice_courant],
                        noeuds_sortie,
                        routes_sortie,
                        false);

        indice_courant = indice_suivant;
    }

    ajouter_segment(points_cles[indice_courant],
                    points_cles[0],
                    tous_parents[indice_courant],
                    toutes_routes_parent[indice_courant],
                    noeuds_sortie,
                    routes_sortie,
                    false);

    return meilleur;
}