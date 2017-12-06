typedef struct _bst_node {
	struct _bst_node *left;
	struct _bst_node *right;
	void *data;
} BSTNode;

typedef struct _bst_set {
	int size;
	int height;
	int (* comparator)(const void *, const void *);
	BSTNode *root;
} BSTSet;

BSTSet *create_BST();
int add_to_BST(BSTSet *bst, void *data);
void *get_data_from_BST(BSTSet *bst, void *data);
void *remove_data_from_BST(BSTSet *bst, void *data);
int get_height_of_BST(BSTSet *bst);

void destroy_BST(BSTSet *bst, void (* data_destructor)(void *data));