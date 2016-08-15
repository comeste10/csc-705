#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "spritz.h"

int main(int argc, char **argv) {

	// setup
	size_t i;
	unsigned char plaintext[100000];
	unsigned char key[] = {'a','b','c','d'};
	unsigned char ciphertext[sizeof(plaintext)];
	unsigned char decryptedtext[sizeof(plaintext)];
	size_t text_len = 0;
	size_t key_len = sizeof(key);

	// read input
	unsigned char *ptr = plaintext;
	i = 0;
	while(scanf("%c",ptr++) != EOF) i++;
	text_len = i;

	// operations
	encrypt(ciphertext, plaintext, text_len, key, key_len);
	decrypt(decryptedtext, ciphertext, text_len, key, key_len);

	// correctness check
	for(i=0; i<text_len; i++) {
		if(plaintext[i] != decryptedtext[i]) {
			printf("Error: Messages do not match\n");
			return 0;
		}
	}
	//printf("Success\n");

	return 0;
}
