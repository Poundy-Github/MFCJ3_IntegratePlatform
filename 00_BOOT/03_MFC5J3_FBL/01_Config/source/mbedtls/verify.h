#ifndef MBEDTLS_VERIFY_H
#define MBEDTLS_VERIFY_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int mbedtls_verify(const unsigned char hash[16], const unsigned char Signature[16]);

int mbedtls_aes_decrypt_ecb(const unsigned char *key, const unsigned char input[16], unsigned char output[16]);

#ifdef __cplusplus
}
#endif

#endif
