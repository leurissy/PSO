/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GetOpt.h
 * Author: wilson
 *
 * Created on 1 de Fevereiro de 2018, 17:04
 */

#ifndef GETOPT_H
#define GETOPT_H

#include <string>

namespace std {

    class GetOpt {
    public:
        GetOpt();
        GetOpt(const GetOpt& orig);
        GetOpt(int c, char** v, const char *opt);
        GetOpt(int c, char** v, const char *opt, const string msg);
        virtual ~GetOpt();
        void uso();
        bool temOpcao(char opt);
        char* argOpcao(char opt);
        int resto() const;
    private:
        const char *optstring;
        int argc;
        char** argv;
        bool *tem_opcao;
        char **arg_opcao;
        int num_opt;
        const string uso_msg;
    };
}

#endif /* GETOPT_H */

