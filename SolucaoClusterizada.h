/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SolucaoClusterizada.h
 * Author: wilson
 *
 * Created on 10 de Setembro de 2020, 09:37
 */

#ifndef SOLUCAOCLUSTERIZADA_H
#define SOLUCAOCLUSTERIZADA_H
#include "Solucao.h"

namespace std {

    class SolucaoClusterizada : public Solucao {
    public:
        SolucaoClusterizada();
        SolucaoClusterizada(const SolucaoClusterizada& orig);
        SolucaoClusterizada(const Solucao& orig);
        virtual ~SolucaoClusterizada();
        void clusterizar(int num_clusters, bool sem_outliers = false, bool incluir_Outliers = true);

        Vetor<int> cluster;

        friend ostream& operator<<(ostream& out, const SolucaoClusterizada& b) {
            //            out << "Obrigatorios: " << endl;
            //            out << setprecision(6) << fixed;
            //            for (int i = 0; i < b.getNumObrigatorios(); ++i) {
            //                out << i + 1 << ": " << b.getObrigatorios()[i];
            //            }
            //            out << endl;
            //            out << "Steiner: " << endl;
            //            out << setprecision(6) << fixed;
            //            for (int i = 0; i < b.getNumSteiner(); ++i) {
            //                out << b.getNumObrigatorios() + i + 1 << ": " << b.getSteiner()[i];
            //            }
            //            out << endl;
            out << "Arestas depois da clusterizacao: " << endl;
            for (int i = 0; i < b.getTamanho(); ++i) {
                out << i + 1 << " -> ";
                for (int j : b.grafo.adj(i)) {
                    out << j + 1 << " ";
                }
                out << endl;
            }
            out << endl;

            int num_clusters = 1;
            cout << "Cluster [0]: ";
            for (int i = 0; i < b.getTamanho(); i++) {
                if (b.cluster[i] + 1 > num_clusters)
                    num_clusters = b.cluster[i] + 1;
                if (b.cluster[i] == 0)
                    cout << ' ' << i + 1;
            }
            cout << endl;
            for (int c = 1; c < num_clusters; c++) {
                cout << "Cluster [" << c << "]: ";
                for (int i = 0; i < b.getTamanho(); i++) {
                    if (b.cluster[i] == c)
                        cout << ' ' << i + 1;
                }
                cout << endl;
            }

            return out;
        }
    };

};
#endif /* SOLUCAOCLUSTERIZADA_H */
