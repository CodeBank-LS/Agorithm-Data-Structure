//
// Created by L Su on 23/9/2022.
//
/*
Sample input 1: A1 A2 A3 IN
Sample output 1: 1 2 3
Sample input 2: A1 A2 A3 PRE
Sample output 2: 2 1 3
Sample input 3: A1 D1 POST
Sample output 3: EMPTY
*/
/* Mindset:
1. construct AVL tree (height check,balance operation：rr,ll,lr,rl)
2. insert/search/delete node=>form a new structure tree
3. balance the new structure tree
4. print node's key based on preorder/inorder/postorder
*/

#include <iostream>
#include<string>
#include<sstream>
using namespace std;
//AVL tree implementation
// AVL tree implementation in C++

#include <iostream>
using namespace std;

class AVL_Node {
public:
    int key;
    AVL_Node *left;
    AVL_Node *right;
    int height;//height of the node
};


// Calculate height，balance（）需要
int height(AVL_Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}
//函数用来计算balance factor
int max(int a, int b) {
    return (a > b) ? a : b;
}
// construct a new node
AVL_Node *newNode(int key){
    AVL_Node *node = new AVL_Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}
//Four rotations to balance the tree
// Right rotate
AVL_Node *RR(AVL_Node *y){
    AVL_Node *x = y->left;
    AVL_Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    return x;
}

// Rotate left
AVL_Node *LR(AVL_Node *x) {
    AVL_Node *y = x->right;
    AVL_Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    return y;
}

// Get the balance factor of each node，每次insert、delete后要对bst进行balance操作
int getBalanceFactor(AVL_Node *N) {
    if (N == NULL)
        return 0;
    //balance factor = height of left subtree - height of right subtree
    return height(N->left) -
           height(N->right);
}
//Search a node 构建search等下delete需要
AVL_Node *searchNode(AVL_Node *root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (root->key < key){
        return searchNode(root->right, key);
    }else{
        return searchNode(root->left, key);
    }
}
//balance the tree
AVL_Node *balance(AVL_Node *node) {
    node->height = 1 + max(height(node->left),
                           height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        //left subtree is heavier
        if (getBalanceFactor(node->left) >= 0) {
            //right-right case
            return RR(node);
        } else {
            //left-right case
            node->left = LR(node->left);
            return RR(node);
        }
    }
    if (balanceFactor < -1) {
        //right subtree is heavier
        if (getBalanceFactor(node->right) <= 0) {
            //left-right case
            return LR(node);
        } else {
            //right-right case
            node->right = RR(node->right);
            return LR(node);
        }
    }
    return node;
}
// Insert a node
AVL_Node *insertNode(AVL_Node *node, int key) {
    // If key is already in the tree
    if(searchNode(node,key)!=NULL){
        return node;
    }else{
    if (node == NULL)
        return (newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    // Update the balance factor of each node and
    // balance the tree
    return balance(node);
    }
}
//两个获取最大最小值节点的函数，删除节点需要
//get max value node 
AVL_Node *nodeMax(AVL_Node *node) {
    AVL_Node *max = node;
    while (max->right != NULL)
        max = max->right;
    return max;
}
//get min value node
AVL_Node *nodeMin(AVL_Node *node) {
    AVL_Node *min = node;
    while (min->left != NULL)
        min = min->left;
    return min;
}
// Delete a node
AVL_Node *deleteNode(AVL_Node *root, int k) {  
    // 树如果是空或者不存在该节点
    if (root == NULL||searchNode(root,k)==NULL)
        return root;
    //否则左右递归删除
    if (k < root->key)
         root->left = deleteNode(root->left, k);
      else if (k > root->key)
         root->right = deleteNode(root->right, k);
   else{
    //如果左子树为空
      if (root->left == NULL){
         AVL_Node *temp = root->right;
         free(root);
         return temp;
      }
      else if (root->right == NULL){//如果右子树为空
         AVL_Node *temp = root->left;
         free(root);
         return temp;
      }
      //如果左右子树都不为空 用左子树的最大值替换被删掉的节点（题意要求）
      //也可以用右子树的最小值替换被删掉的节点
      AVL_Node* temp = nodeMax(root->left);
        root->key = temp->key;
        root->left = deleteNode(root->left, temp->key);
   }
   return balance(root);

    }
  
    


// Print the tree in different orders
void preorder(AVL_Node *root) {
    if (root != NULL) {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
    
}

void inorder(AVL_Node *root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
    
}

void postorder(AVL_Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
    }
    
}

int main() {
    AVL_Node *root = NULL;
    string line;
    getline(cin, line, '\n');
    stringstream ss;
    ss.str(line);
    string tempstr;
    while (ss >> tempstr) {
        if (tempstr[0] == 'A') {
            root = insertNode(root, atoi(tempstr.substr(1).c_str()));
        } 
        if (tempstr[0] == 'D') {
            root = deleteNode(root, atoi(tempstr.substr(1).c_str()));
        }
        if(tempstr=="PRE"){
            if(root==NULL){
                cout<<"EMPTY"<<endl;   
            }
            preorder(root);
        }
        if(tempstr=="IN"){
            if(root==NULL){
                cout<<"EMPTY"<<endl;   
            }
            inorder(root);
        }
        if(tempstr=="POST"){
            if(root==NULL){
                cout<<"EMPTY"<<endl;   
            }
            postorder(root);
        }
    }
    return 0;
}

