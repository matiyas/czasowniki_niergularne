#include <iostream>

using namespace std;

void drukuj(int x) {
    for(int i=0; i<x; i++) cout << x-i << " ";
    cout << endl;
}

int minus(int a, int b) {
    return a-b;
}

int main() {
    for(int i=0; i<10; ++i) cout << i << " ";
    cout << endl;

    drukuj(15);
    cout << "minus(93,21) = " << minus(93,21) << endl;
       
    return 0;
}
