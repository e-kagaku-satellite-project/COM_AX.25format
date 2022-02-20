/**
 * @file main.c
 * @author Rin Yoshino (you@domain.com)
 * @brief  AX.25
 * @version 0.1
 * @date 2022-02-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include <stdio.h>

#define CALL_SIGNE_SATELLITE "JQ1ZEL"
#define SSID_SATELLITE		 0b00000111
#define FLAG				 0x7E
#define CONTROL				 0x03
#define PID					 0xF0
#define END_ADDRESS			 0b00000001

uint8_t FormatData[276];
uint8_t Data[256] = {"HELTH OK BATTERY OK"};
uint8_t SenderCallSigne[6];
uint8_t DestinationCallSigne[6];
uint8_t SenderAddress[7];
uint8_t DestinationAddress[7];

//小道具用関数プロトタイプ宣言----------------------------------
void bit_print(uint8_t data);
int pow_int(int m, int n);
uint8_t bit_inversion(uint8_t data);
int check_bit(int num, uint8_t data);
char DtoH(int dec);
void hex_print(uint8_t data);
//------------------------------------------------------------
int main() {

	//先頭フラグ
	FormatData[0] = FLAG;

	//アドレスフィールド作成
	uint8_t CommandKinds			= 1;		//1:フレームはコマンド,0:フレームは応答
	uint8_t SenderCallSigne[6]		= "JK1FUT";
	uint8_t SenderSSID				= 0b00001001 << 1;
	uint8_t DestinationCallSigne[6] = CALL_SIGNE_SATELLITE;
	uint8_t DestinationSSID			= SSID_SATELLITE << 1;
	SenderAddress[0]				= SenderCallSigne[0] << 1;
	SenderAddress[1]				= SenderCallSigne[1] << 1;
	SenderAddress[2]				= SenderCallSigne[2] << 1;
	SenderAddress[3]				= SenderCallSigne[3] << 1;
	SenderAddress[4]				= SenderCallSigne[4] << 1;
	SenderAddress[5]				= SenderCallSigne[5] << 1;
	SenderAddress[6]				= 0b01100000 + SenderSSID;
	DestinationAddress[0]			= DestinationCallSigne[0] << 1;
	DestinationAddress[1]			= DestinationCallSigne[1] << 1;
	DestinationAddress[2]			= DestinationCallSigne[2] << 1;
	DestinationAddress[3]			= DestinationCallSigne[3] << 1;
	DestinationAddress[4]			= DestinationCallSigne[4] << 1;
	DestinationAddress[5]			= DestinationCallSigne[5] << 1;
	DestinationAddress[6]			= 0b01100000 + DestinationSSID + 0b00000001;
	if(CommandKinds == 1) {
		SenderAddress[6] += 0b10000000;
	}
	if(CommandKinds == 0) {
		DestinationAddress[6] += 0b10000000;
	}
	FormatData[1]  = SenderAddress[0];
	FormatData[2]  = SenderAddress[1];
	FormatData[3]  = SenderAddress[2];
	FormatData[4]  = SenderAddress[3];
	FormatData[5]  = SenderAddress[4];
	FormatData[6]  = SenderAddress[5];
	FormatData[7]  = SenderAddress[6];
	FormatData[8]  = DestinationAddress[0];
	FormatData[9]  = DestinationAddress[1];
	FormatData[10] = DestinationAddress[2];
	FormatData[11] = DestinationAddress[3];
	FormatData[12] = DestinationAddress[4];
	FormatData[13] = DestinationAddress[5];
	FormatData[14] = DestinationAddress[6];

	//制御コマンド
	FormatData[15] = CONTROL;

	//PID
	FormatData[16] = PID;

	//データ挿入
	int DataCount = 0;
	while(Data[DataCount] > 0) {
		FormatData[17 + DataCount] = Data[DataCount];
		DataCount++;
	}

	//FCS
	FormatData[17 + DataCount]	   = 0xFF;
	FormatData[17 + DataCount + 1] = 0xFF;
	//終端フラグ
	FormatData[17 + DataCount + 2] = FLAG;

	//データ表示
	int i = 0;
	while(FormatData[i] > 0) {
		bit_print(FormatData[i]);
		i++;
	}
}

//-------------------------------------------------------------------------------------------------
//小道具用関数群
/*
基本的には、ここにある関数と同類のものは作成しないこと。関数名の変更はなし。個々への関数追加は
COM系担当ｻﾎﾟｰﾀｰに一声かけること
*/

//データ2進数表記(0d10 -> 00001010)
void bit_print(uint8_t data) {
	hex_print(data);
	printf(":");
	for(int i = 7; i >= 0; i--) {
		int bit = data / pow_int(2, i);
		data -= pow_int(2, i) * bit;
		printf("%d", bit);
	}
	printf("\r\n");
}

//累乗の関数(正の数値専用)(m^n)
int pow_int(int m, int n) {
	int temp = 1;		 //temporaryの略。
	for(int i = 0; i < n; i++) {
		temp = temp * m;		//累乗の計算
	}
	return temp;		//結果をだす。
}

//ビット順番反転(00011110 -> 01111000)
uint8_t bit_inversion(uint8_t data) {
	uint8_t data_inversion = 0;
	for(int i = 7; i >= 0; i--) {
		int bit = data / pow_int(2, i);
		data -= pow_int(2, i) * bit;
		data_inversion += pow_int(2, 7 - i) * bit;
	}
	return data_inversion;
}

//ビット確認(dataの左からnum番目のビット値を取得)
int check_bit(int num, uint8_t data) {
	int bit_data[8];
	for(int i = 7; i >= 0; i--) {
		int bit = data / pow_int(2, i);
		data -= pow_int(2, i) * bit;
		bit_data[i] = bit;
	}
	return bit_data[num - 1];
}

//10進→16進変換
char DtoH(int dec) {
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

//データ16進数表記
void hex_print(uint8_t data) {
	for(int i = 1; i >= 0; i--) {
		int bit = data / pow_int(16, i);
		data -= pow_int(16, i) * bit;
		printf("%c", DtoH(bit));
	}
}
