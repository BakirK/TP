#include <iostream>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cout << "Unesite tri broja: ";
    double a, b, c;
    std::cin >> a >> b >> c;
    if( a<0 || b<0 || c<0 || (a+b)<=c || (a+c)<=b || (c+b)<=a) {
        std::cout << "Ne postoji trougao cije su duzine stranica " << a << ", " << b << " i " << c << "!" << std::endl;
    }
    else {
        long double s {(a+b+c)/2};
        long double povrsina {sqrt(s*(s-a)*(s-b)*(s-c))};
        long double obim {a+b+c};
        std::cout << "Obim trougla sa duzinama stranica " << a << ", " << b << " i " << c << " iznosi " << obim << "." << std::endl;
        std::cout << "Njegova povrsina iznosi " << povrsina << "." << std::endl;
        double gama, alfa, beta;
        gama=acos( ( (a*a) + (b*b) - (c*c) ) / (2*a*b) );
        alfa=acos( ( (c*c) + (b*b) - (a*a) ) / (2*c*b) );
        beta=acos( ( (a*a) + (c*c) - (b*b) ) / (2*a*c ));
        double pi=4.*atan(1.);
        if(alfa <= beta && alfa <= gama) {
            alfa = alfa * (180./pi);
            double stepeni, minute, sekunde, temp;
            stepeni = static_cast<int> (alfa);
            temp = (alfa - stepeni) * 60;
            minute = static_cast<int> (temp);
            sekunde = static_cast<int> ((temp - minute) * 60);
            std::cout << "Njegov najmanji ugao ima " << stepeni << " stepeni, " << minute << " minuta i "
                      << sekunde << " sekundi." << std::endl;   
        }
        else if (beta <= alfa && beta <= gama) {
            beta = beta * (180./pi);
            double stepeni, minute, sekunde, temp;
            stepeni = static_cast<int> (beta);
            temp = (beta - stepeni) * 60;
            minute = static_cast<int> (temp);
            sekunde = static_cast<int> ((temp - minute) * 60);
            std::cout << "Njegov najmanji ugao ima " << stepeni << " stepeni, " << minute << " minuta i "
                      << sekunde << " sekundi." << std::endl;  
        }
        else {
            gama = gama * (180./pi);
            double stepeni, minute, sekunde, temp;
            stepeni = static_cast<int> (gama);
            temp = (gama - stepeni) * 60;
            minute = static_cast<int> (temp);
            sekunde = static_cast<int> ((temp - minute) * 60);
            std::cout << "Njegov najmanji ugao ima " << stepeni << " stepeni, " << minute << " minuta i "
                      << sekunde << " sekundi." << std::endl; 
        }
    }
    return 0;
}