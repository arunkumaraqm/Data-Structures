// Insertion, deletion and traversals in a binary search tree

#include <stdio.h>
#include <stdlib.h> // for malloc

struct Node; // Forward declaration
typedef struct Node* NodePointer;

struct Node{

	int data;
	NodePointer left;
	NodePointer right;
};

// struct Tree contains the root of the tree. 
// It's just here to make passing to functions much easier.
typedef struct Tree{

	NodePointer root;
} Tree;

typedef Tree* TreePointer;

// Macro to free the pointer and then assign it to NULL
#define free_and_null(ptr){\
			   \
	free(ptr); \
	ptr = NULL;\
}\

// Called after a TreePointer is delared.
void constructor(TreePointer tree){ // Modifies tree.root

	tree->root = NULL;
}

// Recursive function to free memory
void destroy_children(NodePointer parent){ // Modifies non-root nodes

	if (parent->left){
	
		destroy_children(parent->left);
		free_and_null(parent->left);
	}
	
	if (parent->right){
	
		destroy_children(parent->right);
		free_and_null(parent->right);
	}
}

// Called when a TreePointer is no longer needed
void destructor(TreePointer tree){ // Modifies tree.root

	if (tree->root){
	
		destroy_children(tree->root);
		free_and_null(tree->root);
	}
}

// Returns newly created Node
NodePointer create(int data){

	NodePointer new_node = malloc(sizeof *new_node);
	new_node->left = new_node->right = NULL;
	new_node->data = data; 
}

// Inserting an element into the tree
void recursive_insert(NodePointer parent, int element){ // Modifies non-root nodes

	if (element < parent->data){
	
		if (parent->left){
		
			recursive_insert(parent->left, element);
		}
		else{
		
			parent->left = create(element);
		}
	}
	
	else{
	
		if (parent->right){
		
			recursive_insert(parent->right, element);
		}
		else{
		
			parent->right = create(element);
		}
	}
}

// Inserting an element into a tree
void insert_into_tree(TreePointer tree, int element){ // Modifies tree.root in one of the cases

	if (tree->root){
	
		recursive_insert(tree->root, element);
	}
	else{
	
		tree->root = create(element);
	}
}
// Tabbed display
void recursive_display(NodePointer parent, int noof_tabs){

	for (int i = 0; i < noof_tabs; ++i){
	
		printf("\t");
	}
	
	if (parent){
	
		printf("%d\n", parent->data);
		recursive_display(parent->left, noof_tabs + 1);
		recursive_display(parent->right, noof_tabs + 1);
	}
	
	else{
	
		printf("NULL\n");
	}
}

void display_tree(Tree tree){ //Note: Tree is passed by data

	recursive_display(tree.root, 0);
}

void recursive_preorder(NodePointer parent){

	if (parent){
		
		printf("%d ", parent->data);
		recursive_preorder(parent->left);
		recursive_preorder(parent->right);
	}
}

void recursive_inorder(NodePointer parent){

	if (parent){
		
		recursive_inorder(parent->left);
		printf("%d ", parent->data);
		recursive_inorder(parent->right);
	}
}

void recursive_postorder(NodePointer parent){

	if (parent){
		
		recursive_postorder(parent->left);
		recursive_postorder(parent->right);
		printf("%d ", parent->data);
	}
}

void preorder_traversal(Tree tree){

	recursive_preorder(tree.root);
	printf("\n");
}

void inorder_traversal(Tree tree){

	recursive_inorder(tree.root);
	printf("\n");
}

void postorder_traversal(Tree tree){

	recursive_postorder(tree.root);
	printf("\n");
}

// Returns parent of minimum element
NodePointer get_parent_of_minimum(NodePointer parent){

	if (parent->left->left){
		return get_parent_of_minimum(parent->left);
	}
	else{
		return parent;
	}
}

