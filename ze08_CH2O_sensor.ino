#include<SoftwareSerial.h>
const byte start_QAmode_cmd[] = {0xFF,0x01,0x78,0x40,0x00,0x00,0x00,0x00,0x47};
const byte read_cmd[] = {0xFF,0x01,0x78,0x40,0x00,0x00,0x00,0x00,0x47};
const byte return_cmd[] = {0xFF,0x86,0x00,0x2A,0x00,0x00,0x00,0x20,0x30};
byte received_bytes[9];

SoftwareSerial ze08_serial(D1,D2);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
ze08_serial.begin(9600);
for(int i =0;i<9;i++)
{
  ze08_serial.write(start_QAmode_cmd[i]);
}

}

void loop() {
  // put your main code here, to run repeatedly:
float ch2o;
ch2o = read_ch2o();
//memset(received_bytes,0,sizeof(received_bytes));
Serial.print("formaldehyde: ");
Serial.println(ch2o);
delay(2000);
}

float read_ch2o()
{
  float ch2; 
   //ze08_serial.write(read_cmd,sizeof(read_cmd));
    if(ze08_serial.write(read_cmd,sizeof(read_cmd)) == 9);
    {
    for(byte i = 0;i<9;i++)
    {
      received_bytes[i] = ze08_serial.read();
    }

    //print function
    for(byte j = 0;j<9;j++)
    {
      Serial.println(received_bytes[j]);
    }
    Serial.println();
    
    //Gas concentration value=High byte of concentration *256+ Low byte of concentration
    ch2 = (received_bytes[2] * 256) + received_bytes[3];
    //ch2 = ch2/1000;
 }
return ch2;

}
