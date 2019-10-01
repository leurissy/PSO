#include "HeapMinChave.h"
#include "myexception.h"

namespace std {

HeapMinChave::HeapMinChave( int n ) : heap(vector<VerticeChave>(n)), comprimento(0) {
	aponta = vector<int>(n);
	for( int i = 0; i < aponta.size(); ++i ) {
		aponta[i] = -1;
	}
}


HeapMinChave::HeapMinChave( initializer_list<VerticeChave> args ) : heap( args ) {
	comprimento = heap.size();
	aponta = vector<int>(heap.size());
	for( int i = 0; i < comprimento; ++i ) {
		fixaAponta(i); //aponta[heap[i].vertice] = i;
	}
}


void HeapMinChave::troca( int i, int j ) {
	VerticeChave aux;

	aux = heap[i];
	heap[i] = heap[j];
	fixaAponta(i); //aponta[heap[i].vertice] = i;
	heap[j] = aux;
	fixaAponta(j); //aponta[heap[j].vertice] = j;
}

// metodo heapfy modificado de Cormen
void HeapMinChave::heap_fica( int i ) {
   	int f_esq, f_dir, menor;

	f_esq = filhoEsq( i );
	f_dir = filhoDir( i );
   	menor = i;
   	if( f_esq < this->comprimento && heap[f_esq] < heap[menor] )
		menor = f_esq;
   	if( f_dir < this->comprimento && heap[f_dir] < heap[menor] )
   		menor = f_dir;
	if( menor != i ) {
		troca( i, menor );
		heap_fica( menor );
	}
}

//transforma vetor em heap minimo
void HeapMinChave::transforma_heap() {
	for( int i = this->comprimento/2-1; i >= 0; i-- ) {
		heap_fica( i );
	}
}

void HeapMinChave::decrementar_chave( int i, const VerticeChave& item ) {
	if( item > heap[i] )
		throw myexception("Nova chave deve ser menor que a atual.");

	if( item.vertice != heap[i].vertice )
		throw myexception("Item deve ter o mesmo vertice que o atual.");

	while( i > 0 && item < heap[pai(i)] ) {
		heap[i] = heap[pai(i)];
		fixaAponta(i); //aponta[heap[i].vertice] = i;
		i = pai(i);
	}
   	heap[i] = item;
   	fixaAponta(i); //aponta[heap[i].vertice] = i;
}

void HeapMinChave::decrementar( const VerticeChave& item ) {
   	decrementar_chave( aponta[item.vertice], item );
}

void HeapMinChave::inserir( const VerticeChave& item ) {
	if( comprimento == heap.size() )
		throw myexception("Estouro da heap.");

	if( aponta[item.vertice] != -1 )
		throw myexception("Os vertices devem ser unicos.");

	heap[comprimento] = item;
	fixaAponta(comprimento); //aponta[heap[comprimento].vertice] = comprimento;
	comprimento++;
	decrementar_chave( comprimento - 1, item );
}


VerticeChave HeapMinChave::retirar() {
	return retirar(0);
}

VerticeChave HeapMinChave::retirar(int i) {
	VerticeChave topo;

	if( this->comprimento == 0 )
		throw myexception("Esvaziamento da lista.");
	if( i < 0 || i >= this->comprimento )
		throw myexception("Item inexistente.");

	topo = heap[i];
	comprimento-- ;
	aponta[heap[i].vertice] = -1;
	heap[i] = heap[comprimento];
	fixaAponta(i); //aponta[heap[i].vertice] = i;
	heap_fica( i );

	return topo;
}

VerticeChave& HeapMinChave::getVertice(int i) {
	if( i < 0 || i >= heap.size() )
		throw myexception("Item inexistente...");
	if( aponta[i] == -1 )
		throw myexception("Item nao pertence.");

	return heap[aponta[i]];
}

VerticeChave& HeapMinChave::getHeapVertice(int i) {
	if( i < 0 || i >= comprimento )
		throw myexception("Item inexistente...");

	return heap[i];
}


VerticeChave HeapMinChave::consultarTopo() {
	if( this->comprimento == 0 )
		throw myexception("Esvaziamento da lista.");

	return heap[0];
}

int HeapMinChave::getComprimento() const {
	return this->comprimento;
}

const VerticeChave& HeapMinChave::operator[] (int i) const {
	if( i < 0 || i >= comprimento)
		throw myexception("HeapMinChave::operator[] : Indice fora dos limites.");
	return heap[i];
}

} // namespace std


