#ifndef _GRAFO2_H_
#define _GRAFO2_H_

#include <iostream>
#include <iomanip>
#include "Vetor.h"
#include <list>
#include "myexception.h"
#include "Ponto.h"

namespace std {

class Grafo2 {
	int num_classes;
	int dimensao;
	int tam_vet;
	int tamanho;
	Ponto canto_inferior;
	Ponto canto_superior;
	Vetor< list<int> > adja;
	Vetor<int> posicao;
	Vetor<int> grau;
	void cubo( int dim, int pos, int i );
public:
	Grafo2() : Grafo2(0,0,0) {}
	Grafo2( int n, int d, int t );
	Grafo2( int n, int d, int t, const Ponto& ci, const Ponto& cs );
	void setCantoInferior( const Ponto& ci );
	void setCantoSuperior( const Ponto& cs );
	void addPonto( int i, const Ponto& ponto );
	const list<int>& adj( int i ) const ;
	int inicio() const;

	ostream& operator<< ( ostream& in ) const;

	friend ostream& operator<< ( ostream& out, const Grafo2& b ) {
		for( int i = 0; i < b.tam_vet; ++i ) {
			out << i << ": ";
			for( auto j : b.adj(i) ) {
				out << j << " ";
			}
			out << endl;
		}
		return out;
	}
};


} // namespace std

#endif

