#include <string>
#include <iostream>
#include <string>
using namespace std;

class Surovina
{
    private:
        std::string nazev;
        int mnozstvi;
    public:
        Surovina();
        Surovina(string n, int m);

        string getNazev();
        int getMnozstvi();

        bool jeDostatek(int potreba);
        void spotrebovat(int s);

};

Surovina::Surovina(string n, int m)
{
    this->nazev = n;
    this->mnozstvi = m;
}

string Surovina::getNazev()
{
    return this->nazev;
}

int Surovina::getMnozstvi()
{
    return this->mnozstvi;
}

bool Surovina::jeDostatek(int potreba)
{
    return this->mnozstvi >= potreba;
}

void Surovina::spotrebovat(int s)
{
    this->mnozstvi -= s;
}


