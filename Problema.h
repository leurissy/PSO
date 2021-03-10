#ifndef _PROBLEMA_H_
#define _PROBLEMA_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Tempo.h"
#include "Vetor.h"
#include "Solucao.h"
#include "SolucaoClusterizada.h"
#include <list>
#include "Ponto.h"
#include "comum.h"


namespace std {

    class Problema {
    private:

        class LinhaDoTempo {
            int iteracao;
            int particula;
            double tempo;
            double custo;
        public:

            LinhaDoTempo() {
            }

            LinhaDoTempo(int i, int p, double t, double c) : iteracao(i), particula(p), tempo(t), custo(c) {
            }

            ostream& operator<<(ostream& in) const {
                return in;
            };
            string str() const;

            friend ostream& operator<<(ostream& out, const LinhaDoTempo& b) {
                out << setprecision(6) << fixed;
                out << b.iteracao << ";" << b.particula << ";" << ldtos(b.tempo, 15) << ";" << ldtos(b.custo, 15) << endl;
                return out;
            }
        };
        list<LinhaDoTempo> linha_do_tempo;
        int dimensao;
        Ponto canto_inferior;
        Ponto canto_superior;
        int tamanho;
        Vetor<Ponto> pontos_obrigatorios;
        Vetor<Solucao> particulas;
        Solucao melhor_solucao;
        SolucaoClusterizada solucao_clusterizada;
        int ultima_atualizacao;
        bool proc_anterior;
    public:
        Problema();
        Problema(const string nomearq, bool proc_anterior = false);
        int getTamanho() const;
        void gera_particulas_aleatorizado(int quant);
        double swarm_particle(int num_particulas, int max_iteracoes, double peso = 0.7298, double c1 = 1.49618, double c2 = 1.49618);
        int getUltimaAtualizacao() const;

        ostream& operator<<(ostream& in) const {
            return in;
        };
        string getLinhaDoTempo() const;
        string getVetTop() const;
        string getSaidaDados() const;
        const Solucao& getMelhorSolucao() const;
        const SolucaoClusterizada& getSolucaoClusterizada() const;
        void clusterizar(int num_clusters, bool sem_outliers = false, bool incluir_Outliers = true);
    };

} //namespace std

#endif
