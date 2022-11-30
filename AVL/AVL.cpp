#include<iostream>
#include <sstream>
using namespace std;

// Creates class AVLNode for AVL tree
class AVLNode
{
// To store data
int data;
// To point to left
struct AVLNode *leftChield;
// To point to right
struct AVLNode *rightChield;
// To store height
int height;

// Function to get maximum of two integers
int getMax(int a, int b);
// Function to get minimum node
AVLNode * minValueNode(AVLNode* node);
// Function to get height of the tree
int getHeight(AVLNode *node);
// Function that allocates a new node with the given key and sets NULL to the left and right child
AVLNode* newNode(int value);
// Function to right rotate subtree rooted with temp.
AVLNode *rightRotate(AVLNode *temp);
// Function to left rotate subtree rooted with temp
AVLNode *leftRotate(AVLNode *temp);
// Get Balance factor of node ND
int getBalance(AVLNode *ND);

public:

// Function to insert a node
AVLNode* insertNode(AVLNode* node, int value);
// Function to delete a node
AVLNode* deleteNode(AVLNode* root, int value);
// Function to print pr eorder traversal of the tree.
void preOrder(AVLNode *root);
// Function to print postorder traversal of the tree.
void postOrder(AVLNode *root);
// Recursive function to in order traversal
void inOrder(AVLNode *root);
};// End of class


// Function to get height of the tree
int AVLNode::getHeight(AVLNode *node)
{
// Checks if root is null return 0
if (node == NULL)
return 0;
// Otherwise return height
return node -> height;
}// End of function

// Function to get maximum of two integers
int AVLNode::getMax(int a, int b)
{
return (a > b)? a : b;
}// End of function

// Function that allocates a new node with the given key and sets NULL to the left and right child
AVLNode* AVLNode::newNode(int value)
{
// Allocates memory to create a new node
AVLNode* node = new AVLNode;
node->data = value;
node->leftChield = NULL;
node->rightChield = NULL;
// new node is added at leaf
node->height = 1;
// returns the newly created node
return(node);
}// End of function

// Function to right rotate subtree rooted with temp.
AVLNode* AVLNode::rightRotate(AVLNode *temp)
{
// Creates two temporary pointers for left and right sub tree
AVLNode *newRoot = temp->leftChield;
AVLNode *T2 = newRoot->rightChield;

// Perform rotation
newRoot->rightChield = temp;
temp->leftChield = T2;

// Update heights
temp->height = max(getHeight(temp->leftChield), getHeight(temp->rightChield))+1;
newRoot->height = max(getHeight(newRoot->leftChield), getHeight(newRoot->rightChield))+1;

// Return new root
return newRoot;
}// End of function

// Function to left rotate subtree rooted with temp
AVLNode*AVLNode::leftRotate(AVLNode *temp)
{
// Creates two temporary pointers for left and right sub tree
AVLNode *newRoot = temp->rightChield;
AVLNode *T2 = newRoot->leftChield;

// Perform rotation
newRoot->leftChield = temp;
temp->rightChield = T2;

// Update heights
temp->height = max(getHeight(temp->leftChield), getHeight(temp->rightChield))+1;
newRoot->height = max(getHeight(newRoot->leftChield), getHeight(newRoot->rightChield))+1;

// Return new root
return newRoot;
}// End of function

// Get Balance factor of node NodeBalance
int AVLNode::getBalance(AVLNode *NodeBalance)
{
if (NodeBalance == NULL)
return 0;
return getHeight(NodeBalance->leftChield) - getHeight(NodeBalance->rightChield);
}// End of function

// Function to insert a node
AVLNode* AVLNode::insertNode(AVLNode* node, int value)
{
// Perform the normal BST rotation
if (node == NULL)
return(newNode(value));

// Checks if the parameter value is less than the current node data
if (value < node->data)
// Recursively calls the function for left child
node->leftChield = insertNode(node->leftChield, value);
// Otherwise checks if the parameter value is greater than the current node data
else if (value > node->data)
// Recursively calls the function for right child
node->rightChield = insertNode(node->rightChield, value);
// Otherwise equals
else
return node;

// Update height of this ancestor node
node->height = 1 + max(getHeight(node->leftChield),getHeight(node->rightChield));

// Get the balance factor of this ancestor node to check whether this node became unbalanced
int balance = getBalance(node);

// If this node becomes unbalanced, then there are four cases need to consider
// Left Left Case
if (balance > 1 && value < node->leftChield->data)
return rightRotate(node);

// Right Right Case
if (balance < -1 && value > node->rightChield->data)
return leftRotate(node);

// Left Right Case
if (balance > 1 && value > node->leftChield->data)
{
node->leftChield = leftRotate(node->leftChield);
return rightRotate(node);
}// End of if condition

// Right Left Case
if (balance < -1 && value < node->rightChield->data)
{
node->rightChield = rightRotate(node->rightChield);
return leftRotate(node);
}// End of if condition

// return the (unchanged) node pointer
return node;
}// End of function

/*
* Given a non-empty binary search tree, return the node with minimum key value found in that tree.
* Note that the entire tree does not need to be searched.
*/
AVLNode * AVLNode::minValueNode(AVLNode* node)
{
AVLNode* current = node;

// Loops down to find the leftmost leaf
while (current->leftChield != NULL)
current = current->leftChield;
// Return the current node
return current;
}// End of function

