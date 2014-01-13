#pragma once

#include <stack>
#include <vector>

using namespace std;

template <class T>
struct Node
{
    Node* left;
    Node* right;
    T value;

    Node(T v){
        value = v;
        left = NULL;
        right = NULL;
    }
};

template<class T> bool isBalanced(Node<T>* root)
{
    if(root == NULL)
    {
        return true;
    }

    //depth first to find min/max depth, root has depth 1, empty tree has depth 0
    int maxDepth = 1;
    int minDepth = std::numeric_limits<int>::max();
    struct Pair
    {
        Node<T>* node;
        int depth;
    };
    stack<Pair*> s;
    Pair* p = new Pair();
    p->node = root;
    p->depth = 1;
    s.push(p);
    while(!s.empty())
    {
        p = s.top();
        s.pop();
        cout << "visiting node: " << p->node->value << endl;
        Node<T>* n = p->node;
        
        if(n->left == NULL || n->right == NULL)
        {
            //update min/max
            if(p->depth > maxDepth)
                maxDepth = p->depth;

            if(p->depth < minDepth)
                minDepth = p->depth;
        }
        
        if(n->left != NULL)
        {
            Pair * l = new Pair();
            l->node = n->left;
            l->depth = p->depth + 1;
            s.push(l);
        }
        
        if(n->right != NULL)
        {
            Pair* r = new Pair();
            r->node = n->right;
            r->depth = p->depth + 1;
            s.push(r);
        }
        delete p;
    }
    cout<< "min: "  << minDepth << " max: " << maxDepth << endl;
    return (maxDepth - minDepth < 2);
}

template<class T> int countChildren(Node<T>* root)
{
    if(root == NULL)
    {
        return 0;
    }
    cout << "visiting node: " << root->value << endl;
    return countChildren(root->left) + countChildren(root->right) + 1;
}

template<class T> void deleteTree(Node<T>* root)
{
    if(root == NULL) 
    {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

template<class T> int maxDepth(Node<T>* root)
{
    if(root == NULL)
    {
        return 0;
    }
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

template<class T> int minDepth(Node<T>* root)
{
    if(root == NULL)
    {
        return 0;
    }
    return 1 + min(minDepth(root->left), minDepth(root->right));
}

//build a binary search tree
template<class T> Node<T>* insert(Node<T>* node, T value)
{   
    if(node == NULL)
    {
        Node<T>* n = new Node<T> (value);
        return n;
    }
    else if(node->value < value) 
    {
        node->right = insert(node->right, value);
    }
    else
    {
        node->left = insert(node->left, value);
    }
    return node;
}

template<class T> void inOrderVisit(Node<T>* n)
{
    if(n == NULL)
    {
        return;
    }
    inOrderVisit(n->left);
    cout << n->value << endl;
    inOrderVisit(n->right);
}

template<class T> void postOrderVisit(Node<T>* n)
{
    if(n == NULL)
    {
        return;
    }
    postOrderVisit(n->left);
    postOrderVisit(n->right);
    cout << n->value << endl;
}

template<class T> void preOrderVisit(Node<T>* n)
{
    if(n == NULL)
    {
        return;
    }
    cout << n->value << endl;
    preOrderVisit(n->left);
    preOrderVisit(n->right);
}

template<class T> bool hasPathSum(Node<T>* n, int target)
{
    int newTarget = target - n->value;

    if(n->left == NULL && n->right == NULL)
    {
        return (newTarget == 0);
    }

    return hasPathSum(n->left, newTarget) || hasPathSum(n->right, newTarget);
}

//print all root to leaf paths
template<class T> void printAllPaths(Node<T>* root)
{
    vector<T> path;
    printAllPathsR(root, path);
}

template<class T> 
void printAllPathsR(Node<T>* node, vector<T>& path)
{
    if(node == NULL)
    {
        return;
    }

    if(node->left == NULL && node->right == NULL)
    {
        for(vector<T>::iterator i = path.begin(); i != path.end(); ++i)
        {
            cout << *i << ' ';
        }
        cout << node->value << endl;
        return;
    }
    path.push_back(node->value);
    printAllPathsR(node->left, path);
    printAllPathsR(node->right, path);
    path.pop_back();
}

template<class T>
void printTreeFormat1(Node<T>* root)
{
    //preorder
    if(root == NULL)
    {
        return;
    }
    cout << root->value;
    if(root->left == NULL || root->right == NULL)
    {
        return;
    }
    cout<<"(";
    printTreeFormat1(root->left);
    cout << ",";
    printTreeFormat1(root->right);
    cout <<")";
}