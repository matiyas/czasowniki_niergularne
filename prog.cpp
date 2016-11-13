// LOL
// Komentarz
#include <iostream>

using namespace std;

int log_and(int a, int b) {
    return a&b;
}

int bit_p(int a, int b) {
    return a>>b;
}

int bit_l(int a, int b) {
    return a<<b;
}

int mod(int a, int b) {
    return a%b;
}

int pomnoz(int a, int b) {
    return a*b;
}

int podziel(int a, int b) {
    return a/b;
}

void drukuj(int x) {
    for(int i=0; i<x; i++) cout << x-i << " ";
    cout << endl;
}

int dodaj(int a, int b) {
    return a+b;
}

int minus(int a, int b) {
    return a-b;
}

int main() {
    for(int i=0; i<10; ++i) cout << i << " ";
    cout << endl;

    drukuj(15);
    cout << "dodaj(32,12) = " << dodaj(32,12) << endl;
    cout << "minus(93,21) = " << minus(93,21) << endl;
       
    return 0;
}
