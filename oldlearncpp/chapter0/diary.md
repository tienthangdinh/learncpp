# 0.2 Programming Languages
## General principles
C++ ---(Compiler)--.o---(Linker)--> assembly --(Assembler)-->Machine code (Executable .exe)
## ISA
each ISA (CPU family) has different assembly and machine code language
<ul>
  <li>x86</li>
  <li>Arm64</li>
  <li>PowerPC</li>
  <li>MIPS</li>
</ul>

# 0.3 Introduction C/C++
Originally operating system written in Assembly (ISA specific)

Assembly programming knows specific register names,...

But with C++ operating system becomes portable => Unix developed

# 0.4 C++ development
most important thing still
- understanding problem
- sketching solution with psuedo code

# 0.5 Compiler, Linker, Libraries

## Compiler
- input: .cpp
- compilation to find errors
- transalte into object file (.o)
- output: .o

## Linking object files & libraries
- after compilation
- linker
    - input: object1.o, object2.o,..., objectn.o
    - reference dependencies between object files
    - linking libraries files (precompiled code)
    (e.g iostream is most common part of the C++ Standard Library)
    - output: single .exe

Compile + Link = Build

# 0.6 IDE
for C++17 support at least:
- GCC/G++ 7
- Clang++ 8

# 0.7 - 0.13 Setting up in each environment
Visual Studio, Code Block, Clang terminal, VSCode using task.json
gcc (C compiler), g++ (C++ compiler) and g++-9 (the only G++ on my computer now)
run g++ -v to see configuration
