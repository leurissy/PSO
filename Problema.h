#ifndef _PROBLEMA_H_
#define _PROBLEMA_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Tempo.h"
#include "Vetor.h"
#include "Solucao.h"
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
				LinhaDoTempo(){}
				LinhaDoTempo( int i, int p, double t, double c ) : iteracao(i), particula(p), tempo(t), custo(c) {}
				ostream& operator<< ( ostream& in ) const { return in; };
				string str() const;
				friend ostream& operator<< ( ostream& out, const LinhaDoTempo& b ) {
					out << setprecision(6) << fixed;
					out << b.iteracao << ";" << b.particula << ";" << ldtos(b.tempo,15) << ";" << ldtos(b.custo,15) << endl;
				}
		};
		Vetor<Ponto> steiner_best;
		list<LinhaDoTempo> linha_do_tempo;
		int dimensao;
		Ponto canto_inferior;
		Ponto canto_superior;
		int tamanho;
		void le_instancia( const string nomearq );
		Vetor<Ponto> pontos_obrigatorios;
		Vetor<Solucao> particulas;
		Solucao melhor_solucao;
		int ultima_atualizacao;
	public:			
		Problema();
		Problema( const string nomearq );
		int getTamanho() const;
		void gera_particulas_aleatorizado( int quant );
		double swarm_particle( int num_particulas, int max_iteracoes, double peso, double c1, double c2 );
		int getUltimaAtualizacao() const;
		ostream& operator<< ( ostream& in ) const { return in; };
		string getLinhaDoTempo() const;
		string getVetTop() const;
		const Solucao& getMelhorSolucao() const;
		
};

} //namespace std

#endif

