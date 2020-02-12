#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<time.h>
//#include "rbtree.h"
#define NIL -50000000

typedef struct
{
	unsigned int data;
	struct NODE* parent;
	struct NODE* left;
	struct NODE* right;
	char color;
	int count;
} NODE;
void print_node(NODE* node)
{
    if(NIL != node->data)
    {
        printf("\n  ");
        NODE* p = node->parent;
        NODE* l = node->left;
        NODE* r = node->right;
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

NODE* node_init(unsigned int data)
{
    NODE* node = (NODE*)calloc(1,sizeof(NODE));
    node->data = data;
    node->count = 1;
    node->color = 'R';
    return node;
}

NODE* nil_node_init()
{
    NODE* root = (NODE*)calloc(1,sizeof(NODE));
    root->data = NIL;
    root->color = 'B';
    return root;
}

NODE* tree_search(NODE* root, unsigned int data)
{
	if(!root)return NULL;
    NODE* p = root;
    while( NIL != p->data)
    {
        if(data == p->data)
            break;
        else if(p->data < data)
            p = p->right;
        else
            p = p->left;
    }
    return p;
}

NODE* rotate_left(NODE* root)
{
    NODE* old_root = root->parent;
    NODE* parent = old_root->parent;
    NODE* left = root->left;
    NODE* right = root->right;
    if( NIL != left->data || NIL != right->data)
    {
        root->color = 'B';
        old_root->color = 'R';
    }
    node_rela_save(parent, root, parent?(root->data < parent->data?'l':'r') : ' ');
    node_rela_save(root, old_root, 'l');
    node_rela_save(old_root, left, 'r');
    return root;
}

NODE* rotate_right(NODE* root)
{
    NODE* old_root = root->parent;
    NODE* parent = old_root->parent;
    NODE* left = root->left;
    NODE* right = root->right;
    if( NIL != left->data || NIL != right->data)
    {
        root->color = 'B';
        old_root->color = 'R';
    }
    node_rela_save(parent, root, parent?(root->data < parent->data?'l':'r') : ' ');
    node_rela_save(root, old_root, 'r');
    node_rela_save(old_root, right, 'l');
    return root;
}
NODE* tree_rb_fixup(NODE* node)
{
    NODE* p = node;
    NODE* parent = node->parent;
    while(parent)
    {
        if(!('R' == p->color && parent->color == p->color))
            break;
        NODE* parent_parent = parent->parent;
        NODE* uncle = NULL;
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
NODE* tree_insert(NODE** ppRoot, unsigned int data)
{
	if(!ppRoot)return NULL;
	if(!*ppRoot)
		*ppRoot = nil_node_init();
    //node is the new added node
    NODE* p = *ppRoot;
    if(NIL == p->data)
    {
        NODE* node = node_init(data);
        node_rela_save(node, *ppRoot, 'l');
        NODE* right_nil_node = nil_node_init();
        node_rela_save(node, right_nil_node, 'r');
        node->color = 'B';
        *ppRoot = node;
    }
    else
    {
        p = tree_search(*ppRoot, data);
        if( NIL != p->data )
            p->count++;
        else
        {
            NODE* node = node_init(data);
            NODE* parent = p->parent;
            node_rela_save(parent, node, node->data < parent->data?'l':'r');
            node_rela_save(node, p, 'l');
            NODE* right_nil_node = nil_node_init();
            node_rela_save(node, right_nil_node, 'r');
            p = tree_rb_fixup(node);
            if(!p->parent && 'R' == p->color)//if root is red, then rotate
                p->color = 'B';
        }
    }
    return p->parent?*ppRoot:p;
}

NODE* rbtree_minimum(NODE* root)
{
    NODE* p = root;
    while(p->data != NIL)
        p = p->left;
    return p->parent;
}

NODE* rbtree_maximum(NODE* root)
{
    NODE* p = root;
    while(p->data != NIL)
        p = p->right;
    return p->parent;
}
NODE* release(NODE* node)
{
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    free(node);
    return node = NULL;
}
NODE* tree_delete(NODE* root, unsigned int data)
{
    NODE* node = tree_search(root, data);
    if( NIL != node->data )
    {
        printf("data has been found:\n");
        print_node(node);
        NODE* left = node->left;
        NODE* right = node->right;
        NODE* p = NULL;
        if( NIL != left->data )
        {
            NODE* p = rbtree_maximum(left);
            node->data = p->data;
            node->count = p->count;
            node = p;
        }
        else if(NIL != right->data)
        {
            NODE* p = rbtree_minimum(right);
            node->data = p->data;
            node->count = p->count;
            node = p;
        }
        //now , parameter "node" is the node deleted
        NODE* parent = node->parent;
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
            NODE* brother = node == parent->left?parent->right : parent->left;
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
                NODE* brother_left = brother->left;
                NODE* brother_right = brother->right;
                if(NIL != brother_left->data)
                    p = tree_rb_fixup(brother_left);
                else if( NIL != brother_right->data )
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

void predecesor(NODE* node)
{
    if(node->data != NIL)
    {
        predecesor(node->right);
        printf("%d(",node->data);
        printf("count:%d,",node->count);
        printf("color:%c),",node->color);
        predecesor(node->left);
    }
}

void predecesor_for_test(NODE* node)
{
    if(node->data != NIL)
    {
        predecesor_for_test(node->right);
        print_node(node);
        predecesor_for_test(node->left);
    }
}

void successor(NODE* node)
{
    if(node->data != NIL)
    {
        successor(node->left);
        printf("%d(",node->data);
        printf("count:%d,",node->count);
        printf("color:%c),",node->color);
        successor(node->right);
    }
}

void successor_for_test(NODE* node)
{
    if(node->data != NIL)
    {
        successor_for_test(node->left);
        print_node(node);
        successor_for_test(node->right);
    }
}

void node_rela_save(NODE* parent, NODE* child, unsigned char lof)
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

    NODE* root = NULL;
    for(int i=0;i<size;i++)
        root = tree_insert(&root, a[i]);
    printf("\nroot is :%d\n",root->data);

//    successor(root);
//    successor_for_test(root);

    int search_rand = rand()%rand_size;
    printf("\n");
    printf("search rand is :%d\n",search_rand);

//    NODE* node = tree_search(root, search_rand);
//    print_node(node);

//    int search_rand = 0;
//    printf("\ndelete data is:%d\n",search_rand);

    root = tree_delete(root, search_rand);
//    printf("root after:%d\n",root->data);
//    print_node(root);
//    successor(root);
//    successor_for_test(root);
    NODE* node = tree_search(root, search_rand);
    if(NIL != node->data)
        printf("data hasn`t been deleted!!");
    else
        printf("data deleted!!!");

	return 0;
}
