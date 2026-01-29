#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "tree.h"

treePos Load(treePos root, const char* filename) 
{
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Greska pri otvaranju datoteke %s\n", filename);
        return root;
    }

    int value;
    while (fscanf(f, "%d", &value) == 1) {
        root = Insert(root, value);
    }

    fclose(f);
    return root;
}

int InorderFile(treePos root, FILE* fp)
{
    if (!root) return 0;
    InorderFile(root->left, fp);
    fprintf(fp, "%d ", root->value);
    InorderFile(root->right, fp);
    return 0;
}

int WriteInorderFile(treePos root, const char* filename)
{
    FILE* fp = fopen(filename, "w");
    if (!fp) return -1;
    InorderFile(root, fp);
    fclose(fp);
    return 0;
}