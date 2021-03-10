#ifndef _MYEXCEPTION_H_
#define _MYEXCEPTION_H_

#include <exception>

namespace std {

    class myexception : public exception {
    private:
        const char *mensagem;
    public:

        myexception(const char* m) : mensagem(m) {
        }

        virtual const char* what() const  throw () override {
            return mensagem;
        }
    };

} //namespace std

#endif

