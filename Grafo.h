#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <iostream>
#include <iomanip>
#include "myexception.h"
#include "Vetor.h"
#include "Aresta.h"
#include <list>

namespace std {
	

class Grafo {
protected:
	int num_vertices;
	Arranjo< list<int> > vertice;
public:
	Grafo();
	Grafo( int tam );
	Grafo( const Grafo& b );
	Grafo( int tam, const Arranjo<Aresta>& arestas );
	int getNumVertices() const { return num_vertices; }
	void addAresta( const Aresta& aresta );
	void addAresta( int de, int para );
	void remAresta( int d,  int para );
	void remAresta( const Aresta& aresta );
	bool temAresta( int de, int para ) const;
	int grau( int i ) const;
	void trocaVertice( int i, int j );
	const list<int>& adj(int u) const;
	int primAdj(int de) const;
	int ultAdj(int de) const;
	Vetor<Aresta> getArestas() const;
	void limpaDados();
	void copia_reduzindo( const Grafo& b );
	void resize( int novo_tamanho );
	ostream& operator<< ( ostream& in ) const;
	
	friend ostream& operator<< ( ostream& out, const Grafo& b ) {
		for( int i = 0; i < b.num_vertices; ++i ) {
			out << i << ": ";
			for( auto j : b.vertice[i] ) {
				out << j << " ";
			}
			out << endl;
		}
		return out;
	}
};


} // namespace std

#endif


