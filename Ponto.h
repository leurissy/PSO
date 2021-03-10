#ifndef _PONTO_H_
#define _PONTO_H_

#include <iomanip>
#include "Vetor.h"

namespace std {

    class Ponto : public Vetor<double> {
    public:
        Ponto();
        Ponto(int n);
        Ponto(initializer_list<double> args);
        Ponto(const Ponto& b);
        Ponto(const Vetor<double>& b);
        Ponto(int n, double val);
        //	Ponto& operator+= ( const Ponto& b );
        //	const Ponto operator+ ( const Ponto& b ) const;
        //	Ponto& operator-= ( const Ponto& b );
        //	const Ponto operator- ( const Ponto& b ) const;

        int getDimensao() const;
        // projecao
        const Ponto proj(const Ponto& b) const;
        const Ponto unitario() const;
        //	friend const Ponto operator* ( double a, const Ponto& b ) {
        //		Ponto res = b;
        //		for( int i = 0; i < res.tamanho; i++ ) {
        //			res.v[i] = a * res.v[i];
        //		}
        //	    return (res);
        //	}

        //	friend const Vetor<Ponto> operator* ( double a, const Vetor<Ponto>& b ) {
        //		Vetor<Ponto> res = b;
        //		for( int i = 0; i < res.getTamanho(); i++ ) {
        //			res[i] = a * res[i];
        //		}
        //	    return (res);
        //	}

        friend ostream& operator<<(ostream& out, const Ponto& b) {
            out << setprecision(6) << fixed;
            for (int i = 0; i < b.getDimensao(); ++i) {
                out << b[i] << " ";
            }
            out << endl;
            return out;
        }

        static Ponto geraAleatorio(const Ponto& canto_superior, const Ponto& canto_inferior);

    }; // fim da classe Ponto

    Ponto sessenta_graus(const Ponto& p1, const Ponto& p2, const Ponto& p3);

    double maior_angulo(const Ponto& p1, const Ponto& p2, const Ponto& p3);

    Ponto baricentro(const Ponto& p1, const Ponto& p2, const Ponto& p3);

    Ponto steiner_exato(const Ponto& p1, const Ponto& p2, const Ponto& p3);


} //namespace std

#endif

