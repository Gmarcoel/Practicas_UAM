#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "types.h"
#include "graph.h"

int main(int argc, char **argv)
{
    FILE *f;
    Graph *g;
    BSTree *tree;
    long *nodes;
    int i;
    Node *aux;
    if (!argv[1])
    {
        printf("Not enough arguments. Please insert a file");
        return -1;
    }
    g = graph_init();
    f = fopen(argv[1], "r");
    graph_readFromFile(f, g);
    fclose(f);

    printf("PRINTING GRAPH:\n--------------\n");
    graph_print(stdout, g);

    tree = tree_init(node_free, node_copy, node_print, node_cmp_id);
    nodes = graph_getNodesId(g);
    for (i = 0; i < graph_getNumberOfNodes(g); i++)
    {
        aux = graph_getNode(g, nodes[i]);
        tree_insert(tree, aux);
        node_free(aux);

    }
    free(nodes);

    printf("\n--------------\n--------------\nPRINTING PREORDER:\n--------------\n");
    tree_preOrder(stdout, tree);
    printf("\n--------------\n--------------\nPRINTING INORDER:\n--------------\n");
    tree_inOrder(stdout, tree);
    printf("\n--------------\n--------------\nPRINTING POSTORDER:\n--------------\n");
    tree_postOrder(stdout, tree);

    tree_destroy(tree);
    graph_free(g);
    return 0;
}