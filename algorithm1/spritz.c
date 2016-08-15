#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 
	Author: Steven Comer
	Description: Spritz Implementation
	Source: https://people.csail.mit.edu/rivest/pubs/RS14.pdf
	Updated: 20 Jul 16
*/

#define N 256
#define LOW(B) ((B) & 0xf)
#define HIGH(B) ((B) >> 4)

typedef struct {
	unsigned char s[N];
	unsigned char i;
	unsigned char j;
	unsigned char k;
	unsigned char z;
	unsigned char a;
	unsigned char w;
} State;

void swap(unsigned char *array, size_t j, size_t k) {
	unsigned char temp = array[j];
	array[j] = array[k];
	array[k] = temp;
}

void initialize_state(State *S) {
	S->i = 0;
	S->j = 0;
	S->k = 0;
	S->z = 0;
	S->a = 0;
	S->w = 1;
	size_t v;
	for(v=0; v<N; v++) {
		S->s[v] = v;
	}
}

void update(State *S) {
	S->i = S->i + S->w;
	S->j = S->k + S->s[S->j+(S->s[S->i])];
	S->k = S->i + S->k + S->s[S->j];
	swap(S->s, S->i, S->j);
}

unsigned char output(State *S) {
	S->z = S->s[S->j + S->s[S->i + S->s[S->z + S->k]]];
	return S->z;
}

void whip(State *S) {
	size_t r = N*2;
	size_t v;
	for(v=0; v<r; v++) {
		update(S);
	}
	S->w += 2;
}

void crush(State *S) {
	size_t v;
	for(v=0; v < N/2; v++) {
		if(S->s[v] > S->s[N-1-v]) {
			swap(S->s, v, N-1-v);
		}
	}
}

void shuffle(State *S) {
	whip(S);
	crush(S);
	whip(S);
	crush(S);
	whip(S);
	S->a = 0;
}

void absorb_nibble(State *S, unsigned char x) {
	if(S->a == N/2) {
		shuffle(S);
	}
	swap(S->s, S->a, N/2+x);
	S->a += 1;
}

void absorb_byte(State *S, unsigned char b) {
	absorb_nibble(S,LOW(b));
	absorb_nibble(S,HIGH(b));
}

void absorb(State *S, unsigned char *in, size_t in_len) {
	size_t v;
	for(v=0; v<in_len; v++) {
		absorb_byte(S,in[v]);
	}
}

void absorb_stop(State *S) {
	if(S->a == N/2) {
		shuffle(S);
	}
	S->a += 1;
}

unsigned char drip(State *S) {
	if(S->a > 0) {
		shuffle(S);
	}
	update(S);
	return output(S);
}

void squeeze(State *S, unsigned char *r, size_t r_len) {
	if(S->a > 0) {
		shuffle(S);
	}
	size_t v;
	for(v=0; v<r_len; v++) {
		r[v] = drip(S);
	}
}

void key_setup(State *S, unsigned char *key, size_t key_len) {
	initialize_state(S);
	absorb(S, key, key_len);
}

void encrypt(unsigned char *ct, unsigned char *pt, size_t pt_len, unsigned char *key, size_t key_len) {
	State *S = malloc(sizeof(State));
	memset(S,0,sizeof(State));
	unsigned char r[pt_len];
	memset(r,0,pt_len);
	size_t v;
	key_setup(S, key, key_len);
	squeeze(S, r, pt_len);
	for(v=0; v<pt_len; v++) {
		ct[v] = pt[v] + r[v];
		//printf("ct[%d]=%d\tpt[%d]=%d\tr[%d]=%d\n", v, ct[v], v, pt[v], v, r[v]);
	}
	free(S);
}

void decrypt(unsigned char *pt, unsigned char *ct, size_t ct_len, unsigned char *key, size_t key_len) {
	State *S = malloc(sizeof(State));
	memset(S,0,sizeof(State));
	unsigned char r[ct_len];
	memset(r,0,ct_len);
	size_t v;
	key_setup(S, key, key_len);
	squeeze(S, r, ct_len);
	for(v=0; v<ct_len; v++) {
		pt[v] = ct[v] - r[v];
		//printf("ct[%d]=%d\tpt[%d]=%d\tr[%d]=%d\n", v, ct[v], v, pt[v], v, r[v]);
	}
	free(S);
}

