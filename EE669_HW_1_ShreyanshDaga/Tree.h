
class Node
{
private:
	int iValue;
	float fProb;

	Node *pLeft;
	Node *pRight;

public:
	Node();
	Node(int iVal);

	void AddLeftChild(Node *pChild);
	void AddRightChild(Node *pChild);
};

class Tree
{
	private:
		Node *pRoot;

	public:
		Tree();
		void InsertVal(int iVal);
		Node* SearchVal(int iVal);
};
