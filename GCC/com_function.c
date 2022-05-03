#include<stdint.h>
#include<stdio.h>
#include "com_function.h"

#define RAW_DATA_LENGTH		  253
#define ENCRYPTED_DATA_LENGTH 256
uint8_t decryption(uint8_t* enc_data, uint8_t* plain_data, uint8_t enc_key) {
	// for(int i = 0; i < ENCRYPTED_DATA_LENGTH; i++) {
	// 	printf("%x", enc_data[i]);
	// 	printf(", ");
	// }

	//有効データ数カウント
	int data_size = 3;
	while(enc_data[data_size] != 0) {
		data_size++;
	}
	data_size--;

	dataNotGate(enc_data, data_size);

	initializeArrayByZero(plain_data, ENCRYPTED_DATA_LENGTH);
	for(int i = 0; i <= data_size; i++) {
		plain_data[i] = enc_data[i];
	}

	for(int i = data_size; i > 0; i--) {
		if(plain_data[i] >= enc_key) {
			plain_data[i] -= enc_key;
		} else {
			int a = plain_data[i] + 256 - enc_key;

			plain_data[i] = a & 0x00FF;
			int j		  = i - 1;
			while(1) {
				if(enc_data[j] > 0) {
					plain_data[j] -= 1;
					break;
				}
				else if(j == 0) {
					return 0;
				}
				else {
					plain_data[j] = 255;
					j--;
				}
			}
		}
	}
	dataBitInv(plain_data, data_size);

	return 1;
}

void dataNotGate(uint8_t* data, int size) {
	//ビット反転
	for(int i = 0; i <= size; i++) {
		data[i] = ~data[i];
	}
}

void dataBitInv(uint8_t* data, int size) {
	//ビット順列反転
	for(int i = 1; i <= size; i++) {
		data[i] = invertBit(data[i]);
	}
}

void printByBit(uint8_t data) {
	printByHex(data);
	printf(":");
	for(int i = 7; i >= 0; i--) {
		int bit = data / powInt(2, i);
		data -= powInt(2, i) * bit;
		printf("%d", bit);
	}
	printf("\r\n");
}

//?????(??????)(m^n)
int powInt(int m, int n) {
	int temp = 1;		 //temporary???
	for(int i = 0; i < n; i++) {
		temp = temp * m;		//?????
	}
	return temp;		//??????
}

//???????(00011110 -> 01111000)
uint8_t invertBit(uint8_t data) {
	uint8_t data_inversion = 0;
	for(int i = 7; i >= 0; i--) {
		int bit = data / powInt(2, i);
		data -= powInt(2, i) * bit;
		data_inversion += powInt(2, 7 - i) * bit;
	}
	return data_inversion;
}

//?????(data????num??????????)
int checkBit(int num, uint8_t data) {
	int bit_data[8];
	for(int i = 7; i >= 0; i--) {
		int bit = data / powInt(2, i);
		data -= powInt(2, i) * bit;
		bit_data[i] = bit;
	}
	return bit_data[num - 1];
}

//10??16???
char decToHex(int dec) {
	if(dec == 0)
		return '0';
	if(dec == 1)
		return '1';
	if(dec == 2)
		return '2';
	if(dec == 3)
		return '3';
	if(dec == 4)
		return '4';
	if(dec == 5)
		return '5';
	if(dec == 6)
		return '6';
	if(dec == 7)
		return '7';
	if(dec == 8)
		return '8';
	if(dec == 9)
		return '9';
	if(dec == 10)
		return 'A';
	if(dec == 11)
		return 'B';
	if(dec == 12)
		return 'C';
	if(dec == 13)
		return 'D';
	if(dec == 14)
		return 'E';
	if(dec == 15)
		return 'F';
}

//???16????
void printByHex(uint8_t data) {
	for(int i = 1; i >= 0; i--) {
		int bit = data / powInt(16, i);
		data -= powInt(16, i) * bit;
		printf("%c", decToHex(bit));
	}
}

void initializeArrayByZero(uint8_t* array, int lenth) {
	for(int i = 0; i < lenth; i++) {
		array[i] = 0x00;
	}
}
