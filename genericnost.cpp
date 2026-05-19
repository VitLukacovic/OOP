#include <iostream>
#include <string>

using namespace std;

template<class T>
class Zasobnik
{
    private:
        T* pole;
        int kapacita;
        int vrchol;

    public:
        Zasobnik(int kap);
        ~Zasobnik();

        void Push(T prvek);
        T Pop();
        bool IsEmpty();
};

template<class T>
Zasobnik<T>::Zasobnik(int kap)
{
    this->kapacita = kap;
    this->vrchol = 0;
    this->pole = new T[this->kapacita];
}

template<class T>
Zasobnik<T>::~Zasobnik()
{
    delete[] this->pole;
}

template<class T>
void Zasobnik<T>::Push(T prvek)
{
    if(this->vrchol < this->kapacita)
    {
        this->pole[this->vrchol++] = prvek;
    }
    else
    {
        cout << "Zasobnik je plny" << endl;
    }
}

template<class T>
T Zasobnik<T>::Pop()
{
    if(!this->IsEmpty())
    {
        this->vrchol--;
        return this->pole[this->vrchol];
    }
    return T();
}

template<class T>
bool Zasobnik<T>::IsEmpty()
{
    return this->vrchol == 0;
}

class A
{
    protected:
        int value;

    public:
        A(int v);
        virtual ~A();
        
        int GetValue();
        virtual void Vypis();
};

A::A(int v)
{
    this->value = v;
}

A::~A()
{

}

int A::GetValue()
{
    return this->value;
}

void A::Vypis()
{
    cout << "A, hodnota: " << this->value << endl;
}

class B : public A
{
    public:
        B(int v);
        void Vypis() override;
};

B::B(int v) : A(v)
{

}

void B::Vypis()
{
    cout << "B, hodnota: " << this->value << endl;
}

int main()
{
    cout << "--- Zkouska generickeho zasobniku s polymorfismem ---" << endl;

    Zasobnik<A*>* mujZasobnik = new Zasobnik<A*>(5);

    // do zásobníku typu A* lze vkládat objekty A i B
    mujZasobnik->Push(new A(10));
    mujZasobnik->Push(new B(20));
    mujZasobnik->Push(new A(30));
    mujZasobnik->Push(new B(40));

    // LIFO
    while (!mujZasobnik->IsEmpty())
    {
        A* prvek = mujZasobnik->Pop();
        
        // dochází k protnutí generičnosti a polymorfismu
        // díky pozdní vazbě se zavolá správná metoda
        prvek->Vypis();
        
        delete prvek;
    }

    delete mujZasobnik;

    getchar();
    return 0;
}