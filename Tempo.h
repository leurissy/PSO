#ifndef _TEMPO_H_
#define _TEMPO_H_
#include <ctime>
#include <chrono>
#include <string>

namespace std {
	
class Tempo {
	private:
//		struct timeval tvBegin, tvEnd;
//		clock_t clock_inicio;
		chrono::steady_clock::time_point start;
	public:
		Tempo();
		double getDecorrido();
		string horario();
};




} //namespace

#endif

