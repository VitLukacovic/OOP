#include <iostream>
#include <string>
using namespace std;

class StaticValue
{
    private:
        static int value; // data a metody deklarované jako static patří třídě, přístup k nim mají i objekty
        //StaticValue();   

    public:
        static void IncValue();
        static int GetValue();
};

int StaticValue::value = 0; //Pokud má třída třídní (static) proměnné, pak je musíme inicializovat zvlášť

void StaticValue::IncValue()
{
    StaticValue::value += 1;
}

int StaticValue::GetValue()
{
    return StaticValue::value;
}

int main()
{
    cout << StaticValue::GetValue() << endl;
    StaticValue::IncValue();
    cout << StaticValue::GetValue << endl;

    StaticValue *sv = new StaticValue();
    cout << sv->GetValue() << endl;

    getchar();
    return 0;
}