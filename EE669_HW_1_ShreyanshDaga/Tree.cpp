#include"HW_1.h"
#include"Tree.h"

// For Tree
Tree::Tree()
{
	this->pRoot = NULL;
}

// For Node
Node::Node()
{
	this->strCode = "";
	this->cSym = 0;
	this->pLeft = NULL;
	this->pRight = NULL;
}

Node::Node(unsigned int cSym, float fProb, bool bIsSym)
{
	this->cSym = cSym;
	this->bIsSym = bIsSym;
	this->fProb = fProb;
	this->strCode = "";

	this->pLeft = NULL;
	this->pRight = NULL;
}

void Node::AddLeftChild(Node *pChild)
{
	this->pLeft = pChild;
	this->pLeft->pParent = this;
}

void Node::AddRightChild(Node *pChild)
{
	this->pRight = pChild;
	this->pRight->pParent = this;
}