#ifndef TREE_H_
#define TREE_H_

class Node
{
public:
	unsigned int cSym;
	float fProb;
	bool bIsSym;
	string strCode;

	Node *pParent;
	Node *pLeft;
	Node *pRight;

public:
	Node();
	Node(unsigned int cSymbol, float fProb, bool bIsSym);

	void AddLeftChild(Node *pChild);
	void AddRightChild(Node *pChild);	
};

class Tree
{
	public:
		Node *pRoot;

	public:
		Tree();
};

#endif