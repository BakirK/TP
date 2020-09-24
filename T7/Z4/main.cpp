#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

int main ()
{
	std::cout << "Koliko zelite recenica: ";
	int n;
	std::cin >> n;
	//std::cin.ignore(100, '\n');
	std::cin.get();
	std::cout << "Unesite recenice:" << std::endl;
	int i = 0;
	std::unique_ptr<std::shared_ptr<std::string>[]> recenice = nullptr;
	try {
		recenice = std::unique_ptr<std::shared_ptr<std::string>[]> (new std::shared_ptr<std::string>[n]{});
		//unos
		while (i < n) {
			//?
			recenice[i] = std::make_shared<std::string>(std::string());
			//recenice[i] = std::shared_ptr<std::string>(new std::string());
			std::getline(std::cin, *recenice[i], '\n');
			i++;
		}
		
		//sortiranje
		for (int j = 0; j < n; j++) {
			for (int i = 0; i < n - 1; i++) {
				if (*recenice[i] > *recenice[i+1]) {
					auto recenica1 = recenice[i];
					recenice[i] = recenice[i + 1];
					recenice[i + 1] = recenica1;
					j--;
				}
			}
		}
		
		std::cout << "Sortirane recenice:" << std::endl;
		for (int i(0); i < n; i++) {
			std::cout << *recenice[i] << std::endl;
		}
	} catch (...) {
		std::cout << "Problemi s memorijom!" << std::endl;
		recenice = nullptr;
	}
	recenice = nullptr;
	return 0;
}
