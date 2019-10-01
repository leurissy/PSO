#include "Ponto.h"
#include "comum.h"
#include <cmath>
#include <cstdlib>

namespace std {

Ponto::Ponto() : Vetor() {}

Ponto::Ponto(int n) : Vetor(n) {}

Ponto::Ponto( initializer_list<double> args ) : Vetor( args ) {}

Ponto::Ponto( const Ponto& b ) : Vetor(b) {}

Ponto::Ponto( const Vetor<double>& b ) : Vetor(b) {}

Ponto::Ponto( int n, double val ) : Vetor(n) {
	for( int i = 0; i < tamanho; i++ ) {
		v[i] = val;
	}
}

//Ponto& Ponto::operator+= ( const Ponto& b ) {
//	if( tamanho != b.tamanho)
//		throw myexception("Vetores com tamanhos diferentes.");
//    for( int i = 0; i < tamanho; i++ ) {
//        this->v[i] += b.v[i];
//    }
//    return *this;
//}

//const Ponto Ponto::operator+ ( const Ponto& b ) const {
//	Ponto res;
//    return (res = *this) += b;
//}

//Ponto& Ponto::operator-= ( const Ponto& b ) {
//	if( tamanho != b.tamanho)
//		throw myexception("Vetores com tamanhos diferentes.");
//    for( int i = 0; i < tamanho; i++ ) {
//        this->v[i] -= b.v[i];
//    }
//    return *this;
//}

//const Ponto Ponto::operator- ( const Ponto& b ) const {
//	Ponto res;
//    return (res = *this) -= b;
//}

int Ponto::getDimensao() const {
	return getTamanho();
}

Ponto Ponto::geraAleatorio( const Ponto& canto_superior, const Ponto& canto_inferior ) {
	int dimensao = canto_superior.getTamanho();
	Ponto aleatorio(dimensao);

	for( int j = 0; j < dimensao; j++ ) {
		aleatorio[j] = (canto_superior[j] - canto_inferior[j]) *
			(double)rand() / (double)RAND_MAX + canto_inferior[j];
	}

	return aleatorio;
}

//const double raiz_3_sobre_2 = sqrt(3.0)/2.0;
//const double _PI = acos(-1);

// projecao
const Ponto Ponto::proj( const Ponto& b ) const {
	double numerador = 0.0;
	double denominador = 0.0;

	if( this->getTamanho() != b.getTamanho() )
		throw myexception("Vetores com tamanhos diferentes.");

//	res = (( (*this) * b )/( (*this) * (*this) )) * (*this);
//	res = (( a * b )/( a * a )) * a;
    for( int i = 0; i < this->getTamanho(); i++ ) {
        numerador = numerador + this->operator[](i) * b[i];
        denominador = denominador + this->operator[](i) * this->operator[](i);
    }
	Ponto res = this->operator* (numerador/denominador);
	return res;
}

// vetor unitario
const Ponto Ponto::unitario() const {
	Ponto res(this->getTamanho());

	double modulo = this->norma();
	if( modulo == 0.0 )
		throw myexception("Vetor nulo.");
	res =  (*this) * (1.0/modulo);
	return res;
}

Ponto sessenta_graus( const Ponto& p1, const Ponto& p2, const Ponto& p3 ) {

	Ponto v1 = p2 - p1;
	Ponto v2 = p3 - p1;

//	Ponto w1 = v1;
//	Ponto u1 = w1.unitario();

	Ponto w2 = v2 - v1.proj(v2);
	Ponto u2 = w2.unitario();

	Ponto res = p1 + 0.5 * v1 - u2 * ( raiz_3_sobre_2 * v1.norma() );

	return (res);
}

double maior_angulo( const Ponto& p1, const Ponto& p2, const Ponto& p3 ) {

	double a = (p2 - p1).norma();
	double b = (p3 - p1).norma();
	double c = (p2 - p3).norma();

	if( a == 0.0 || b == 0.0 || c == 0.0 )
		throw myexception("Triangulo deteriorado. Um lado nulo.");
	if( a < b )
		troca( a, b );
	if( a < c )
		troca( a, c );

	double angulo = acos( ( b*b + c*c - a*a ) / ( 2 * b * c ) );

	return angulo * (double)(180 / _PI);
}


Ponto baricentro( const Ponto& p1, const Ponto& p2, const Ponto& p3 ) {
	return ( (1.0/3.0) * (p1+p2+p3) );
}

Ponto steiner_exato( const Ponto& p1, const Ponto& p2, const Ponto& p3 ) {

	const Ponto v21(p2 - p1);
	const Ponto v31 = p3 - p1;
	const Ponto v23 = p2 - p3;

//	cout << "v21: " << v21 << endl;
//	cout << "v31: " << v31 << endl;
//	cout << "v23: " << v23 << endl;

	double a = v23.norma();
	double b = v31.norma();
	double c = v21.norma();

//	if( a == 0.0 || b == 0.0 || c == 0.0 )
//		throw myexception("Triangulo deteriorado. Um lado nulo.");

	if( a == 0.0 ) {
//		cout << "a nulo. p2 coincidente com p3." << endl;
		return p2;
	}

	if( b == 0.0 || c == 0.0 ) {
//		cout << "b ou c nulo. p3 coincidente com p1 ou p2 coincidente com p1." << endl;
		return p1;
	}

	if( (a*a) >= (b*b) + (c*c) + (b*c) ) {
//		cout << "a grande. angulo maior que 120 graus." << endl;
		return p1;
	}

	if( (b*b) >= (a*a) + (c*c) + (a*c) ) {
//		cout << "b grande. angulo maior que 120 graus." << endl;
		return p2;
	}

	if( (c*c) >= (b*b) + (a*a) + (b*a) ) {
//		cout << "c grande. angulo maior que 120 graus." << endl;
		return p3;
	}

//	Ponto w1 = v21;
//	Ponto u1 = w1.unitario();
//	cout << "v31: " << v31 << endl;
//	cout << "w1: " << w1 << endl;

//	Ponto w2 = v31 - w1.proj(v31);
//	Ponto u2 = w2.unitario();

//	cout << "w1: " << w1 << endl;
//	cout << "vetor unitario na direcao de v1: " << u1 << endl;
//	cout << "w2: " << w2 << endl;
//	cout << "vetor unitario ortogonal a v1: " << u2 << endl;

//	cout << "w1 * w2: " << w1 * w2 << endl;

	Ponto p4 = sessenta_graus( p1, p2, p3 );

//	cout << "p4: " << p4 << endl;

//	cout << "distancia entre P1 e P2: " << (p2 - p1).norma() << endl;
//	cout << "distancia entre P1 e o P4: " << (p4 - p1).norma() << endl;
//	cout << "distancia entre P2 e o P4: " << (p4 - p2).norma() << endl;

	Ponto p5 = sessenta_graus( p1, p3, p2 );

//	cout << "p5: " << p5 << endl;

//	cout << "distancia entre P3 e P1: " << (p3 - p1).norma() << endl;
//	cout << "distancia entre P1 e o P5: " << (p5 - p1).norma() << endl;
//	cout << "distancia entre P3 e o P5: " << (p5 - p3).norma() << endl;

//	Ponto p6 = sessenta_graus( p2, p3, p1 );

//	cout << "p6: " << p6 << endl;

//	cout << "distancia entre P3 e P2: " << (p3 - p2).norma() << endl;
//	cout << "distancia entre P2 e o P6: " << (p6 - p2).norma() << endl;
//	cout << "distancia entre P3 e o P6: " << (p6 - p3).norma() << endl;

	Ponto v43 = p4 - p3;
	Ponto v25 = p2 - p5;
//	Ponto v61 = p6 - p1;

	double lambda1 = INFINITY;
	double lambda2 = INFINITY;

	// procura duas coordenadas espaciais em que nao haja paralelismo ou vetor coplanar com um plano coordenado
	// em outras palavras, o determinante de um par de coordenadas deve ser nao nulo
	int i, j, dimensao;
	dimensao = v43.getTamanho();
	for ( i = 0; i < dimensao-1; ++i ) {
		for( j = i+i; j < dimensao; ++j ) {
			if( (v43[i]*v25[j] - v25[i]*v43[j]) != 0 ) {
				sistema_2_grau( v43[i], v25[i], v43[j], v25[j], v23[i], v23[j], lambda1, lambda2 );
				break;
			}
		}
		if( lambda1 != INFINITY )
			break;
	}

	if( lambda1 == INFINITY )
		throw myexception("Funcao steiner_exato() - Todos os determinantes sao nulo."); // nao tenho nem ideia do que eh isso

//	cout << "lambda1: " << lambda1 << endl;
//	cout << "lambda2: " << lambda2 << endl;

	Ponto steiner1 = p3 + lambda1 * v43;

//	cout << "steiner1: " << steiner1 << endl;

//	Ponto steiner2 = p2 - lambda2 * v25;

//	cout << "steiner2: " << steiner2 << endl;

//	double lambda3;

//	sistema_2_grau( v61[0], v25[0], v61[1], v25[1], v21[0], v21[1], lambda3, lambda2 );

//	cout << "lambda3: " << lambda3 << endl;
//	cout << "lambda2: " << lambda2 << endl;

//	Ponto steiner3 = p1 + lambda3 * v61;

//	cout << "steiner3: " << steiner3 << endl;

//	Ponto steiner4 = p2 - lambda2 * v25;

//	cout << "steiner4: " << steiner4 << endl;

	return (steiner1);
}

} //namespace std


