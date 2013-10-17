#include <iostream>

int add(int x, int y) {
    int a, b;
    do {
        a = x & y;
        b = x ^ y;
        x = a << 1;
        y = b;
	std::cout<<"a:"<<a<<" b:"<<b<<" x:"<<x<<" y:"<<y<<std::endl;
    } while (a);
    return b;
}


int main( void ){
    std::cout<<"3+7= "<<add(3,7)<<"\n";
    return 0;
}
