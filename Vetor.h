#ifndef _VETOR_H_
#define _VETOR_H_

#include <initializer_list>
#include "myexception.h"
#include "Arranjo.h"
#include <iostream>
#include <cfloat>
#include <cmath>


namespace std {

    template <class T>
    class Vetor : public Arranjo<T> {
    public:

        Vetor() : Arranjo<T>() {
        }

        Vetor(int n) : Arranjo<T>(n) {
        }

        Vetor(const Vetor<T>& b) : Arranjo<T>(b) {
        }

        Vetor(initializer_list<T> args) : Arranjo<T>(args) {
        }
        Vetor<T>& operator+=(const Vetor<T>& b);
        const Vetor<T> operator+(const Vetor<T>& b) const;
        Vetor<T>& operator-=(const Vetor<T>& b);
        const Vetor<T> operator-(const Vetor<T>& b) const;
        const Vetor<T> operator-() const;
        // produto por escalar no template. ATENCAO: NAO FUNCIONA EM Vetor< Vetor<T> >
        const Vetor<T> operator*(const T& b) const;

        friend const Vetor<T> operator*(const T& a, const Vetor<T>& b) {
            return (b * a);
        }
        // produto escalar ou interno
        const T operator*(const Vetor<T>& b) const;
        const T dif(const Vetor<T> b) const;
        const T dif_rel(const Vetor<T> b) const;
        const T max_mod() const;
        const T norma() const;
        //    ostream& operator<< ( ostream& in ) const ;

        friend ostream& operator<<(ostream& out, const Vetor<T>& b) {
            for (int i = 0; i < b.tamanho; ++i) {
                out << b[i] << " ";
            }
            out << endl;
            return out;
        }
    };

    template <class T>
    Vetor<T>& Vetor<T>::operator+=(const Vetor<T>& b) {
        if (this->tamanho != b.tamanho)
            throw myexception("Vetores com tamanhos diferentes.1");
        for (int i = 0; i < this->tamanho; i++) {
            this->v[i] += b.v[i];
        }
        return *this;
    }

    template <class T>
    const Vetor<T> Vetor<T>::operator+(const Vetor<T>& b) const {
//        cout << "------------------aqui------------------" << endl;
        if (this->tamanho != b.tamanho) {
            
            cout << "this->tamanho " << this->tamanho << endl;
            cout << "b.tamanho " << b.tamanho << endl;
            throw myexception("Vetores com tamanhos diferentes.8");
        }
        Vetor<T> res(this->tamanho);

        for (int i = 0; i < this->tamanho; i++) {
            res.v[i] = this->v[i] + b.v[i];
        }

        return res;
    }

    template <class T>
    Vetor<T>& Vetor<T>::operator-=(const Vetor<T>& b) {
        if (this->tamanho != b.tamanho)
            throw myexception("Vetores com tamanhos diferentes.2");
        for (int i = 0; i < this->tamanho; i++) {
            this->v[i] -= b.v[i];
        }
        return *this;
    }

    template <class T>
    const Vetor<T> Vetor<T>::operator-(const Vetor<T>& b) const {
        Vetor<T> res;
        return (res = *this) -= b;
    }

    template <class T>
    const Vetor<T> Vetor<T>::operator-() const { // unario
        Vetor<T> res(this->tamanho);
        for (int i = 0; i < this->tamanho; i++) {
            res[i] = -this->v[i];
        }
        return res;
    }

    template <class T>
    const Vetor<T> Vetor<T>::operator*(const T& b) const {
        Vetor<T> res(this->tamanho);
        for (int i = 0; i < this->tamanho; i++) {
            res[i] = this->v[i] * b;
        }
        return (res);
    }

    template <class T>
    const T Vetor<T>::operator*(const Vetor<T>& b) const {
        T soma(0);

        if (this->tamanho != b.tamanho)
            throw myexception("Vetores com tamanhos diferentes.3");
        for (int i = 0; i < this->tamanho; i++) {
            soma = soma + this->v[i] * b.v[i];
        }
        return soma;
    }

    template <class T>
    const T Vetor<T>::dif(const Vetor<T> b) const {
        if (this->tamanho != b.tamanho)
            throw myexception("Vetores com tamanhos diferentes.4");
        return ( ((*this) - b).max_mod());
    }

    template <class T>
    const T Vetor<T>::dif_rel(const Vetor<T> b) const {
        if (this->tamanho != b.tamanho)
            throw myexception("Vetores com tamanhos diferentes.5");
        return ( ((*this) - b).max_mod() / (*this).max_mod());
    }

    template <class T>
    const T Vetor<T>::max_mod() const {
        T max(0);

        for (int i = 0; i < this->tamanho; i++) {
            if (modulo((*this)[i]) > max)
                max = modulo((*this)[i]);
        }
        return max;
    }

    template <class T>
    const T Vetor<T>::norma() const {
        T soma(0);

        for (int i = 0; i < this->tamanho; i++) {
            soma += (*this)[i] * (*this)[i];
        }
        return sqrt(soma);
    }

} //namespace std

#endif

