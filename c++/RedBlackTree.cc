#include <iostream>

/*

A node is either red or black.

- The root is black. (This rule is sometimes omitted. Since the root
can always be changed from red to black, but not necessarily
vice-versa, this rule has little effect on analysis.)  

- All leaves (NIL) are black. (All leaves are same color as the root.)

- Every red node must have two black child nodes.  

- Every path from a given node to any of its descendant leaves
contains the same number of black nodes.

*/

class Node {

public:

  enum NodeColor_t { Red, Black };

  Node(int value, Node *myFather) : m_value(value), 
		    m_color(Red),
		    m_parent(myFather), 
		    m_left_child(0), 
		    m_right_child(0) {}
  

  Node *InsertNormaly(int value);
  void SetColor(NodeColor_t myColor) { m_color = myColor; };
  void Print(void);
  void RotateLeft(void);
  void RotateRight(void);
  void PrintColor(void);
  void PrintNode(void);

  Node *GrandParent(void);
  Node *Uncle(void);
  void InsertCase1(void);
  void InsertCase2(void);
  void InsertCase3(void);
  void InsertCase4(void);
  void InsertCase5(void);

private:

  int          m_value;
  NodeColor_t  m_color;
  Node        *m_parent;
  Node        *m_left_child;
  Node        *m_right_child;

};

void Node::PrintNode(void)
{
  std::cout << "Node:" << m_value << "\n";
  PrintColor();
}

void Node::PrintColor(void)
{
  if (m_color == Red)
  {
    std::cout << "Red";
  }
  else
  {
    std::cout << "Black";
  }
}

void Node::Print(void)
{
  std::cout << "Value:" << m_value << "(Node:";
  PrintColor();
  if (m_left_child)
  {
    std::cout << "\nLeft:" <<  "(";
    m_left_child->Print();
    std::cout << ")";
  }

  if (m_right_child)
  {
    std::cout << "\nRight:" << "(";
    m_right_child->Print();
    std::cout << ")";
  }
  std::cout << ")";
  
}

Node *Node::InsertNormaly(int value)
{  

  if (value < m_value)
  {
    if (m_right_child)
      return(m_right_child->InsertNormaly(value));
    else
    {
      m_right_child = new Node(value, this);
      return m_right_child;
    }
  }
  else if (m_left_child)
  {
    return(m_left_child->InsertNormaly(value));
  }
  else
  {
    m_left_child = new Node(value, this);
    return m_left_child;
  }

}
 
Node *Node::GrandParent(void)
{
  if (m_parent != 0)
  {
    return m_parent->m_parent;
  }
  else
    return 0;
}

Node *Node::Uncle(void)
{

  Node *grandPa = GrandParent();

  if (grandPa == 0)
  {
    return 0;
  }

  if (m_parent == grandPa->m_left_child)
    return grandPa->m_right_child;
  else
    return grandPa->m_left_child;
}

/*

  Case 1: The current node N is at the root of the tree. 
  In this case, it is repainted black to satisfy property 2 (the root
  is black).  Since this adds one black node to every path at once,
  property 5 (all paths from any given node to its leaf nodes contain
  the same number of black nodes) is not violated.

*/

void Node::InsertCase1(void)
{  
  std::cout << "InsertCases..:" << m_value << "\n";
  if (m_parent == 0)
  { 
    m_color = Black;
    std::cout << "Case 1\n";
    return;
  }
  else
  {
    InsertCase2();
  }  
}

/*

  Case 2: The current node's parent P is black, so property 4 (both
  children of every red node are black) is not invalidated. In this
  case, the tree is still valid. Property 5 (all paths from any given
  node to its leaf nodes contain the same number of black nodes) is not
  threatened, because the current node N has two black leaf children,
  but because N is red, the paths through each of its children have the
  same number of black nodes as the path through the leaf it replaced,
  which was black, and so this property remains satisfied.  

*/

void Node::InsertCase2(void)
{

  if (m_parent != NULL && m_parent->m_color == Black)
  {
    std::cout << "Case 2: "; PrintNode(); m_parent->PrintNode();
    std::cout << "\n";
    return;
  }
  else
    InsertCase3();

}

/*

  Case 3: If both the parent P and the uncle U are red, then both of
  them can be repainted black and the grandparent G becomes red (to
  maintain property 5 (all paths from any given node to its leaf nodes
  contain the same number of black nodes)). Now, the current red node N
  has a black parent. Since any path through the parent or uncle must
  pass through the grandparent, the number of black nodes on these paths
  has not changed. However, the grandparent G may now violate properties
  2 (The root is black) or 4 (Both children of every red node are black)
  (property 4 possibly being violated since G may have a red parent). To
  fix this, the entire procedure is recursively performed on G from case
  1. Note that this is a tail-recursive call, so it could be rewritten
  as a loop; since this is the only loop, and any rotations occur after
  this loop, this proves that a constant number of rotations occur.

*/

