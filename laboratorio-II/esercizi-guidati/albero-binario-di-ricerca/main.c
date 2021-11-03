#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct N
{
    int val;
    struct N *sx;
    struct N *dx;
};
typedef struct N Node;
typedef Node *Tree;

void insertNode(Tree *, int);
Tree minValueNode(Tree);
Tree deleteNode(Tree, int);
void fancyPrintAux(char *, Tree, int);
void fancyPrint(Tree);
void printTree(Tree);

int main(void)
{
    Tree albero = NULL;
    int n = 0;

    // while (n >= 0)
    // {
    //     scanf("%d", &n);
    //     if (n >= 0)
    //     {
    //         insertNode(&albero, n);
    //     }
    // }

    insertNode(&albero, 4);
    insertNode(&albero, 0);
    insertNode(&albero, 7);
    insertNode(&albero, 2);
    insertNode(&albero, 5);
    insertNode(&albero, 9);
    insertNode(&albero, 8);
    insertNode(&albero, 3);
    insertNode(&albero, 6);
    insertNode(&albero, 1);
    printf("Inseriti!\n");
    fancyPrint(albero);
    printf("\n");

    albero = deleteNode(albero, 4);

    albero = deleteNode(albero, 3);

    albero = deleteNode(albero, 9);
    
    printf("Cancellati!\n");
    fancyPrint(albero);
    printf("\n");

    printf("\n");
    return 0;
}

void insertNode(Tree *radice, int v)
{
    if (*radice == NULL)
    {
        Node *tmp = (Node *)malloc(sizeof(Node));
        tmp->val = v;
        tmp->sx = NULL;
        tmp->dx = NULL;
        *radice = tmp;
    }
    else
    {
        if ((*radice)->val > v) //vai a sx
        {
            insertNode(&(*radice)->sx, v);
        }
        else if ((*radice)->val <= v) //vai a dx
        {
            insertNode(&(*radice)->dx, v);
        }
    }
}

Tree minValueNode(Tree node)
{
    Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->sx != NULL)
        current = current->sx;

    return current;
}

Tree deleteNode(Tree root, int key)
{
    // base case
    if (root == NULL)
        return root;

    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in sx subtree
    if (key < root->val)
        root->sx = deleteNode(root->sx, key);

    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (key > root->val)
        root->dx = deleteNode(root->dx, key);

    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->sx == NULL)
        {
            Node *temp = root->dx;
            free(root);
            return temp;
        }
        else if (root->dx == NULL)
        {
            Node *temp = root->sx;
            free(root);
            return temp;
        }

        // node with two children:
        // Get the inorder successor
        // (smallest in the dx subtree)
        Node *temp = minValueNode(root->dx);

        // Copy the inorder
        // successor's content to this node
        root->val = temp->val;

        // Delete the inorder successor
        root->dx = deleteNode(root->dx, temp->val);
    }
    return root;
}

void fancyPrintAux(char *prefix, Tree radice, int isLeft)
{
    if (radice != NULL)
    {
        printf("%s", prefix);
        printf("%s", isLeft ? "├── " : "└── ");
        printf("%d\n", radice->val);

        char *s = prefix;
        char *s1 = (isLeft ? "│   " : "    ");
        char *target = malloc(strlen(s) + strlen(s1) + 1);
        strcpy(target, s);
        strcat(target, s1);

        fancyPrintAux(target, radice->sx, 1);
        fancyPrintAux(target, radice->dx, 0);

        free(target);
    }
}

void fancyPrint(Tree Radice)
{
    fancyPrintAux("", Radice, 0);
}

void printTree(Tree radice)
{
    if (radice->sx != NULL)
    {
        printTree(radice->sx);
    }
    printf("%d ", radice->val);
    if (radice->dx != NULL)
    {
        printTree(radice->dx);
    }
}