#include <iostream>

double myfunc(double x){
    return x*x;
}
int main(){
   auto k =  myfunc(5.0);   
   std::cout << k;
}