void Node::InsertCase3(void)
{

  Node *myUncle = Uncle();

  if (myUncle != NULL && myUncle->m_color == Red)
  {
    std::cout << "Case 3\n";
    m_parent->m_color = Black;
    myUncle->m_color = Black;
    Node *myGrandPa = GrandParent();     
    myGrandPa->m_color = Red;
    myGrandPa->InsertCase1();
  }
  else
  {
    InsertCase4();
  }
  
}

void Node::RotateLeft(void)
{
  Node *gp = GrandParent();
  Node *saved_p = gp->m_left_child;
  Node *saved_left_n = m_left_child;;
  gp->m_left_child = this;
  m_left_child = saved_p;
  if (saved_p) { saved_p->m_right_child = saved_left_n;  }
 
}

/*
 * rotate_right can be the below to take advantage of already having *g =  grandparent(n) 
 *
 * struct node *saved_p=g->right, *saved_right_n=n->right;
 * g->right=n; 
 * n->right=saved_p;
 * saved_p->left=saved_right_n;
 * 
 */
 
void Node::RotateRight(void)
{

  std::cout << "RotateRight ================================================================\n";
  Node *gp = GrandParent();
  gp->PrintNode();
  Node *saved_p = gp->m_right_child;
  Node *saved_right_n = m_right_child;;
  gp->m_right_child = this;
  m_right_child = saved_p;
  saved_p->m_left_child = saved_right_n;

}  

/*

Note: In the remaining cases, it is assumed that the parent node P is
the left child of its parent. If it is the right child, left and right
should be reversed throughout cases 4 and 5. The code samples take
care of this.

Case 4: The parent P is red but the uncle U is black; also, the
current node N is the right child of P, and P in turn is the left
child of its parent G. In this case, a left rotation on P that
switches the roles of the current node N and its parent P can be
performed; then, the former parent node P is dealt with using case 5
(relabeling N and P) because property 4 (both children of every red
node are black) is still violated. The rotation causes some paths
(those in the sub-tree labelled "1") to pass through the node N where
they did not before. It also causes some paths (those in the sub-tree
labelled "3") not to pass through the node P where they did
before. However, both of these nodes are red, so property 5 (all paths
from any given node to its leaf nodes contain the same number of black
nodes) is not violated by the rotation. After this case has been
completed, property 4 (both children of every red node are black) is
still violated, but now we can resolve this by continuing to case 5.

*/

void Node::InsertCase4(void)
{

  Node *myGrandPa = GrandParent();
  Node *node;

  if (myGrandPa != NULL)
  {
    if ((this == m_parent->m_right_child) && 
	 (m_parent == myGrandPa->m_left_child))
      {
	std::cout << "Case 4 - Rotate Left\n";
	RotateLeft();
	m_left_child->InsertCase5();
	return;
      }
    else if ((this == m_parent->m_left_child) && (m_parent == myGrandPa->m_left_child))
      {
	std::cout << "Case 4 - Rotate Right\n";
	RotateRight();
        m_right_child->InsertCase5();
	return;
      }
  }

  InsertCase5();
  
}

/*

Case 5: The parent P is red but the uncle U is black, the current node
N is the left child of P, and P is the left child of its parent G. In
this case, a right rotation on G is performed; the result is a tree
where the former parent P is now the parent of both the current node N
and the former grandparent G. G is known to be black, since its former
child P could not have been red otherwise (without violating property
4). Then, the colors of P and G are switched, and the resulting tree
satisfies property 4 (both children of every red node are
black). Property 5 (all paths from any given node to its leaf nodes
contain the same number of black nodes) also remains satisfied, since
all paths that went through any of these three nodes went through G
before, and now they all go through P. In each case, this is the only
black node of the three.

 */

void Node::InsertCase5(void)
{

  Node *grandPa = GrandParent();


  std::cout << "Case 5\n";
  m_parent->m_color = Black;
  m_color = Red;

  if (this == m_parent->m_left_child)
  {
      RotateRight();
  }    
else
  {
     RotateLeft();
  }

}

class RedBlackTree
{
  
private:

  Node *m_root;

private:

  Node *InsertNormaly(int value);
  
public:

  RedBlackTree() : m_root(0) {};
  Node *Insert(int value);
  bool Delete(int value);
  bool LookUp(int value);
  void Print(void);

};
 
Node *RedBlackTree::InsertNormaly(int value)
{
  if (m_root == 0)
  {
    m_root = new Node(value, 0);
    m_root->SetColor(Node::Black);
    return m_root;
  }
  else
  {
    return(m_root->InsertNormaly(value));
  }
}

Node *RedBlackTree::Insert(int value)
{
  Node *myNode = InsertNormaly(value);
  std::cout << "Insert Normally:"; myNode->PrintNode(); std::cout <<"\n";
  myNode->InsertCase1();
  return myNode;
}



void RedBlackTree::Print(void)
{
  if (m_root == 0)
  {
    std::cout << "The tree is empty\n";
  }
  else
  {
    m_root->Print();
  }
}

int main()
{

  RedBlackTree myTree;

  for(int i=0;i<3;i++)
  {
    std::cout << "############ Insert: " << i << "\n";
    myTree.Insert(i); 
  }
  std::cout << "############## Print the whole tree\n";
  myTree.Print();

}
