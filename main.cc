#include <iostream>
#include <vector>
#include "KDTree.hh"
#include <cmath>

void escriuPunt(const Punt& p) {
    vector<double> v = p.coords;
    int k = v.size();

    cout << '{' << v[0];
    for (int i = 1; i < k; ++i) {
        cout << ',' << v[i];
    }
    cout << '}' << endl;
}


int main() {
    
    int k;
    cin >> k;

    KDTree kdt = KDTree();

    string s;
    while (cin >> s and s != "fin") {
        if (s == "afegirNode") {
            vector<double> c(k);
            for (int i = 0; i < k; ++i) cin >> c[i];

            Punt p = Punt(c);
            kdt.afegirNode(p);
        }

        else if (s == "borrarArbre") 
            kdt.borrarArbre(kdt.getRoot());

        else if (s == "consultarArbre") 
            kdt.escriuArbre();

        else if (s == "creaArbreAletori") {
            int mida;
            cin >> mida;
            kdt.generarArbreAleatori(k, mida);
        }

        else if (s == "buscaVeiMesProper") {
            vector<double> c(k);
            for (int i:c) cin >> c[i];

            Punt obj = Punt(c);
            Punt mesProper = kdt.veiMesProper(obj);

            cout << "El veí més proper és ";
            escriuPunt(mesProper);
            cout << "L'algorisme ha visitat " << kdt.getNodesVisitats() << " nodes" << endl;
        }

        else 
            cout << "Error en la entrada\n";
    }
}
