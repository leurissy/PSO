#ifndef _SOLUCAO_H_
#define _SOLUCAO_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include "myexception.h"
#include "Vetor.h"
#include "Ponto.h"
#include "Grafo.h"
#include "Grafo2.h"
#include "Smith.h"
#include "VetTop.h"
#include <list>


namespace std {



class Solucao {
	private:
		int dimensao;
		int num_obrigatorios; //ok
		int num_steiner; //ok
		int tamanho; //ok
		Ponto canto_inferior;
		Ponto canto_superior;
		Vetor<Ponto> pontos_obrigatorios; //ok
		Vetor<Ponto> pontos_steiner; //ok
		Vetor<Ponto> velocidade_pontos_steiner; //ok
		Vetor<int> vetTop;
		double custo_por_Smith;
		double distancia( int i, int j ) const; //ok
		Ponto& ponto( int i );
		const Ponto& ponto( int i ) const;
		list<int> disponiveis;
		void AGM_Prim(int r);
		void limpaSteinerGrau1();
		void limpaSteinerGrau2();
		void calculaPontoExato( int i );
		void corrigeObrigatoriosGrauDiferenteDe1();
		void corrigeSteinerGrauDiferenteDe3();
		void trocaPontosSteiner( int i, int j );

		Vetor<Aresta> melhor_arestas;
	public:
		Smith smith;
		Solucao();
		Solucao( int tam );
		Solucao( const Vetor<Ponto>& obrigatorios );
		Solucao( const Solucao& b );
		Grafo grafo;
		int getTamanho() const { return tamanho; }
		int getNumObrigatorios() const { return num_obrigatorios; }
		int getNumSteiner() const { return num_steiner; }
		void setObrigatorios( const Vetor<Ponto>& obrigatorios );
		const Vetor<Ponto>& getObrigatorios() const;
		void setSteiner( const Vetor<Ponto>& steiner );
		const Vetor<Ponto>& getSteiner() const;
		void setVelocidadePontosSteiner( const Vetor<Ponto>& velocidade_steiner );
		const Vetor<Ponto>& getVelocidadePontosSteiner() const;
		void setCantoInferior( const Ponto& ci );
		void setCantoSuperior( const Ponto& cs );
		void geraSteinerAleatorio( const Ponto& canto_superior, const Ponto& canto_inferior );
		void geraMatrizDeAdjacencia();
		double custo() const;
		int getNaoConformidade() const;
		void removeNaoConformidade();
		void reOrganiza();
		Vetor<Ponto> passo_de_particula( const Solucao& melhor_solucao_propria,  const Solucao& melhor_solucao_social, double peso = 0.7298, double c1 = 1.49618, double c2 = 1.49618 ) const;
		void caminha( const Vetor<Ponto>& b );
		double custoPorSmith( double precisao = 0.0001 );
		void debugando( string s ) const;
		void AGM_Prim2();

		ostream& operator<< ( ostream& in ) const;

		friend ostream& operator<< ( ostream& out, const Solucao& b ) {
			double valcalc=0;
			int dimensao = b.pontos_obrigatorios[0].getTamanho();
			out << "Obrigatorios: " << endl;
			out << setprecision(6) << fixed;
//			out << "{";
			ofstream ptFixos;
			ptFixos.open ("gnuplot/ptFixos.tsv");
			for( int i = 0; i < b.num_obrigatorios; ++i ) {
				ptFixos << b.getObrigatorios()[i] << endl;
				out << i+1 << ": " << b.getObrigatorios()[i];
				
//				out << "{ ";
//				for( int j = 0; j < dimensao; ++j ) {
//					if( j != 0 )
//						out << ", ";
//					out << b.pontos_obrigatorios[i][j];
//				}
//				out << "}";
//				if( i != b.num_obrigatorios-1 )
//					out << "," << endl;
			}
			ptFixos.close();
//			out << "};";
			out << endl;
//			out << "Grau: " << endl;
//			for( int i = 0; i < b.grafo.getNumVertices(); ++i ) {
//				out << "Grau[" << i+1 << "]=" << b.grafo.grau(i) << "\t";
//			}
//			out << endl;
			out << "Steiner: " << endl;
			out << setprecision(6) << fixed;
//			out << "{";
			ofstream ptSteiner;
			ptSteiner.open ("gnuplot/ptSteiner.tsv");
			for( int i = 0; i < b.num_steiner; ++i ) {
				
				ptSteiner << b.getSteiner()[i] << endl;
				out << b.num_obrigatorios+i+1 << ": " << b.getSteiner()[i];
				
//				out << "{ ";
//				for( int j = 0; j < dimensao; ++j ) {
//					if( j != 0 )
//						out << ", ";
//					out << b.pontos_steiner[i][j];
//				}
//				out << "}";
//				if( i != b.num_steiner-1 )
//					out << "," << endl;
			}
			ptSteiner.close();
//			out << "};";
			out << endl;
			out << "Arestas: " << endl;
			/****
			for( int d = 0, i = 0; d < b.tamanho; ++d ) {
				for( int p : b.grafo.adj(d) ) {
					if( d < p ) {
						out << "arestas[" << i++ << "] = Aresta( " << d << ", " << p << " );" << endl;
					}
				}
			}
			****/
			ofstream ptEdges;
			ptEdges.open ("gnuplot/edges.tsv");
			for( int i = 0; i < b.tamanho-1; i++){ //}++i ) {
				out << i+1 << " -> ";
				for( int j = i+1; j < b.tamanho; j++ ) {
					if( b.grafo.temAresta(i,j) ) {
						out << j+1 << " (" << b.distancia(i,j) << ") ";
						// //gravar os pontos das arestas aqui

						if(i<b.num_obrigatorios){
                        	ptEdges << b.getObrigatorios()[i] << endl;
						}
						else{
							ptEdges << b.getSteiner()[i-b.num_obrigatorios] << endl;	
						}

                        if(j<b.num_steiner){
                        	ptEdges << b.getSteiner()[j] << "\n" << endl;
						}else{
							ptEdges << b.getSteiner()[j-b.num_obrigatorios] << "\n" << endl;	
						}

						if (i>j) {
							valcalc=valcalc+b.distancia(i,j);
						}
					}
				}
				if( i < b.getNumObrigatorios() && b.grafo.grau(i) != 1 ) {
					out << " <=";
				}
				if( i >= b.getNumObrigatorios() && b.grafo.grau(i) != 3 ) {
					out << " <=<=<=";
				}
				out << endl;
			}
			ptEdges.close();
//			out << "Velocidade dos pontos de Steiner: " << endl;
//			for( int i = 0; i < b.getSteiner().getTamanho(); ++i ) {
//				out << b.getVelocidadePontosSteiner()[i];
//			}
			out << endl;
			out << "Custo: " << b.custo() << " Custo2: " << valcalc << endl;
			system("gnuplot plota.gnu");
//			out << "Nao conformidade: " << b.getNaoConformidade() << endl;
			return out;
		}
};


} // namespace std

#endif
