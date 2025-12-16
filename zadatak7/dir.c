#define _CRT_SECURE_NO_WARNINGS
#include "dir.h"

Position createDir(char* name, Position parent) {
	Position d = (Position)malloc(sizeof(dir));//alokacija memorije
	if (!d) {
		printf("Neuspjesna alokacija memorije!\n");
		return NULL;
	}
	strcpy(d->name, name);
	d->parent = parent;//postavljanje roditeljskog direktorija
	d->child = NULL;//nema pod-direktorija
	d->next = NULL;//nema sljedeceg direktorija
	return d;
}
Position mkDir(Position curr, char* name) {
	Position newDir = createDir(name, curr);
	if (!newDir)
		return curr;

	if (!curr->child){
		curr->child = newDir;//ako nema djece novi direktorij postaje prvo dijete
	}
	else {
		Position temp = curr->child;
		while (temp->next)
			temp = temp->next;
		temp->next = newDir;//dodavanje na kraj
	}
	return curr;
}
Position cd(Position curr, char* name) {
	Position temp = curr->child;
	while (temp) {
		if (strcmp(temp->name, name) == 0) {
			return temp;//ako nademo dijete ulazimo u njega
		}
		temp = temp->next;
	}
	printf("Direktorij ne postoji.\n");
	return curr;

}
Position cd_return(Position curr) {
	if (curr->parent)
		return curr->parent;//vracamo se u roditeljski direktorij
	printf("Nalazimo se u roditeljskom direktoriju.\n ");
	return curr;
}
Position listDir(Position curr) {
	Position temp = curr->child;
	if (!temp) {
		printf("Direktorij je prazan.\n");
		return curr;
	}
	while (temp) {
		printf("[DIR]\t%s\n", temp->name);
		temp = temp->next;
	}
	return curr;
}
Position rd(Position curr, char* name) {
	Position prev = NULL;
	Position temp = curr->child;

	while (temp) {
		if (strcmp(temp->name, name) == 0) {
			if (prev) {
				prev->next = temp->next;
			}//uklanjanje djece
			else {
				curr->child = temp->next;
			}
			freeAll(temp);//oslobadanje memorije
			return curr;
		}
		prev = temp;
		temp = temp->next;

	}
	printf("Direktorij ne postoji.\n");
	return curr;
}
Position freeAll(Position root) {
	if (!root) return NULL;

	freeAll(root->child);
	freeAll(root->next);

	free(root);
	return NULL;
}