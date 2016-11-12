#include <iostream>

using namespace std;

void drukuj(int x) {
    for(int i=0; i<x; i++) cout << x-i << " ";
    cout << endl;
}

int main() {
    for(int i=0; i<10; ++i) cout << i << " ";
    cout << endl;

    drukuj(15);
    
    return 0;
}
