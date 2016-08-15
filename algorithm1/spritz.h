#ifndef __SPRITZ_H__
#define __SPRITZ_H__

void encrypt(unsigned char *ct, unsigned char *pt, size_t pt_len, unsigned char *key, size_t key_len);

void decrypt(unsigned char *pt, unsigned char *ct, size_t ct_len, unsigned char *key, size_t key_len);

#endif
