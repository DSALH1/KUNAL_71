#include <bits/stdc++.h>
using namespace std;
int size = 100;
class HashTable
{
public:
    string name;
    int ph_no;
    HashTable(string name, int ph_no)
    {
        this->name = name;
        this->ph_no = ph_no;
    }
};
class HashMap
{
public:
    HashTable **table;
    HashMap()
    {
        table = new HashTable *[size];
        for (int i = 0; i < size; i++)
        {
            table[i] = NULL;
        }
    }
    int HashFunc(int ph_no)
    {
        return ph_no % 10;
    }
    void insert(string name, int ph_no)
    {
        int h = HashFunc(ph_no);
        while (table[h] != NULL and table[h]->ph_no != ph_no)
        {
            h = HashFunc(h + 1);
        }
        if (table[h] != NULL)
        {
            delete table[h];
        }
        table[h] = new HashTable(name, ph_no);
    }
    string Search(int ph_no)
    {
        int h = HashFunc(ph_no);
        while (table[h] != NULL and table[h]->ph_no != ph_no)
        {
            h = HashFunc(h + 1);
        }
        if (table[h] == NULL)
        {
            return "null";
        }
        else
        {
            return table[h]->name;
        }
    }
    void remove(int ph_no)
    {
        int h = HashFunc(ph_no);
        while (table[h] != NULL)
        {
            if (table[h]->ph_no == ph_no)
            {
                break;
            }
            h = HashFunc(h + 1);
        }
        if (table[h] == NULL)
        {
            cout << "No Element found at key" << endl;
            return;
        }
        else
        {
            delete table[h];
        }
        cout << "Element deleted" << endl;
    }
    ~HashMap()
    {
        for (int i = 0; i < size; i++)
        {
            if (table[i] != NULL)
            {
                delete table[i];
                delete[] table;
            }
        }
    }
};
int main()
{
    HashMap h;
    h.insert("Kunal", 1234);
    h.insert("abcd", 1236);
    h.insert("ghjl", 1239);
    h.insert("noob", 1244);
    cout << h.Search(1244)<<endl;
    // h.remove(1236);
    cout << h.Search(1236)<<endl;
    return 0;
}