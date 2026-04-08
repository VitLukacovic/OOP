#include <iostream>
#include <string>
using namespace std;

class StringNode
{
    private:
        string key;
        string value;
        StringNode *left;
        StringNode *right;

    public:
        StringNode(string k, string v);
        ~StringNode();

        string GetKey();
        string GetValue();

        StringNode* GetLeft();
        StringNode* GetRight();

        StringNode* CreateLeft(string k, string v);
        StringNode* CreateRight(string k, string v);
};

StringNode::StringNode(string k, string v)
{
    this->key = k;
    this->value = v;
    this->left = nullptr;
    this->right = nullptr;
}

StringNode::~StringNode()
{
    if(this->left != nullptr)
    {
        delete this->left;
        this->left = nullptr;
    }

    if(this->right != nullptr)
    {
        delete this->right;
        this->right = nullptr;
    }
}

string StringNode::GetKey()
{
    return this->key;
}

string StringNode::GetValue()
{
    return this->value;
}

StringNode* StringNode::GetLeft()
{
    return this->left;
}

StringNode* StringNode::GetRight()
{
    return this->right;
}

StringNode* StringNode::CreateLeft(string k, string v)
{
    this->left = new StringNode(k, v);
    return this->left;
}

StringNode* StringNode::CreateRight(string k, string v)
{
    this->right = new StringNode(k, v);
    return this->right;
}

int main()
{
    StringNode* root = new StringNode("A", "koren");

    StringNode* leftNode = root->CreateLeft("B", "levy potomek");
    StringNode* rightNode = root->CreateRight("C", "pravy potomek");

    leftNode->CreateLeft("D", "levy syn B");
    leftNode->CreateRight("E", "pravy syn B");

    rightNode->CreateLeft("F", "levy syn C");
    rightNode->CreateRight("G", "pravy syn C");

    cout << "Koren: " << root->GetKey() << " -> " << root->GetValue() << endl;
    cout << "Levy potomek korene: " << root->GetLeft()->GetKey() << endl;
    cout << "Pravy potomek korene: " << root->GetRight()->GetKey() << endl;

    delete root;
    return 0;
}