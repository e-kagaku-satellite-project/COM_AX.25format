#include<stdio.h>
#include<stdint.h>
#include"com_function.c"
#define DATA_ARRAY_LENGTH 100
void CreatePacket(uint8_t *s_sign, uint8_t *d_sign, uint8_t s_ssid, uint8_t d_ssid, uint8_t *data, uint8_t *output_pac);
int main(){
	uint8_t source_sign[6] = "JK1FUT";
	uint8_t dest_sign[6] = "OTTW21";
	uint8_t source_ssid = 0b1101;
	uint8_t dest_ssid = 0b0010;
	uint8_t data[DATA_ARRAY_LENGTH];
	initializeArrayByZero(data,DATA_ARRAY_LENGTH);
	data[0]  ='w';
	data[1]  ='1';
	data[2]  ='6';
	data[3]  ='1';
	data[4]  ='3';
	data[5]  ='3';


	uint8_t output_packet[130];
	initializeArrayByZero(output_packet,130);
	
	CreatePacket(source_sign, dest_sign, source_ssid, dest_ssid, data, output_packet);
	
	for(int i=0;i<=23;i++){
		printf("%02X, ",output_packet[i]);
	}
	
}
void CreatePacket(uint8_t *s_sign, uint8_t *d_sign, uint8_t s_ssid, uint8_t d_ssid, uint8_t *data, uint8_t *output_pac){
	output_pac[0] = 0x7E;
	
	for(uint16_t i=0;i<=6;i++){
		output_pac[i+1] = s_sign[i] << 1;
	}
	
	output_pac[7] = 0b01100000 | (s_ssid << 1);
	
	for(uint16_t i=0;i<=6;i++){
		output_pac[i+8] = d_sign[i] << 1;
	}
	
	output_pac[14] = 0b01100001 | (d_ssid << 1);
	
	output_pac[15] = 0x03;
	
	output_pac[16] = 0xF0;


	uint16_t data_size = 1;
	//有効データ数カウント
    while(1){
		if(data_size == 252){
			break;
		}else if(data[data_size] == 0){
			data_size--;
            break;
        }else{
            data_size++;
        }
    }

	uint16_t cursor;
	for(cursor=17;cursor<= 17+data_size;cursor++){
		output_pac[cursor] = data[cursor-17];
	}
	output_pac[cursor] = 0x7E;

}
