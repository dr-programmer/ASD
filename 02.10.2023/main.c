#include <stdio.h>
/*
int main() {
	char a = 6, b = 7;
	if((a & b) == a) printf("Works\n");
	else printf("Doesn't work\n");
	return 0;
}
*/
/*
int main() {
	char a = 6, b = 7;
	if(!(a ^ b)) printf("Works\n");
	else printf("Doesn't work\n");
	return 0;
}
*/

typedef struct {
	char *name;
	int owner;
	int ownerGroup;
	int perm;
} File;

char check_perm(File* file, int uid, int gid, int want_to_do) {
	if(file->owner == uid) {
		want_to_do<<=6;
	}
	else if(file->owner == gid) {
		want_to_do<<=3;
	}
	return (want_to_do & file->perm) == want_to_do;
}

int main() {
	return 0;
}
