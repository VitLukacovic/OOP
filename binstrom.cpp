#include <iostream>
#include <string>
using namespace std;

class RozhodovaciStrom
{
private:
    string key;
    string value;
    RozhodovaciStrom *ano;
    RozhodovaciStrom *ne;  //ne

public:
    RozhodovaciStrom(string k, string v);
    ~RozhodovaciStrom();

    string GetKey();
    string GetValue();
    RozhodovaciStrom* GetAno();
    RozhodovaciStrom* GetNe();

    RozhodovaciStrom* CreateAno(string k, string v);
    RozhodovaciStrom* CreateNe(string k, string v);

    void PrintTree(string prefix = "", string branch = "KOREN");
};

RozhodovaciStrom::RozhodovaciStrom(string k, string v)
{
    this->key = k;
    this->value = v;
    this->ano = nullptr;
    this->ne = nullptr;
}

RozhodovaciStrom::~RozhodovaciStrom()
{
    if (this->ano != nullptr)
    {
        delete this->ano;
        this->ano = nullptr;
    }

    if (this->ne != nullptr)
    {
        delete this->ne;
        this->ne = nullptr;
    }
}

string RozhodovaciStrom::GetKey()
{
    return this->key;
}

string RozhodovaciStrom::GetValue()
{
    return this->value;
}

RozhodovaciStrom* RozhodovaciStrom::GetAno()
{
    return this->ano;
}

RozhodovaciStrom* RozhodovaciStrom::GetNe()
{
    return this->ne;
}

RozhodovaciStrom* RozhodovaciStrom::CreateAno(string k, string v)
{
    this->ano = new RozhodovaciStrom(k, v);
    return this->ano;
}

RozhodovaciStrom* RozhodovaciStrom::CreateNe(string k, string v)
{
    this->ne = new RozhodovaciStrom(k, v);
    return this->ne;
}

void RozhodovaciStrom::PrintTree(string prefix, string branch)
{
    cout << prefix << "[" << branch << "] "
         << "Kriterium: " << this->key
         << " | Hodnota: " << this->value << endl;

    if (this->ano != nullptr)
    {
        this->ano->PrintTree(prefix + "   ", "ANO");
    }

    if (this->ne != nullptr)
    {
        this->ne->PrintTree(prefix + "   ", "NE");
    }
}

int main()
{
    //začátek stromu
    RozhodovaciStrom* koren = new RozhodovaciStrom("Zije zvire ve vode?", "zvire");

    //1. úroveň
    RozhodovaciStrom* vodni = koren->CreateAno("Ma ploutve?", "vodni zvire");
    RozhodovaciStrom* ne_vodni = koren->CreateNe("Ma ctyri nohy?", "suchozemske nebo letajici zvire");

    //2. úroveň - vodní
    RozhodovaciStrom* savec = vodni->CreateAno("Je to savec?", "vodni tvor");
    RozhodovaciStrom* dlouhy = vodni->CreateNe("Ma dlouhe telo?", "vodni tvor");

    //2. úroveň - souš
    RozhodovaciStrom* ctyri_nohy = ne_vodni->CreateAno("Je to domaci zvire?", "ctyrnohe zvire");
    RozhodovaciStrom* ne_ctyri_nohy = ne_vodni->CreateNe("Ma kridla?", "jiny typ zivocicha");

    //3. úroveň - vodní
    savec->CreateAno("Je to delfin?", "delfin");
    savec->CreateNe("Je to zralok?", "zralok");

    dlouhy->CreateAno("Je to had?", "had");
    dlouhy->CreateNe("Je to meduza?", "meduza");

    //3. úroveň - souš
    RozhodovaciStrom* domaci = ctyri_nohy->CreateAno("Steka?", "domaci zvire");
    RozhodovaciStrom* divoke = ctyri_nohy->CreateNe("Ma pruhy?", "divoke zvire");

    ne_ctyri_nohy->CreateAno("Je aktivni hlavne v noci?", "ptak");
    ne_ctyri_nohy->CreateNe("Skace a ma dlouhe usi?", "jine zvire");

    //4. úroveň
    domaci->CreateAno("Je to pes?", "pes");
    domaci->CreateNe("Je to kocka?", "kocka");

    divoke->CreateAno("Je to zebra?", "zebra");
    divoke->CreateNe("Je to slon?", "slon");

    ne_ctyri_nohy->GetAno()->CreateAno("Je to sova?", "sova");
    ne_ctyri_nohy->GetAno()->CreateNe("Je to orel?", "orel");

    ne_ctyri_nohy->GetNe()->CreateAno("Je to kralik?", "kralik");
    ne_ctyri_nohy->GetNe()->CreateNe("Je to had?", "had");

    koren->PrintTree();

    delete koren;
    return 0;
}