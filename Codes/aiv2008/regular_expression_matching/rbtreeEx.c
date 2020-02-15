#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<time.h>
//#include "rbtree.h"
#define NIL -50000000

typedef struct
{
//	unsigned int data;
	char *data;
	struct TreeNode* parent;
	struct TreeNode* left;
	struct TreeNode* right;
	char color;
	int count;
} TreeNode;

void print_node(TreeNode* node)
{
    if(NIL != node->data)
    {
        printf("\n  ");
        TreeNode* p = node->parent;
        TreeNode* l = node->left;
        TreeNode* r = node->right;
        if(p)
        {
            printf("%d(",p->data);
            printf("%c)\n",p->color);
        }
        else
            printf("nil\n");
        printf("   |\n");
        printf(" ");
        printf("%d(",node->data);
        printf("%c)\n",node->color);
        printf(" /   \\\n");
        if(NIL != l->data)
        {
            printf("%d(",l->data);
            printf("%c)",l->color);
        }
        else
            printf("nil");
        printf("   ");
        if(NIL != r->data)
        {
            printf("%d(",r->data);
            printf("%c)",r->color);
        }
        else
            printf("nil");
        printf("\n");
    }

}

TreeNode* node_init(char *data)
{
    TreeNode* node = (TreeNode*)calloc(1,sizeof(TreeNode));
    node->data = data;
    node->count = 1;
    node->color = 'R';
    return node;
}

TreeNode* nil_node_init()
{
    TreeNode* root = (TreeNode*)calloc(1,sizeof(TreeNode));
    root->data = NIL;
    root->color = 'B';
    return root;
}

TreeNode* tree_search(TreeNode* root, char *data)
{
	if(!root)return NULL;
    TreeNode* p = root;
    while( NULL != p->data)
    {
        if(*data == *p->data)
            break;
        else if(*p->data < *data)
            p = p->right;
        else
            p = p->left;
    }
    return p;
}

TreeNode* rotate_left(TreeNode* root)
{
    TreeNode* old_root = root->parent;
    TreeNode* parent = old_root->parent;
    TreeNode* left = root->left;
    TreeNode* right = root->right;
    if( NULL != left->data || NULL != right->data)
    {
        root->color = 'B';
        old_root->color = 'R';
    }
    node_rela_save(parent, root, parent?(*root->data < *parent->data?'l':'r') : ' ');
    node_rela_save(root, old_root, 'l');
    node_rela_save(old_root, left, 'r');
    return root;
}

TreeNode* rotate_right(TreeNode* root)
{
    TreeNode* old_root = root->parent;
    TreeNode* parent = old_root->parent;
    TreeNode* left = root->left;
    TreeNode* right = root->right;
    if( NULL != left->data || NULL != right->data)
    {
        root->color = 'B';
        old_root->color = 'R';
    }
    node_rela_save(parent, root, parent?(*root->data < *parent->data?'l':'r') : ' ');
    node_rela_save(root, old_root, 'r');
    node_rela_save(old_root, right, 'l');
    return root;
}
TreeNode* tree_rb_fixup(TreeNode* node)
{
    TreeNode* p = node;
    TreeNode* parent = node->parent;
    while(parent)
    {
        if(!('R' == p->color && parent->color == p->color))
            break;
        TreeNode* parent_parent = parent->parent;
        TreeNode* uncle = NULL;
        if(parent == parent_parent->left)
            uncle = parent_parent->right;
        else
            uncle = parent_parent->left;
        if('R' == uncle->color)
        {
            parent->color = 'B';
            parent_parent->color = 'R';
            uncle->color = 'B';
            p = parent_parent;
            parent = parent_parent->parent;
        }
        else
        {
            if(parent == parent_parent->left)
                //if parent is pp`s left child node, then rotate right
                p = p == parent->left?rotate_right(parent):rotate_right(rotate_left(p));
            else
                //if parent is pp`s right child node, then rotate left
                p = p == parent->left?rotate_left(rotate_right(p)):rotate_left(parent);
            parent = p->parent;
        }
    }
    return p;
}
TreeNode* tree_insert(TreeNode** ppRoot, char *data)
{
	if(!ppRoot)return NULL;
	if(!*ppRoot)
		*ppRoot = nil_node_init();
    //node is the new added node
    TreeNode* p = *ppRoot;
    if(NULL == p->data)
    {
        TreeNode* node = node_init(data);
        node_rela_save(node, *ppRoot, 'l');
        TreeNode* right_nil_node = nil_node_init();
        node_rela_save(node, right_nil_node, 'r');
        node->color = 'B';
        *ppRoot = node;
    }
    else
    {
        p = tree_search(*ppRoot, data);
        if( NULL != p->data )
            p->count++;
        else
        {
            TreeNode* node = node_init(data);
            TreeNode* parent = p->parent;
            node_rela_save(parent, node, *node->data < *parent->data?'l':'r');
            node_rela_save(node, p, 'l');
            TreeNode* right_nil_node = nil_node_init();
            node_rela_save(node, right_nil_node, 'r');
            p = tree_rb_fixup(node);
            if(!p->parent && 'R' == p->color)//if root is red, then rotate
                p->color = 'B';
        }
    }
    return p->parent?*ppRoot:p;
}

TreeNode* rbtree_minimum(TreeNode* root)
{
    TreeNode* p = root;
    while(p->data != NULL)
        p = p->left;
    return p->parent;
}

