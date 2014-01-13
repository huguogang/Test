// Algo_Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyBinaryTree.h"

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template<class t> 
void printVector(vector<t>& v)
{
    for(vector<t>::const_iterator i = v.begin(); i != v.end(); ++i)
    {
        cout << *i << endl;
    }
}
int fibonacciTailR(int n, int previous1 = 0, int previous = 1)
{
    if(n == 1)
    {
        return previous;
    }
    return fibonacciTailR(n - 1, previous, previous + previous1);
}

int fibonacciR(int n)
{
    if(n <= 2)
    {
        return 1;
    }
    return(fibonacciR(n - 1) + fibonacciR(n-2));
}

template<class t>
bool findElementR(vector<t>& input, const t& target)
{
    if(input.size() == 0)
    {
        return false;
    }
    if(input.back() == target)
    {
        return true;
    }
    input.pop_back();
    return findElementR<t>(input, target);
}



//the first nIn elements are in the subset
template<class t>
void allSubsetR(vector<t>& input, int nVisited = 0, int nIn = 0)
{    
    int len = input.size();
    //terminal
    if (nVisited == len)
    {
        for(int i = 0; i < nIn; i++)
        {
            cout << input[i];
            cout << "\t";
        }
        cout << endl;
        return;
    }
    //all subset without me
    allSubsetR(input, nVisited + 1, nIn);

    //all subset with me
    t tmp = input[nIn];
    input[nIn] = input[nVisited];
    input[nVisited] = tmp;
    nIn++;
    allSubsetR(input, nVisited + 1, nIn);
}

void sortStack(stack<int>& input, stack<int>& output)
{
    while(!input.empty())
    {
        int top = input.top();
        input.pop();
        while(!output.empty() && output.top() >= top)
        {
            input.push(output.top());
            output.pop();
        }
        output.push(top);
    }
}

//print all permutation of n pair of matched parenth
void printMatchedParentheseR(int n, vector<char>& result, int l, int r)
{
    if(l == 0 && r == 0)
    {
        for(int i = 0; i < 2 * n; i++)
        {
            cout << result[i];
        }
        cout << endl;
        return;
    }
    else if(l < 0 || r < 0)
    {
        return; //back track
    }
    else
    {
        //left p
        if(l > 0)
        {
            result[n * 2 - l - r] = '(';
            printMatchedParentheseR(n, result, l - 1, r);
        }
        //right p
        if(l < r)
        {
            result[n * 2 - l - r] = ')';
            printMatchedParentheseR(n, result, l, r - 1);
        }

    }
}

void printMatchedParenthese(int n)
{
    vector<char> result(n*2);
    printMatchedParentheseR(n, result, n, n);
}

void merge(vector<int>& a, const vector<int>& b, int aSize, int bSize)
{
    int total = aSize + bSize ;
    int aLoc = aSize - 1;
    int bLoc = bSize - 1;
    a.resize(total);
    for(int i = total -1; i >=0; --i)
    {
        if(aLoc < 0)
        {
            a[i] = b[bLoc];
            bLoc--;
        }
        else if(bLoc < 0)
        {
            return; //done
        }
        else
        {
            if(a[aLoc] >= b[bLoc])
            {
                a[i] = a[aLoc];
                aLoc--;
            }
            else
            {
                a[i] = b[bLoc];
                bLoc--;
            }
        }
    }
}

void merge1(vector<int>& a, const vector<int>& b, int aSize, int bSize)
{
    int aLoc = aSize - 1;
    int bLoc = bSize - 1;
    int tail = aSize + bSize - 1;

    while(aLoc >= 0 && bLoc >= 0)
    {
        if(a[aLoc] >= b[bLoc])
        {
            a[tail] = a[aLoc];
            aLoc--;
        }
        else
        {
            a[tail] = b[bLoc];
            bLoc--;
        }
        tail--;
    }
    while(bLoc >= 0)
    {
        a[tail] = b[bLoc];
        tail--;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    //--merge two arrays
    //vector<int> a;
    //a.push_back(1);
    //a.push_back(5);
    //a.push_back(8);

    //vector<int> b;
    //b.push_back(2);
    //b.push_back(3);
    //b.push_back(4);
    //b.push_back(10);
    //b.push_back(15);

    //a.resize(a.size() + b.size());
    
    //merge(a, b, 3, 5);
    //printVector(a);

    //merge1(a, b, 3, 5);
    //printVector(a);

    ///-print change
    //--printMatchedParenthese
    //cout << "-- result for 1 pair" << endl;
    //printMatchedParenthese(1);

    //cout << "-- result for 2 pair" << endl;
    //printMatchedParenthese(2);

    //cout << "-- result for 3 pair" << endl;
    //printMatchedParenthese(3);
    
    //cout << "-- result for 4 pair" << endl;
    //printMatchedParenthese(4);
    //--binary search tree
    Node<int>* root;
    root = NULL;
    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 5);
    root = insert(root, 1);
    root = insert(root, 3);
    //printAllPaths(root);
    printTreeFormat1(root);
    //int count = countChildren(root);
    //cout << "count: " << count << endl;

    //bool is = isBalanced(root);
    //cout << "is balanced: " << is << endl;

    //cout << "max depth: " << maxDepth(root) << endl;
    //cout << "min depth: " << minDepth(root) << endl;
    
    //cout << "in order visit" << endl;
    //inOrderVisit(root);

    //cout << "pre order visit" << endl;
    //preOrderVisit(root);

    //cout << "post order visit" << endl;
    //postOrderVisit(root);

    //cout << "hasPathSum(root, 7): " << hasPathSum(root, 7) << endl;
    //cout << "hasPathSum(root, 11): " << hasPathSum(root, 11) << endl;

    //deleteTree(root);

    //-- check if tree is balanced
    //Node<int>* n;
    //Node<int>* root;
    //root = n = new Node<int>(2);
    //n->left = new Node<int>(3);
    //n = n->left;
    //n->left = new Node<int>(4);
    //n->right = new Node<int>(5);

    //int count = countChildren(root);
    //cout << "count: " << count << endl;

    //bool is = isBalanced(root);
    //cout << "is balanced: " << is << endl;

    //cout << "max depth: " << maxDepth(root) << endl;
    //cout << "min depth: " << minDepth(root) << endl;
    //deleteTree(root);
    
    //--sort stack test
    //stack<int> input;
    //stack<int> output;
    //input.push(100);
    //input.push(20);
    //input.push(1000);
    //sortStack(input, output);
    //while(!output.empty())
   // {
   //     cout << output.top() << endl;
   //     output.pop();
   // }
    //-- test allsubsteR
    //vector<int> v;
    //v.push_back(1);
    //v.push_back(2);
    //v.push_back(3);
    //allSubsetR(v);

    //- - test find element
    //vector<int> v(6);
    //v.push_back(1);
    //v.push_back(-81);
    //v.push_back(5);
    //v.push_back(3);
    //cout << findElementR(v, 1) << endl;
    //cout << findElementR(v, 2) << endl;
    //cout << findElementR(v, -81) << endl;

    //--test fibonacciR
    //cout << fibonacciTailR(1) << endl;
    //cout << fibonacciTailR(5) << endl;
    //cout << fibonacciTailR(6) << endl;
    //cout << fibonacciTailR(7) << endl;
    //cin.ignore(1);

    //--test fibonacciR
    //cout << fibonacciR(5) << endl;
    //cout << fibonacciR(6) << endl;
    //cout << fibonacciR(7) << endl;
    //cin.ignore(1);

    cin.ignore(1);
	return 0;
}

