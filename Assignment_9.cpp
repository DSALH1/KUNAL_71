#include <bits/stdc++.h>
using namespace std;
class Node{
    private:
    int data;
    int height;
    Node* left;
    Node* right;
    public:
    Node()
    {
        this->data = 0;
        this->height = 1;
        this->left = NULL;
        this->right = NULL;
    }
    friend class AVL;

};
class AVL{
    public:
    Node* root;
    AVL()
    {
        root = NULL;
    }
    int update_height(Node* root)
    {
        if(root == NULL)
        {
            return 0;
        }
        root->height = (max((update_height(root->left)), (update_height(root->right))) + 1);
        return root->height;
    }
    int balance_factor(Node* root)
    {
        if(root == NULL)
        {
            return 0;
        }
        return ((update_height(root->left)) - (update_height(root->right)));
    }
    Node* balance(Node* c)
    {
        if(balance_factor(c) == 2)
        {
            if(balance_factor(c->left) < 0)
            {
                c = LRrotation(c);
            }
            else
            {
                c = LLrotation(c);
            }
        }
        else if(balance_factor(c) == -2)
        {
            if(balance_factor(c->right) > 0)
            {
                c = RLrotation(c);
            }
            else
            {
                c = RRrotation(c);
            }
        }
        update_height(c);
        return c;
    }
    Node* LLrotation(Node* root)
    {
        Node* temp = root->left;
        root->left = temp->right;
        temp->right = root;
        update_height(root);
        update_height(temp);
        return temp;
    }
    Node* RRrotation(Node* root)
    {
        Node* temp = root->right;
        root->right = temp->left;
        temp->left = root;
        update_height(root);
        update_height(temp);
        return temp;
    }
    Node* RLrotation(Node* root)
    {
        root->right = LLrotation(root->right);
        return RRrotation(root);
    }
    Node* LRrotation(Node* root)
    {
        root->left = RRrotation(root->left);
        return LLrotation(root);
    }
    void inorder(Node* root)
    {
        if(root == NULL)
        {
            return;
        }
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
    Node* search(Node* root, int x)
    {
        int cnt=0;
        Node* curr = root;
        while(curr->data != x)
        {
            cnt++;
            if(curr!=NULL)
            {
                if(curr->data > x)
                {
                    curr = curr->left;
                }
                else
                {
                    curr = curr->right;
                }
            }
            if(curr == NULL)
            {
                return NULL;
            }
        }
        return curr;
    }
    void levelOrderTravesal(Node* root)
    {
        queue<Node*>q;
        Node* temp = root;
        q.push(root);
        q.push(NULL);
        while(!q.empty())
        {
            temp = q.front();
            q.pop();
            if(temp == NULL)
            {
                cout<<endl;
                if(!q.empty())
                {
                    q.push(NULL);
                }
            }
            else
            {
                cout<<temp->data<<" ";
                if(temp->left)
                {
                    q.push(temp->left);
                }
                if(temp->right)
                {
                    q.push(temp->right);
                }
            }
        }
    }
    Node* insert(Node* root, int k)
    {
        if(root == NULL)
        {
            root = new Node;
            root->data = k;
            return root;
        }
        if(root->data > k)
        {
            root->left = insert(root->left, k);
        }
        else if(root->data < k)
        {
            root->right = insert(root->right, k);
        }
        cout<<root->height<<endl;
        return balance(root);
    
    }
};
using namespace std;
int main()
{
    int c = 1;
    AVL t;
    int key;
    // node *p=t.get_root();
    Node *p = NULL;
    while (c > 0)
    {
        cout << "MENU" << endl;
        cout << "1.Insert" << endl;
        cout << "2.Search" << endl;
        cout << "3.Inorder" << endl;
        cout << "4.Level Order Traversing" << endl;
        cout << "5.Exit" << endl;
        cout << "Enter Your Choice:";
        cin >> c;
        if (c == 1)
        {
            int n;
            cout<<"Enter the total number of nodes: "<<endl;
            cin>>n;
            while(n--)
            {
                cout << "Enter data" << endl;
                cin >> key;
                p = t.insert(p, key);
            }
        }
        else if (c == 2)
        {
            cout << "Enter key to search" << endl;
            cin >> key;
            if (t.search(p, key))
            {
                cout << "Key Found" << endl;
            }
            else
            {
                cout << "Key not found" << endl;
            }
        }
        else if (c == 3)
        {
            t.inorder(p);
            cout << endl;
        }
        else if (c == 4)
        {
            t.levelOrderTravesal(p);
            cout << endl;
        }
        else if (c == 5)
        {
            break;
        }
    }
   return 0;
}
