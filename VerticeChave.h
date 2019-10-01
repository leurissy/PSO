#ifndef _VERTICE_CHAVE_H_
#define _VERTICE_CHAVE_H_

#include <iostream>
#include <iomanip>
#include <cmath>

namespace std {
	
class VerticeChave {
	public:
		int vertice;
		double chave;
		int pai;
		VerticeChave() : vertice(0), chave(INFINITY), pai(-1) {}
		VerticeChave( int v, double c, int p ) : vertice(v), chave(c), pai(p) {}
		VerticeChave( const VerticeChave& b ) {
			this->vertice = b.vertice;
			this->chave = b.chave;
			this->pai = b.pai;
		}
		VerticeChave& operator= ( const VerticeChave& b ) {
			this->vertice = b.vertice;
			this->chave = b.chave;
			this->pai = b.pai;
			return *this;
		}
		bool operator< ( const VerticeChave& b ) const {
			return (this->chave < b.chave);
		}
		bool operator> ( const VerticeChave& b ) const {
			return (this->chave > b.chave);
		}
		bool operator<= ( const VerticeChave& b ) const {
			return (this->chave <= b.chave);
		}
		bool operator>= ( const VerticeChave& b ) const {
			return (this->chave >= b.chave);
		}
		bool operator== ( const VerticeChave& b ) const {
			return (this->chave == b.chave);
		}
		bool operator!= ( const VerticeChave& b ) const {
			return (this->chave != b.chave);
		}
		ostream& operator<< ( ostream& in ) const {
    		return in;
		}
	    friend ostream& operator<< ( ostream& out, const VerticeChave& b ) {
	    	cout << setprecision(1) << fixed;
//	    	out << scientific;
	    	out << "(" << b.vertice << ", " << b.chave << ")";
	    	return out;
		}

};
		
} // namespace std

#endif