// Recursive function to delete a node with given value from subtree with given root.
// It returns root of the modified subtree.
AVLNode* AVLNode::deleteNode(AVLNode* root, int value)
{
// Checks if root is NULL then empty tree
if (root == NULL)
return root;

// If the value to be deleted is smaller than the root's data, then it lies in left subtree
if ( value < root->data )
root->leftChield = deleteNode(root->leftChield, value);

// If the value to be deleted is greater than the root's data, then it lies in right subtree
else if( value > root->data)
root->rightChield = deleteNode(root->rightChield, value);

// If value is same as root's data, then This is the node to be deleted
else
{
// node with only one child or no child
if( (root->leftChield == NULL) || (root->rightChield == NULL) )
{
AVLNode *temp = root->leftChield ? root->leftChield : root->rightChield;

// No child case
if (temp == NULL)
{
temp = root;
root = NULL;
}// End of if condition
// One child case
else
// Copy the contents of the non-empty child
*root = *temp;
delete(temp);
}// End of if outer condition
else
{
// node with two children: Get the inorder successor (smallest in the right subtree)
AVLNode* temp = minValueNode(root->rightChield);

// Copy the inorder successor's data to this node
root->data = temp->data;

// Delete the inorder successor
root->rightChield = deleteNode(root->rightChield, temp->data);
}// End of inner else
}// End of outer else

// If the tree had only one node then return
if (root == NULL)
return root;

// Update hight of the current node
root->height = 1 + max(getHeight(root->leftChield), getHeight(root->rightChield));

// Get the balance factor of root node (to check unbalance)
int balance = getBalance(root);

// If this node becomes unbalanced, then there are four cases needs to consider

// Left Left Case
if (balance > 1 && getBalance(root->leftChield) >= 0)
return rightRotate(root);

// Left Right Case
if (balance > 1 && getBalance(root->leftChield) < 0)
{
root->leftChield = leftRotate(root->leftChield);
return rightRotate(root);
}// End of if condition

// Right Right Case
if (balance < -1 && getBalance(root->rightChield) <= 0)
return leftRotate(root);

// Right Left Case
if (balance < -1 && getBalance(root->rightChield) > 0)
{
root->rightChield = rightRotate(root->rightChield);
return leftRotate(root);
}// End of if condition

return root;
}// End of function

// Function to print preorder traversal of the tree.
void AVLNode::preOrder(AVLNode *root)
{
// Traverse: Left, Root, Right
// Checks if current node is not null
if(root != NULL)
{
cout<<root->data<<" ";
preOrder(root->leftChield);
preOrder(root->rightChield);
}// End of if condition
}// End of function

// Function to print postorder traversal of the tree.
void AVLNode::postOrder(AVLNode *root)
{
// Traverse: Left, Right, Root
// Checks if current node is not null
if(root != NULL)
{
postOrder(root->leftChield);
postOrder(root->rightChield);
cout<<root->data<<" ";
}// End of if condition
}// End of function


// Recursive function to inorder traversal
void AVLNode::inOrder(AVLNode *root)
{
// Traverse: Left, Root, Right
// Checks if current node is not null
if (root != NULL)
{
// Moves towards left
inOrder(root->leftChield);
// Displays the root node value
cout<<root->data<<" ";
// Moves towards right
inOrder(root->rightChield);
}// End of if condition
}// End of function

// main function definition
int main()
{
// Creates a root node
AVLNode *root = NULL;
// To store the command number
int number;
// To store the command
string command;
// Accepts the command from the user
cout<<"\n Sample input: ";
getline(cin, command);

// Loops till length of the command
for(int x = 0; x < command.length(); x++)
{
// Checks if character at x index position is 'A' or 'a' then insert
if(command.at(x) == 'A' || command.at(x) == 'a')
{
// Convert the next index position character to integer by subtracting '0' from it
number = command.at(++x) - '0';
// Calls the function to insert
root = root->insertNode(root, number);
}// End of if condition

// Otherwise checks if character at x index position is 'D' or 'd' then delete
else if(command.at(x) == 'D' || command.at(x) == 'd')
{
// Convert the next index position character to integer by subtracting '0' from it
number = command.at(++x) - '0';
// Calls the function to delete
root = root->deleteNode(root, number);
}// End of else if condition

// Otherwise checks if character at x index position is 'I' or 'i' then in order traversal
else if(command.at(x) == 'I' || command.at(x) == 'i')
{
cout<<"\nIn order traversal of the constructed AVL tree is \n";
// Checks if root node is NULL then tree is empty
if(root == NULL)
cout<<"\n EMPTY";

root->inOrder(root);
}// End of else if condition

// Otherwise checks if character at x index position is 'P' or 'p'
else if(command.at(x) == 'P' || command.at(x) == 'p')
{
// Then checks if character at next character is 'R' or 'r' then Pre order traversal
if(command.at(x+1) == 'R' || command.at(x) == 'r')
{
cout<<"\nPre order traversal of the constructed AVL tree is \n";
// Checks if root node is NULL then tree is empty
if(root == NULL)
cout<<"\n EMPTY";

root->preOrder(root);
}// End of if condition

// Then checks if character at next character is 'O' or 'o' then Post order traversal
else if(command.at(x+1) == 'O' || command.at(x) == 'o')
{
cout<<"\nPostorder traversal of the constructed AVL tree is \n";
// Checks if root node is NULL then tree is empty
if(root == NULL)
cout<<"\n EMPTY";

root->postOrder(root);
}// End of else if condition
}// End of else if condition
// Otherwise checks if character at x index position is space then do nothing
else if(command.at(x) == ' ')
;// Do nothing statement
}// End of for loop
return 0;
}// End of main function