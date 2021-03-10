/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SolucaoClusterizada.cpp
 * Author: wilson
 *
 * Created on 10 de Setembro de 2020, 09:37
 */

#include "SolucaoClusterizada.h"
#include "HeapMax.h"

namespace std {

    SolucaoClusterizada::SolucaoClusterizada() {
    }

    SolucaoClusterizada::SolucaoClusterizada(const SolucaoClusterizada& b) : Solucao(b), cluster(b.cluster) {
    }

    SolucaoClusterizada::SolucaoClusterizada(const Solucao& b) : Solucao(b), cluster(b.getTamanho()) {
        for (int i = 0; i < cluster.getTamanho(); i++) {
            cluster[i] = 0;
        }
    }

    SolucaoClusterizada::~SolucaoClusterizada() {
    }

    void SolucaoClusterizada::clusterizar(int num_clusters, bool sem_outliers, bool incluir_Outliers) {//variavel desprezarOutliers
        Arranjo<Aresta> temp = grafo.getArestas();
        int num_arestas = temp.getTamanho();
        HeapMax<Aresta> heap_max(num_arestas);

        if (incluir_Outliers){

          for (int i = 0; i < num_arestas; ++i) {
            if (temp[i].de >= getNumObrigatorios() && temp[i].para >= getNumObrigatorios()) {
              heap_max.inserir(temp[i]);
            }
          }

        }
        else{
          for (int i = 0; i < num_arestas; ++i) {
              heap_max.inserir(temp[i]);
          }
        }

        //pesos são atribuidos para transformar o grafo em heap
        for (int i = 0; i < heap_max.getTamanho(); i++) {
            heap_max[i].peso = distancia(heap_max[i].de, heap_max[i].para);
        }//fazer um if de e para e atribuir o peso zero se for ponto obrigatorios

        //transforma o grafo em heap
        heap_max.transforma_heap();
        for (int c = 1; c < num_clusters; c++) {
            Aresta maior_aresta = heap_max.retirar();

            grafo.remAresta(maior_aresta);
            for (int i : grafo.percorre(maior_aresta.para)) {
                cluster[i] = c;
            }
            if (sem_outliers && (maior_aresta.de < this->getNumObrigatorios() || maior_aresta.para < this->getNumObrigatorios())) {
                num_clusters++;
            }
        }
  }

};
