/*Binary Search Tree*/
#include <iostream>
using namespace std;

//struct which defines any leaf in the tree

struct node {
	int info;
	int key;
	node *left;
	node *right;
	node *parent;
};

//class tree which takes care of operations like searching, insertions and deletion of tree

class tree {
	
	//Private recursive functions
	
	void destroy(node *leaf);
	void insert(int key, node *leaf, int n);
	node *search(int key, node *leaf);
	void display(node *leaf);
	node *minimum(node *leaf);
	void transplant(node *leaf1, node *leaf2);
	void delete_node(node *leaf);
	
	node *root;
		
	public :
		tree();
		~tree();
		
		//Easy to use, simplified functions. Public access.
		
		void insert(int key, int n);    
		node *search(int key);
		void destroy();
		void display();
		void minimum();
		void delete_node(int key);
};

void tree :: delete_node(node *leaf) {
	node *y = NULL;
	if (leaf->left == NULL)
	transplant(leaf, leaf->right);
	else if (leaf->right == NULL)
	transplant(leaf, leaf->left);
	else {
		y = minimum(leaf->right);
		if (y->parent != leaf) {
			transplant (leaf, y);
			y->right = leaf->right;
			y->right->parent = y;
		}
		transplant(leaf, y);
		y->left = leaf->left;
		y->left->parent = y;
	}
}

void tree :: delete_node(int key) {
	node *temp = search(key, root);
	delete_node(temp);
}

void tree :: transplant(node *leaf1, node *leaf2) {
	if (leaf1->parent == NULL)
	root = leaf2;
	else if (leaf1 == leaf1->parent->left)
	leaf1->parent->left = leaf2;
	else
	leaf1->parent->right = leaf2;
	
	if (leaf2 != NULL)
	leaf2->parent = leaf1->parent; 
}

//Constructor to initialise root to NULL
tree :: tree() {
	root = NULL;
}

//Destructor would set off recursive funtion destroy()
tree :: ~tree() {
	destroy();
}

/*This function recursively goes down to the last child and
destroys the left leaf followed by the right leaf*/
void tree :: destroy(node *leaf) {
	if (leaf != NULL) {
		destroy(leaf->left);
		destroy(leaf->right);
		delete leaf;
	}
}

/*Functions takes a key and a node (root) as argument
and determines the correct position to insert a leaf
and initializes the leaf with NULL values*/

void tree :: insert(int key, node *leaf, int n) {
	if (key < leaf->key) {
		if (leaf->left != NULL) {
			insert(key, leaf->left, n);
		}
		else {
			leaf->left = new node;
			leaf->left->key = key;
			leaf->left->info = n;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
			leaf->left->parent = leaf;
		}
	}
	else if (key > leaf->key) {
		if (leaf->right != NULL) {
			insert (key, leaf->right, n);
		}
		else {
			leaf->right = new node;
			leaf->right->key = key;
			leaf->right->info = n;
			leaf->right->left = NULL;
			leaf->right->right = NULL;
			leaf->right->parent = leaf;
		}
	}
}

/*Recursive function that determines the position of a 
certain node given its key and the root node*/

node *tree :: search(int key, node *leaf) {
	if (leaf != NULL) {
		if (key == leaf->key) {
			cout << leaf->key << '\t' << leaf->info << endl;
			return leaf;
		}
		
		if (key < leaf->key) 
		return search(key, leaf->left);
		else 
		return search(key, leaf->right);
	}
	else {
		cout << "NULL" << endl;
		return NULL;
	}
}

node* tree :: minimum(node *leaf) {
	node *temp = leaf;
	if (temp != NULL) {
		while (temp->left != NULL)
			temp = temp->left;
		cout << temp->key << '\t' << temp->info << endl;
		return temp;
	}
	else {
		cout << "NULL\n";
		return NULL;
	}
}

void tree :: display(node *leaf) {
	if (leaf != NULL) {
		display(leaf->left);
		cout << leaf->key << '\t' << leaf->info << endl;
		display(leaf->right);
	}
}

/*Public function that takes only an integer argument and calls 
private insert() function to implement insertion*/

void tree :: insert(int key, int n) {
	if (root != NULL) {
		insert(key, root, n);
	}
	else {
		root = new node;
		root->key = key;
		root->info = n;
		root->left = NULL;
		root->right = NULL;
	}
}

/*Public function that calls the private destroy() function to
implement deletion*/

void tree :: destroy() {
	destroy(root);
}

node *tree :: search (int key) {
	return search(key, root);
}

void tree :: display() {
	display(root);
}

void tree :: minimum() {
	minimum(root);
}

int main() {
	tree btree;
	btree.insert(1, 0);
	btree.insert(4, 3);
	btree.insert(5, 2);
	btree.insert(17, 3);
	btree.insert(21, 7);
	cout << "Binary Tree:\n";
	btree.display();
	cout << endl << "Searcing for node with key: 5\n";
	btree.search(5);
	cout << endl << "Minimum key in the tree\n";
	btree.minimum();
	cout << endl << "Deleting node with key: 17\n";
	btree.delete_node(17);
	cout << endl << "Tree after deletion:\n";
	btree.display();
			
	return 0;
}
