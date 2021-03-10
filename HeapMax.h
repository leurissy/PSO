/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HeapMax.h
 * Author: wilson
 *
 * Created on 12 de setembro de 2020, 14:06
 */

#ifndef _HEAPMAX_H_
#define _HEAPMAX_H_


#include <initializer_list>
#include "myexception.h"
#include "Arranjo.h"

namespace std {

    template <class T>
    class HeapMax : public Arranjo<T> {
    private:
        int comprimento;
        void troca(int i, int j);
        int Pai(int i);
        int FilhoEsq(int i);
        int FilhoDir(int i);
        void heap_fica(int i);
    public:

        HeapMax() : Arranjo<T>(), comprimento(0) {
        }

        HeapMax(int n) : Arranjo<T>(n), comprimento(0) {
        }

        HeapMax(initializer_list<T> args) : Arranjo<T>(args) {
            comprimento = this->tamanho;
        }

        HeapMax(const Arranjo<T>& b) : Arranjo<T>(b), comprimento(b.getTamanho()) {
        }
        
        HeapMax(const HeapMax& b) : Arranjo<T>(b), comprimento(b.comprimento) {
        }
        void transforma_heap();
        void inserir(const T& item);
        void incrementar_chave(int i, const T& item);
        T retirar();
        T consultarTopo();
        int getComprimento() const;
        int busca(const T& item);

        friend ostream& operator<<(ostream& out, const HeapMax<T>& b) {
            for (int i = 0; i < b.comprimento; ++i) {
                out << b[i] << "\t";
            }
            out << endl;
            return out;
        }
    };

    template <class T>
    void HeapMax<T>::troca(int i, int j) {
        T aux;

        aux = this->v[i];
        this->v[i] = this->v[j];
        this->v[j] = aux;
    }

    template <class T>
    int HeapMax<T>::Pai(int i) {
        return (i + 1) / 2 - 1;
    }

    template <class T>
    int HeapMax<T>::FilhoEsq(int i) {
        return 2 * i + 1;
    }

    template <class T>
    int HeapMax<T>::FilhoDir(int i) {
        return 2 * i + 2;
    }

    //heap_fica minimo

    template <class T>
    void HeapMax<T>::heap_fica(int i) {
        int f_esq, f_dir, maior;

        f_esq = FilhoEsq(i);
        f_dir = FilhoDir(i);
        maior = i;
        if (f_esq < this->comprimento && this->v[f_esq] > this->v[i])
            maior = f_esq;
        if (f_dir < this->comprimento && this->v[f_dir] > this->v[maior])
            maior = f_dir;
        if (maior != i) {
            troca(i, maior);
            heap_fica(maior);
        }
    }

    //transforma vetor em heap minimo

    template <class T>
    void HeapMax<T>::transforma_heap() {
        for (int i = this->comprimento / 2 - 1; i >= 0; i--) {
            heap_fica(i);
        }
    }

    template <class T>
    void HeapMax<T>::incrementar_chave(int i, const T& chave) {
        if (chave < this->v[i])
            throw myexception("Nova chave menor que a atual.");

        while (i > 0 && chave > this->v[Pai(i)]) {
            this->v[i] = this->v[Pai(i)];
            i = Pai(i);
        }
        this->v[i] = chave;
    }

    template <class T>
    void HeapMax<T>::inserir(const T& chave) {
        if (this->comprimento >= this->tamanho)
            throw myexception("Estouro da heap.");

        this->v[this->comprimento] = chave;
        this->comprimento++;
        incrementar_chave(this->comprimento - 1, chave);
    }

    //template <class T>
    //void HeapMax<T>::inserir( const T& item ) {
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
    T HeapMax<T>::retirar() {
        T topo;

        if (this->comprimento == 0)
            throw myexception("Esvaziamento da lista.");

        topo = this->v[0];
        this->comprimento--;
        this->v[0] = this->v[this->comprimento];
        heap_fica(0);

        return topo;
    }

    template <class T>
    T HeapMax<T>::consultarTopo() {
        if (this->comprimento == 0)
            throw myexception("Esvaziamento da lista.");

        return this->v[0];
    }

    template <class T>
    int HeapMax<T>::getComprimento() const {
        return this->comprimento;
    }

    template <class T>
    int HeapMax<T>::busca(const T& item) {
        for (int i = 0; i < this->comprimento; i++) {
            if (item == this->v[i])
                return i;
        }
        return -1;
    }

} // namespace std


#endif /* HEAPMAX_H */

