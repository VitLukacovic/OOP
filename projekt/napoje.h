#include <string>
#include <iostream>
#include <string>
using namespace std;

class Napoj
{
    protected:
        string nazev;
        double cena;
        
    public:
        Napoj(std::string n, double c) : nazev(n), cena(c) {}
        virtual ~Napoj() {}
        
        // Čistě virtuální metody (Abstraktní třída)
        virtual void priprav() const = 0;
        virtual void vypisInformace() const = 0;
        
        double getCena() const { return cena; }
        std::string getNazev() const { return nazev; }
};