#ifndef _VETTOP_H_
#define _VETTOP_H_

#include "Vetor.h"
#include "Aresta.h"
#include "Grafo.h"
#include "Ponto.h"

namespace std {

Vetor<Aresta> vetTop2Grafo( const Vetor<int>& vetTop );
Vetor<int> Grafo2vetTop( const Vetor<Aresta>& arestas2 );
Vetor<int> Grafo2vetTop( Grafo& grafo, Vetor<Ponto>& steiner );
void Grafo2vetTopRecur( Vetor<Aresta>& arestas, int num_arestas, Vetor<int>& vet );

} // namespace std

#endif

