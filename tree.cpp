#include "tree.h"

/** Inserts new node with 'data' value if not already present
 * if data is a new value, it is added as a leaf node
 * the tree is rotated back upward toward the root until the
 * treap value held by the new node respects the min heap
 * property of the treap
 * A std::vector of pairs is used as a stack to keep a memory of the
 * traversal order and the direction of each child node
 *
 * @param data, string value to be inserted
 */
void Tree::insert(std::string data)
{
	if (root == nullptr)
	{
		root = std::make_unique<Node>(data);
		iterVector.push_back(root.get()); // sets iterator to root
		return;
	}

	// stack contains both a node and the direction from parent bool isLeft, 
	// true if in left subtree, false if in right
	bool isLeft = true;
	std::vector<pair<Node*, bool>> traversalStack;
	Node* node = root.get();
	
	traversalStack.push_back({node, true}); // direction is adjusted as tree traversed
	
	while (true)
	{
		if (data.compare(node->data) < 0)
		{
			if (node->left != nullptr)
			{
				node = node->left.get();
				traversalStack.back().second = isLeft;
				traversalStack.push_back({node, isLeft});
			}
			else
			{
				node->left = std::make_unique<Node>(data);
				traversalStack.back().second = isLeft;
				break;
			}
		}
		else if (data.compare(node->data) > 0)
		{
			if (node->right != nullptr)
			{
				node = node->right.get();
				traversalStack.back().second = !isLeft;
				traversalStack.push_back({node, !isLeft});
			}
			else
			{
				node->right = std::make_unique<Node>(data);
				traversalStack.back().second = !isLeft;
				break;
			}
		}
		else // element is already in the tree
		{
			node->count++;
			return; // just returns, no change in tree structure so no rotation
		}
	}
	
	pair<Node*, bool> grandp;
	pair<Node*, bool> parent;
	// rotate nodes if the treap value is out of place, continuing back up the tree
	while (traversalStack.empty() == false)
	{
		parent = traversalStack.back();
		traversalStack.pop_back();
		if (traversalStack.empty())
			break;
		else
		{
			grandp = traversalStack.back();
			traversalStack.pop_back();
		}
		
		if (grandp.second == isLeft)
		{
			if (parent.second == isLeft)
			{
				if (parent.first->left->treap <= parent.first->treap )
					rotateRight(grandp.first->left);
			}
			else
			{
				if (parent.first->right->treap < parent.first->treap )
					rotateLeft(grandp.first->left);
			}
		}
		else
		{
			if (parent.second == isLeft)
			{
				if (parent.first->left->treap <= parent.first->treap )
					rotateRight(grandp.first->right);
			}
			else
			{
				if (parent.first->right->treap < parent.first->treap )
					rotateLeft(grandp.first->right);
			}
		}
	}
	
	// at the root
	if (root->left != nullptr)
	{
		if (root->left->treap >= root->treap)
			rotateRight(root);
	}
	if (root->right != nullptr)
	{
		if (root->right->treap < root->treap)
			rotateLeft(root);
	}
}

/** Returns true if data found in tree, else false
 * Traversal compares each node from the root
 * moves left if less, right if greater
 *
 * @param data, a string to search for in tree
 * @return true if found, false if not
 */
bool Tree::search(std::string data) const
{
	if (root == nullptr)
	{
		return false;
	}
	
	Node* node = root.get();
	while (true)
	{
		if (node->data.compare(data) == 0)
			return true;
		else if (node->data.compare(data) > 0)
		{
			if (node->left != nullptr)
				node = node->left.get();
			else
				return false;
		}
		else
		{
			if (node->right != nullptr)
				node = node->right.get();
			else
				return false;
		}
	}
}

/** Prints contents of Tree, smallest element to largest
 * Traversal uses std::stack to implement DFS post order traversal
 */
void Tree::print() const
{
	if (root == nullptr)
	{
		cout << "Tree empty" << endl;
		return;
	}
	
	std::stack<Node*> parentStack;
	
	parentStack.push(root.get());
	Node* node = root.get();
	while (parentStack.empty() == false)
	{
		// go all the way left, adding each node on the way
		while (node->left != nullptr)
		{
			node = node->left.get();
			parentStack.push(node);
		}
		// unwind the stack, printing each node, until there is
		// a right child to push onto the stack
		while (parentStack.empty() == false)
		{
			node = parentStack.top();
			cout << ":" << node->data << endl;
			parentStack.pop();
			if (node->right != nullptr)
			{
				parentStack.push(node->right.get());
				node = parentStack.top();
				break;
			}
		}
	}
}

/** Returns data currently being pointed at by the Tree's iterator
 *
 * @return iterator's pointed to data
 */
std::string Tree::getIterData() const
{
	if (iterVector.empty())
		return "INVALID ITERATOR empty";
	else if (iterVector.back() == nullptr)
		return "INVALID ITERATOR nullptr";
	else
		return iterVector.back()->data;
}
/** Moves Tree's iterator to the next node as defined by DFS traversal
 */
void Tree::incrIter()
{
	if (iterVector.empty())
		return;
	Node* node = iterVector.back();
	iterVector.pop_back();
	if (node->right != nullptr)
		iterVector.push_back(node->right.get());
	if (node->left != nullptr)
		iterVector.push_back(node->left.get());
}

/** Moves unique_ptr to node's children to complete rotation
 *
 * @param node, the node to be rotated, and therefore modified
 */
void Tree::rotateLeft(std::unique_ptr<Node>& node)
{
	std::unique_ptr<Node> temp = std::move(node->right);
	
	node->right = std::move(temp->left);
	temp->left = std::move(node);
	
	node = std::move(temp);
}

/** Moves unique_ptr to node's children to complete rotation
 *
 * @param node, the node to be rotated, and therefore modified
 */
void Tree::rotateRight(std::unique_ptr<Node>& node)
{
	std::unique_ptr<Node> temp = std::move(node->left);
	
	node->left = std::move(temp->right);
	temp->right = std::move(node);
	
	node = std::move(temp);
}


























