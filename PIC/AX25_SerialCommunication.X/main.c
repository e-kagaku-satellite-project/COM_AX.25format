/*
20211229
PIC16F1779によるAX.25フォーマット作成(衛星送信側)
参考：https://qiita.com/OzoraKobo/items/e411705f2295d5a6f27d
参考：http://www.tapr.org/pdf/AX25.2.2.pdf
参考：http://www.sr1bsz.ampr.org/aprs/aprs_ssid_guide.html
参考：https://sagamifj1300.blog.fc2.com/blog-entry-876.html
*/

/*
AX.25プロトコル

"Flag,Adress,Control,PID,Data,FCS,Flag"
20byte~276byte
Mandatory20byte
Flag    (1byte)     :0x7E
Address (14byte)    :Destination(7byte)+sender(7byte)
Control (1byte)     :0x03
PID     (1byte)     :0xF0
Data    (0~256Byte) :data
FCS     (2byte)     :CRC-16-CCITT
Flag    (1byte)     :0x7E
*/

#include "mcc_generated_files/mcc.h"

#define SEND_SENDER_CALLSIGN "JQ1ZEL"
#define SEND_SENDER_SSID	 9
#define AX25_FLAG			 0x7E
#define AX25_CONTROL		 0x30
#define AX25_PID			 0xF0

//衛星送信用変数群
uint8_t send_data[276];										   //送信バッファ
uint8_t send_sender_callsign[6] = SEND_SENDER_CALLSIGN;		   //送信元コールサイン
uint8_t send_sender_ssid		= SEND_SENDER_SSID;			   //送信元SSID
uint8_t send_destination_calllsign[6];						   //送信先コールサイン
uint8_t send_destination_ssid;								   //送信先SSID
uint16_t send_data_fcs;										   //送信データチェックサム
uint8_t send_data[256];										   //送信データ

void MakeSendAddressField() {
	//送信先設定
	send_data[1] = (send_destination_calllsign[0] << 1);
	send_data[2] = (send_destination_calllsign[1] << 1);
	send_data[3] = (send_destination_calllsign[2] << 1);
	send_data[4] = (send_destination_calllsign[3] << 1);
	send_data[5] = (send_destination_calllsign[4] << 1);
	send_data[6] = (send_destination_calllsign[5] << 1);
	send_data[7] = (send_destination_ssid << 1) + 0b01100000;

	//送信元設定
	send_data[8]  = (send_destination_calllsign[0] << 1);
	send_data[9]  = (send_destination_calllsign[1] << 1);
	send_data[10] = (send_destination_calllsign[2] << 1);
	send_data[11] = (send_destination_calllsign[3] << 1);
	send_data[12] = (send_destination_calllsign[4] << 1);
	send_data[13] = (send_destination_calllsign[5] << 1);
	send_data[14] = (send_destination_ssid << 1) + 0b11100001;
}

void main(void) {

	SYSTEM_Initialize();		//システム初期化

	while(1) {
	}
}
