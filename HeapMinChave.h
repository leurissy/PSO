#ifndef _HEAP_MIN_CHAVE_H_
#define _HEAP_MIN_CHAVE_H_

#include <initializer_list>
#include <vector>
#include "VerticeChave.h"

namespace std {

class HeapMinChave {
private:
	int comprimento;
	vector<VerticeChave> heap;
	vector<int> aponta;
	void troca( int i, int j );
	inline int pai( int i ) { return (i+1)/2-1; }
	inline int filhoEsq( int i ) { return 2*i+1; }
	inline int filhoDir( int i ) { return 2*i+2; }
	inline void fixaAponta( int i ) { aponta[heap[i].vertice] = i;	}
	void heap_fica( int i );
public:
	HeapMinChave() : HeapMinChave(0) {}
	HeapMinChave( int n );
	HeapMinChave( initializer_list<VerticeChave> args );
	HeapMinChave( const HeapMinChave& b ) : heap(b.heap), aponta(b.aponta), comprimento(b.comprimento) {}
	void transforma_heap();
	void inserir( const VerticeChave& item );
	void decrementar_chave( int i, const VerticeChave& item );
	void decrementar( const VerticeChave& item );
	VerticeChave retirar();
	VerticeChave retirar(int pos);
	VerticeChave& getVertice(int pos);
	VerticeChave& getHeapVertice(int i);
	VerticeChave consultarTopo();
	bool pertence( int i ) { return (aponta[i] != -1); }
	bool pertence( const VerticeChave& item ) { return (aponta[item.vertice] != -1); }
	int getComprimento() const;
	const VerticeChave& operator[] (int i) const;

    friend ostream& operator<< ( ostream& out, const HeapMinChave& b ) {
    	for( int i = 0; i < b.comprimento; ++i ) {
    		out << b.heap[i] << "\t";
    	}
    	out << endl;
		for( auto u : b.aponta ) {
			out << u << "\t";
		}
		out << endl;

    	return out;
	}
};

} // namespace std

#endif

