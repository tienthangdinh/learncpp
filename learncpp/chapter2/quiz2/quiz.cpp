

int readNumber();
void writeAnswer(int x, int y);

int main() {
    int x { readNumber() };
    int y { readNumber() };
    writeAnswer(x, y);
    return 0;
}

/*
C1: link 2 file vao voi nhau 1 object la ok
 g++ quiz.cpp io.cpp -o hi
./hi

C2: compile seperately then link together
g++ -c main.cpp -o main.o
g++ -c io.cpp -o io.o
g++ main.o io.o -o my_program

C3: Makefile
add the above in Makefile
then run make
*/