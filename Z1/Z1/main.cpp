#include <iostream>
#include <vector>
#include <cmath>
#include <deque>

std::vector<unsigned long long int> PalindromskaOtpornost (std::vector<long long int> numbers) {
	int n (0);
	std::vector<unsigned long long int> otpornost;
	//obrnuti brojevi
	std::deque <unsigned long long int> reverse;
	
	//neobrnuti brojevi
	std::deque <unsigned long long int> non_reverse;

	
	for (long long int i: numbers) {
		reverse.clear();
		non_reverse.clear();
		n = 0;
		unsigned long long int temp ( std::abs(i) );
		while (temp != 0) {
			reverse.push_back(temp%10);
			non_reverse.push_front(temp%10);
			temp /= 10;
		}
		
		if (reverse != non_reverse) {
			temp = std::abs(i);
			while (true) {
				unsigned long long int acutalNumber (0);
				unsigned long long int reversedNumber (0);
				for (unsigned long long int j = 0; j < reverse.size(); j++) {
					 reversedNumber *= 10;
					 reversedNumber += reverse.at(j) ;
				}
				reverse.clear();
				non_reverse.clear();
				temp += reversedNumber;
				n++;
				acutalNumber = temp;
				while (temp != 0) {
					reverse.push_back(temp%10);
					non_reverse.push_front(temp%10);
					temp /= 10;
				}
				//std::cout << n << " reverse: " << reverse << " temp: "<< acutalNumber << "\n";
				if (reverse == non_reverse) {
					otpornost.push_back(n);
					break;
				}
				temp = acutalNumber;
			}
		} else {
			otpornost.push_back(n);
			continue;
		}
	}
	return otpornost;
}
	


int main ()
{
	unsigned long long int numberOfElements;
	while (true) {
	        std::cout << "Koliko zelite unijeti elemenata: ";
	        std::cin >> numberOfElements;
	        if (numberOfElements < 1) {
	            std::cout << "Broj elemenata mora biti veci od 0!" << std::endl;
	            return 0;
	        }
	        break;
	}
	unsigned long long int i (0);
	std::vector<long long int> numbers;
	std::cout << "Unesite elemente: ";
	while (i < numberOfElements) {
		long long int temp;
		std::cin >> temp;
		numbers.push_back(temp);
		i++;
	}
	std::vector<unsigned long long int> otpornost = PalindromskaOtpornost(numbers);
	for (unsigned long long int i = 0; i < numbers.size(); i++) {
		std::cout << "Palindromska otpornost broja " << numbers.at(i) << " iznosi " << otpornost.at(i) << " " << std::endl;
	}
	
	return 0;
}