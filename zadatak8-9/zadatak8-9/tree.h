#pragma once
#ifndef TREE_H
#define TREE_H


typedef struct tree* treePos;


typedef struct tree {
    int value;
    treePos left; 
    treePos right;    
} tree;


treePos Insert(treePos root, int value);//deklaracija funkcije za umetanje èvora u stablo
treePos Delete(treePos root, int value);//deklaracija funkcije za brisanje cvora
treePos FindMin(treePos root);// deklaracija funkcije za traženje najmanjeg elementa u stablu 

int Inorder(treePos root, int depth); // inorder ispis 
int Preorder(treePos root,int depth);// preorder ispis 
int Postorder(treePos root, int depth);// postorder ispis 
int height(treePos root);//dubina stabla
int level(treePos root, int level);
int height(treePos root);// visina stabla
int Levelorder(treePos root);//level order ispis
treePos InsertRandom(treePos root, int n);




int Free(treePos root);//oslobaðanje memorije

int replace(treePos root);

#endif

