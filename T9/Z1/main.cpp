#include <iostream>
#include <cmath>

class Vektor3d
{
    double x, y, z;
public:
    void Postavi(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void Ocitaj (double &x, double &y, double &z) const
    {
        x = this->x;
        y = this->y;
        z = this->z;
    }
    void Ispisi() const
    {
        std::cout << "{" << x << "," << y << "," << z << "}";
    }
    double DajX() const
    {
        return x;
    }
    double DajY() const
    {
        return y;
    }
    double DajZ() const
    {
        return z;
    }
    void PostaviX (double x)
    {
        this->x= x;
    }
    void PostaviY (double y)
    {
        this->y= y;
    }
    void PostaviZ (double z)
    {
        this->z= z;
    }
    double DajDuzinu() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }
    Vektor3d &PomnoziSaSkalarom(double s)
    {
        this->x *= s;
        this->y *= s;
        this->z *= s;
        return *this;
    }
    Vektor3d &SaberiSa(const Vektor3d &v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }
    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);

};

int main ()
{
    return 0;
}



Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2)
{
    Vektor3d v3;
    v3.x = v1.x + v2.x;
    v3.y = v1.y + v2.y;
    v3.z = v1.z + v2.z;
    return v3;
}