NodePointer recursive_delete(NodePointer root, int item, int* not_found_flag){ // Modifies non-root nodes and returns modified root
	
	// Empty subtree
	if (root == NULL){

		*not_found_flag = 1;
		return NULL;
	}

	if (item < root->data)
		root->left = recursive_delete(root->left, item, not_found_flag);

	else if (item > root->data)
		root->right = recursive_delete(root->right, item, not_found_flag);

	else{

		if (root->right == NULL){
			
			// Node to be deleted is a leaf
			if (root->left == NULL){
			
				free(root);
				root = NULL;
				return NULL;
			}
			
			// Node to be deleted has only left child
			else{

				NodePointer temp = root->left;
				free(root);
				return temp;
			}
		}
		
		// Node to be deleted has only right child
		else if (root->left == NULL){
	
			{
				NodePointer temp = root->right;
				free(root);
				return temp;
			}
		}

		// Node to be deleted has both children
		else
		{
			// The inorder successor of root is the leftmost node on the right subtree
			if(root->right->left != NULL){
				NodePointer pomin = get_parent_of_minimum(root->right);
				NodePointer min = pomin->left;
				root->data = min->data;
				pomin->left = min->right;
				free(min);
				return root;
			}

			// The right subtree has no left node, so root->right is the inorder successor
			else{

				root->data = root->right->data;
				NodePointer temp = root->right;
				root->right = root->right->right;
				free(temp);
				return root;
			}
		}
	}
}

int delete_from_tree(TreePointer tree, int item){

	int not_found_flag = 0;
	tree->root = recursive_delete(tree->root, item, &not_found_flag);

	return !not_found_flag;
}

// The menu
void main(){

	Tree tree;
	constructor(&tree);

	int choice;
	do{
	
		scanf("%d", &choice);
		
	switch(choice){
	
		case 1: {int element;
			    scanf("%d", &element); 
			    insert_into_tree(&tree, element); 
			    break;} // Shows a compilation error without braces - not entirely sure why
			    
		case 2: {int item;
			    scanf("%d", &item); 
			    if (delete_from_tree(&tree, item) == 0){
			    	
			    	printf("Not Found.\n");
			    } 
			    break;}
		
		case 3: preorder_traversal(tree); break;
		
		case 4: inorder_traversal(tree); break;
		
		case 5: postorder_traversal(tree); break;
		
		case 6: display_tree(tree); break;

		default: choice = 0;
	}
	
	} while (choice);
	
	destructor(&tree);
}
/*
#
2
3
4
5
6
7

#
1 20
3
4
5
6
2 30
2 20
2 20
1 30
6
7

#
1 20
1 15
1 25
6
3
4
5
2 20
6
7

---------------
#
1 18
1 15
1 10
1 9
1 16
1 22
1 25
1 55
1 76
1 35
6
3
4
5
7


#
1 18
1 15
1 10
1 9
1 16
1 22
1 25
1 55
1 76
1 35
2 18
6 
7

#
1 18
1 15
1 10
1 9
1 16
1 22
1 25
1 55
1 76
1 35
2 15
6
7

#
1 18
1 15
1 10
1 9
1 16
1 22
1 25
1 55
1 76
1 35
2 10
6
7

#
1 18
1 15
1 10
1 9
1 16
1 22
1 25
1 55
1 76
1 35
2 9
6
7

#
1 18
1 15
1 10
1 9
1 16
1 22
1 25
1 55
1 76
1 35
2 16
6
7

#
1 18
1 15
1 10
1 9
1 16
1 22
1 25
1 55
1 76
1 35
2 22
6
7

#
1 18
1 15
1 10
1 9
1 16
1 22
1 25
1 55
1 76
1 35
2 25
6
7

#
1 18
1 15
1 10
1 9
1 16
1 22
1 25
1 55
1 76
1 35
2 55
6
7

#
1 18
1 15
1 10
1 9
1 16
1 22
1 25
1 55
1 76
1 35
2 76
6
7

#
1 18
1 15
1 10
1 9
1 16
1 22
1 25
1 55
1 76
1 35
2 35
6
7
--------

# 
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
6
3
4
5
7

#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 50
6
7


#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 25
6
7

#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 70
6
7

#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 12
6
7

#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 37
6
7

#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 60
6
7

#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 85
6
7

#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 11
6
7

#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 14
6
7

#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 33
6
7


#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 81
6
7

#
1 50
1 25 1 70
1 12 1 37 1 60 1 85
1 11 1 14 1 33 1 40 1 59 1 61 1 80 1 100
1 10 1 13 1 34 1 41 1 58 1 62 1 81 1 99
2 26
7
-----------------------
#
1 10 1 20 1 30 1 5
2 10 6
2 5 6
2 30 6
2 20 6
7
*/
