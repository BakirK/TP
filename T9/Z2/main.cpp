#include <iostream>
#include <cmath>

class Vektor3d
{
    //double x, y, z;
    double koordinate[3];
public:
    void Postavi(double x, double y, double z)
    {
        this->koordinate[0] = x;
        this->koordinate[1] = y;
        this->koordinate[2] = z;
    }
    void Ocitaj (double &x, double &y, double &z) const
    {
        x = this->koordinate[0];
        y = this->koordinate[1];
        z = this->koordinate[2];
    }
    void Ispisi() const
    {
        std::cout << "{" << koordinate[0] << "," << koordinate[1] << "," << koordinate[2] << "}";
    }
    double DajX() const
    {
        return koordinate[0];
    }
    double DajY() const
    {
        return koordinate[1];
    }
    double DajZ() const
    {
        return koordinate[2];
    }
    void PostaviX (double x)
    {
        this->koordinate[0]= x;
    }
    void PostaviY (double y)
    {
        this->koordinate[1]= y;
    }
    void PostaviZ (double z)
    {
        this->koordinate[2] = z;
    }
    double DajDuzinu() const
    {
        return std::sqrt(koordinate[0] * koordinate[0] + koordinate[1] * koordinate[1] + koordinate[2] * koordinate[2]);
    }
    Vektor3d &PomnoziSaSkalarom(double s)
    {
        this->koordinate[0] *= s;
        this->koordinate[1] *= s;
        this->koordinate[2] *= s;
        return *this;
    }
    Vektor3d &SaberiSa(const Vektor3d &v)
    {
        Vektor3d::koordinate[0] += v.koordinate[0];
        Vektor3d::koordinate[1] += v.koordinate[1];
        Vektor3d::koordinate[2] += v.koordinate[2];
        return *this;
    }
    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);

};

int main ()
{
    
    Vektor3d v1, v2;
    v2.PostaviX(1);
  v2.PostaviY(2);
  v2.PostaviZ(3);
  v2.PomnoziSaSkalarom(-1).PomnoziSaSkalarom(2).Ispisi();
  v2.SaberiSa(v2).Ispisi();
    return 0;
}



Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2)
{
    Vektor3d v3;
    v3.koordinate[0] = v1.koordinate[0] + v2.koordinate[0];
    v3.koordinate[1] = v1.koordinate[1] + v2.koordinate[1];
    v3.koordinate[2] = v1.koordinate[2] + v2.koordinate[2];
    return v3;
}
