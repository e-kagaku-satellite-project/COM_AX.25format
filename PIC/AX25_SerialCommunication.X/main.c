/*
20211229
PIC16F1779によるAX.25フォーマット作成
参考：https://qiita.com/OzoraKobo/items/e411705f2295d5a6f27d
参考：http://www.tapr.org/pdf/AX25.2.2.pdf
参考：http://www.sr1bsz.ampr.org/aprs/aprs_ssid_guide.html
参考：https://sagamifj1300.blog.fc2.com/blog-entry-876.html
*/

/*
AX.25プロトコル

"Flag,Adress,Control,PID,Data,FCS,Flag"
Flag    (1byte)     :0x7E
Address (14byte)    :Destination(7byte)+sender(7byte)
Control (1byte)     :0x03
PID     (1byte)     :0xF0
Data    (0~256Byte) :data
FCS     (2byte)     :CRC-16-CCITT
Flag    (1byte)     :0x7E
*/

#define DESTINATISON_CALLSIGN JQ1ZEL
#define DESTINATISON_SSID
#define SENDER_CALLSIGN JK1FUT
#define DESTINATISON_SSID

#include "mcc_generated_files/mcc.h"

void main(void) {

	SYSTEM_Initialize();		//システム初期化

	while(1) {
	}
}
