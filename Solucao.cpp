#include "Solucao.h"
#include <cstdlib>
#include "VerticeChave.h"
#include "HeapMinChave.h"
#include "comum.h"


namespace std {

    Solucao::Solucao() : Solucao(3) {
    }

    Solucao::Solucao(int tam) {
        if(tam < 3) {
            throw myexception("A solucao nao pode ter menos que 3 pontos obrigatorios.");
        }
        dimensao = 2;
        num_obrigatorios = tam;
        num_steiner = num_obrigatorios - 2;
        tamanho = num_obrigatorios + num_steiner;
        grafo = Grafo(tamanho);
        disponiveis = list<int>();
        pontos_obrigatorios = Vetor<Ponto>(num_obrigatorios);
        pontos_steiner = Vetor<Ponto>(num_steiner);
        velocidade_pontos_steiner = Vetor<Ponto>(num_steiner);
        smith = Smith(num_obrigatorios, dimensao);
        canto_inferior = Ponto(dimensao);
        canto_superior = Ponto(dimensao, 1.0);
    }

    Solucao::Solucao(const Vetor<Ponto>& obrigatorios) : Solucao(obrigatorios.getTamanho()) {
        dimensao = pontos_obrigatorios[0].getDimensao();
        pontos_obrigatorios = obrigatorios;
        smith = Smith(pontos_obrigatorios);
        canto_inferior = Ponto(dimensao);
        canto_superior = Ponto(dimensao, 1.0);
    }

    Solucao::Solucao(const Solucao& b) {
        dimensao = b.dimensao;
        num_obrigatorios = b.num_obrigatorios;
        num_steiner = b.num_steiner;
        tamanho = b.tamanho;
        grafo = b.grafo;
        disponiveis = b.disponiveis;
        pontos_obrigatorios = b.pontos_obrigatorios;
        pontos_steiner = b.pontos_steiner;
        velocidade_pontos_steiner = b.velocidade_pontos_steiner;
        smith = b.smith;
        canto_inferior = b.canto_inferior;
        canto_superior = b.canto_superior;
    }

    void Solucao::setObrigatorios(const Vetor<Ponto>& obrigatorios) {
        dimensao = pontos_obrigatorios[0].getDimensao();
        pontos_obrigatorios = obrigatorios;
        smith.setObrigatorios(obrigatorios);
        canto_inferior = Ponto(dimensao);
        canto_superior = Ponto(dimensao, 1.0);
    }

    const Vetor<Ponto>& Solucao::getObrigatorios() const {
        return pontos_obrigatorios;
    }

    void Solucao::setSteiner(const Vetor<Ponto>& steiner) {
        pontos_steiner = steiner;
    }

    const Vetor<Ponto>& Solucao::getSteiner() const {
        return pontos_steiner;
    }

    void Solucao::setVelocidadePontosSteiner(const Vetor<Ponto>& velocidade_steiner) {
        velocidade_pontos_steiner = velocidade_steiner;
    }

    const Vetor<Ponto>& Solucao::getVelocidadePontosSteiner() const {
        return velocidade_pontos_steiner;
    }

    void Solucao::setCantoInferior(const Ponto& ci) {
        canto_inferior = ci;
    }

    void Solucao::setCantoSuperior(const Ponto& cs) {
        canto_superior = cs;
    }

    void Solucao::geraSteinerAleatorio(const Ponto& canto_superior, const Ponto& canto_inferior) {
        this->canto_inferior = canto_inferior;
        this->canto_superior = canto_superior;
        // gera pontos de Steiner aleat�rios
        for (int i = 0; i < getNumSteiner(); i++) {
            pontos_steiner[i] = Ponto::geraAleatorio(canto_superior, canto_inferior);
        }
        // gera velocidade inicial nula
        int dimensao = canto_superior.getDimensao();
        for (int i = 0; i < getNumSteiner(); i++) {
            velocidade_pontos_steiner[i] = Ponto(dimensao);
        }
        geraMatrizDeAdjacencia();
        reOrganiza();
    }

    void Solucao::geraMatrizDeAdjacencia() {
        //	AGM_Prim(0);
        AGM_Prim2();
        removeNaoConformidade();
    }

    void Solucao::removeNaoConformidade() {
        // limpa pontos de steiner com grau 1
        limpaSteinerGrau1();

        // limpa pontos de steiner com grau 2 pela desigualdade triangular
        limpaSteinerGrau2();

        // sobrepoe pontos de steiner com grau maior que 1 por pontos obrigatorios
        corrigeObrigatoriosGrauDiferenteDe1();

        // sobrepoe pontos de obrigatorios com grau maior que 3 por outros pontos obrigatorios
        corrigeSteinerGrauDiferenteDe3();
    }

