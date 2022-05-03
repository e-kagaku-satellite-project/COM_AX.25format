/* 
 * File:   receive.h
 * Author: asapy
 *
 * Created on March 29, 2022, 9:05 PM
 */

#ifndef RECEIVE_H_20220329
#define RECEIVE_H_20220329

#ifdef __cplusplus
extern "C" {
#endif
uint8_t decryption(uint8_t* enc_data, uint8_t* plain_data, uint8_t enc_key);
void dataNotGate(uint8_t* data, int size);
void dataBitInv(uint8_t* data, int size);
void printByBit(uint8_t data);
int powInt(int m, int n);
uint8_t invertBit(uint8_t data);
int checkBit(int num, uint8_t data);
char decToHex(int dec);
void printByHex(uint8_t data);
void initializeArrayByZero(uint8_t* array, int lenth);
#ifdef __cplusplus
}
#endif

#endif /* RECEIVE_H */
