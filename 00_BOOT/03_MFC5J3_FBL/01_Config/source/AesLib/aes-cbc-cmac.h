/**
 * @brief 
 * 
 */

#ifndef AES_CBC_CMAC_H_
#define AES_CBC_CMAC_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BLOCK_SIZE 16
#define LAST_INDEX (BLOCK_SIZE - 1)

int AES_CBC_ENC(const unsigned char *IV, const unsigned char *key,
		const unsigned char *input, int inputLength, unsigned char *output,
		int outputLength);

int AES_CBC_DEC(const unsigned char *IV, const unsigned char *key,
		const unsigned char *input, int inputLength, unsigned char *output,
		int outputLength);

void AES_CMAC(const unsigned char *key, const unsigned char *input, int length,
		unsigned char *mac);

int AES_CMAC_CHECK(const unsigned char *key, const unsigned char *input,
		int length, const unsigned char *mac);

void xor_128(const unsigned char *a, const unsigned char *b, unsigned char *out);
void AES_128_DEC(unsigned const char *key, unsigned const char* msg, unsigned char *cipher);

#ifdef DEBUG_CMAC
void print_hex(const char *str, const unsigned char *buf, int len);
void print128(const unsigned char *bytes);
void print96(const unsigned char *bytes);
#endif

#ifdef __cplusplus
}
#endif

#endif /* AES_CBC_CMAC_H_ */