    void Solucao::AGM_Prim2() {
        int dimensao = pontos_obrigatorios[0].getDimensao();
        int num_classes = static_cast<int> (pow(tamanho / 2, 1.0 / dimensao));
        Grafo2 grafo2(num_classes, dimensao, tamanho, canto_inferior, canto_superior);
        HeapMinChave Q(tamanho);
        Arranjo<VerticeChave> verticesChave(tamanho);

        for (int i = 0; i < tamanho; i++) {
            grafo2.addPonto(i, ponto(i));
        }
        int r = grafo2.inicio();

        //	cout << "Q inicial: " << endl << Q << endl;
        for (int i = 0; i < tamanho; i++) {
            VerticeChave vc;
            if (i == r)
                vc.chave = 0.0; //key[r] == 0.0;
            vc.vertice = i;
            verticesChave[i] = vc;
            Q.inserir(vc);
            //		cout << "Vertice: " << vc << endl;
            //		cout << "Q: " << endl << Q << endl;
            grafo2.addPonto(i, ponto(i));
        }

        //	cout << "HEAP:" << endl;
        //	cout << Q << endl;

        while (Q.getComprimento() > 0) {
            VerticeChave u;
            VerticeChave v;

            u = Q.retirar();
            //		cout << "Extraindo u: " << u << endl;
            bool achou = false;
            for (auto j : grafo2.adj(u.vertice)) {
                if (j == u.vertice) continue;
                //			cout << Q << endl;
                if (Q.pertence(j)) {
                    achou = true;
                    v = Q.getVertice(j);
                    //					cout << "adjacente de " << u << ": " << v << endl;
                    double dist = distancia(u.vertice, v.vertice);
                    if (dist < v.chave) {
                        v.pai = u.vertice;
                        v.chave = dist;
                        verticesChave[v.vertice] = v;
                        //						cout << "v: " << v << endl;
                        Q.decrementar(v);
                    }
                }
            }
            if (!achou) { // grafo classificado disjunto
                //		cout << "passou por aqui" << endl;
                for (int j = 0; j < Q.getComprimento(); j++) { // o grafo eh completamente conectado
                    //			cout << Q << endl;
                    // v pertence a Q
                    VerticeChave v = Q[j];
                    //			cout << "adjacente de " << u << ": " << v << endl;
                    double dist = distancia(u.vertice, v.vertice);
                    if (dist < v.chave) {
                        v.pai = u.vertice;
                        v.chave = dist;
                        verticesChave[v.vertice] = v;
                        //				cout << "v: " << v << endl;
                        Q.decrementar(v);
                        //					Q.decrementar_chave(j, v);
                    }
                }
            }
            //		cout << "HEAP:" << endl;
            //		cout << Q << endl;
        }

        // limpa a matriz de adjacencia antes do c�lculo.
        grafo.limpaDados();

        for (int i = 0; i < verticesChave.size(); i++) {
            if (verticesChave[i].pai != -1) {
                grafo.addAresta(verticesChave[i].vertice, verticesChave[i].pai);
            }
        }
    }

    void Solucao::AGM_Prim(int r) {
        HeapMinChave Q(tamanho);
        //	HeapMin<VerticeChave> Q(tamanho);
        Arranjo<VerticeChave> verticesChave(tamanho);

        //	cout << "Q inicial: " << endl << Q << endl;
        for (int i = 0; i < tamanho; i++) {
            VerticeChave vc;
            if (i == r)
                vc.chave = 0.0; //key[r] == 0.0;
            vc.vertice = i;
            verticesChave[i] = vc;
            Q.inserir(vc);
            //		cout << "Vertice: " << vc << endl;
            //		cout << "Q: " << endl << Q << endl;
        }

        //	cout << "HEAP:" << endl;
        //	cout << Q << endl;

        while (Q.getComprimento() > 0) {
            VerticeChave u;
            //		VerticeChave v;

            u = Q.retirar();
            //		cout << "Extraindo u: " << u << endl;
            //		for ( auto j : grafo.adj(u.vertice) ) {
            for (int j = 0; j < Q.getComprimento(); j++) { // o grafo eh completamente conectado
                //			cout << Q << endl;
                // v pertence a Q
                VerticeChave v = Q[j];
                //			cout << "adjacente de " << u << ": " << v << endl;
                double dist = distancia(u.vertice, v.vertice);
                if (dist < v.chave) {
                    v.pai = u.vertice;
                    v.chave = dist;
                    verticesChave[v.vertice] = v;
                    //				cout << "v: " << v << endl;
                    //				Q.decrementar(v);
                    Q.decrementar_chave(j, v);
                }
            }
            //		cout << "HEAP:" << endl;
            //		cout << Q << endl;
        }

        // limpa a matriz de adjacencia antes do c�lculo.
        grafo.limpaDados();

        for (int i = 0; i < verticesChave.size(); i++) {
            if (verticesChave[i].pai != -1) {
                grafo.addAresta(verticesChave[i].vertice, verticesChave[i].pai);
            }
        }
    }

