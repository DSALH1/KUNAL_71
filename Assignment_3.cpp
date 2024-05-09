// 0) Create an inordered threaded binary search tree for integer. Perform inorder traversal,
// and deletion of a node.
// Note: Display lbit, rbit for every node

#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    int rbit;
    int lbit;

    Node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
        this->rbit = 0;
        this->lbit = 0;
    }

    friend class TBST;
};

class TBST
{
public:
    Node *root, *head;

    TBST()
    {
        root = NULL;
        head = NULL;
    }

    Node *get_root()
    {
        return root;
    }

    void insert(int x)
    {
        if (root == NULL)
        {
            head = new Node(999);
            head->right = head;
            root = new Node(x);
            head->left = root;
            head->lbit = 1;
            root->left = head;
            root->right = head;
            return;
        }
        else
        {
            Node *p = root;
            Node *q = new Node(x);

            while (true)
            {
                if (x == p->data)
                {
                    delete q;
                    return;
                }
                else if (x < p->data)
                {
                    if (p->lbit == 1)
                    {
                        p = p->left;
                    }
                    else
                    {
                        q->left = p->left;
                        q->right = p;
                        p->left = q;
                        p->lbit = 1;
                        return;
                    }
                }
                else
                {
                    if (p->rbit == 1)
                    {
                        p = p->right;
                    }
                    else
                    {
                        q->right = p->right;
                        q->left = p;
                        p->right = q;
                        p->rbit = 1;
                        return;
                    }
                }
            }
        }
    }

    void Inorder()
    {
        Node *p = root;

        while (p->lbit == 1)
        {
            p = p->left;
        }
        while (p != head)
        {
            cout << p->data << " " << endl;
            cout << "The lbit of " << p->data << " is : " << p->lbit << endl;
            cout << "The rbit of " << p->data << " is : " << p->rbit << endl;

            if (p->rbit == 1)
            {
                p = p->right;
                while (p->lbit == 1)
                {
                    p = p->left;
                }
            }

            else
            {
                p = p->right;
            }
        }
        cout << endl;
    }

   void preorder()
    {
        if(root == NULL)
        {
            cout<<"Tree is empty"<<endl;
            return;
        }
        Node* p = root;
        while(p!=head)
        {
           cout<<p->data<<endl;
           cout<<"lbit: "<<p->lbit<<endl;
           cout<<"rbit: "<<p->rbit<<endl;
           if(p->lbit == 1)
           {
              p = p->left;
           }
           else if(p->rbit == 1)
           {
              p = p->right;
           }
           else
           {
              while(p != NULL and p->rbit == 0)
              {
                 p=this->inoderSuccesor(p);
              }
              if(p != NULL)
              {
                 p = p->right;
              }
           }
        }
        return;
    }

    Node *InOrderSuccessor(Node *root)
    {
        if (root == NULL)
        {
            return NULL;
        }

        if (root->rbit == 0)
        {
            return root->right;
        }

        root = root->right;
        while (root->lbit == 1)
        {
            root = root->left;
        }

        return root;
    }

    Node *deletionNode(Node *&root, int key)
    {
        if (root == NULL)
        {
            return root;
        }

        Node *p = NULL;
        Node *curr = root;

        // Search for the node to be deleted
        while (curr && curr->data != key)
        {
            p = curr;

            if (key < curr->data)
            {
                if (curr->lbit == 1)
                {
                    curr = curr->left;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (curr->rbit == 1)
                {
                    curr = curr->right;
                }
                else
                {
                    break;
                }
            }
        }

        if (curr == NULL)
        {
            return root; // Node not found, return unchanged tree
        }

        Node *child;
        if (curr->lbit == 0 || curr->rbit == 0)
        {
            // Node has at most one child
            if (curr->lbit == 0 && curr->rbit == 1)
            {
                child = curr->right;
            }
            else if (curr->rbit == 0 && curr->lbit == 1)
            {
                child = curr->left;
            }
            else
            {
                if (curr == p->left)
                {
                    p->lbit = 0;
                    p->left = curr->left;
                }
                else
                {
                    p->rbit = 0;
                    p->right = curr->right;
                }

                return p;
            }

            if (p == NULL)
            {
                return child; // Node to delete is root
            }
            if (curr == p->left)
            {
                p->left = child;
                if (child)
                {
                    p->lbit = 1;
                }
                else
                {
                    p->lbit = 0;
                }
                // p->lbit = (child == NULL) ? 0 : 1; // Update threaded link
            }
            else
            {
                p->right = child;
                if (child)
                {
                    p->rbit = 1;
                }
                else
                {
                    p->rbit = 0;
                }
                // p->rbit = (child == NULL) ? 0 : 1; // Update threaded link
            }

            delete curr;
        }
        else
        {
            // Node has both children
            Node *s = InOrderSuccessor(curr); // Find in-order successor
            int temp = s->data;               // Swap data with successor
            deletionNode(root, temp);         // Delete successor node
            curr->data = temp;                // Replace data with successor's data
        }

        return root;
    }
};

int main()
{

    TBST tree;

    tree.insert(15);
    tree.insert(11);
    tree.insert(17);
    tree.insert(10);
    tree.insert(14);
    tree.insert(16);
    tree.insert(18);
    tree.Inorder();

    tree.root = tree.deletionNode(tree.root, 15);
    tree.Inorder();

    return 0;
}
