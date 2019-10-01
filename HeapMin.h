#ifndef _HEAP_MIN_H_
#define _HEAP_MIN_H_

#include <initializer_list>
#include "myexception.h"
#include "Arranjo.h"
	
namespace std {
	
template <class T>
class HeapMin : public Arranjo<T> {
private:
	int comprimento;
	void troca( int i, int j );
	int Pai( int i );
	int FilhoEsq( int i );
	int FilhoDir( int i );
	void heap_fica( int i );
public:
	HeapMin() : Arranjo<T>(), comprimento(0) {}
	HeapMin( int n ) : Arranjo<T>(n), comprimento(0) {}
	HeapMin( initializer_list<T> args ) : Arranjo<T>( args ) { comprimento = this->tamanho; }
	HeapMin( const HeapMin& b ) : Arranjo<T>(b), comprimento(b.comprimento) {}
	void transforma_heap();
	void inserir( const T& item );
	void decrementar_chave( int i, const T& item );
	T retirar();
	T consultarTopo();
	int getComprimento() const;
	int busca( const T& item );


    friend ostream& operator<< ( ostream& out, const HeapMin<T>& b ) {
    	for( int i = 0; i < b.comprimento; ++i ) {
    		out << b[i] << "\t";
    	}
    	out << endl;
    	return out;
	}
};

template <class T>
void HeapMin<T>::troca( int i, int j ) {
	T aux;
	
	aux = this->v[i];
	this->v[i] = this->v[j];
	this->v[j] = aux;
}

template <class T>
int HeapMin<T>::Pai( int i ) {
	return (i+1)/2-1;
}

template <class T>
int HeapMin<T>::FilhoEsq( int i ) {
	return 2*i+1;
}

template <class T>
int HeapMin<T>::FilhoDir( int i ) {
	return 2*i+2;
}

//heap_fica minimo
template <class T>
void HeapMin<T>::heap_fica( int i ) {
   	int f_esq, f_dir, menor;
	
	f_esq = FilhoEsq( i );
	f_dir = FilhoDir( i );
   	menor = i;
   	if( f_esq < this->comprimento && this->v[f_esq] < this->v[i] )
		menor = f_esq;
   	if( f_dir < this->comprimento && this->v[f_dir] < this->v[menor] )
   		menor = f_dir;
	if( menor != i ) {
		troca( i, menor );
		heap_fica( menor );
	}
}

//transforma vetor em heap minimo
template <class T>
void HeapMin<T>::transforma_heap() {
	for( int i = this->comprimento/2-1; i >= 0; i-- ) {
		heap_fica( i );
	}
}

template <class T>
void HeapMin<T>::decrementar_chave( int i, const T& chave ) {
	if( chave > this->v[i] )
		throw myexception("Nova chave maior que a atual.");
	
	while( i > 0 && chave < this->v[Pai(i)] ) {
		this->v[i] = this->v[Pai(i)];
		i = Pai(i);
	}
   	this->v[i] = chave;
}

template <class T>
void HeapMin<T>::inserir( const T& chave ) {
	if( this->comprimento == this->tamanho )
		throw myexception("Estouro da heap.");
	
	this->v[this->comprimento] = chave;
	this->comprimento++;
	decrementar_chave( this->comprimento - 1, chave );
}

//template <class T>
//void HeapMin<T>::inserir( const T& item ) {
//	int ind;
//	
//	if( this->comprimento == this->tamanho )
//		throw myexception("Estouro da lista.");
//	
//	ind = this->comprimento;
//	while( ind > 0 && this->v[Pai(ind)] < item ) {
//		this->v[ind] = this->v[Pai(ind)];
//		ind = Pai(ind);
//	}
//   	this->v[ind] = item;
//	this->comprimento++;
//}

template <class T>
T HeapMin<T>::retirar() {
	T topo;
	
	if( this->comprimento == 0 )
		throw myexception("Esvaziamento da lista.");
	
	topo = this->v[0];
	this->comprimento-- ;
	this->v[0] = this->v[this->comprimento];
	heap_fica( 0 );
	
	return topo;
}

template <class T>
T HeapMin<T>::consultarTopo() {
	if( this->comprimento == 0 )
		throw myexception("Esvaziamento da lista.");
	
	return this->v[0];
}

template <class T>
int HeapMin<T>::getComprimento() const {
	return this->comprimento;
}

template <class T>
int HeapMin<T>::busca( const T& item ) {
	for( int i = 0; i < this->comprimento; i++ ) {
		if( item == this->v[i] ) 
			return i;
	}
	return -1;
}

} // namespace std

#endif