    double Solucao::custo() const {
        double custo = 0.0;
        for (int de = 0; de < tamanho; de++) {
            for (auto para : grafo.adj(de)) {
                if (de > para)
                    custo += distancia(de, para);
            }
        }
        return custo;
    }

    int Solucao::getNaoConformidade() const {
        int nao_conformidade = 0;
        for (int i = 0; i < tamanho; i++) {
            if (i < num_obrigatorios && grafo.grau(i) != 1 || i >= num_obrigatorios && grafo.grau(i) != 3) {
                nao_conformidade++;
            }
        }
        return nao_conformidade;
    }

    void Solucao::limpaSteinerGrau1() {
        // limpa pontos de steiner com grau 1 - versao com classe grafo
        disponiveis.clear();
        int i = num_obrigatorios;
        int prox_i = -1;
        while (i < getTamanho()) {
            if (grafo.grau(i) == 1) {
                int j = grafo.primAdj(i);
                grafo.remAresta(i, j);
                disponiveis.push_back(i);
                if (grafo.grau(j) == 1 && num_obrigatorios <= j && j < i) {
                    prox_i = j;
                }
            }
            if (prox_i == -1) {
                i++;
            } else {
                i = prox_i;
                prox_i = -1;
            }
        }
    }

    void Solucao::limpaSteinerGrau2() {
        // limpa pontos de steiner com grau 2 pela desigualdade triangular - versao com a classe grafo
        for (int i = num_obrigatorios; i < getTamanho(); i++) {
            if (grafo.grau(i) == 2) {
                int j = grafo.primAdj(i);
                int k = grafo.ultAdj(i);
                grafo.remAresta(i, j);
                grafo.remAresta(i, k);
                grafo.addAresta(j, k);
                disponiveis.push_back(i);
            }
        }
        //	cout << "Steiner liberados: " << disponiveis.size() << endl;
    }

    void Solucao::calculaPontoExato(int i) {
        if (disponiveis.empty())
            throw myexception("Naum ha pontos steiner disponiveis.");

        double menor_distancia_total = INFINITY;
        Ponto melhor_ponto_exato;
        int melhor_j = -1;
        int melhor_k = -1;
        for (list<int>::const_iterator it = grafo.adj(i).begin(); it != grafo.adj(i).end(); ++it) {
            int j = *it;
            list<int>::const_iterator it2 = it;
            for (++it2; it2 != grafo.adj(i).end(); ++it2) {
                int k = *it2;
                Ponto p1 = ponto(i);
                //			Ponto p1 = ( i < num_obrigatorios ? pontos_obrigatorios[i] : pontos_steiner[i - num_obrigatorios] );
                Ponto p2 = ponto(j);
                Ponto p3 = ponto(k);
                Ponto ponto_exato = steiner_exato(p1, p2, p3);
                double distancia_total = (p1 - ponto_exato).norma() + (p2 - ponto_exato).norma() + (p3 - ponto_exato).norma();
                if (distancia_total < menor_distancia_total) {
                    melhor_ponto_exato = ponto_exato;
                    menor_distancia_total = distancia_total;
                    melhor_j = j;
                    melhor_k = k;
                }
            }
        }
        int j = melhor_j;
        int k = melhor_k;

        // adiciona o ponto l a partir dos pontos i, j, k
        int l = disponiveis.front();
        disponiveis.pop_front();
        grafo.remAresta(i, j);
        grafo.remAresta(i, k);
        pontos_steiner[l - num_obrigatorios] = melhor_ponto_exato;
        grafo.addAresta(l, i);
        grafo.addAresta(l, j);
        grafo.addAresta(l, k);
    }


    // funcao corrigeObrigatoriosGrauDiferenteDe1() - versao ponto exato

