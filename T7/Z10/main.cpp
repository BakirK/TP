#include <iostream>
#include <functional>

std::function<int(int)> IteriranaFunkcija(int f(int), int n) {
    if (n <= 0) {
        return [](int a) {
            return a;
        };
    }
    if (n == 1) {
        return [f](int x) {
                return f(x);    
            }; 
    }
    else {
        
            std::function<int(int)> lambda = [f, n](int a) {
                return f(IteriranaFunkcija(f, n - 1)(a));  
            };
            return lambda;
            //return f(IteriranaFunkcija(f, n - 1));
        }
}
int main ()
{
    std::cout << IteriranaFunkcija([](int x) { return x * x; }, 2)(3) << std::endl;
	return 0;
}