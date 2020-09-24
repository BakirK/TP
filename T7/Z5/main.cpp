#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
int main ()
{
	std::cout << "Koliko zelite recenica: ";
	int n;
	std::cin >> n;
	std::cin.get();
	std::cout << "Unesite recenice:" << std::endl;
	int i = 0;
	std::shared_ptr<std::shared_ptr<std::string>> recenice;
	try {
		recenice = std::shared_ptr<std::shared_ptr<std::string>[]> (new std::shared_ptr<std::string>[n], [](std::shared_ptr<std::string> *p){
			delete[] p;
		});
		//unos
		
		while (i < n) {
			recenice.get()[i] = std::make_shared<std::string>(std::string());
			std::getline(std::cin, *recenice.get()[i], '\n');
			i++;
		}
		
		//sortiranje
		for (int j = 0; j < n; j++) {
			for (int i = 0; i < n - 1; i++) {
				if (*recenice.get()[i] > *recenice.get()[i+1]) {
					auto recenica1 = recenice.get()[i];
					recenice.get()[i] = recenice.get()[i + 1];
					recenice.get()[i + 1] = recenica1;
					j--;
				}
			}
		}
		//p.get()[i]
		std::cout << "Sortirane recenice:" << std::endl;
		for (int i(0); i < n; i++) {
			std::cout << *recenice.get()[i] << std::endl;
		}
	} catch (...) {
		std::cout << "Problemi s memorijom!" << std::endl;
		recenice = nullptr;
	}
	recenice = nullptr;
	return 0;
}
