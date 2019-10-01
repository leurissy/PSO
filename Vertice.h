#ifndef _VERTICE_H_
#define _VERTICE_H_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <list>

namespace std {
	
class Vertice {
	public:
		int vertice;
		int grau;
		list<int> adjacentes;
		Vertice() : vertice(0), grau(0), adjacentes(list<int>()) {}
		Vertice( int v, int g ) : vertice(v), grau(g), adjacentes(list<int>()) {}
		Vertice( int v, int g, list<int>& a ) : vertice(v), grau(g), adjacentes(a) {}
		Vertice( const Vertice& b ) {
			this->vertice = b.vertice;
			this->grau = b.grau;
			this->adjacentes = b.adjacentes;
		}
//		Vertice& operator= ( const Vertice& b ) {
//			this->vertice = b.vertice;
//			this->grau = b.grau;
//			this->adjacentes = b.adjacentes;
//			return *this;
//		}
		bool operator== ( const Vertice& b ) const {
			return (this->vertice == b.vertice && this->grau == b.grau && this->adjacentes == b.adjacentes);
		}
		bool operator!= ( const Vertice& b ) const {
			return (this->vertice != b.vertice || this->grau != b.grau || this->adjacentes != b.adjacentes);
		}
		ostream& operator<< ( ostream& in ) const {
    		return in;
		}
	    friend ostream& operator<< ( ostream& out, const Vertice& b ) {
	    	out << setprecision(1) << fixed;
//	    	out << scientific;
	    	out << "(" << b.vertice << ")";
	    	return out;
		}

};
		
} // namespace std

#endif

