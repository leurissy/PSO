#ifndef _LISTA_H_
#define _LISTA_H_

#include "myexception.h"

#define MAX 100000


namespace std {
	

template <class T>
class Lista {
	private:
		T *itens;
		int comprimento;
		int tam_max;
	public:
		Lista();
		Lista( int tam );
		Lista( const Lista<T>& b );
		void reset();
		void add( const T& item );
		void add_ordenado( const T& item );
		void add_ordenado_desc( const T& item );
		void insert( const T& item, int pos );
		T& get( int i ) const;
		int size() const { return comprimento; }
		int getTamMax() { return tam_max; }
		Lista<T> operator+( const Lista<T>& lista );
		Lista<T> complemento( int i );
		void troca( int i, int j );
		bool presente( const T& item ) const;
		ostream& operator<< ( ostream& in ) const;
		friend ostream& operator<< ( ostream& out, const Lista<T>& b ) {
			for( int i = 0; i < b.comprimento; ++i ) {
				 out << b.get(i) << endl;
			}
			return out;
		}
		T& operator[] (int i) const ;
		bool operator== ( const Lista<T>& b );
};

template <class T>
Lista<T>::Lista() {
	comprimento = 0;
	tam_max = 0;
	itens = new T [tam_max];
}

template <class T>
Lista<T>::Lista( int tam ) {
	comprimento = 0;
	tam_max = tam;
	itens = new T [tam_max];
}

template <class T>
Lista<T>::Lista( const Lista<T>& b ) {
	comprimento = b.comprimento;
	tam_max = b.tam_max;
	itens = new T [tam_max];
	for( int i = 0; i < comprimento; i++ ) {
        itens[i] = b[i];
    }
}

template <class T>
void Lista<T>::reset() {
   	comprimento = 0;
}

template <class T>
void Lista<T>::add( const T& item ) {
   	itens[comprimento++] = item;
}

template <class T>
void Lista<T>::add_ordenado( const T& item ) {
	int i;
	
	for( i = comprimento; i > 0 && item < itens[i-1] ; i-- ) {
		itens[i] = itens[i-1];
	}
	itens[i] = item;
	comprimento++;
}

template <class T>
void Lista<T>::add_ordenado_desc( const T& item ) {
	int i;
	
	for( i = comprimento; i > 0 && itens[i-1] < item; i-- ) {
		itens[i] = itens[i-1];
	}
	itens[i] = item;
	comprimento++;
}

template <class T>
void Lista<T>::insert( const T& item, int pos ) {
	int i;
	
    if( pos < 0 )
    	throw myexception("Indice negativo na lista.");
	for( i = comprimento; i > pos; i-- ) {
   		itens[i] = itens[i-1];
	}
   	itens[i] = item;
   	comprimento++;
}

template <class T>
T& Lista<T>::get( int i ) const {
    if( i < 0 || i >= comprimento)
    	throw myexception("Indice fora dos limites.");

	return itens[i];
}

template <class T>
Lista<T> Lista<T>::operator+( const Lista<T>& lista) { 
   Lista<T> temp;
   temp = *this;
   for( int i = 0; i < lista.size(); i++ )
      temp.add(lista.get(i));
   return temp; 
}

template <class T>
bool Lista<T>::operator== ( const Lista<T>& b ) {
	if( comprimento != b.comprimento )
		return false;
	for( int i = 0; i < comprimento; i++ ) {
		if( !(itens[i] == b.itens[i]) )
			return false;
    }
    return true;
}

template <class T>
Lista<T> Lista<T>::complemento( int i ) { 
   Lista<T> temp;

   for( int j = 0; j < this->size(); j++ )
      if( j != i )
         temp.add(this->get(j));
   return temp; 
}

template <class T>
void Lista<T>::troca( int i, int j ) {
	T aux;
	
	aux = itens[i];
	itens[i] = itens[j];
	itens[j] = aux;
}

template <class T>
bool Lista<T>::presente( const T& item ) const {
	for( int i = 0; i < comprimento; i++ ) {
		if( itens[i] == item ) 
			return true;
	}
	return false;
}

template <class T>
ostream& Lista<T>::operator<< ( ostream& in ) const {
    return in;
}

template <class T>
T& Lista<T>::operator[] (int i) const {
    if( i < 0 || i >= comprimento)
    	throw myexception("Indice fora dos limites.");

	return itens[i]; 
}

} // namespace std

#endif

