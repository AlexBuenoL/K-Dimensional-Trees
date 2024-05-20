#ifndef KDTREE_HH
#define KDTREE_HH

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std; 

struct Punt {
    //Coordenades
    vector<double> coords;

    // Constructor
    Punt(vector<double> coords) : coords(coords) {}

    // Calcula la distancia cuadrada entre dos puntos
    double distanciaEucl(const Punt& p2) const {
        double result = 0.0;
        for (int i = 0; i < int(coords.size()); ++i) {
            double dif = coords[i] - p2.coords[i];
            result += dif * dif;
        }
        return result;
    }
};

struct Node {
    Punt punt;
    Node* esq;
    Node* dre;

    Node(Punt punt) : punt(punt), esq(nullptr), dre(nullptr) {}
};

class KDTree {

    public:

        //Constructora
        KDTree();

        //Afegir nodes
        void afegirNode(const Punt& p);

        //Borrar nodes arbre
        void borrarArbre(Node* r);

        //Escriu arbre 
        void escriuArbre();

        //Numero de nodes que visita la cerca al veí
        int getNodesVisitats();

        //Retorna l'arrel de l'arbre
        Node* getRoot();

        void setNodesVisitats (int i);

        //Funció per buscar el veí més proper
        Punt veiMesProper(const Punt& objectiu);  

        //Funció per generar un arbre aleatori
        void generarArbreAleatori(int k, int n);

    
    private:

        int nodes_visitats = 0;
        double millorDistancia;
        Node* millorPunt;
        Node* root;

        Node* afegirNode2(Node* r, const Punt& p, int prof);
        
        void escriu(Node* node);

        void searchNearest(Node* node, const Punt& objectiu, int prof);

};

#endif