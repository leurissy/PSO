/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   drand.cpp
 * Author: wilson
 *
 * Created on 2 de Novembro de 2017, 14:15
 * referencias: 
 * <http://www.cplusplus.com/forum/beginner/176265/>
 * <http://www.cplusplus.com/forum/beginner/159383/>
 * <http://www.cplusplus.com/forum/general/59165/>
 * 
 */


#ifdef _GNU_SOURCE

#include <random>
#include <chrono>
#include <algorithm>

#else
#include <stdlib.h>
#endif

namespace std {

#ifdef _GNU_SOURCE
    std::mt19937 initialize_twister(size_t seed = chrono::system_clock::now().time_since_epoch().count());

    std::mt19937 initialize_twister(size_t seed) {
        static constexpr size_t NUM_DISCARD = 10240;

        minstd_rand lcg(seed);
        lcg.discard(NUM_DISCARD);

        size_t seeds[mt19937::state_size];
        generate_n(seeds, mt19937::state_size, lcg);

        try {
            // check if there is a random_device available
            seeds[0] = random_device{}
            ();
        } catch (const exception&) {
            /* ignore */
        }

        seed_seq seed_sequence(begin(seeds), end(seeds));
        return mt19937{seed_sequence}; // warm-up with seed seed_sequence.generate()
        //   return seed_sequence;
    }
#endif

    double drand() {
#ifdef _GNU_SOURCE
        static mt19937 generator = initialize_twister();
        static uniform_real_distribution<double> distribution(0.0, 1.0);

        return distribution(generator);
#else
        //inicializa a semente do gerador de numeros pseudo-randomicos
        static bool inicializado = false;
        if (inicializado == false) {
            srand(time(NULL));
            inicializado = true;
        }
        return (double) rand() / (double) RAND_MAX;
#endif
    }

}
