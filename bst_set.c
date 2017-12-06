#include <stdlib.h>

#include "bst_set.h"

#define MAX_OF(a, b) (((a) > (b)) ? (a) : (b))



static BSTNode *_create_BST_node(void *data);
static BSTNode *_add_to_bst(BSTNode *node,
	int (* comparator)(const void *, const void *), void *data);
static void *_get_data(BSTNode *node,
	int (* comparator)(const void *, const void *), void *data);
static BSTNode *_remove_data(BSTNode *node,
	int (* comparator)(const void *, const void *), void *data, void **dataOut);
static BSTNode *_remove_greatest_data(BSTNode *node, void **greatest_data);
static int _get_height(BSTNode *node);


BSTSet *create_BST() {
	BSTSet *temp = malloc(sizeof(BSTSet));
	if (temp == NULL) {
		return NULL;
	}

	temp->size = 0;
	temp->height = -1;
	temp->root = NULL;

	return temp;
}

static BSTNode *_create_BST_node(void *data) {
	// Data should not be NULL.
	// The other add methods should take care of this.
	BSTNode *node = malloc(sizeof(BSTNode));

	if (node == NULL) {
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;
	node->data = data;

	return node;
}

int add_to_BST(BSTSet *bst, void *data) {
	if (bst == NULL || data == NULL) {
		return -1;
	}

	bst->root = _add_to_bst(bst->root, bst->comparator, data);
	return ++bst->size;
}

static BSTNode *_add_to_bst(BSTNode *node,
	int (* comparator)(const void *, const void *), void *data) {

	BSTNode *temp;

	if (node == NULL) {
		// End of recursion reached, create new node and send it
		// back up.
		temp = _create_BST_node(data);
		if (temp == NULL) {
			return NULL;
		}
		temp->data = data;
		return temp;
	}

	// Otherwise, send the data to a descendant.
	// Note that below, suppose _add_to_bst fails. The failure will
	// not carry up any more levels, since "node" is returned.
	if (comparator(data, node->data) < 0) {
		node->left = _add_to_bst(node->left, comparator, data);
	} else if (comparator(data, node->data) > 0) {
		node->right = _add_to_bst(node->right, comparator, data);
	} // else { the data is equal, so do nothing. }

	return node;
}

void *get_data_from_BST(BSTSet *bst, void *data) {
	if (bst == NULL || data == NULL) {
		return NULL;
	}

	return _get_data(bst->root, bst->comparator, data);
}

static void *_get_data(BSTNode *node,
	int (* comparator)(const void *, const void *), void *data) {
	if (node == NULL) {
		return NULL;
	}

	if (comparator(data, node->data) < 0) {
		return _get_data(node->left, comparator, data);
	} else if (comparator(data, node->data) > 0) {
		return _get_data(node->right, comparator, data);
	} // else { the data was found}

	return node->data;
}

void *remove_data_from_BST(BSTSet *bst, void *data) {
	if (bst == NULL || data == NULL) {
		return NULL;
	}

	void *dataOut;
	bst->root = _remove_data(bst->root, bst->comparator, data, &dataOut);
	return dataOut;
}

static BSTNode *_remove_data(BSTNode *node,
	int (* comparator)(const void *, const void *), void *data, void **dataOut) {

	if (node == NULL) {
		// If the data wasn't found
		*dataOut = NULL;
		return NULL; // "node" is NULL
	}

	if (comparator(data, node->data) < 0) {
		node->left = _remove_data(node->left, comparator, data, dataOut);
	} else if (comparator(data, node->data) > 0) {
		node->right = _remove_data(node->right, comparator, data, dataOut);
	} else {
		// If the data is equal, remove the node.
		*dataOut = node->data;
		BSTNode *temp;
		if (node->left == NULL && node->right == NULL) {
			// Since both children are NULL, simply destroy this node.
			free(node);
			return NULL;
		} else if (node->left == NULL) {
			temp = node->right;
			free(node);
			return temp;
		} else if (node->right == NULL) {
			temp = node->left;
			free(node);
			return temp;
		} else {
			// If both children aren't NULL, find the greatest predecessor
			// and replace the current node's data with its data.
			void *greatest_data;
			node->left = _remove_greatest_data(node->left, &greatest_data);
			node->data = greatest_data;
			return node;
		}
	}
}


static BSTNode *_remove_greatest_data(BSTNode *node, void **greatest_data) {

	BSTNode *temp;

	if (node->right == NULL) {
		// The greatest has been found.
		temp = node->left;
		*greatest_data = node->data;
		free(node);
		return temp;
	}

	node->right = _remove_greatest_data(node->right, greatest_data);
	return node;
}

int get_height_of_BST(BSTSet *bst) {
	if (bst == NULL) {
		return -2;
	}
	return _get_height(bst->root);
}

static int _get_height(BSTNode *node) {
	if (node == NULL) {
		return -1;
	}
	return MAX_OF(_get_height(node->left), _get_height(node->right))
		+ 1;
}