#include <iostream>
#include <string>
using namespace std;
#include <stack>
#include <ostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "arithmeticExpression.h"

arithmeticExpression::arithmeticExpression(const string& express): infixExpression(express), root(0)
{
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

/* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */
    void arithmeticExpression::buildTree()
    {
      string pfExpression = infix_to_postfix(); 
    stack <TreeNode*> tree;
    char item;

    for(unsigned i = 0; i < pfExpression.size(); ++i)
    {
      item = pfExpression.at(i);
      if(item != '+' && item != '-' && item != '*' && item != '/') 
      {
        TreeNode* next = new TreeNode(item, 'a' + i);
        tree.push(next);
        
      }
      else 
      {
        TreeNode* nextRoot = new TreeNode(item, 'a' + i); //initialize root
        nextRoot -> left = tree.top();  //stack's top is left child
        tree.pop(); //pops top
        nextRoot -> right = tree.top(); //stack's new top is right child
        tree.pop();  //pops top again
        tree.push(nextRoot);  //the tree is pushed on stack
      }
    }
    root = tree.top();
    tree.pop();
      
    }

    /* Calls the recursive infix function. */
    void arithmeticExpression::infix()
    {
      if(root == 0)  //base case
      {
        return;
      }
      infix(root);
    }

    /* Calls the recursive prefix function. */
    void arithmeticExpression::prefix()
    {
      if(root == 0)
      {
        return;
      }
      prefix(root);
    }

    /* Calls the recursive postfix function. */
    void arithmeticExpression::postfix()
    {
      if(root == 0)
      {
        return;
      }
      postfix(root);
    }

    /* Helper function that outputs the infix notation of the arithmetic expression tree
       by performing the inorder traversal of the tree.
       An opening and closing parenthesis must be added at the 
       beginning and ending of each expression. */
    /*void arithmeticExpression::infix(TreeNode *curr)
    {
      
      if(curr)
      {
       if(curr -> left != nullptr && curr -> right != nullptr)
       cout << "(";
       infix(curr -> right);
       cout << curr->data;
       infix(curr -> left);
       if(curr -> left != nullptr && curr -> right != nullptr)
       cout << ")";
      }
      else
      {
        return;
      }

    }*/
    void arithmeticExpression::infix(TreeNode* node){
    if (node != nullptr){
    if (node->left != nullptr && node -> right != nullptr)
    cout << "(" ;
    infix(node->right);
    cout << node -> data;
    infix(node -> left);
    if (node->left != nullptr && node -> right != nullptr)
    cout << ")";
}
  else  
  {
    return;
  }
}

    /* Helper function that outputs the prefix notation of the arithmetic expression tree
       by performing the preorder traversal of the tree. */
    void arithmeticExpression::prefix(TreeNode *curr)
    {
      if (curr)
      {
        /* first print data of node */
        cout << curr->data ;
  
        /* now recur on right subtree */
        prefix(curr->right);

        /* then recur on left sutree */
        prefix(curr->left);
  
      }
      else
      {
        return; 
      }
    }

    /* Helper function that outputs the postfix notation of the arithmetic expression tree
       by performing the postorder traversal of the tree. */
    void arithmeticExpression::postfix(TreeNode *curr)
    {
      if(curr != nullptr)
      {
        postfix(curr -> right); 
        postfix(curr -> left); 
        cout << curr -> data;
      }
      else
      {
        return;
      }
    }

    


    /* Helper function for generating the dotty file. This is a recursive function. */
  
    void arithmeticExpression::visualizeTree(ofstream & outFS, TreeNode* node)
{
   if(node){
        outFS<<node->key << "[ label = \""<<node->data<<"\"];"<<endl;
        if(node->left){
            visualizeTree(outFS,node->left);
            outFS<<node->key <<" -> " <<node->left->key<<";"<<endl;    
        }
        
        if(node->right){
            visualizeTree(outFS,node->right);
            outFS<<node->key <<" -> " <<node->right->key<<";"<<endl;    
        }
    }
}
    


