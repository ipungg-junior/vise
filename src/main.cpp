// main.cpp
#include <iostream>

// Deklarasi fungsi dari shared library
extern "C" void starting_point();

int main() {
    starting_point() // Memanggil fungsi dari file C++
    return 0;
}
