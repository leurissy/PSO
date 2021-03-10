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
#include "GetOpt.h"


using namespace std;

string uso_txt = " [ opcoes ] arquivo\n"
        " Onde:\n"
        "  arquivo: nome do arquivo da instancia do problema - obrigatorio\n"
        " Opcoes:\n"
        "  -p n_p: numero de particulas do enxame. Valor padrao = 100\n"
        "  -m n_m: numero maximo de movimentacoes das particulas. Valor padrao = 10\n"
        "  -r n_r: numero maximo de repeticoes, para gerar estatisticas. Valor padrao = 1\n"
        "  -s arq_saida: nome opcional do arquivo de saida\n"
        "  -e : o arquivo da instancia contem resultado de processamento anterior\n"
        "  -n : novo processamento a partir da entrada de resultado anterior\n"
        "  -c n_c: numero de clusters. Valor padrao = 1\n"
        "  -o : remover outliers\n"
        "  -g : plota o grafo chamando GNUPlot\n"
        "  -t : gera estatisticas da linha de tempo\n"
        "  -i : incluir todas as arestas para a clusterizacao\n";

ofstream abre_arq_saida(const string& nome_arquivo_saida) {
    ofstream arq_saida;
    arq_saida.exceptions(ofstream::failbit | ofstream::badbit);

    try {
        if (!nome_arquivo_saida.empty())
            arq_saida.open(nome_arquivo_saida, ios::out);
    } catch (ofstream::failure e) {
        cerr << "Erro na abertura do arquivo de saida: " << nome_arquivo_saida << endl;
        cerr << e.what() << endl;
        throw e;
    }

    return arq_saida;
}

/*
 *
 */
int main(int argc, char* argv[]) {
    // processa linha de comando
    int num_particulas = 100;
    int max_iteracoes = 10;
    int num_repeticoes = 1;
    string nome_arquivo_saida;

    GetOpt opcao(argc, argv, "p:m:r:s:c:enogti", uso_txt);
    if (argc < 2) {
        opcao.uso();
        throw myexception("argc < 2");
        return 1;
    }
    if (opcao.temOpcao('p'))
        num_particulas = atoi(opcao.argOpcao('p'));
    if (opcao.temOpcao('m'))
        max_iteracoes = atoi(opcao.argOpcao('m'));
    if (opcao.temOpcao('r'))
        num_repeticoes = atoi(opcao.argOpcao('r'));
    if (opcao.temOpcao('s')) {
        nome_arquivo_saida = opcao.argOpcao('s');
        cout << "nome_arquivo_saida: \"" << nome_arquivo_saida << "\"" << endl;
    }
    bool proc_anterior = (opcao.temOpcao('e'));

    // cria o objeto problema passando o nome do arquivo de instancia como parametro
    char *arquivo_instancia = argv[opcao.resto()];
    Problema p(arquivo_instancia, proc_anterior);

    // Abre o arquivo de saida
    ofstream arq_saida = abre_arq_saida(nome_arquivo_saida);
    ostream& saida = (nome_arquivo_saida.empty() ? cout : arq_saida);

    // gera arquivo de resultados estatisticos cujo home eh "result data_e_hora.txt"
    Tempo tempo_inicio;
    string data_hora = tempo_inicio.horario();

    if (!proc_anterior || opcao.temOpcao('n')) {
        string arq_nome_result = "result " + data_hora + ".csv";
        cout << "Gravando estatisticas em \"" << arq_nome_result << "\"" << endl;
        cout << "Instancia: " << arquivo_instancia << " - Tamanho: " << p.getTamanho() << endl;

        ofstream arq_saida_result = abre_arq_saida(arq_nome_result);
        ostream& saida_result = arq_saida_result;
        saida_result << "\"Instancia\";\"custo minimo\";\"tempo decorrido\";\"ultima atualizacao do gbest\";\"vetor de topologia\"" << endl;

        for (int i = 0; i < num_repeticoes; i++) {
            double custo_minimo;


            Tempo tempoSP;

            custo_minimo = p.swarm_particle(num_particulas, max_iteracoes);
            double decorrido = tempoSP.getDecorrido();

            cout << "Melhor Particula: " << endl << p.getMelhorSolucao() << endl;
            //cout << "Vetor de topologia: " << p.getVetTop() << endl;

            int ultima_atualizacao = p.getUltimaAtualizacao();

            cout << "Execucao numero " << i + 1 << endl;
            cout << "Swarm Particle: a solucao para numero de particulas = " << num_particulas << endl;
            cout << " e numero de iteracoes " << max_iteracoes << endl;
            cout << setprecision(20) << fixed;
            cout << "Melhor Custo Global: " << custo_minimo << endl;
            cout << "Tempo decorrido: " << decorrido << endl;
            cout << "Ultima atualizacao do gbest: " << ultima_atualizacao << endl;
            cout << "============================================================================" << endl << endl << endl;

            saida_result << arquivo_instancia << ";" << ldtos(custo_minimo, 15) << ";" << ldtos(decorrido, 15) << ";" << ultima_atualizacao << ";" << p.getVetTop() << endl;

            if (opcao.temOpcao('t')) {
                // gera arquivo de resultados estatisticos cujo home eh "linha do tempo - iteracao..."
                stringstream arq_nome_linha_tempo;
                arq_nome_linha_tempo << "linha do tempo - iteracao " << i + 1 << " - " << data_hora << ".csv";
                cout << "Gravando linha do tempo em \"" << arq_nome_linha_tempo.str() << "\"" << endl;
                ofstream arq_saida_linha_tempo = abre_arq_saida(arq_nome_linha_tempo.str());
                ostream& saida_linha_tempo = arq_saida_linha_tempo;
                saida_linha_tempo << p.getLinhaDoTempo();
                arq_saida_linha_tempo.close();
            }
        }

        arq_saida_result.close();
    }
    if (opcao.temOpcao('s')) {
        saida << p.getSaidaDados();
    }

    if (opcao.temOpcao('c')) {
        int num_clusters = atoi(opcao.argOpcao('c'));
        if (num_clusters > 1) {
            cout << "Numero de clusters: " << num_clusters << endl;
            p.clusterizar(num_clusters, opcao.temOpcao('o'), !opcao.temOpcao('i'));
            cout << p.getSolucaoClusterizada() << endl;
        }
        if (opcao.temOpcao('g')) {
            p.getSolucaoClusterizada().plotar(data_hora);
        }
    } else if (opcao.temOpcao('g')) {
        p.getMelhorSolucao().plotar(data_hora);
    }

    if (!nome_arquivo_saida.empty()) {
        arq_saida.close();
    }

    return EXIT_SUCCESS;
}
