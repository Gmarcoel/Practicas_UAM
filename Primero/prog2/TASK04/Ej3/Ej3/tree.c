#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "tree.h"

typedef struct _BTNode
{
    void *info;
    struct _BTNode *left;
    struct _BTNode *right;
} BTNode;
struct _BSTree
{
    BTNode *root;
    destroy_element_function_type destroy_element;
    copy_element_function_type copy_element;
    print_element_function_type print_element;
    cmp_element_function_type cmp_element;
};

/*** DECLARACIÓN DE FUNCIONES PRIVADAS ***/

BTNode *bt_node_new();
void bt_node_free(BTNode *pn, destroy_element_function_type free_elem);
int tree_node_depth(BTNode *node);
BTNode *tree_node_insert(BSTree *tree, BTNode *node, const void *elem);
void tree_node_preOrder(FILE *f, const BSTree *tree, BTNode *node);
void tree_node_inOrder(FILE *f, const BSTree *tree, BTNode *node);
void tree_node_postOrder(FILE *f, const BSTree *tree, BTNode *node);
void tree_node_destroy(BSTree *tree, BTNode *node);
/*** PRIMITIVAS PRIVADAS DE BT-NODOS ***/
BTNode *bt_node_new()
{
    BTNode *pn = NULL;
    pn = malloc(sizeof(BTNode));
    if (!pn)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    pn->left = NULL;
    pn->right = NULL;
    pn->info = NULL;
    return pn;
}
void bt_node_free(BTNode *pn, destroy_element_function_type free_elem)
{
    if (!pn)
        return;
    free_elem(pn->info);
    free(pn);
    return;
}

/*** CREACIÓN Y LIBERACIÓN DE UN ÁRBOL ***/
/*Inicializa un árbol vacío.*/
BSTree *tree_init(destroy_element_function_type f1,
                  copy_element_function_type f2,
                  print_element_function_type f3,
                  cmp_element_function_type f4)
{
    BSTree *tree = malloc(sizeof(BSTree));
    if (!tree)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    tree->root = NULL;
    tree->destroy_element = f1;
    tree->copy_element = f2;
    tree->print_element = f3;
    tree->cmp_element = f4;
    return tree;
}
/*Indica si el árbol está o no vacio*/
Bool tree_isEmpty(const BSTree *tree)
{
    if (!tree || !(tree->root))
        return TRUE;
    return FALSE;
}
/*Libera la memoria utilizada por un árbol.*/
void tree_destroy(BSTree *tree)
{
    tree_node_destroy(tree, tree->root);
    free(tree);
}

void tree_node_destroy(BSTree *tree, BTNode *node)
{
    if (!tree || !node)
        return;
    tree_node_destroy(tree, node->left);
    tree_node_destroy(tree, node->right);
    bt_node_free(node, tree->destroy_element);
    return;
}
/*Indica la profundidad del árbo. Un árbol vacio profundidad -1*/
int tree_depth(const BSTree *tree)
{
    if (!tree)
        return -1;
    return tree_node_depth(tree->root);
}
int tree_node_depth(BTNode *node)
{
    if (!node)
        return 0;
    if (tree_node_depth(node->left) > tree_node_depth(node->right))
        return tree_node_depth(node->left) + 1;
    return tree_node_depth(node->right) + 1;
}
/*** INSERCIÓN ***/
/*Inserta un elemento en un árbol binario de búsqueda.*/
Status tree_insert(BSTree *tree, const void *elem)
{
    BTNode * next;
    if (!tree || !elem)
        return ERROR;
    next = tree_node_insert(tree, tree->root, elem);
    if (!next)
    {
        tree->root = bt_node_new();
        tree->root->info = tree->copy_element(elem);
    }
    return OK;
}
BTNode *tree_node_insert(BSTree *tree, BTNode *node, const void *elem)
{
    BTNode *next;
    if (!node)
        return NULL;
    if (tree->cmp_element(node->info, elem) <= 0)
    {
        next = tree_node_insert(tree, node->left, elem);
        if (!next)
        {
            node->left = bt_node_new();
            node->left->info = tree->copy_element(elem);
            return node;
        }
    } else {
        next = tree_node_insert(tree, node->right, elem);
        if (!next)
        {
            node->right = bt_node_new();
            node->right->info = tree->copy_element(elem);
            return node;
        }
    }
    return next;
}
/*** RECORRIDOS ***/
/*Recorre un árbol en orden previo.*/
void tree_preOrder(FILE *f, const BSTree *tree)
{
    if (!f || !tree)
        return;
    tree_node_preOrder(f, tree, tree->root);
    return;
}
void tree_node_preOrder(FILE *f, const BSTree *tree, BTNode *node)
{
    if (!node)
        return;
    tree->print_element(f, node->info);
    printf("\n");
    tree_node_preOrder(f, tree, node->left);
    tree_node_preOrder(f, tree, node->right);
    return;
}
/*Recorre un árbol en orden medio.*/
void tree_inOrder(FILE *f, const BSTree *tree)
{

    if (!f || !tree)
        return;
    tree_node_inOrder(f, tree, tree->root);
    return;
}
void tree_node_inOrder(FILE *f, const BSTree *tree, BTNode *node)
{
    if (!f || !node || !tree)
        return;
    tree_node_inOrder(f, tree, node->left);
    tree->print_element(f, node->info);
    printf("\n");
    tree_node_inOrder(f, tree, node->right);
    return;
}
/*Recorre un árbol en orden posterior.*/
void tree_postOrder(FILE *f, const BSTree *tree)
{
    if (!f || !tree)
        return;
    tree_node_postOrder(f, tree, tree->root);
    return;
}
void tree_node_postOrder(FILE *f, const BSTree *tree, BTNode *node)
{
    if (!f || !node || !tree)
        return;
    tree_node_postOrder(f, tree, node->left);
    tree_node_postOrder(f, tree, node->right);
    tree->print_element(f, node->info);
    printf("\n");
    return;
}
