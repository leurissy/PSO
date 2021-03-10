#ifndef _SMITH_H_
#define _SMITH_H_

#include <cstdlib>
#include <cmath>
#include "comum.h"
#include "Vetor.h"
#include "Ponto.h"
#include "Aresta.h"
#include "Grafo.h"

#define MAXDIM 12  /* max space dimensao permitted */
#define NMAX  1001  /* max number of sites permitted */

namespace std {

class Smith {
	double escala;
	int num_obrigatorios;
	int dimensao;
	Vetor<Ponto> ponto;
	Vetor<Aresta> aresta;
	Vetor< Vetor<int> > adj;
	Vetor< Vetor<double> > comprAresta;
	Vetor<int> topvec;
	Vetor< Vetor<double> > B;
	Vetor<Ponto> C;
	Vetor<int> eqnstack;
	Vetor<int> leafQ;
	Vetor<int> val;
	void optimize(double tol);
	double dist(int a, int b) const;
public:
	Smith();
	Smith( int n, int d );
	Smith( const Vetor<Ponto>& obrigatorios );
	Smith( const Smith& b );
	void setObrigatorios( const Vetor<Ponto>& obrigatorios );
	void setSteiner( const Vetor<Ponto>& steiner );
	void buildtree( const Vetor<int>& vet );
	void buildtree( const Arranjo<Aresta>& arestas );
	void buildtree( const Grafo& grafo );
	double length();
	double error();
	double otimiza_maior_que_3( double precisao = 0.0001 );
	Vetor<Ponto> getSteiner() const;
	ostream& operator<< ( ostream& in ) const { return in; }

	friend ostream& operator<< ( ostream& out, const Smith& b ) {
//		out << "Vetor descritor da topologia:";
//		for (int i = 0; i < b.num_obrigatorios-3; i++) {
//			out << " " << b.topvec[i];
//		}
		out << endl << "Coordenadas dos pontos de Steiner" << endl;
		out << setprecision(20) << fixed;
		for (int i = b.num_obrigatorios+1; i <= 2*b.num_obrigatorios-2; i++) {
			for (int j = 0; j < b.dimensao; j++) {
				out << b.ponto[i][j] << " ";
			}
			out << endl;
		}
		out << "Arestas" << endl;
		for (int i = 1; i <= 2*b.num_obrigatorios-3; i++) {
			out << b.aresta[i].de << "-" << b.aresta[i].para << ";";
		}
		out << endl;
		out << "Distancias" << endl;
		double custo = 0.0;
		for (int i = 1; i <= b.num_obrigatorios-2; i++) {
			for( int j = 0; j < 3; j++ ) {
				if( b.adj[i][j] < i+b.num_obrigatorios ) {
					custo += b.comprAresta[i][j];
					out << "Distancia[" << b.adj[i][j] << "][" << i+b.num_obrigatorios << "] = " << b.comprAresta[i][j] << endl;
				}
			}
		}
		out << "Custo: " << custo << endl;
		return out;
	}
};

} // namespace std

#endif

