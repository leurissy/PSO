#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "comum.h"
#include <string>
#include <cmath>
#include <cfloat>
#include "Problema.h"
#include "Tempo.h"
#include "myexception.h"


using namespace std;


int main(int argc, char* argv[]) {
	int num_particulas;
	int max_iteracoes;
	int num_repeticoes;
	double custo_minimo;

	ofstream arq_saida;
	ofstream arq_saida_result;
	ofstream arq_saida_linha_tempo;

	arq_saida.exceptions ( ofstream::failbit | ofstream::badbit );
	arq_saida_result.exceptions ( ofstream::failbit | ofstream::badbit );
	arq_saida_linha_tempo.exceptions ( ofstream::failbit | ofstream::badbit );

	if( argc  < 2 ) {
		cout << "Uso: " << argv[0] << " arq n_p n_m n_r [arq_saida]" << endl;
		cout << " Onde:" << endl;
		cout << "  arq: nome do arquivo da instancia do problema - obrigatorio" << endl;
		cout << "  n_p: numero de particulas do enxame - opcional. Valor padrao = 100" << endl;
		cout << "  n_m: numero maximo de movimentacoes das particulas - opcional. Valor padrao = 10" << endl;
		cout << "  n_r: numero maximo de repeticoes, para gerar estatisticas - opcional. Valor padrao = 1" << endl;
		cout << "  [arq_saida]: nome opcional do arquivo de saida" << endl;
		exit(EXIT_FAILURE);
	}
	
	num_particulas = ( argc > 2 ? atoi(argv[2]) : 100 );
	max_iteracoes = ( argc > 3 ? atoi(argv[3]) : 20 );
	num_repeticoes = ( argc > 4 ? atoi(argv[4]) : 1 );

	if( argc > 5 ) {
		try{
			arq_saida.open( argv[5], ios::out );
		} catch(exception e) {
			cerr << "Erro na abertura do arquivo de saida: " << argv[5] << endl;
			cerr << e.what() << endl;
			exit( EXIT_FAILURE );
		}
	}
	ostream& saida = ( argc > 5 ? arq_saida : cout );
	
	// gera arquivo de resultados estatisticos cujo home eh "result data_e_hora.txt"
	Tempo tempo_inicio;
	string data_hora = tempo_inicio.horario();
	string arq_nome_result = "result " + data_hora + ".csv";
	saida << "Gravando estatisticas em \"" << arq_nome_result << "\"" << endl;

	try {
		arq_saida_result.open( arq_nome_result, ios::out );
	} catch(exception e) {
		cerr << "Erro na abertura do arquivo de resultado: " << arq_nome_result << endl;
		cerr << e.what() << endl;
		exit( EXIT_FAILURE );
	}
	ostream& saida_result = arq_saida_result;

	// cria o objeto problema passando o nome do arquivo de instancia como parametro
	Problema p( argv[1] );
	
	saida << "Instancia: " << argv[1] << " - Tamanho: " << p.getTamanho() << endl;
	saida_result << "\"Instancia\";\"custo minimo\";\"tempo decorrido\";\"ultima atualizacao do gbest\";\"vetor de topologia\"" << endl;


	for( int i = 0; i < num_repeticoes; i++ ) {
		stringstream arq_nome_linha_tempo;
		arq_nome_linha_tempo << "linha do tempo - iteracao " << i+1 << " - " << data_hora << ".csv";
		saida << "Gravando linha do tempo em \"" << arq_nome_linha_tempo.str() << "\"" << endl;

		try {
			arq_saida_linha_tempo.open( arq_nome_linha_tempo.str(), ios::out );
		} catch(exception e) {
			cerr << "Erro na abertura do arquivo de resultado: " << arq_nome_linha_tempo.str() << endl;
			cerr << e.what() << endl;
			exit( EXIT_FAILURE );
		}
		ostream& saida_linha_tempo = arq_saida_linha_tempo;


		Tempo tempoSP;

		custo_minimo = p.swarm_particle( num_particulas, max_iteracoes, 0.7298, 1.49618, 1.49618 );
		double decorrido = tempoSP.getDecorrido();
		
		saida << "Melhor Particula: " << endl << p.getMelhorSolucao() << endl;
		//saida << "Vetor de topologia: " << p.getVetTop() << endl;

		int ultima_atualizacao = p.getUltimaAtualizacao();

		saida << "Execucao numero " << i+1 << endl;
		saida << "Swarm Particle: a solucao para numero de particulas = " << num_particulas << endl;
		saida << " e numero de iteracoes " << max_iteracoes << endl;
		saida << setprecision(20) << fixed;
		saida << "Melhor Custo Global: " << custo_minimo << endl;
		saida << "Tempo decorrido: " << decorrido << endl;
		saida << "Ultima atualizacao do gbest: " << ultima_atualizacao << endl;
		saida_result << argv[1] << ";" << ldtos( custo_minimo, 15 ) << ";" << ldtos( decorrido, 15 ) << ";" << ultima_atualizacao << ";" << p.getVetTop() << endl;
		saida << "============================================================================" << endl << endl << endl;
		saida_linha_tempo << p.getLinhaDoTempo();

		arq_saida_linha_tempo.close();
	}

	arq_saida_result.close();
	if( argc > 5 ) {
		arq_saida.close();
	}

	return EXIT_SUCCESS;
}

