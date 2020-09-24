#include <iostream>
#include <algorithm>

template <typename TipElemenata>
void UnistiMatricu(TipElemenata **mat, int br_redova)
{
	if(!mat) return;
	for(int i = 0; i < br_redova; i++) delete mat[i];
	delete[] mat;
}

int main ()
{
	std::cout << "Koliko zelite recenica: ";
	int n;
	std::cin >> n;
	//std::cin.ignore(100, '\n');
	std::cin.get();
	std::cout << "Unesite recenice:" << std::endl;
	int i = 0;
	std::string **recenice = nullptr;
	try {
		recenice = new std::string*[n]{};
		while (i < n) {
			recenice[i] = new std::string();
			std::getline(std::cin, *recenice[i], '\n');
			i++;
		}
		//sortiranje
		std::string **kraj = recenice + n;
		std::sort(recenice, kraj, [](std::string *p1, std::string *p2) -> bool {
				return *p1 < *p2;
		});

		std::cout << "Sortirane recenice:" << std::endl;
		for (int i(0); i < n; i++) {
			std::cout << *recenice[i] << std::endl;
		}
	} catch (...) {
		UnistiMatricu(recenice, n);
		std::cout << "Problemi s memorijom!" << std::endl;
		recenice = nullptr;
	}

	UnistiMatricu(recenice, n);

	return 0;
}
