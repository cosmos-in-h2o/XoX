#include <iostream>
import xox;
struct Foo{
    int x,y;
    Foo()=default;
    Foo(xox::SPool* sp,int x,int y):x(x),y(y){}
};
int main(){
    xox::SPool sp(16);
    Foo *a;
    sp.push(a,1,2);
    std::cout<<a->x<<'\t'<<a->y<<std::endl;
    sp.destroy();
    return 0;
}