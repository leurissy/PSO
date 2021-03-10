/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GetOpt.cpp
 * Author: wilson
 * 
 * Created on 1 de Fevereiro de 2018, 17:04
 */

#include "GetOpt.h"
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <iostream>
#include <string>

namespace std {

    GetOpt::GetOpt() {
    }

    GetOpt::GetOpt(const GetOpt& orig) {
    }

    GetOpt::~GetOpt() {
        delete[] tem_opcao;
        delete[] arg_opcao;
    }

    GetOpt::GetOpt(int c, char** v, const char *opt) : argc(c), argv(v), optstring(opt), uso_msg("") {
    }

    GetOpt::GetOpt(int c, char** v, const char *opt, const string msg) : argc(c), argv(v), optstring(opt), uso_msg(msg) {
        int ch;
        num_opt = strlen(optstring);
        opterr = 0;

        tem_opcao = new bool[num_opt]();
        arg_opcao = new char*[num_opt]();
        while ((ch = getopt(argc, argv, optstring)) != -1) {
            for (int i = 0; i < num_opt; i++) {
                if (ch == optstring[i]) {
                    tem_opcao[i] = true;
                    if (optstring[i + 1] == ':') {
                        arg_opcao[i] = optarg;
                    }
                    break;
                }
            }
            if (ch == '?') {
                this->uso();
                exit(EXIT_FAILURE);
            }
        }
    }

    void GetOpt::uso() {
        std::cerr << "Uso: " << argv[0] << " " << uso_msg << std::endl;
    }

    bool GetOpt::temOpcao(char opt) {
        for (int i = 0; i < num_opt; i++) {
            if (optstring[i] == opt && tem_opcao[i]) {
                return true;
            }
        }
        return false;
    }

    char* GetOpt::argOpcao(char opt) {
        char* par;
        static char c = '\0';

        for (int i = 0; i < num_opt; i++) {
            if (optstring[i] == opt && tem_opcao[i]) {
                if (arg_opcao[i] != NULL) {
                    par = arg_opcao[i];
                } else {
                    par = &c;
                }
                return par;
            }
        }
        return NULL;
    }

    int GetOpt::resto() const {
        return optind;
    }

}
