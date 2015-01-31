#include"HW_1.h"
#include"Tree.h"

// For Tree
Tree::Tree()
{

}

void Tree::InsertVal(int iVal)
{

}

Node* Tree::SearchVal(int iVal)
{
	Node *pNode = NULL;

	return pNode;
}

// For Node
Node::Node()
{
	this->iValue = 0;
	this->pLeft = NULL;
	this->pRight = NULL;
}

Node::Node(int iVal)
{
	this->iValue = iVal;
	this->pLeft = NULL;
	this->pRight = NULL;
}

void Node::AddLeftChild(Node *pChild)
{
	this->pLeft = pChild;
}

void Node::AddRightChild(Node *pChild)
{
	this->pRight = pChild;
}