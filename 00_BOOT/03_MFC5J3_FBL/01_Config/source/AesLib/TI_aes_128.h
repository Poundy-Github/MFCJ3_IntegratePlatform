/**
 * @brief 
 * 
 */

#ifndef TI_OPT_AES_H_
#define TI_OPT_AES_H_

#ifdef __cplusplus
extern "C" {
#endif

void aes_enc_dec(unsigned char *state, unsigned char *key, unsigned char dir);

#ifdef __cplusplus
}
#endif
#endif /* TI_OPT_AES_H_ */
