#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

treePos Insert(treePos root, int value)
{
    if (root == NULL) {//ako je stablo prazno, kreiranje novog cvora
        root = (treePos)malloc(sizeof(tree));//alokacija memorije
        root->value = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    if (value < root->value)//ako je vrijednost manja, ide u lijevo
        root->left = Insert(root->left, value);
    else//ako je vrijednost veca, ide desno
        root->right = Insert(root->right, value);

    return root;
}



treePos FindMin(treePos root)
{
    while (root && root->left)//pronalazi manji element prema lijevo
        root = root->left;
    return root;
}


treePos Delete(treePos root, int value)
{
    if (!root) return NULL;

    if (value < root->value)
        root->left = Delete(root->left, value);
    else if (value > root->value)
        root->right = Delete(root->right, value);
    else {
        // Ako nema lijevo ili desno dijete
        if (!root->left || !root->right) {
            treePos temp = root->left ? root->left : root->right;
            free(root);
            return temp;// vraca podstablo ili NULL ako nema djece
        }

        // Ako ima oba djeteta, jednostavno spajamo desno na najdesniji cvor lijevog podstabla 
        treePos temp = root->left;
        while (temp->right) temp = temp->right;
        temp->right = root->right;  // spojimo desno podstablo
        treePos del = root;
        root = root->left;// korijen postaje lijevo podstablo
        free(del);
    }

    return root;
}




int Inorder(treePos root, int depth)//lijevo, value, desno
{
    if (!root) return 0;

    Inorder(root->left, depth+1);
    printf("|  %*s-> %d\n", depth * 2, "", root->value);
    Inorder(root->right, depth+1);
    return 0;
}


int Preorder(treePos root, int depth)//value, lijevo, desno
{
    if (!root) return 0;
    for (int i = 0; i < depth; i++)
        printf("|  ");
    printf("-> %d\n ", root->value);
    Preorder(root->left, depth+1);
    Preorder(root->right,depth+1);
    return 0;
}


int Postorder(treePos root, int depth)//lijevo, desno, value
{
    if (!root) return 0;
    Postorder(root->left, depth+1);
    Postorder(root->right, depth+1);
    for (int i = 0; i < depth; i++)
        printf("|  ");
    printf("-> %d\n", root->value);
    return 0;
}
int level(treePos root, int l) {
    if (root == NULL)
        return 0;
    if (l == 1)
        printf("%d ", root->value);
    else {
        level(root->left, l - 1);//-1 jer se spustamo na nizu razinu
        level(root->right, l - 1);
    }
    return 0;
}

int height(treePos root) {
    if (root == NULL)
        return 0;
    int left_h = height(root->left);
    int right_h = height(root->right);
    return (left_h > right_h ? left_h : right_h) + 1;
}

int Levelorder(treePos root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        level(root, i);
        printf("\n");
    }
    return 0;
}

int Free(treePos root)//oslobadanje
{
    if (root) {
        Free(root->left);
        Free(root->right);
        free(root);
    }
    return 0;
}

int replace(treePos root)//zamjena
{
    if (!root) return 0;
    int sumLeft = replace(root->left), sumRight = replace(root->right);
    
    int prev = root->value;
    root->value = sumLeft + sumRight;
    return prev + sumLeft + sumRight;
}

treePos InsertRandom(treePos root, int n)
{
    int value;

   
    srand((unsigned)time(NULL));

    for (int i = 0; i < n; i++) {
        value = rand() % 81 + 10;// raspon 10–90
        root = Insert(root, value);
    }

    return root;
}
