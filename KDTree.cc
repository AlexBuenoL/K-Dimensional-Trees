#include "KDTree.hh"
#include <random>

using namespace std;

/*-----------------------------------------------------
                FUNCIONS PUBLIQUES
------------------------------------------------------*/

KDTree::KDTree() { root = nullptr; }

void KDTree::afegirNode(const Punt& p) {
    afegirNode2(root, p, 0);
}

void KDTree::borrarArbre(Node* r) {
    if (r == nullptr) return;

    borrarArbre(r->esq);
    borrarArbre(r->dre);
    
    r = nullptr;
}

void KDTree::escriuArbre() {
    escriu(root);
    cout << endl;
}

int KDTree::getNodesVisitats() { 
    return nodes_visitats;
}

Node* KDTree::getRoot() {
    return root;
}

void KDTree::setNodesVisitats (int i) {
    nodes_visitats = i;
}

Punt KDTree::veiMesProper(const Punt& objectiu) {
    millorPunt = nullptr;
    millorDistancia = numeric_limits<double>::max();
    searchNearest(root, objectiu, 0);
    return millorPunt->punt;
}

void KDTree::generarArbreAleatori(int k, int n) {
    //configuracio randoms
    random_device myRandomDevice;
    unsigned seed = myRandomDevice(); // para generar la "semilla"
    uniform_real_distribution<double> Uniforme(0.0, 1.0); // distribucion de probabilidad que se quiere: uniforme entre 0 y 1
    default_random_engine RNG(seed); // metodo de generacion de los numeros (pseudo)aleatorios

    //s'afegeixen n nodes
    for (int i = 0; i < n; ++i) {
        vector<double> v(k);
        for (int l = 0; l < k; l++) {
            double random_double = Uniforme(RNG);
            v[l] = random_double;
        }
        this->afegirNode(Punt(v));
    }
}



/*-----------------------------------------------------
                FUNCIONS PRIVADES
------------------------------------------------------*/



Node* KDTree::afegirNode2(Node* r, const Punt& p, int prof) {
    if (r == nullptr or r->punt.coords.empty()) {
        r = new Node(p);
        if (prof == 0) root = r;
    }
    else {
        int dim = p.coords.size();
        int discr = prof % dim;
        if (p.coords[discr] < r->punt.coords[discr]) r->esq = afegirNode2(r->esq, p, prof + 1);
        else r->dre = afegirNode2(r->dre, p, prof + 1);
    }
    return r;
}

void KDTree::escriu(Node* node) {
    if (node == nullptr) cout << "(---)";
    else {
        int n = node->punt.coords.size();

        cout << "( [" << node->punt.coords[0];
        for (int i = 1; i < n; ++i) {
            cout << "," << node->punt.coords[i];
        }
        cout << "] ";

        cout << " FE";
        escriu(node->esq);
        cout << " FD";
        escriu(node->dre);
        cout << ")";
    }
}


void KDTree::searchNearest(Node* node, const Punt& objectiu, int prof) {
    if (node == nullptr) return;
    ++nodes_visitats;

    double currentDistance = node->punt.distanciaEucl(objectiu);
    if (currentDistance != 0 and currentDistance < millorDistancia) {
        millorPunt = node;
        millorDistancia = currentDistance;
    }

    int k = node->punt.coords.size();
    int discr = prof % k;
    double distanciaDiscr = objectiu.coords[discr] - node->punt.coords[discr];

    Node* subarbreProp;
    Node* subarbreLlun;

    if (distanciaDiscr < 0) {
        subarbreProp = node->esq;
        subarbreLlun = node->dre;
    }
    else {
        subarbreProp = node->dre;
        subarbreLlun = node->esq;
    }

    searchNearest(subarbreProp, objectiu, prof + 1);

    if (distanciaDiscr * distanciaDiscr < millorDistancia) {
        searchNearest(subarbreLlun, objectiu, prof + 1);
    }
}