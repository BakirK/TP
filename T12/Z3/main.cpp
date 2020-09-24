#include <iostream>

enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};

Dani &operator++(Dani &d)
{
	d = Dani ((int(d) + 1) % 7);
	return d;
}

Dani operator++(Dani &d, int)
{
	Dani pomocni = d;
	++d;
	return pomocni;
}


Dani operator +(Dani d, int n)
{
	return Dani((int(d) + n) % 7);
}


std::ostream &operator <<(std::ostream &stream, Dani d)
{
	int i = int(d);
	switch(i) {
		case 0: {
			stream << "Ponedjeljak";
			break;
		}
		case 1: {
			stream << "Utorak";
			break;
		}
		case 2: {
			stream << "Srijeda";
			break;
		}
		case 3: {
			stream << "Cetvrtak";
			break;
		}
		case 4: {
			stream << "Petak";
			break;
		}
		case 5: {
			stream << "Subota";
			break;
		}
		case 6: {
			stream << "Nedjelja";
			break;
		}
	}
	return stream;
}


int main ()
{
	Dani d = Ponedjeljak;
	for(; d <= Nedjelja; d++) {
		std::cout << d << std::endl;
		if (d == Nedjelja) {
			break;
		}
	}

	return 0;
}
