
#ifndef BASE32_H
#define BASE32_H

#ifdef __cplusplus
extern "C" {
#endif

char * base32_encode(const void *buf, unsigned int len);
void * base32_decode(const char * buf, unsigned int * outlen);

#ifdef __cplusplus
}
#endif

#endif // BASE32_H
