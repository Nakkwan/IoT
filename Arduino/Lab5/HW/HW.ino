#include <SArduino.h>

#define PRIVATE 0
#define PUBLIC 1

void dump(byte* buf, int len){
  int i;

  for(i = 0; i < len; i++){
    Serial.print((char)buf[i]);
  }
  Serial.println();
}

void GetPlain(byte* plain, int plain_len, byte* getplain, int *get_len){
  for(int i = 0; i < plain_len; i++){
    getplain[i] = plain[i];
  }
  *get_len = plain_len;
}

void mergeData(byte* hash, int hash_len, byte* enc, int enc_len, byte* merg, int *merg_len){
  int i;
  *merg_len = 160;
  for(i = 0; i < hash_len; i++){
    merg[i] = hash[i];
  }
  for(i = hash_len; i < 160; i++){
    merg[i] = enc[i - hash_len];
  }
}

void GetData(byte* merg, int merge_len, byte* dhash, int *dhash_len, byte* dec, int *dec_len){
  int i;
  *dhash_len = 32;
  *dec_len = 128;
  for(i = 0; i < merge_len; i++){
    if(i < 32){
      dhash[i] = merg[i];
    }else{
      dec[i - 32] = merg[i];
    }
  }
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

  byte getplain[32];
  int getplain_len;

  byte digest[32];
  int digest_len = 32;

  byte ddigest[32];
  int ddigest_len;

  byte enc_data[128];
  int enc_len;

  byte dec_data[64];
  int dec_len;

  byte get_data[128];
  int get_len;

  byte merge_data[160];
  int merge_len;

  if(!Generate_RSA1024Key(key_num)){
    Serial.println("Set RSA1024 Key Pair Failure");
  }
  Serial.print("plain data: ");
  dump(plain_data, plain_len);

  if(SHA_256(plain_data, plain_len, digest, &digest_len)){
    Serial.print("digest: ");
    dump(digest, digest_len);
  }

  if(Encrypt_RSA1024(key_num, PRIVATE, digest, digest_len, enc_data, &enc_len)){
    Serial.print("enc_data: ");
    dump(enc_data, enc_len);
  }else{
    Serial.println("Encrypt plain_data Failure");
  }

  mergeData(digest, digest_len, enc_data, enc_len, merge_data, &merge_len);

  GetData(merge_data, merge_len, ddigest, &ddigest_len, get_data, &get_len);
  
  if(Decrypt_RSA1024(key_num, PUBLIC, get_data, get_len, dec_data, &dec_len)){
    Serial.print("dec_data: ");
    dump(dec_data, ddigest_len);
  }else{
    Serial.println("Decrypt enc_Data Failure");
  }

  Serial.print("digest: ");
  dump(ddigest, ddigest_len);

  GetPlain(plain_data, plain_len ,getplain, &getplain_len);

  Serial.print("Get plain data: ");
  dump(getplain, getplain_len);
}

void loop() {
  // put your main code here, to run repeatedly:

}
