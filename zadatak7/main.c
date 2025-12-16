
#define _CRT_SECURE_NO_WARNINGS
#include "dir.h"

int main() {
    Position root = createDir("root", NULL);// root direktorij
    Position curr = root;// trenutno aktivni direktorij

    char input[100];
    char arg[50];

   
    printf("Komande: mkdir ime | cd ime | cd.. | ls | rd ime | exit\n");

    while (1) {
        
        printf("\n[%s]> ", curr->name);
        if (!fgets(input, sizeof(input), stdin))
            break;

        input[strcspn(input, "\n")] = 0;  // uklanjanje \n

        if (strncmp(input, "mkdir ", 6) == 0) {
            sscanf(input + 6, "%s", arg);
            curr = mkDir(curr, arg);
        }
        else if (strncmp(input, "cd ", 3) == 0) {
            sscanf(input + 3, "%s", arg);
            curr = cd(curr, arg);    // ulazak u direktorij
        }
        else if (strcmp(input, "cd..") == 0) {
            curr = cd_return(curr);    // povratak u roditelja
        }
        else if (strcmp(input, "ls") == 0) {
            curr = listDir(curr);// ispis sadrzaja
        }
        else if (strncmp(input, "rd ", 3) == 0) {
            sscanf(input + 3, "%s", arg);
            curr = rd(curr, arg);// brisanje direktorija
        }
        else if (strcmp(input, "exit") == 0) {
            break;// izlaz iz programa
        }
        else {
            printf("Nepoznata komanda.\n");
        }
    }

    root = freeAll(root);// oslobadanje memorije prije izlaska
    return 0;
}
