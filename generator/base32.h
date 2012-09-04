
#ifndef BASE32_H
#define BASE32_H

char * base32_encode(const void *buf, unsigned int len);
void * base32_decode(const char * buf, unsigned int * outlen);

#endif // BASE32_H
