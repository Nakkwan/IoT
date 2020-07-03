#include <SArduino.h>

void dump(byte* buf, int len){
  int i;

  for(i = 0; i < len; i++){
    Serial.print((char)buf[i]);
  }
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600, SERIAL_8E2);

  if(!Init_SE()){
    Serial.println("SE Connection Failure");
  }

  int key_num = 0x0;

  byte plain_data[] = "나는 2018년 6월 1일에 홍길동에게 100만원을 입금하였다";
  int plain_len =strlen(plain_data);

  byte modify_data[] = "나는 2018년 6월 2일에 홍길동에게 100만원을 입금하였다";
  int modify_len =strlen(modify_data);

  byte digest[32];
  int digest_len = 32;

  byte sign_data[128];
  int sign_len;

  byte enc_data[128];
  int enc_len;

  byte dec_data[64];
  int dec_len;

  if(!Generate_RSA1024Key(key_num)){
    Serial.println("Set RSA1024 Key Pair Failure");
  }
  Serial.print("plain data: ");
  dump(plain_data, plain_len);

  if(Sign_RSA1024(key_num, plain_data, plain_len, sign_data, &sign_len)){
    Serial.print("sign_data: ");
    dump(sign_data, sign_len);
  }else{
    Serial.println("Sign plain_data Failure");
  }

  if(Verify_RSA1024(key_num, sign_data, sign_len, plain_data, &plain_len)){
    Serial.println("Verify plain_data Success");
  }else{
    Serial.println("Verify plain_data Failure");
  }

  if(Verify_RSA1024(key_num, sign_data, sign_len, modify_data, &modify_len)){
    Serial.println("Verify modify_data Success");
  }else{
    Serial.println("Verify modify_data Failure");
  }

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
