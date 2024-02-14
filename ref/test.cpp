#include <iostream>
struct A{
    int x;
    int print(){return x+y;};
    A(int x, int y) : x(x), y(y) {};
    private:
    int y;
};

using namespace std;

int main(){
    A a = {.x=1, .y=2};
    cout << a.x << " " << a.print() << endl;
}