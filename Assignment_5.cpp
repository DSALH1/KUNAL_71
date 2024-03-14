#include <iostream>
using namespace std;
class Node
{
public:
    int key;
    string data;
    Node *next;
    Node(int key, string data)
    {
        this->key = key;
        this->data = data;
        this->next = NULL;
    }
};

class Hashmap
{
public:
    Node *arr[10];
    Hashmap()
    {
        for (int i = 0; i < 10; i++)
        {
            arr[i] = NULL;
        }
    }

    void insert(int k, string data)
    {
        int k1 = k % 10;
        Node *temp = arr[k1];
        if (arr[k1] == NULL)
        {
            arr[k1] = new Node(k, data);
            return;
        }
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new Node(k, data);
    }

    void display()
    {
        for (int i = 0; i < 10; i++)
        {
            Node *temp = arr[i];
            cout << i << "->";
            if (temp == NULL)
            {
                cout << "NULL" << endl;
            }
            while (temp != NULL)
            {
                cout << temp->data << "->";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void search(int key)
    {
        int k1 = key % 10;
        Node *temp = arr[k1];
        while (temp != NULL and temp->key != key)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            cout << "Key is not present" << endl;
        }
        else
        {
            cout << "Key " << temp->key << " is present" << endl;
        }
    }
};

int main()
{
    Hashmap h;
    h.insert(1, "KUNAL");
    h.insert(3, "NEEL");
    h.insert(6, "BHVYAM");
    h.insert(8, "PARIMAL");
    h.insert(33, "ZEEL");
    h.display();
    h.search(43);
    return 0;
}
