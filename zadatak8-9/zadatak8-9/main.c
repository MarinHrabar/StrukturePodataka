#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "tree.h"
#include "files.h"


 char* file = "stablo.txt";
treePos Load( root, file);//funkcija za ucitavanje datoteke

int main()
{
    treePos root = NULL;
    int choice, value;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Dodaj broj\n2. Obrisi broj\n3. Ispisi inorder\n4. Ispisi preorder\n5. Ispisi postorder\n6. Level order: \n");
        printf("7. Ucitaj iz datoteke\n8. Replace\n9. Random\n10. Inorder file\n 0. Izlaz\n");
        printf("Odabir: "); scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Unesi broj: ");
            scanf("%d", &value);
            root = Insert(root, value);
            break;
        case 2:
            printf("Unesi broj za brisanje: "); 
            scanf("%d", &value);
            root = Delete(root, value);
            break;
        case 3:
            printf("Inorder:\n ");
            Inorder(root, 0); 
            printf("\n");
            break;
        case 4:
            printf("Preorder:\n "); 
            Preorder(root,0); 
            printf("\n");
            break;
        case 5:
            printf("Postorder:\n "); 
            Postorder(root,0); 
            printf("\n");
            break;
        
        case 6:
            printf("Level order:\n ");
            Levelorder(root);
            printf("\n");
            break;
        case 7:
            root = Load(root, "stablo.txt");
            printf("Brojevi ucitani iz datoteke.\n");
            break;
        case 8:
            replace(root);
            printf("Replace zavrsen.\n");
            break;
        case 9:
            printf("Koliko brojeva generirati? ");
            int n;
            scanf("%d", &n);
            root = InsertRandom(root, n);
            printf("%d random brojeva dodano.\n", n);
            break;
        case 10:
            WriteInorderFile(root, "inorder.txt");
            printf("Inorder zapisano u inorder.txt\n");
            break; 
        case 0:
            root = Free(root);
            printf("Izlaz.\n");
            break;
        default:
            printf("Pokusajte ponovno\n");
        }
    } while (choice != 0);

    return 0;
}
