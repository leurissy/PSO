#include "Grafo.h"
#include <cstdlib>

namespace std {

Grafo::Grafo() : Grafo(0) {}

Grafo::Grafo( int tam ) : num_vertices(tam) {
	vertice = Arranjo< list<int> >(num_vertices);
}

Grafo::Grafo( int tam, const Arranjo<Aresta>& arestas ) : Grafo(tam) {
	int num_arestas = arestas.getTamanho();
	for ( int i = 0; i < num_arestas; i++ ) {
		addAresta( arestas[i] );
	}
}

Grafo::Grafo( const Grafo& b ) {
	num_vertices = b.num_vertices;
	vertice = b.vertice;
}

void Grafo::limpaDados() {
	for ( int i = 0; i < num_vertices; i++ ) {
		vertice[i].clear();
	}
}

void Grafo::addAresta( const Aresta& aresta ) {
	addAresta( aresta.de, aresta.para );
}

void Grafo::addAresta( int de, int para ) {
 	if( de == para )
		return;
	if( !temAresta(de, para) ) {
		vertice[de].push_back(para);
		vertice[para].push_back(de);
	}
}

bool Grafo::temAresta( int de, int para ) const {
 	if( de == para )
		return false;
//	bool achou = false;
	for( int x : vertice[de] ) {
		if( x == para ) {
			return true;
//			achou = true;
//			break;
		}
	}
//	return achou;
	return false;
//	return vertice[de].is_present(para);
}

void Grafo::remAresta( int de,  int para ) {
 	if( de == para )
		return;
	vertice[de].remove(para);
	vertice[para].remove(de);
}

void Grafo::remAresta( const Aresta& aresta ) {
	remAresta( aresta.de, aresta.para );
}

void Grafo::trocaVertice( int i, int j ) {
	if( i < 0 || j < 0 || i >= num_vertices || j >= num_vertices )
		throw myexception("Funcao Grafo::trocaVertice: indice fora da faixa.");

	if( i != j ) {
		list<int> aux_i = vertice[i];
		list<int> aux_j = vertice[j];

		for( auto x : aux_i ) {
			remAresta( i, x );
		}
		for( auto x : aux_j ) {
			remAresta( j, x );
		}
		for( auto x : aux_j ) {
			if( x == i )
				addAresta( i, j );
			else
				addAresta( i, x );
		}
		for( auto x : aux_i ) {
			if( x == j )
				addAresta( j, i );
			else
				addAresta( j, x );
		}
	}
}

const list<int>& Grafo::adj(int u) const {
	return (vertice[u]);
}

int Grafo::primAdj(int de) const {
	return vertice[de].front();
}

int Grafo::ultAdj(int de) const {
	return vertice[de].back();
}

int Grafo::grau( int i ) const {
	return ( vertice[i].size() );
}

Vetor<Aresta> Grafo::getArestas() const {
	int i;
	list<Aresta> lista;

	for( int d = 0; d < num_vertices; ++d ) {
		for( int p : vertice[d] ) {
			if ( d < p ) {
				lista.push_back( Aresta( d, p ) );
			}
		}
	}

	Vetor<Aresta> arestas( lista.size() );
	i = 0;
	for( Aresta a : lista ) {
		arestas[i++] = a;
	}

	return arestas;
}

void Grafo::copia_reduzindo( const Grafo& b ) {
	if( b.num_vertices < num_vertices )
		throw myexception("Erro em Grafo::copia_reduzindo() - a copia tem que ser igual ou reduzindo.");

	for ( int i = 0; i < num_vertices; i++ ) {
		vertice[i] = b.vertice[i];
//		cout << "b.vertice[i]" << endl;
//		for( auto x : b.vertice[i] )
//			cout << x << " ";
//		cout << endl;
//		cout << "vertice[i]" << endl;
//		for( auto x : vertice[i] )
//			cout << x << " ";
//		cout << endl;
		// verificando se há erros no algoritmo. Pode ser removida na versao definitiva
		for( int x : vertice[i] ) {
			if( x >= num_vertices )
				throw myexception("Erro em Grafo::copia_reduzindo() - vertice fora do limite máximo (num_vertices).");
		}
	}
}

void Grafo::resize( int novo_tamanho ) {
	if( novo_tamanho < 0 )
		throw myexception("Grafo::resize : Novo tamanho negativo.");
	if( num_vertices != novo_tamanho ) {
		vertice.resize(novo_tamanho);
		num_vertices = novo_tamanho;
	}
}

ostream& Grafo::operator<< ( ostream& in ) const {
    return in;
}


} // namespace std



