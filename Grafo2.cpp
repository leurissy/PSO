#include "Grafo2.h"
#include "comum.h"

namespace std {

Grafo2::Grafo2( int n, int d, int t ) : num_classes(n), dimensao(d), tamanho(t) {
	tam_vet = pot( num_classes, dimensao );
//		cout << "tam_vet " << tam_vet << endl;
	adja = Vetor<list<int>>(tam_vet);
	posicao = Vetor<int>(tamanho);
	grau = Vetor<int>(tamanho);
	canto_inferior = Ponto(dimensao);
	canto_superior = Ponto( dimensao, 1.0 );
}

Grafo2::Grafo2( int n, int d, int t, const Ponto& ci, const Ponto& cs ) : num_classes(n), dimensao(d), tamanho(t), canto_inferior(ci), canto_superior(cs) {
	tam_vet = pot( num_classes, dimensao );
//		cout << "tam_vet " << tam_vet << endl;
	adja = Vetor<list<int>>(tam_vet);
	posicao = Vetor<int>(tamanho);
	grau = Vetor<int>(tamanho);
}

void Grafo2::setCantoInferior( const Ponto& ci ) {
	canto_inferior = ci;
}

void Grafo2::setCantoSuperior( const Ponto& cs ) {
	canto_superior = cs;
}

void Grafo2::cubo( int dim, int pos, int i ) {
	if( pos < 0 || pos >= tam_vet ) {
//		cout << "pos " << pos << endl;
//		cout << "i " << i << endl;
		throw myexception("Funcao cubo: indice fora da faixa.");
	}
//		cout << "Calculando pos= " << pos << " dim " << dim << endl;
	if( dim == 1 ) {
		if( pos%num_classes-1 >= 0 ) {
//				cout << "colocando " << i << " na classe " << pos-1 << endl;
			adja[pos-1].push_back(i);
		}
		adja[pos].push_back(i);
//				cout << "colocando " << i << " na classe " << pos << endl;
		if( pos%num_classes+1 < num_classes ) {
			adja[pos+1].push_back(i);
//				cout << "colocando " << i << " na classe " << pos+1 << endl;
		}
	} else {
		int clas_pot_dim_1 = pot( num_classes, dim-1 );
		int clas_pot_dim = clas_pot_dim_1*num_classes;
		if( pos%clas_pot_dim-clas_pot_dim_1 >= 0 ) {
			cubo( dim-1, pos-clas_pot_dim_1, i );
		}
		cubo( dim-1, pos, i );
		if( pos%clas_pot_dim+clas_pot_dim_1 < clas_pot_dim ) {
			cubo( dim-1, pos+clas_pot_dim_1, i );
		}
	}
}

void Grafo2::addPonto( int i, const Ponto& ponto ) {
//		int pos[dimensao];
	int pos_vet = 0;
	for( int d = dimensao-1; d >= 0; d-- ) {
//			pos[d] = static_cast<int>(pontos_obrigatorios[i][d]*num_classes);
//			cout << "pos[d] " << pos[d] << endl;
		double normalizado = ( ponto[d] - canto_inferior[d] )/( canto_superior[d] - canto_inferior[d] );
		if( normalizado >= 1.0 ) {
			pos_vet = pos_vet * num_classes + num_classes - 1;
		} else if( normalizado < 0.0 ) {
			pos_vet = pos_vet * num_classes;
		} else {
			pos_vet = pos_vet * num_classes + static_cast<int>(normalizado*num_classes);
		}
	}
//	if( pos_vet < 0 || pos_vet >= tam_vet ) {
//		cout << "pos_vet " << pos_vet << endl;
//		cout << "i " << i << endl;
//		cout << "ponto " << ponto << endl;
//		system("pause");
//	}
	posicao[i] = pos_vet;
	cubo( dimensao, pos_vet, i );
}

const list<int>& Grafo2::adj( int i ) const {
	return adja[posicao[i]];
}

int Grafo2::inicio() const {
	return adja[0].front();
}


ostream& Grafo2::operator<< ( ostream& in ) const {
    return in;
}


} // namespace std


