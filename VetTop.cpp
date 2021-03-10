#include "VetTop.h"
#include "comum.h"

namespace std {

Vetor<Aresta> vetTop2Grafo( const Vetor<int>& vetTop ) {
	int k, de, para;
	int num_obrigatorios = vetTop.size() + 3;
	int num_steiner = num_obrigatorios - 2;
	int tamanho = num_steiner + num_obrigatorios;
	Vetor<Aresta> arestas(tamanho-1);

	arestas[0] = Aresta( 0, num_obrigatorios );
	arestas[1] = Aresta( 1, num_obrigatorios );
	arestas[2] = Aresta( 2, num_obrigatorios );

	for( k = 0; k < num_obrigatorios-3; ++k ) {
		de = arestas[vetTop[k]-1].de;
		para = arestas[vetTop[k]-1].para;
		arestas[vetTop[k]-1] = Aresta( de, num_obrigatorios+k+1 );
		arestas[2*k+4] = Aresta( para, num_obrigatorios+k+1 );
		arestas[2*k+3] = Aresta( k+3, num_obrigatorios+k+1 ); // novo obrigatorio
	}

	return arestas;
}

void Grafo2vetTopRecur( Arranjo<Aresta>& arestas, int num_arestas, Vetor<int>& vet ) {
	int tamanho = arestas.size() + 1;
	if( tamanho % 2 != 0 )
		throw myexception("Grafo2vetTop - Quantidade de arestas incompativel.");
	if( num_arestas > tamanho-1 || (num_arestas + 1) % 2 != 0 )
		throw myexception("Grafo2vetTop - Numero de arestas incompativel.");
	int num_obrigatorios = (tamanho + 2)/2;

	if( num_arestas <= 3 ) {
		if( arestas[0].de > arestas[1].de )
			troca( arestas[0], arestas[1] );
		if( arestas[1].de > arestas[2].de )
			troca( arestas[1], arestas[2] );
		if( arestas[0].de > arestas[1].de )
			troca( arestas[0], arestas[1] );
//		cout << "Arestas 3 " << endl << arestas << endl;
		return;
	} else {
		int w, novo, obrigatorio, pos, de , para, pos_de, pos_para;
		pos = num_arestas-2;
		obrigatorio = (pos+3)/2;
		for( int w = num_arestas-1; w >= 0; --w ) {
			if( obrigatorio == arestas[w].de ) {
				novo = arestas[w].para;
				if( pos != w )
					troca( arestas[w], arestas[pos] );
				break;
			}
		}
//		cout << "novo " << novo << endl;
		for( w = num_arestas-1; w >= 0; --w ) {
//			cout << "w " << w << endl;
			if( arestas[w].de == novo ) {
//				cout << "Achou aresta[" << w << "] " << arestas[w] << endl;
				para = arestas[w].para;
				if( pos+1 != w )
					troca( arestas[w], arestas[pos+1] );
				pos_para = pos+1;
				break;
			}
			if( arestas[w].para == novo && w != pos ) {
//				cout << "Achou aresta[" << w << "] " << arestas[w] << endl;
				para = arestas[w].de;
				if( pos+1 != w )
					troca( arestas[w], arestas[pos+1] );
				pos_para = pos+1;
				break;
			}
		}
		for( --w; w >= 0; --w ) {
			if( arestas[w].de == novo ) {
//				cout << "Achou aresta[" << w << "] " << arestas[w] << endl;
				de = arestas[w].para;
				pos_de = w;
				break;
			}
			if( arestas[w].para == novo && w != pos ) {
//				cout << "Achou aresta[" << w << "] " << arestas[w] << endl;
				de = arestas[w].de;
				pos_de = w;
				break;
			}
		}
//		cout << "Nova aresta " << de << " " << para << endl;
		if( para < de ) {
			troca( de, para );
			troca( arestas[pos_de], arestas[pos_para] );
		}
		Aresta temp = arestas[pos_de];
		arestas[pos_de].de = de; arestas[pos_de].para = para;

		Grafo2vetTopRecur( arestas, num_arestas-2, vet );

		for( w = num_arestas-1; w >= 0; --w ) {
			if( arestas[w].de == de && arestas[w].para == para ) {
				arestas[w] = temp;
				vet[(num_arestas-5)/2] = w+1;
				break;
			}
		}

//		cout << "Arestas" << endl << arestas << endl;
	}
//	cout << "Arestas" << endl << arestas << endl;
}

Vetor<int> Grafo2vetTop( const Arranjo<Aresta>& arestas2 ) {
	int num_arestas = arestas2.getTamanho();
	int tamanho = num_arestas+1;
	int num_obrigatorios = (tamanho+2)/2;
	Arranjo<Aresta> arestas(arestas2);
	Vetor<int> vetTop(num_obrigatorios-3);

	Grafo2vetTopRecur( arestas, num_arestas, vetTop );

	return vetTop;
}

Vetor<int> Grafo2vetTop( Grafo& grafo, Vetor<Ponto>& steiner ) {
	int tamanho = grafo.getNumVertices();
	if( tamanho % 2 != 0 )
		throw myexception("Grafo2vetTop - Tamanho do grafo incompativel.");
	int num_obrigatorios = (tamanho + 2)/2;

	Vetor<Aresta> arestas(tamanho-1);
	for( int de = 0; de < num_obrigatorios; de++ ) {
		if( grafo.grau(de) != 1 )
			throw myexception("Grafo2vetTop - Ponto obrigatorio com grau diferente de 1.");
		int pos = ( de < 3 ? de : 2*de-3 );
		arestas[pos].de = de;
		arestas[pos].para = grafo.primAdj(de);
	}
	for( int de = num_obrigatorios, s = 4; de < tamanho; de++ ) {
		if( grafo.grau(de) != 3 )
			throw myexception("Grafo2vetTop - Ponto de Steiner com grau diferente de 3.");
		for( int para : grafo.adj(de) ) {
			if( de < para ) {
				arestas[s].de = de;
				arestas[s].para = para;
				s += 2;
			}
		}
	}

	Vetor<int> posicao(num_obrigatorios-2); // so para teste

	Vetor<int> vetTop( num_obrigatorios - 3 );
	for( int k = num_obrigatorios-4; k >= 0; --k ) {
		int para, j;
		int i = 2*k+3;
		int novo = arestas[i].para;
		for( j = i + 1; j > 2; j -= 2 ) {
			if( arestas[j].de == novo ) {
				para = arestas[j].para;
				break;
			}
			if( arestas[j].para == novo ) {
				para = arestas[j].de;
				break;
			}
		}
		if( j <= 2 ){
			throw myexception("Grafo2vetTop - Quantidade de arestas incompativel.");
		}
		if( j != i + 1 )
			troca(arestas[j], arestas[i+1]);

		while( --i >= 0 ) {
			if(arestas[i].para == novo) {
				arestas[i].para = para;
				break;
			}
			if (arestas[i].de == novo) {
				arestas[i].de = para;
				break;
			}
		}
		if( i < 0 )
			throw myexception("Grafo2vetTop - Indice negativo.");
		vetTop[k] = i+1;
//		cout << "novo: " << novo << endl;
//		cout << "Troca " << novo << " por " << k+num_obrigatorios+1 << endl;
		posicao[k+1] = novo;

	}
	posicao[0] = arestas[0].para;
	cout << "Vetor de posicao: " << posicao << endl;
	for( int i = num_obrigatorios-3; i >= 0; --i ) {
		int j = posicao[i] - num_obrigatorios;
		if( i != j ) {
//			cout << "Troca posicao " << j+num_obrigatorios << " por posicao " << i+num_obrigatorios << endl;
			cout << "Troca vertice " << posicao[i] << " por vertice " << posicao[j] << endl;
			troca( posicao[i], posicao[j] );
//			troca( steiner[i], steiner[j] );
//			grafo.trocaVertice( posicao[i], posicao[j] );
		}
	}
	cout << "Vetor de posicao: " << posicao << endl;
	return vetTop;
}

} // namespace std


