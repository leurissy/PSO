#include "Tempo.h"
#include <sys/time.h>
#include <iostream>

namespace std {
	
Tempo::Tempo() {
//	gettimeofday(&tvBegin, NULL);
//	clock_inicio = clock();
	start = chrono::steady_clock::now();
}

double Tempo::getDecorrido() {
//	struct timeval tvAtual;
////	cout << "Segundos inicial: " << tvBegin.tv_usec << endl;
//	gettimeofday(&tvAtual, NULL);
////	cout << "Segundos atual: " << tvAtual.tv_usec << endl;
//	return ( (double)((tvAtual.tv_usec + 1000000 * tvAtual.tv_sec) - (tvBegin.tv_usec + 1000000 * tvBegin.tv_sec)) / 1000000 );

//	clock_t clock_atual = clock();
//	clock_t diff_clock = clock_atual - clock_inicio;
//	cout << "diff_clock " << diff_clock << endl;
//	cout << "CLOCKS_PER_SEC " << CLOCKS_PER_SEC << endl;
//	double decorrido = (double)(diff_clock)/CLOCKS_PER_SEC;
//	cout << "decorrido " << decorrido << endl;
//	cout << "precisao de clock_t " << sizeof(clock_t) << endl;
//	return decorrido;
//	return static_cast<double>(clock()-clock_inicio)/CLOCKS_PER_SEC;
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	return chrono::duration_cast<chrono::duration<double>>(diff).count();
}

string Tempo::horario() {
	time_t tempo_inicio;
	tempo_inicio = time(NULL);

	struct tm * timeinfo;
	timeinfo = localtime ( &tempo_inicio );
	char buffer[80];

	strftime( buffer, 80, "%Y-%m-%d %Hh%Mm%Ss", timeinfo );

//	cout << buffer << endl;

	return string(buffer);
}

} //namespace

