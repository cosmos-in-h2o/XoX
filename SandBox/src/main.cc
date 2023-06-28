#include <iostream>
import xox;
using std::cout;
int fun(){
    []{cout<<"hello world\n";}();
}
int main(){
    cout<<"hello world\n";
    xox::Action<> action;
    action+=[]{cout<<"hello world\n";};
    action.invoke();
    return 0;
}