    void Solucao::corrigeObrigatoriosGrauDiferenteDe1() {
        for (int i = 0; i < num_obrigatorios; i++) {
            while (grafo.grau(i) > 1) {
                calculaPontoExato(i);
            }
        }
    }


    // funcao corrigeSteinerGrauDiferenteDe3() - versao ponto exato

    void Solucao::corrigeSteinerGrauDiferenteDe3() {
        for (int i = num_obrigatorios; i < tamanho; i++) {
            while (grafo.grau(i) > 3) {
                calculaPontoExato(i);
            }
        }
    }

    void Solucao::trocaPontosSteiner(int i, int j) {
        if (i < num_obrigatorios || j < num_obrigatorios || i >= tamanho || j >= tamanho)
            throw myexception("Funcao trocaPontosSteiner: indice fora da faixa.");

        troca(pontos_steiner[i - num_obrigatorios], pontos_steiner[j - num_obrigatorios]);
        this->grafo.trocaVertice(i, j);
    }

    void Solucao::reOrganiza() {
        int j = 0;
        for (int i = num_obrigatorios; i < tamanho; i++) {
            while (j < num_obrigatorios && this->grafo.adj(j).front() < i) {
                j++;
            }
            if (j == num_obrigatorios)
                break;
            if (this->grafo.adj(j).front() > i) {
                trocaPontosSteiner(this->grafo.adj(j).front(), i);
                j++;
            }
        }
    }

    Vetor<Ponto> Solucao::passo_de_particula(const Solucao& melhor_solucao_propria, const Solucao& melhor_solucao_social, double peso, double c1, double c2) const {

        Vetor<Ponto> vel(velocidade_pontos_steiner);

        // solucao com diferentes valores rand�micos por dimensao
        for (int p = 0; p < vel.getTamanho(); p++) {
            for (int d = 0; d < vel[p].getDimensao(); d++) {
                // PSO Gbest com peso inercial
                vel[p][d] = peso * vel[p][d];
                vel[p][d] = vel[p][d] + c1 * alfa() * (melhor_solucao_propria.pontos_steiner[p][d] - this->pontos_steiner[p][d]);
                vel[p][d] = vel[p][d] + c2 * alfa() * (melhor_solucao_social.pontos_steiner[p][d] - this->pontos_steiner[p][d]);
            }
        }
        return ( pontos_steiner + vel);
    }

    void Solucao::caminha(const Vetor<Ponto>& b) {
        double custo_velho = custo();
        // Guarda dados
        int num_steiner_velho = num_steiner;
        int tamanho_velho = tamanho;
        Vetor<Ponto> pontos_steiner_velho = pontos_steiner;
        Vetor<Ponto> velocidade_pontos_steiner_velho = velocidade_pontos_steiner;
        Grafo grafo_velho = grafo;

        // Conjuga dados
        num_steiner = num_steiner_velho + b.getTamanho();
        tamanho = num_obrigatorios + num_steiner;
        pontos_steiner = Vetor<Ponto>(num_steiner);
        for (int i = 0; i < num_steiner_velho; i++) {
            pontos_steiner[i] = pontos_steiner_velho[i];
        }
        for (int i = 0; i < b.getTamanho(); i++) {
            pontos_steiner[i + num_steiner_velho] = b[i];
        }
        grafo = Grafo(tamanho);

        //	AGM_Prim(0);
        AGM_Prim2();
        removeNaoConformidade();

        // Arruma solucao expandida
        for (int i = num_obrigatorios; i < num_obrigatorios + num_steiner_velho; i++) {
            if (this->grafo.grau(i) == 0) {
                for (int j = num_obrigatorios + num_steiner_velho; j < tamanho; j++) {
                    if (this->grafo.grau(j) == 3) {
                        troca(pontos_steiner[i - num_obrigatorios], pontos_steiner[j - num_obrigatorios]);
                        this->grafo.trocaVertice(i, j);
                        break;
                    }
                }
            }
        }

        if (custo() < custo_velho) {
            pontos_steiner.resize(num_steiner_velho);
            grafo_velho.copia_reduzindo(grafo);
        } else {
            pontos_steiner = pontos_steiner_velho;
        }

        // Restaura dados
        num_steiner = num_steiner_velho;
        tamanho = tamanho_velho;
        grafo = grafo_velho;
    }

    double Solucao::custoPorSmith(double precisao) {
        smith.buildtree(grafo);
        smith.setSteiner(pontos_steiner);
        custo_por_Smith = smith.otimiza_maior_que_3(precisao);
        return custo_por_Smith;
    }

