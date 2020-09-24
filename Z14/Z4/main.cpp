//TP 2018/2019: Tutorijal 14, Zadatak 4
#include <iostream>
#include <fstream>

void IzvrniDatoteku(std::string name) {
    std::fstream tok;
    tok.open(name, std::ios::binary | std::ios::in | std::ios::out);
    if(!tok) {
        throw std::logic_error("Datoteka ne postoji");
    }
    int brojElemenata;
    tok.seekg(0, std::ios::end);
    brojElemenata = tok.tellg() / sizeof(double);
    double temp, temp2;
    for (int i = 0; i < (brojElemenata/2); i++) {
        tok.seekg(i * sizeof(double));
        tok.read(reinterpret_cast<char*>(&temp), sizeof(double));
        
        tok.seekg(-sizeof(double) * (i+1), std::ios::end);
        tok.read(reinterpret_cast<char*>(&temp2), sizeof(double));
        
        tok.seekp(int(tok.tellg())-int(sizeof(double)));
        tok.write(reinterpret_cast<char*>(&temp), sizeof(double));
        
        tok.seekp(i * sizeof(double));
        tok.write(reinterpret_cast<char*>(&temp2), sizeof(double));
        
    }
}

int main ()
{
	return 0;
}