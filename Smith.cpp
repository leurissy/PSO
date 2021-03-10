#include <iostream>
#include <iomanip>
#include "comum.h"
#include "Smith.h"
#include "VetTop.h"

namespace std {

Smith::Smith() : Smith(3,2) {}

Smith::Smith(int n, int d) : num_obrigatorios(n), dimensao(d) {
	int tamanho = 2*num_obrigatorios-2;
	ponto = Vetor<Ponto>(tamanho+1);
	aresta = Vetor<Aresta>(tamanho);
	adj = Vetor< Vetor<int> >(num_obrigatorios-1);
	comprAresta = Vetor< Vetor<double> >(num_obrigatorios-1);
	B = Vetor< Vetor<double> >(num_obrigatorios+1);
	C = Vetor<Ponto>(num_obrigatorios+1);
	eqnstack = Vetor<int>(num_obrigatorios+1);
	leafQ = Vetor<int>(num_obrigatorios+1);
	val = Vetor<int>(num_obrigatorios+1);
	for( int i = 0; i < tamanho+1; ++i ) {
		ponto[i] = Ponto(dimensao);
		if( i < num_obrigatorios-1 ) {
			adj[i] = Vetor<int>(3);
			comprAresta[i] =  Vetor<double>(3);
		}
		if( i < num_obrigatorios+1 ) {
			B[i] =  Vetor<double>(3);
			C[i] = Ponto(dimensao);
		}
	}
}

Smith::Smith(const Vetor<Ponto>& obrigatorios) : Smith(obrigatorios.getTamanho(), obrigatorios[0].getTamanho()) {
	escala = 0.0;
	for( int i = 0; i < num_obrigatorios; ++i ) {
		ponto[i+1] = obrigatorios[i];
		for (int j = 0; j < dimensao; j++) {
			double q = ponto[i+1][j] - ponto[1][j];
			if (q < 0.0)
				q = -q;
			if (q > escala)
				escala = q;
		}
	}
}

Smith::Smith( const Smith& b ) {
	num_obrigatorios = b.num_obrigatorios;
	dimensao = b.dimensao;
	ponto = b.ponto;
	escala = b.escala;
	aresta = b.aresta;
	adj = b.adj;
	comprAresta = b.comprAresta;
	topvec = b.topvec;
}

void Smith::setObrigatorios( const Vetor<Ponto>& obrigatorios ) {
	if( obrigatorios.getTamanho() != num_obrigatorios )
		throw myexception("Smith::setObrigatorios - Quantidade de pontos obrigatorios incompativel.");
	escala = 0.0;
	for( int i = 0; i < num_obrigatorios; ++i ) {
		ponto[i+1] = obrigatorios[i];
		for (int j = 0; j < dimensao; j++) {
			double q = ponto[i+1][j] - ponto[1][j];
			if (q < 0.0)
				q = -q;
			if (q > escala)
				escala = q;
		}
	}
}

void Smith::setSteiner( const Vetor<Ponto>& steiner ) {
	int num_steiner;
	if( ( num_steiner = steiner.getTamanho() ) != num_obrigatorios-2 )
		throw myexception("Smith::setSteiner - Quantidade de pontos de Steiner incompativel.");

	for( int i = 0; i < num_steiner; ++i ) {
		ponto[i+num_obrigatorios+1] = steiner[i];
	}
}

void Smith::buildtree( const Vetor<int>& vet ) {
	topvec = vet;
	int k = topvec.getTamanho();
	register int e, m, j, sn, ea, eb, en;
	/* First build the tree corresponding to the null vector */
	m = num_obrigatorios+1;
	adj[1][0] = 1; adj[1][1] = 2; adj[1][2] = 3;
	aresta[1].de = 1; aresta[2].de = 2; aresta[3].de = 3;
	aresta[1].para = m; aresta[2].para = m; aresta[3].para = m;
	for (int d = 0; d < dimensao; d++)
		ponto[m][d] = (ponto[1][d]+ponto[2][d]+ponto[3][d])/3.0 + 0.001*escala*drand();

	for (int i = 0; i < k; i++) { 
		en = i+4; m = i+2; sn = m+num_obrigatorios;
		e = topvec[i]; ea = aresta[e].de; eb = aresta[e].para;
		adj[m][0] = ea; adj[m][1] = eb; adj[m][2] = en;
		m = ea - num_obrigatorios;
		if (m > 0) for (j = 0; j < 3; j++) if (adj[m][j] == eb) { adj[m][j] = sn; break; }
		m = eb - num_obrigatorios;
		if (m > 0) for (j = 0; j < 3; j++) if (adj[m][j] == ea) { adj[m][j] = sn; break; }
		aresta[e].para = sn; e = en+en-4; aresta[e].de = en; aresta[e].para = sn;
		e++; aresta[e].de = eb; aresta[e].para = sn;
		for (j = 0; j < dimensao; j++)
			ponto[sn][j] = (ponto[ea][j] + ponto[eb][j] + ponto[en][j])/3.0 + 0.001*escala*drand();
	}
}

void Smith::buildtree( const Arranjo<Aresta>& arestas ) {
	Vetor<int> grau(num_obrigatorios-1);
	int num_arestas;
	if( ( num_arestas = arestas.getTamanho() ) != 2*num_obrigatorios-3 )
		throw myexception("Smith::buildtree - Quantidade de arestas incompativel.");
	for( int e = 0; e < num_arestas; e++ ) {
		int d = aresta[e+1].de = arestas[e].de+1;
		int p = aresta[e+1].para = arestas[e].para+1;
//		cout << "aresta: " << aresta[e+1];
		if( d > num_obrigatorios ) {
			int pos = d-num_obrigatorios;
			adj[pos][grau[pos]] = p;
//			cout<< "adj[" << pos << "][" << grau[pos] << "] = " << p << endl;
			grau[pos]++;
		}
		if( p > num_obrigatorios ) {
			int pos = p-num_obrigatorios;
			adj[pos][grau[pos]] = d;
//			cout<< "adj[" << pos << "][" << grau[pos] << "] = " << d << endl;
			grau[pos]++;
		}
	}
}

void Smith::buildtree( const Grafo& grafo ) {
	buildtree( grafo.getArestas() );
}

double Smith::length() {
	register int m, i2, i, j; int n0, n1, n2, k1; double leng, t;
	leng = 0.0; k1 = num_obrigatorios - 2;
	for (i = 1; i <= k1; i++) {
		i2 = i + num_obrigatorios;
		n0 = adj[i][0]; n1 = adj[i][1]; n2 = adj[i][2];
		if (n0 < i2) {
			t = dist(n0, i2); leng += t; comprAresta[i][0] = t; n0 -= num_obrigatorios;
			if (n0 > 0) for (j = 0; j < 3; j++) if (adj[n0][j] == i2) { comprAresta[n0][j] = t; break; }
		}
		if (n1 < i2) {
			t = dist(n1, i2); leng += t; comprAresta[i][1] = t; n1 -= num_obrigatorios;
			if (n1 > 0) for (j = 0; j < 3; j++) if (adj[n1][j] == i2) { comprAresta[n1][j] = t; break; }
		}
		if (n2 < i2) {
			t = dist(n2, i2); leng += t; comprAresta[i][2] = t; n2 -= num_obrigatorios;
			if (n2 > 0) for (j = 0; j < 3; j++) if (adj[n2][j] == i2) { comprAresta[n2][j] = t; break; }
		}
	}
	return (leng);
}

void Smith::optimize(double tol)
{
#define prep(a,b,c) if (b > num_obrigatorios) { val[i]++; B[i][a] = c; } \
	else for (m = 0; m < dimensao; m++) C[i][m] += ponto[b][m]*c;
//	double B[NMAX][3];
//	double C[NMAX][MAXDIM];
//	int eqnstack[NMAX], leafQ[NMAX], val[NMAX];
	int i, m, j, i2;  int n0, n1, n2, lqp, eqp, k1;  double q0, q1, q2, t;
	lqp = eqp = 0; k1 = num_obrigatorios - 2;
	/* First: compute B array, C array, and valences. Set up leafQ. */
	for (i = k1; i > 0; i--) {
		n0 = adj[i][0]; n1 = adj[i][1]; n2 = adj[i][2];
		q0 = 1.0 / (comprAresta[i][0] + tol); q1 = 1.0 / (comprAresta[i][1] + tol); q2 = 1.0 / (comprAresta[i][2] + tol);

		/* Have now figured out reciprocal distances q0, q1, q2 from
		 * Steiner pt. i to neighbors n0, n1, n2 */
		t = q0 + q1 + q2; q0 /= t; q1 /= t; q2 /= t;
		val[i] = 0; B[i][0] = B[i][1] = B[i][2] = 0.0;
		for (m = 0; m < dimensao; m++) { C[i][m] = 0.0; }

		prep(0, n0, q0); prep(1, n1, q1); prep(2, n2, q2);

		/* Now: Steiner point i has Steiner valence val[i];
		 * coords obey eqns ponto[i+num_obrigatorios][] = sum(j)of B[i][j]*ponto[nj][] + C[i][] */
		if (val[i] <= 1) { leafQ[lqp] = i; lqp++; } /* puts leafs on leafQ */
	} /* Have set up equations - now to solve them. */
	/* Second: eliminate leaves */
	while(lqp > 1) {
		lqp--; i = leafQ[lqp]; val[i]--; i2 = i + num_obrigatorios;
		/* now to eliminate leaf i */
		eqnstack[eqp] = i; eqp++; /* push i onto stack */
		for (j = 0; j < 3; j++) if (B[i][j] != 0.0) break; /* neighbor is #j */
		q0 = B[i][j];
		j = adj[i][j] - num_obrigatorios; /* neighbor is j */
		val[j]--; if (val[j] == 1) { leafQ[lqp] = j; lqp++; } /* new leaf? */
		for (m = 0; m < 3; m++) if (adj[j][m] == i2) break;
		q1 = B[j][m]; B[j][m] = 0.0;
		t = 1.0 - q1*q0; t = 1.0 / t;
		for (m = 0; m < 3; m++) B[j][m] *= t;
		for (m = 0; m < dimensao; m++) { C[j][m] += q1*C[i][m]; C[j][m] *= t; }
	}
	/* Third: Solve 1-vertex tree! */
	i = leafQ[0]; i2 = i + num_obrigatorios;
	for (m = 0; m < dimensao; m++) ponto[i2][m] = C[i][m];

	/* Fourth: backsolve */
	while (eqp > 0) {
		eqp--; i = eqnstack[eqp]; i2 = i + num_obrigatorios;
		for (j = 0; j < 3; j++) if (B[i][j] != 0.0) break; /* neighbor is #j */
		q0 = B[i][j];
		j = adj[i][j]; /* neighbor is j */
		for (m = 0; m < dimensao; m++) ponto[i2][m] = C[i][m] + q0*ponto[j][m];
	}

	return;
}

double Smith::error()
{ /* Returns the error figure of tree T with Steiner coords in ponto[][].
   * Assumes aresta lengths have been pre-stored in array comprAresta[][]. */
	int i, m, i2, n0, n1, n2;  int k1;  double r, s, t, efig, d01, d12, d02;
	k1 = num_obrigatorios - 2; efig = 0.0;
	for (i = 1; i <= k1; i++) {
		i2 = i + num_obrigatorios;
		n0 = adj[i][0]; n1 = adj[i][1]; n2 = adj[i][2];

		d12 = d01 = d02 = 0.0;
		for (m = 0; m < dimensao; m++) {
			t = ponto[i2][m];
			r = ponto[n0][m] - t; s = ponto[n1][m] - t; t = ponto[n2][m] - t;
			d12 += s*t; d01 += r*s; d02 += r*t;
		}
		/* only angles < 120 cause error */
		t = d12 + d12 + comprAresta[i][1]*comprAresta[i][2]; if (t > 0.0) efig += t;
		t = d01 + d01 + comprAresta[i][0]*comprAresta[i][1]; if (t > 0.0) efig += t;
		t = d02 + d02 + comprAresta[i][0]*comprAresta[i][2]; if (t > 0.0) efig += t;
	}
	efig = sqrt(efig); return (efig);
}

double Smith::otimiza_maior_que_3( double precisao ) {
	double q, r;

	q = length();
	r = error();
	do {
		optimize(precisao*r/num_obrigatorios);
		q = length();
		r = error();
	} while (r > q*precisao);

	return q;
}

double Smith::dist(int a, int b) const {
	double r, t = 0.0;
	for( int m = 0; m < dimensao; m++ ) {
		r = ponto[a][m] - ponto[b][m];
		t += r*r;
	}
	return sqrt(t);
}

Vetor<Ponto> Smith::getSteiner() const {
	Vetor<Ponto> steiner( num_obrigatorios-2 );

	for (int i = num_obrigatorios+1, j = 0; i <= 2*num_obrigatorios-2; i++, j++) {
		steiner[j] = ponto[i];
	}
	return steiner;
}

} // namespace std


