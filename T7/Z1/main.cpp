#include <iostream>

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
			recenice[i] = new char[j];
			for(int k(0); k < j; k++) {
				recenice[i][k] = temp[k];
			}
			i++;
		}
		for (int j = 0; j < n; j++) {
			for (int i = 0; i < n - 1; i++) {
				std::string temp1;
				char *p1 = recenice[i];
				while (*p1 != '\0') {
					temp1.push_back(*p1);
					p1++;
				}

				std::string temp2;
				char *p2 = recenice[i + 1];
				while (*p2 != '\0') {
					temp2.push_back(*p2);
					p2++;
				}
				if (temp1 > temp2) {
					auto recenica1 = recenice[i];
					recenice[i] = recenice[i + 1];
					recenice[i + 1] = recenica1;
					j--;
				}
			}
		}
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
