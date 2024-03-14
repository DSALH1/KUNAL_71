#include <bits/stdc++.h>
using namespace std;

struct Node
{
    struct Node *left, *right;
    int info;
    bool lthread;
    bool rthread;
};

struct Node *insert(struct Node *root, int ikey)
{
    Node *ptr = root;
    Node *par = NULL;
    while (ptr != NULL)
    {
        if (ikey == (ptr->info))
        {
            printf("Duplicate Key !\n");
            return root;
        }

        par = ptr;

        if (ikey < ptr->info)
        {
            if (ptr->lthread == false)
                ptr = ptr->left;
            else
                break;
        }

        else
        {
            if (ptr->rthread == false)
                ptr = ptr->right;
            else
                break;
        }
    }

    Node *tmp = new Node;
    tmp->info = ikey;
    tmp->lthread = true;
    tmp->rthread = true;

    if (par == NULL)
    {
        root = tmp;
        tmp->left = NULL;
        tmp->right = NULL;
    }
    else if (ikey < (par->info))
    {
        tmp->left = par->left;
        tmp->right = par;
        par->lthread = false;
        par->left = tmp;
    }
    else
    {
        tmp->left = par;
        tmp->right = par->right;
        par->rthread = false;
        par->right = tmp;
    }

    return root;
}

struct Node *inSucc(struct Node *ptr)
{
    if (ptr->rthread == true)
        return ptr->right;

    ptr = ptr->right;
    while (ptr->lthread == false)
        ptr = ptr->left;

    return ptr;
}

struct Node *inorderSuccessor(struct Node *ptr)
{
    if (ptr->rthread == true)
        return ptr->right;

    ptr = ptr->right;
    while (ptr->lthread == false)
        ptr = ptr->left;
    return ptr;
}

void inorder(struct Node *root)
{
    if (root == NULL)
        printf("Tree is empty");

    struct Node *ptr = root;
    while (ptr->lthread == false)
        ptr = ptr->left;

    while (ptr != NULL)
    {
        printf("%d ", ptr->info);
        ptr = inorderSuccessor(ptr);
    }
}

struct Node *inPred(struct Node *ptr)
{
    if (ptr->lthread == true)
        return ptr->left;

    ptr = ptr->left;
    while (ptr->rthread == false)
        ptr = ptr->right;
    return ptr;
}

struct Node *caseA(struct Node *root, struct Node *par,
                   struct Node *ptr)
{
    if (par == NULL)
        root = NULL;

    else if (ptr == par->left)
    {
        par->lthread = true;
        par->left = ptr->left;
    }
    else
    {
        par->rthread = true;
        par->right = ptr->right;
    }

    free(ptr);
    return root;
}

struct Node *caseB(struct Node *root, struct Node *par,
                   struct Node *ptr)
{
    struct Node *child;

    if (ptr->lthread == false)
        child = ptr->left;
    else
        child = ptr->right;
    if (par == NULL)
        root = child;
    else if (ptr == par->left)
        par->left = child;
    else
        par->right = child;

    Node *s = inSucc(ptr);
    Node *p = inPred(ptr);

    if (ptr->lthread == false)
        p->right = s;

    else
    {
        if (ptr->rthread == false)
            s->left = p;
    }

    free(ptr);
    return root;
}

struct Node *caseC(struct Node *root, struct Node *par,
                   struct Node *ptr)
{
    struct Node *parsucc = ptr;
    struct Node *succ = ptr->right;

    while (succ->lthread == false)
    {
        parsucc = succ;
        succ = succ->left;
    }

    ptr->info = succ->info;

    if (succ->lthread == true && succ->rthread == true)
        root = caseA(root, parsucc, succ);
    else
        root = caseB(root, parsucc, succ);

    return root;
}

struct Node *delThreadedBST(struct Node *root, int dkey)
{
    struct Node *par = NULL, *ptr = root;
    int found = 0;

    while (ptr != NULL)
    {
        if (dkey == ptr->info)
        {
            found = 1;
            break;
        }
        par = ptr;
        if (dkey < ptr->info)
        {
            if (ptr->lthread == false)
                ptr = ptr->left;
            else
                break;
        }
        else
        {
            if (ptr->rthread == false)
                ptr = ptr->right;
            else
                break;
        }
    }

    if (found == 0)
        printf("dkey not present in tree\n");
    else if (ptr->lthread == false && ptr->rthread == false)
        root = caseC(root, par, ptr);
    else if (ptr->lthread == false)
        root = caseB(root, par, ptr);
    else if (ptr->rthread == false)
        root = caseB(root, par, ptr);
    else
        root = caseA(root, par, ptr);

    return root;
}

int main()
{
    struct Node *root = NULL;

    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 16);
    root = insert(root, 14);
    root = insert(root, 17);
    root = insert(root, 13);
    inorder(root);
    cout << endl;
    root = delThreadedBST(root, 20);
    inorder(root);

    return 0;
}