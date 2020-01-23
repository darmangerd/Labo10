/*
 -----------------------------------------------------------------------------------
 Laboratoire : Snake
 Fichier     : sysFunc.cpp
 Auteur(s)   : Yann Lederrey
 Date        : 20.01.2019
 
 Compilateur : g++ (GCC) 9.2.0

 Brief       : Implémentation des fonctions déclarée dans sysFunc.h
 -----------------------------------------------------------------------------------
 */

#include "sysFunc.h"

#if defined(_WIN64) || defined(_WIN32)
#else
    struct termios orig_termios;

    int kbhit() {
        struct timeval tv = {0L, 0L};
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        return select(1, &fds, NULL, NULL, &tv);
    }

    int getch() {
        int r;
        unsigned char c;
        if ((r = read(0, &c, sizeof (c))) < 0) {
            return r;
        } else {
            return c;
        }
    }
#endif


void clearScreen() {
#if defined(_WIN64) || defined(_WIN32)
    std::system("CLS");
#else
    std::system("clear");
#endif
}

void mySleep(int microseconds){
    #if defined(_WIN64) || defined(_WIN32)
        Sleep(microseconds/1000);
    #else
        usleep(microseconds);
    #endif
}