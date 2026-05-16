#include <iostream>
#include <string>
using namespace std;

class KeyValue
{
    private:
        int key;
        double value;

    public:
        KeyValue(int k, double v);
        int GetKey();
        double GetValue();
};

KeyValue::KeyValue(int k, double v)
{
    this->key = k;
    this->value = v;
}

int KeyValue::GetKey()
{
    return this->key;
}

double KeyValue::GetValue()
{
    return this->value;
}

class KeyValues
{
    private:
        KeyValue** keyValues;
        int count;

    public:
        KeyValues(int n);
        ~KeyValues();
        KeyValue* CreateObject(int k, double v);
        KeyValue* SearchObject(int key);
        int Count();
        KeyValue* RemoveObject(int key);
};

KeyValues::KeyValues(int n)
{
    this->keyValues = new KeyValue*[n];
    this->count = 0;
}

KeyValues::~KeyValues()
{
    for(int i = 0; i < this->count; i++)
    {
        delete this->keyValues[i];
    }

    delete[] this->keyValues;
}

KeyValue* KeyValues::CreateObject(int k, double v)
{
    KeyValue *newObject = new KeyValue(k, v);

    this->keyValues[this->count] = newObject;
    this->count += 1;

    return newObject;
}

KeyValue* KeyValues::SearchObject(int k)
{
    for(int i = 0; i < this->count; i++)
    {
        if(this->keyValues[i]->GetKey() == k)
        {
            return this->keyValues[i];
        }
    }

    return nullptr;
}

KeyValue* KeyValues::RemoveObject(int k)
{
    for(int i = 0; i < this->count; i++)
    {
        if(this->keyValues[i]->GetKey() == k)
        {
            KeyValue* for_removal = this->keyValues[i];

            for(int j = i; j < this->count - 1; j++)
            {
                this->keyValues[j] = this->keyValues[j + 1];
            }

            this->count--;

            return for_removal;
        }
    }

    return nullptr;
}

int main()
{
    int N = 5;
    KeyValues* myKeyValues = new KeyValues(N);

    KeyValue* myKeyValue = myKeyValues->CreateObject(0, 0.5);
    cout << myKeyValue->GetValue() << endl;

    for(int i = 1; i < N; i++)
    {
        myKeyValues->CreateObject(i, i + 0.5);
    }
    cout << myKeyValues->SearchObject(4)->GetValue() << endl;

    delete myKeyValues;

    cout << myKeyValue->GetKey() << endl;

    getchar();
    return 0;
}