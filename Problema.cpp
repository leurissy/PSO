#include "Problema.h"
#include "VetTop.h"
#include "Smith.h"
#include <cstdlib>
#include <cfloat>
#include <ctime>
#include <sstream>
#include <iomanip>

	
namespace std {
	
Problema::Problema() : dimensao(2) {
	
	canto_superior = Ponto(dimensao);
	canto_inferior = Ponto(dimensao, INFINITY);

//	for( int j = 0; j < dimensao; j++ ) {
//		canto_superior[j] = 0.0;
//		canto_inferior[j] = INFINITY;
//	}
	
	this->tamanho = 0;

	//inicializa a semente do gerador de numeros pseudo-randomicos
	srand (time(NULL));
}

Problema::Problema(const string nomearq) {
	le_instancia(nomearq);
	    
	//inicializa a semente do gerador de numeros pseudo-randomicos
	srand (time(NULL));
}

void Problema::le_instancia( const string nomearq ) {
	ifstream arquivo;
	string palavra;
	int quant, numero;

	arquivo.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
	try {
		arquivo.open( nomearq, ifstream::in );
		
		arquivo >> quant;
		arquivo >> dimensao;
		
		// Inicializa a lista de posicoes
        pontos_obrigatorios = Vetor<Ponto>(quant);
        // inicializa os cantos
		canto_superior = Ponto(dimensao);
		canto_inferior = Ponto(dimensao, INFINITY);
		
//		for( int j = 0; j < dimensao; j++ ) {
//			canto_superior[j] = 0.0;
//			canto_inferior[j] = INFINITY;
//		}
	
		// Le os dados
		for( int i = 0; i < quant; i++ ) {
			Ponto ponto(dimensao);
			for( int j = 0; j < dimensao; j++ ) {
			  	arquivo >> ponto[j];
				if( ponto[j] > canto_superior[j] ) {
					canto_superior[j] = ponto[j];
				}	
				if( ponto[j] < canto_inferior[j] ) {
					canto_inferior[j] = ponto[j];
				}	
			}
            pontos_obrigatorios[i] = ponto ;
//		  	cout << pontos_obrigatorios[i] << endl;
		}
		arquivo.close();

        this->tamanho = quant;
		
	} catch(...) {
		cerr << "Erro na leitura do arquivo de instancia." << endl;
		exit( EXIT_FAILURE );
	}
}

int Problema::getTamanho() const {
	// nao eh verdade se houver pontos obrigatorios duplicados
	return this->tamanho;
}

int Problema::getUltimaAtualizacao() const {
	return this->ultima_atualizacao;
}

void Problema::gera_particulas_aleatorizado( int quant ) {
	particulas = Vetor<Solucao>(quant);

	for( int i = 0; i < quant; i++ ) {
		Solucao solucao(pontos_obrigatorios);
		solucao.geraSteinerAleatorio( canto_superior, canto_inferior );
		particulas[i] = solucao;
		
//		// debugando
//		cout << "Solucao: " << endl << solucao << endl;		
	}	
}

double Problema::swarm_particle( int num_particulas, int max_iteracoes, double peso, double c1, double c2 ) {

	gera_particulas_aleatorizado(num_particulas);
	linha_do_tempo = list<LinhaDoTempo>();
	Tempo tempo_execucao;
	
	int melhor_particula_global;
	Vetor<Solucao> melhores_particulas(particulas);
	double melhor_custo_global = INFINITY;
	double melhor_custo_individual[num_particulas];
	
	Solucao melhorparticula;//<<==
	
	for( int i = 0; i < num_particulas; i++ ) {
		double custo_individual = particulas[i].custo();
		melhor_custo_individual[i] = custo_individual;
		if( custo_individual < melhor_custo_global ) {
			
			melhorparticula=particulas[i];  //<<==
			melhor_custo_global = custo_individual;
			melhor_particula_global = i;
			//cout << "Custo inicial: " << setprecision(20) << fixed << custo_individual << endl;
			linha_do_tempo.push_back( LinhaDoTempo(0, i, tempo_execucao.getDecorrido(), melhor_custo_global) ) ;
		}
	}


	ultima_atualizacao = 0;
	for( int k = 1; k <= max_iteracoes; k++ ) {
		int nova_melhor_particula_global = melhor_particula_global;
		double novo_melhor_custo_global = melhor_custo_global;
//		Solucao gbest = melhores_particulas[melhor_particula_global];
//		double soma = 0.0;
//		double soma_do_quadrado = 0.0;

		for( int i = 0; i < num_particulas; i++ ) {
//			cout << "Particula " << i+1 << endl;
			// mudanca na particula[i]
			Vetor<Ponto> steiner_anterior = particulas[i].getSteiner();
			
			/****  comentei e 17/06/2019
			if( k == 1 ) {
	//			particulas[i].setSteiner( particulas[i].passo_de_particula( melhores_particulas[i], gbest, peso, c1, c2 ) );
				particulas[i].setSteiner( particulas[i].passo_de_particula( melhores_particulas[i], melhores_particulas[melhor_particula_global], peso, c1, c2 ) );
				particulas[i].geraMatrizDeAdjacencia();
				particulas[i].reOrganiza();
			} else {
				particulas[i].caminha( melhores_particulas[i].getSteiner() );
	//			particulas[i].caminha( gbest.getSteiner() );
				particulas[i].caminha( melhores_particulas[melhor_particula_global].getSteiner() );
			}
			****/
			    /****  comentei e 17/06/2019 - componente cognitiva
				particulas[i].caminha( melhores_particulas[i].getSteiner() );
	            ****/ 
				//componente social
				particulas[i].caminha( melhores_particulas[melhor_particula_global].getSteiner() );
			

			// selecao das novas melhores particulas
//			double custo_individual = particulas[i].custo();
            
			double custo_individual = particulas[i].custoPorSmith();
			particulas[i].setSteiner(particulas[i].smith.getSteiner());
			if( custo_individual < melhor_custo_individual[i] ) {
				melhor_custo_individual[i] = custo_individual;
				melhores_particulas[i] = particulas[i];
				if( custo_individual < novo_melhor_custo_global ) {
					steiner_best = melhores_particulas[i].getSteiner();
					novo_melhor_custo_global = custo_individual;
					nova_melhor_particula_global = i;
					ultima_atualizacao = k;
					//cout << "Custo por Smith: " << setprecision(20) << fixed << custo_individual << endl;
					linha_do_tempo.push_back( LinhaDoTempo(k, i, tempo_execucao.getDecorrido(), melhor_custo_global) ) ;
				}
			}
			/****  comentei e 17/06/2019
			particulas[i].setVelocidadePontosSteiner( particulas[i].getSteiner() - steiner_anterior );
			****/
		}
		melhor_particula_global = nova_melhor_particula_global;
		melhor_custo_global = novo_melhor_custo_global;
		
		//melhorparticula.solucao(particulas[melhor_particula_global]); //<<===
		melhorparticula=particulas[melhor_particula_global];  //<<==
		
		cout << setprecision(20) << fixed;
//		cout << "Iteracao " << k << ": - melhor FST: " << melhores_particulas[melhor_particula_global].custo() << endl;
        if(k==1||k%10==0){
		  cout << "Iteracao " << k << ": - melhor FST por Smith: " << melhor_custo_global << endl;
		  cout << endl;
	    }

	}
	melhor_solucao = melhores_particulas[melhor_particula_global];
	
	//cout << "\nMelhor Solucao ate o momento ";
	//cout << "\n arestas "<< melhorparticula.grafo.getArestas();
	//cout << "\n*******ver o que acontece*******\n\n************\n\n";
	/***esse debugando funciona****
	melhor_solucao.debugando("****MELHOR SOLUCAO****");
	***/
	
	return melhor_custo_global;
}

string Problema::LinhaDoTempo::str() const {
	stringstream out;
	out << setprecision(6) << fixed;
	out << iteracao << ";" << particula << ";" << ldtos(tempo,15) << ";" << ldtos(custo,15) << endl;
	return out.str();
}

string Problema::getLinhaDoTempo() const {
	stringstream out;
	out << "\"iteracao\";\"particula\";\"tempo decorrido\";\"custo\"" << endl;
	for( auto x : linha_do_tempo ) {
		out << x;
	}
	return out.str();
}

string Problema::getVetTop() const {
	stringstream out;
	//out << Grafo2vetTop( melhor_solucao.grafo.getArestas() );
	out << melhor_solucao.grafo.getArestas();
	return out.str();
}

const Solucao& Problema::getMelhorSolucao() const {
	return melhor_solucao;
}


} //namespace std


