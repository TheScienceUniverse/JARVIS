#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char W[50];	// Word
int lW = 0;		// Length of Word

unsigned char *createWordString();
void clearWordBuffer();

int main(int argc, char *argv[]) {
	if (argc < 2) {
		perror("File not specified!\n");
		exit(1);
	}
	
	unsigned char c, *str;

	FILE *fpi = fopen(argv[1], "rb+");
	if(fpi == NULL) {
		perror("Can't open input file!\n");
		exit(1);
	}

	/*FILE *fpo = fopen("op.txt", "wb+");
	if(fpo == NULL) {
		perror("Can't open output file!\n");
		exit(1);
	}
	*/

	fseek(fpi, 1, SEEK_END);
	unsigned long f_ic = 0;		// File Index Counter
	long f_sz = ftell(fpi);	// File SiZe
	printf("File Size: %ld bytes.\n", f_sz);

	long i;
	int j;

	size_t sz;
	rewind(fpi);
	for(i = 0; i < f_sz; i++) {
		sz = fread(&c, 1, 1, fpi);
		if(c >= 0x61 && c <= 0x7a) {
			W[lW++] = c;
		} else if ((c < 0x61 || c > 0x7a) && (lW > 0)) {
			str = createWordString();
			// printf("%s\n", str);
			system(str);
			clearWordBuffer();
		}
	}
	
	printf("********* DONE **********\n");

	fclose(fpi);
	// fclose(fpo);
	return 0;
}

unsigned char *createWordString() {
	unsigned char rawCmd[] = {'p', 'h', 'p', ' ', 'f', 'e', 't', 'c', 'h', '.', 'p', 'h', 'p', ' '};
	unsigned char *word = (unsigned char *) malloc((14 + lW) * sizeof(unsigned char));
	int i;
	for(i = 0; i < 14; i++) {
		word[i] = rawCmd[i];
	}
	for(i = 0; i < lW; ++i) {
		word[14 + i] = W[i];
	}
	return word;
}

void clearWordBuffer() {
	for (int i = 0; i < lW; W[i++] = 0);
	lW = 0;
}
