#ifndef _ARESTA_H_
#define _ARESTA_H_

#include <iostream>

namespace std {
	
class Aresta {
	public:
		int de;
		int para;
		double peso;
		Aresta() : de(0), para(0), peso(0.0) {}
		Aresta( int d, int p, double v = 0.0 ) : de(d), para(p), peso(v) {}
		Aresta& operator= ( const Aresta& b ) {
			this->de = b.de;
			this->para = b.para;
			this->peso = b.peso;
			return *this;
		}
		bool operator< ( const Aresta& b ) const {
			return (this->peso < b.peso);
		}
		bool operator> ( const Aresta& b ) const {
			return (this->peso > b.peso);
		}
		ostream& operator<< ( ostream& in ) const {
    		return in;
		}
	    friend ostream& operator<< ( ostream& out, const Aresta& b ) {
	    	out << "De: " << b.de << " - Para: " << b.para << " - Peso: " << b.peso << endl;
	    	return out;
		}

};
		
} // namespace std

#endif
