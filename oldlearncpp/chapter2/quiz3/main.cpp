#include "io.h"

int main()
{
    int x { readNumber() };
    int y { readNumber() };
    writeAnswer(x, y);
    return 0;
}


//actually the include io.h only for compiling into object .o, when linking we dont even need io.h, instead we just look for io.o (from io.cpp)

//compile: io.h only for main to settle down in compilation, no effect on linking, only to tell that the function exist somewhere
//link: main.o look for functions from io.o fooly and not care if any relationship between io.h and io.cpp