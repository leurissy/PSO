#include "comum.h"

namespace std {

    string ldtos(long double val, int precisao) {
        double intpart, nova_int;
        double fracpart = modf(val, &intpart);
        if (precisao > 15)
            precisao = 15;
        while (precisao-- > 0)
            fracpart *= 10;
        double nova_frac = modf(fracpart, &nova_int);
        char buffer[100];
        snprintf(buffer, 100, "%d,%llu", (int) intpart, (unsigned long long) nova_int);
        string s = buffer;
        return s;
    }

} //namespace std


