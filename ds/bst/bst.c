#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int key;
	char *value;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct TreeNode *get_minimum(struct TreeNode *t)
{
	if (!t)
		return NULL;
	while (t->left) {
		t = t->left;
	}
	return t;
}

void free_node(struct TreeNode *t)
{
	free(t->value);
	free(t);
}

struct TreeNode *remove_minimum(struct TreeNode *t)
{
	struct TreeNode *tmp;
	if (!t)
		return NULL;
	if (!t->left) {
		tmp = t->right;
		free_node(t);
		return tmp;
	}
	t->left = remove_minimum(t->left);
	return t;
}

struct TreeNode *remove_node(struct TreeNode *t, int key)
{
	struct TreeNode *tmp;
	if (!t)
		return NULL;
	if (t->key < key) {
		t->right = remove_node(t->right, key);
	} else if (t->key > key) {
		t->left = remove_node(t->left, key);
	} else {
		if (!t->left) {
			tmp = t->right;
			free_node(t);
			return tmp;
		}
		if (!t->right) {
			tmp = t->left;
			free_node(t);
			return tmp;
		}
		tmp = t;
		t = get_minimum(tmp->right);
		t->left = tmp->left;
		t->right = remove_minimum(tmp->right);
	}
	return t;
}

struct TreeNode *put(struct TreeNode *t, int key, char *value)
{
	if (!t) {
		struct TreeNode *t = malloc(sizeof(*t));
		t->key = key;
		t->value = value;
		t->left = NULL;
		t->right = NULL;
		return t;
	}

	if (key < t->key)
		t->left = put(t->left, key, value);
	else if (key > t->key)
		t->right = put(t->right, key, value);
	return t;
}

void free_bst(struct TreeNode *t)
{
	struct TreeNode *left, *right;
	if (!t)
		return;
	left = t->left;
	right = t->right;
	free_node(t);
	free_bst(left);
	free_bst(right);
}

void print_whole_tree(struct TreeNode *t)
{
	if (!t)
		return;
	print_whole_tree(t->left);
	printf("Node key: %d, value: %s\n", t->key, t->value);
	print_whole_tree(t->right);
}

static struct TreeNode *t;
int main(void)
{
	struct TreeNode *tmp;
	char *val;
	int r_n;
	int i;

	for (i = 32; i > 0; i--) {
		val = malloc(32);
		sprintf(val, "Value number %d", i);
		t = put(t, i, val);
	}
	tmp = get_minimum(t);
	printf("minimum key: %d, value: %s\n", tmp->key, tmp->value);

	print_whole_tree(t);

	while (1) {
		scanf("%d", &r_n);
		if (r_n == 99)
			break;
		t = remove_node(t, r_n);
		print_whole_tree(t);
	}

	free_bst(t);
	return 0;
}
