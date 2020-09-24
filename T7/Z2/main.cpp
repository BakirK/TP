#include <iostream>
#include <algorithm>

template <typename TipElemenata>
void UnistiMatricu(TipElemenata **mat, int br_redova)
{
	if(!mat) return;
	for(int i = 0; i < br_redova; i++) delete[] mat[i];
	delete[] mat;
}

int main ()
{
	std::cout << "Koliko zelite recenica: ";
	int n;
	std::cin >> n;
	std::cin.ignore(100, '\n');
	std::cout << "Unesite recenice:" << std::endl;
	int i = 0;
	char **recenice = nullptr;
	try {
		recenice = new char*[n];
		while (i < n && i < 1000) {
			int j(0);
			char temp[1000];
			char *p = temp;
			while (j < 999 && std::cin.peek() != '\n') {
				*p = static_cast<char> (std::cin.get());
				p++;
				j++;
			}
			if (std::cin.peek() == '\n') {
				std::cin.get();
			}
			*p = '\0';
			j++;
			//kopiranje
			recenice[i] = new char[j];
			for(int k(0); k < j; k++) {
				recenice[i][k] = temp[k];
			}
			i++;
		}
		//sortiranje
		char **kraj = recenice + n;
		std::sort(recenice, kraj, [](char *p1, char *p2) ->bool {
				std::string temp1;
				while (*p1 != '\0') {
					temp1.push_back(*p1);
					p1++;
				}

				std::string temp2;
				while (*p2 != '\0') {
					temp2.push_back(*p2);
					p2++;
				}
				return temp1 < temp2;
		});


		std::cout << "Sortirane recenice:" << std::endl;
		for (int i(0); i < n; i++) {
			char *p = recenice[i];
			while(*p != '\0') {
				std::cout << *p;
				p++;
			}
			std::cout << std::endl;
		}
	} catch (...) {
		UnistiMatricu(recenice, n);
		std::cout << "Problemi s memorijom!" << std::endl;
		recenice = nullptr;
	}

	UnistiMatricu(recenice, n);


	return 0;
}
