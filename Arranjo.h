#ifndef _ARRANJO_H_
#define _ARRANJO_H_

#include <iostream>
#include "myexception.h"

namespace std {

template <class T>
class Arranjo {
protected:
	int tamanho;
    T *v;
public:
    Arranjo();
    virtual ~Arranjo();
    Arranjo(int n);
    Arranjo(const Arranjo<T>& b);
    Arranjo( initializer_list<T> args );
    bool operator== ( const Arranjo<T>& b );
    Arranjo<T>& operator= ( const Arranjo<T>& b );
    ostream& operator<< ( ostream& in ) const ;
    friend ostream& operator<< ( ostream& out, const Arranjo<T>& b ) {
    	for( int i = 0; i < b.tamanho; ++i ) {
    		out << b[i] << " ";
    	}
    	out << endl;
    	return out;
	}
	// assessor somente leitura
    const T& operator[] (int i) const ;
	// assessor leitura e escrita
    T& operator[] (int i) ;
    int getTamanho() const ;
    int size() const ;
	void resize(int novo_tamanho);
	void concatena( const Arranjo<T>& b );
};

template <class T>
Arranjo<T>::Arranjo() : tamanho(0), v(NULL) {}

template <class T>
Arranjo<T>::~Arranjo() {
	delete [] v;
}

template <class T>
Arranjo<T>::Arranjo(int n) : tamanho(n) {
	try {
		v = new T [n]();
	} catch(...) {
		throw myexception("Arranjo(int n): Impossivel alocar memoria para o Arranjo.");
	}
}

template <class T>
Arranjo<T>::Arranjo(const Arranjo<T>& b) {
	try {
        tamanho = b.tamanho;
        v = new T [tamanho];
        for( int i = 0; i < tamanho; i++ ) {
            v[i] = b.v[i];
        }
	} catch(...) {
		throw myexception("Arranjo(const Arranjo<T>& b): Impossivel alocar memoria para o Arranjo.");
	}
}

template <class T>
Arranjo<T>::Arranjo( initializer_list<T> args ) {
	try {
	    this->v = new T [args.size()];
	    this->tamanho = 0;
	    for( T x : args ) {
			this->v[tamanho++] = x;
		}
	} catch(...) {
		throw myexception("Arranjo( initializer_list<T> args ): Impossivel alocar memoria para o Arranjo.");
	}
}

template <class T>
bool Arranjo<T>::operator== ( const Arranjo<T>& b ) {
	if( this->tamanho != b.tamanho )
		return false; 
    for( int i = 0; i < this->tamanho; i++ ) {
    	if( this->v[i] != b.v[i] )
			return false;
    }
    return true;
}

template <class T>
Arranjo<T>& Arranjo<T>::operator= ( const Arranjo<T>& b ) {
	try {
	    if( this != &b ) {
	        delete [] this->v;
	        this->tamanho = b.tamanho;
	        this->v = new T [this->tamanho];
	        for( int i = 0; i < this->tamanho; i++ ) {
	            this->v[i] = b.v[i];
	        }
	    }
	} catch(...) {
		throw myexception("Arranjo<T>::operator= : Impossivel alocar memoria para o Arranjo.");
	}
    return *this;
}

template <class T>
ostream& Arranjo<T>::operator<< ( ostream& in ) const {
	return in;
}

template <class T>
const T& Arranjo<T>::operator[] (int i) const {
	if( i < 0 || i >= this->tamanho)
		throw myexception("Indice fora dos limites.");
	return this->v[i]; 
}

template <class T>
T& Arranjo<T>::operator[] (int i) {
	if( i < 0 || i >= this->tamanho)
		throw myexception("Indice fora dos limites.");
	return this->v[i]; 
}

template <class T>
int Arranjo<T>::getTamanho() const { return this->tamanho; }

template <class T>
int Arranjo<T>::size() const { return this->tamanho; }

template <class T>
void Arranjo<T>::resize( int novo_tamanho ) {
	if( novo_tamanho < 0 )
		throw myexception("Novo tamanho negativo.");
	if( this->tamanho != novo_tamanho ) {
		T* aux;
		try {
			aux = new T [novo_tamanho];
		} catch(...) {
			throw myexception("Impossivel alocar memoria para o Arranjo.");
		}
		for( int i = 0; i < novo_tamanho; i++ ) {
			if( i < this->tamanho )
				aux[i] = this->v[i];
			else
				aux[i] = T();
		}
        this->tamanho = novo_tamanho;
		delete [] v;
		this->v = aux;
	}
}

template <typename T>
void Arranjo<T>::concatena( const Arranjo<T>& b ) {
	if( b.tamanho != 0 ) {
		int novo_tamanho = this->tamanho + b.tamanho;
		T* aux;
		try {
			aux = new T [novo_tamanho];
		} catch(...) {
			throw myexception("Impossivel alocar memoria para o Arranjo.");
		}
		int i;
		for( i = 0; i < this->tamanho; i++ ) {
			aux[i] = this->v[i];
		}
		for( ; i < novo_tamanho; i++ ) {
			aux[i] = b[i - this->tamanho];
		}
        this->tamanho = novo_tamanho;
		delete [] v;
		this->v = aux;
	}
}

} // namespace std

#endif

