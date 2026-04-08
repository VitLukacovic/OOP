#include <iostream>
#include <string>
using namespace std;

class KeyValue
{
    private:
        int key;
        double value;
        KeyValue *next;

    public:
        KeyValue(int k, double v);
        ~KeyValue();
        int GetKey();
        double GetValue();
        KeyValue* GetNext();
        KeyValue* CreateNext(int k, double v);
};

KeyValue::KeyValue(int k, double v)
{
    this->key = k;
    this->value = v;
    this->next = nullptr;
}

KeyValue::~KeyValue()
{
    if(this->next != nullptr)
    {
        delete this->next;
        this->next = nullptr;
    }
}

int KeyValue::GetKey()
{
    return this->key;
}

double KeyValue::GetValue()
{
    return this->value;
}

KeyValue* KeyValue::GetNext()
{
    return this->next;
}

KeyValue* KeyValue::CreateNext(int k, double v)
{
    this->next = new KeyValue(k, v);
    return this->next;
}

int main()
{
    KeyValue* head = new KeyValue(1, 1.5);
    
    KeyValue* current = head;

    for(int i = 2; i <= 1000; i++)
    {
        current = current->CreateNext(i, i + 0.5);
    }

    current = head;
    while(current != nullptr)
    {
        cout << current->GetValue() << endl;
        current = current->GetNext();
    }

    delete head;

    return 0;
}