TreeNode* rbtree_maximum(TreeNode* root)
{
    TreeNode* p = root;
    while(p->data != NULL)
        p = p->right;
    return p->parent;
}
TreeNode* release(TreeNode* node)
{
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    free(node);
    return node = NULL;
}
TreeNode* tree_delete(TreeNode* root, char *data)
{
    TreeNode* node = tree_search(root, data);
    if( NULL != node->data )
    {
        printf("data has been found:\n");
        print_node(node);
        TreeNode* left = node->left;
        TreeNode* right = node->right;
        TreeNode* p = NULL;
        if( NULL != left->data )
        {
            TreeNode* p = rbtree_maximum(left);
            *node->data = *p->data;
            node->count = p->count;
            node = p;
        }
        else if(NULL != right->data)
        {
            TreeNode* p = rbtree_minimum(right);
            *node->data = *p->data;
            node->count = p->count;
            node = p;
        }
        //now , parameter "node" is the node deleted
        TreeNode* parent = node->parent;
        if( node == root )
        {
            //if is red node or the root node,delete directly
            left = node->left;
            root = left;
            left->parent = NULL;
            release(node->right);
            release(node);
        }
        else if( 'R' == node->color)
        {
            //delete the node directly
            node_rela_save(parent, node->left, parent->left == node?'l':'r');
            release(node->right);
            release(node);
        }
        else
        {
            TreeNode* brother = node == parent->left?parent->right : parent->left;
            if('B' == brother->color)
            {
                //the situation is that, the parent node is black or red,
                //and the node and its brother is black
                parent->color = 'B';
                brother->color = 'R';
                //delete the node: begin
                node_rela_save(parent, node->left, parent->left == node?'l':'r');
                release(node->right);
                release(node);
                //delete the node: end
                TreeNode* brother_left = brother->left;
                TreeNode* brother_right = brother->right;
                if(NULL != brother_left->data)
                    p = tree_rb_fixup(brother_left);
                else if( NULL != brother_right->data )
                    p = tree_rb_fixup(brother_right);
            }
            else
            {
                //the situation is that, the parent node is black,
                //and the deleted node is black,which its brother is red
                //delete the node: begin
                node_rela_save(parent, node->left, parent->left == node?'l':'r');
                release(node->right);
                release(node);
                //delete the node: end
                parent->color = 'R';
                p = tree_rb_fixup(node == parent->left?parent->right:parent->left);
            }
        }
        return p?( p->parent?root:p):root;
    }
    else
        printf("data isn`t contained in the tree\n");
    return root;
}

void predecesor(TreeNode* node)
{
    if(node->data != NULL)
    {
        predecesor(node->right);
        printf("%d(",*node->data);
        printf("count:%d,",node->count);
        printf("color:%c),",node->color);
        predecesor(node->left);
    }
}

void predecesor_for_test(TreeNode* node)
{
    if(node->data != NULL)
    {
        predecesor_for_test(node->right);
        print_node(node);
        predecesor_for_test(node->left);
    }
}

void successor(TreeNode* node)
{
    if(node->data != NULL)
    {
        successor(node->left);
        printf("%d(",*node->data);
        printf("count:%d,",node->count);
        printf("color:%c),",node->color);
        successor(node->right);
    }
}

void successor_for_test(TreeNode* node)
{
    if(node->data != NULL)
    {
        successor_for_test(node->left);
        print_node(node);
        successor_for_test(node->right);
    }
}

void node_rela_save(TreeNode* parent, TreeNode* child, unsigned char lof)
{
    child->parent = parent;
    if(parent)
        if('l' == lof)
            parent->left = child;
        else if('r' == lof)
            parent->right = child;
}

int main(void)
{
//    unsigned int i=0;
//    i = ~i;//Ö±½Ó°ÑÖµÈ¡·´.¾ÍÊÇ¶þ½øÖÆ×î´ó¿É±íÊ¾µÄÖµ
//    printf("unsigned int×î´óÖµ:%u\n", UINT_MAX );
//    printf("unsigned int×îÐ¡Öµ:%u\n", i );

    srand(time(NULL));
    size_t size = 10;
    int a[size];
    size_t rand_size = size;

//    int a[] = {1};
//    size_t size = sizeof(a)/sizeof(a[0]);


    for(int i=0;i<size;i++)
    {
        a[i] = rand()%rand_size;
//        printf("%d,",a[i]);
    }

    TreeNode* root = NULL;
    for(int i=0;i<size;i++)
        root = tree_insert(&root, &a[i]);
    printf("\nroot is :%d\n",*root->data);

//    successor(root);
//    successor_for_test(root);

    int search_rand = rand()%rand_size;
    printf("\n");
    printf("search rand is :%d\n",search_rand);

//    TreeNode* node = tree_search(root, search_rand);
//    print_node(node);

//    int search_rand = 0;
//    printf("\ndelete data is:%d\n",search_rand);

    root = tree_delete(root, &search_rand);
//    printf("root after:%d\n",root->data);
//    print_node(root);
//    successor(root);
//    successor_for_test(root);
    TreeNode* node = tree_search(root, &search_rand);
    if(NULL != node->data)
        printf("data hasn`t been deleted!!");
    else
        printf("data deleted!!!");

	return 0;
}
