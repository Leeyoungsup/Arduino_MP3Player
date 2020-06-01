#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <Timer.h>
#include <MsTimer2.h>
#include <WS2812.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


int hour1=13,minute1=9,sec1=0;
int hour2=0,minute2=5,sec2=0;
int hour3=14,minute3=0,sec3=0;
int count1=0,count2=0,count3=0,count4=0,count5=0,count6=0,musiccount=20;
int Button1=1,Button2=1,Button3=1,Button4=1,Button5=1,Button6=1,Button7=1;
int random1=1,musics=0,music2=0;
// 실행시 가장 먼저 호출되는 함수이며, 최초 1회만 실행됩니다.
// 변수를 선언하거나 초기화를 위한 코드를 포함합니다.
void setup() {
  Serial.begin (9600);
  mp3_set_serial (Serial);  
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  pinMode(6,INPUT);
  delay(1);                     // 볼륨값 적용을 위한 delay
  mp3_set_volume (musiccount); 
  // I2C LCD를 초기화 합니다..
  lcd.init();
  // I2C LCD의 백라이트를 켜줍니다.
  lcd.backlight();
  }

void loop() {

  lcd.clear();
  Button1=digitalRead(6);
  Button2=digitalRead(7);
  Button3=digitalRead(8);
  Button4=digitalRead(9);
  Button5=digitalRead(10);
  Button6=digitalRead(11);
  Button7=digitalRead(12);
  
  if(Button2==LOW)
  {
    music2=1;
    random1=(rand()%20)+musics*20;
    mp3_play(random1);
  }
  if(Button3==LOW)
  {
    mp3_stop(); 
    music2=0;
  }
  if(Button4==LOW)
  {
    if(musiccount==30){
    }
    else{
      musiccount+=1;
      mp3_set_volume (musiccount);  
    }  
  }
  if(Button5==LOW)
  {
    if(musiccount==0){
    }
    else{
      musiccount-=1;
      mp3_set_volume (musiccount);  
    }   
  }
  if(Button6==LOW)
  {
    mp3_next(); 
  }
  if(Button7==LOW)
  {
    mp3_prev(); 
  }
  if(Button1==LOW)
  {
    count1++;
    if(count1==3)
    {
      count1=0;
    }
  }
  if(count1==0)
  {
    clock1();
    lcd.setCursor(0,0);
    lcd.print("clock   ");
    lcd.print(hour1);
    lcd.print(":");
    lcd.print(minute1);
    lcd.print(":");
    lcd.print(sec1);
    if(Button4==LOW){
       if(musics==2){
        musics=0;
       }
       else{
        musics+=1;
       }
    if(Button5==LOW){
       if(musics==0){
        musics=2;
       }
       else{
        musics-=1;
       }
    }
  }
  }
  if(count1==1)
  {
    clock1();
    lcd.setCursor(0,0);           // 0번째 줄 0번째 셀부터 입력하게 합니다.
    timer();
    if(hour2==0 && minute2==0 && sec2==0)
    {
      musiccount=30;
      mp3_set_volume (musiccount);
      random1=(rand()%20)+musics*20;
      mp3_play(random1);
    }  
  }
  if(count1==2)
  {
    clock1();
    lcd.setCursor(0,0);           // 0번째 줄 0번째 셀부터 입력하게 합니다.
    alarm();  
  }
  if(hour3==hour1 && minute3==minute1 && sec3==sec1)
  {
    musiccount=30;
    mp3_set_volume (musiccount);
    random1=(rand()%20)+musics*20;
    mp3_play(random1);
  }  
  lcd.setCursor(0,1);
  lcd.print(musics);
  if(musics==0){
    lcd.print(".   hiphop");
  }
  if(musics==1){
    lcd.print(".   pop");  
  }
  if(musics==2){
    lcd.print(".   k-ballade");  
  }  
delay(1000);
}
void alarm()
{
  if(Button4==LOW)
  {
    hour3--;
    if(hour3==0)
    {
      hour3=24;
    }
  }
  if(Button5==LOW)
  {
    hour3++;
    if(hour3==24)
    {
      hour3=0;
    }
  }
  lcd.print("alarm   ");
  lcd.print(hour3);
  lcd.print(":");
  lcd.print(minute3);
  lcd.print(":");
  lcd.print(sec3);
}
void timer()
{
  if(Button5==LOW)
  {
    minute2--;
    if(minute2==0)
    {
      minute2=59;
    }
  }
  if(Button4==LOW)
  {
    minute2++;
    if(minute2==59)
    {
      minute2=0;
    }
  }
  lcd.print("timer   ");
  lcd.print(hour2);
  lcd.print(":");
  lcd.print(minute2);
  lcd.print(":");
  lcd.print(sec2);
  if(sec2!=0 || minute2!=0){
    if(sec2==0)
    {
      if(minute2!=0)
      {
        minute2--;
        sec2=59;
      } 
    }
    else
    {
      sec2--;
    }
  }
  else{
    sec2--;
  }

}
void clock1(){
  sec1++;
  if(sec1==60)
  {
    minute1++;
    sec1=0;
  }
  if(minute1==60)
  {
    minute1=0;
    hour1++;
  }
  if(hour1==24)
  {
    hour1=0;
  }

}

