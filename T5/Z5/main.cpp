#include <iostream>
#include <iomanip>
#include <cmath>

const double PI(4 * std::atan(1));

double TrapeznoPravilo (double f(double), double a, double b, int n) {
	double sum(0);
	int k (1);
	while (k < n) {
		sum += f(a + ( ( (b - a) / n) * k) );
		k++;
	}			
	sum += (1./2) * f(a) + (1./2) * f(b);
	sum *= (b-a) / n;
	return sum;
}


int main ()
{
	std::cout << "Unesite broj podintervala: ";
	int n;
	std::cin >> n;
	std::cout << "Za taj broj podintervala priblizne vrijednosti integrala iznose:" << std::endl;
	 
	double vrijednost1(TrapeznoPravilo (std::sin, 0, PI, n));
	std::cout<<"- Za funkciju sin x na intervalu (0,pi): "<<std::fixed<<std::setprecision(5)<<vrijednost1<<std::endl;
	
	double vrijednost2(TrapeznoPravilo ( [] (double n) -> double { return n*n*n;}, 0, 10, n));
	std::cout<<"- Za funkciju x^3 na intervalu (0,10): "<<std::fixed<<std::setprecision(2)<<vrijednost2<<std::endl;
	
	double vrijednost3(TrapeznoPravilo ( [] (double n) -> double { return (1./n);}, 1, 2, n));
	std::cout<<"- Za funkciju 1/x na intervalu (1,2): "<<std::fixed<<std::setprecision(5)<<vrijednost3<<std::endl;
	return 0;
}