    double Solucao::distancia(int de, int para) const {
        if (de < 0 || para < 0 || de >= tamanho || para >= tamanho)
            throw myexception("Funcao Solucao::distancia: indice fora da faixa.");
        Ponto pd = (de < num_obrigatorios ? pontos_obrigatorios[de] : pontos_steiner[de - num_obrigatorios]);
        Ponto pp = (para < num_obrigatorios ? pontos_obrigatorios[para] : pontos_steiner[para - num_obrigatorios]);
        return (pd - pp).norma();
    }

    Ponto& Solucao::ponto(int i) {
        return ( i < num_obrigatorios ? pontos_obrigatorios[i] : pontos_steiner[i - num_obrigatorios]);
    }

    const Ponto& Solucao::ponto(int i) const {
        return ( i < num_obrigatorios ? pontos_obrigatorios[i] : pontos_steiner[i - num_obrigatorios]);
    }

    ostream& Solucao::operator<<(ostream& in) const {
        return in;
    }

    void Solucao::plotar(const string& data_hora) const {
        string ptFixos_arquivo = "gnuplot/ptFixos-" + data_hora + ".tsv";
        string ptSteiner_arquivo = "gnuplot/ptSteiner-" + data_hora + ".tsv";
        string ptEdges_arquivo = "gnuplot/ptEdges-" + data_hora + ".tsv";
        string gnuPlot_arquivo = "gnuplot/plota-" + data_hora + ".gnu";

        try {
            ofstream ptFixos;
            ptFixos.exceptions(ofstream::failbit | ofstream::badbit);
            ptFixos.open(ptFixos_arquivo);
            for (int i = 0; i < num_obrigatorios; ++i) {
                ptFixos << getObrigatorios()[i] << endl;
            }
            ptFixos.close();
            ofstream ptSteiner;
            ptSteiner.exceptions(ofstream::failbit | ofstream::badbit);

            ptSteiner.open(ptSteiner_arquivo);
            for (int i = 0; i < num_steiner; ++i) {
                ptSteiner << getSteiner()[i] << endl;
            }
            ptSteiner.close();
            ofstream ptEdges;
            ptEdges.exceptions(ofstream::failbit | ofstream::badbit);
            ptEdges.open(ptEdges_arquivo);
            for (int i = 0; i < tamanho - 1; i++) {
                for (int j = i + 1; j < tamanho; ++j) {
                    if (grafo.temAresta(i, j)) {
                        ptEdges << ponto(i) << endl;
                        ptEdges << ponto(j) << endl << endl;
                    }
                }
            }
            ptEdges.close();
            ofstream gnuPlot;
            gnuPlot.exceptions(ofstream::failbit | ofstream::badbit);
            gnuPlot.open(gnuPlot_arquivo);
            gnuPlot << "#ARQUIVO COM AS CONFIGURAÇÕES DA ARVORE GNU" << endl << endl;
            gnuPlot << "#set title \"Árvore de Steiner\"" << endl;
            gnuPlot << "set style arrow 1 nohead lw 4" << endl;
            gnuPlot << "#Seta tamanho da janela automaticamente de acordo com os dados" << endl;
            gnuPlot << "set autoscale" << endl;
            gnuPlot << "unset key" << endl << endl;
            gnuPlot << "numPontos=" << num_obrigatorios << endl << endl;
            gnuPlot << "set key off" << endl;
            gnuPlot << "splot '" << ptEdges_arquivo << "' using 1:2:3 with lines lc rgb \"black\" lw 1 notitle, \\" << endl;
            gnuPlot << "'" << ptSteiner_arquivo << "' using 1:2:3 with points lc rgb \"red\" pointsize 3 pointtype 7,\\" << endl;
            gnuPlot << "'" << ptSteiner_arquivo << "' using 1:2:3:($0+numPontos+1) with labels tc rgb \"white\" offset (0,0) font 'Arial Bold' notitle,\\" << endl;
            gnuPlot << "'" << ptFixos_arquivo << "' using 1:2:3 with points lc rgb \"black\" pointsize 3 pointtype 7,\\" << endl;
            gnuPlot << "'" << ptFixos_arquivo << "' using 1:2:3:($0+1) with labels tc rgb \"white\" offset (0,0) font 'Arial Bold' notitle,\\" << endl << endl;
            gnuPlot << "pause -1" << endl;
            gnuPlot.close();

            string comando = "gnuplot \"" + gnuPlot_arquivo + "\"";
            system(comando.c_str());

        } catch (...) {
            throw myexception("plotar: Impossivel abrir arquivo.");
        }

    }


} // namespace std
