#include<Servo.h>

Servo hori;
int sh = 90;
int sh_limitH = 180;
int sh_limitL = 0;


Servo vert;
int sv = 0;
int sv_limitH = 150;
int sv_limitL = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  hori.attach(9);
  vert.attach(10);
  hori.write(90);
  vert.write(0);
  delay(3000);
}

void loop()
{
  int lt = analogRead(A0);
  int rt = analogRead(A1);
  int ld = analogRead(A2);
  int rd = analogRead(A3);

  int avt = (lt + rt) / 2;  //上平均
  int avd = (ld + rd) / 2;  //下平均
  int avl = (lt + ld) / 2;  //左平均
  int avr = (rt + rd) / 2;  //右平均

  int dvert = avt - avd;  //垂直光強度偏差值
  int dhori = avl - avr;  //水平光強度偏差值
  int toler = 60;  //光強偏差量容忍值

  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print(" ");

  if (-toler > dhori || dhori > toler)
  {
    if (avl > avr)
    {
      sh = ++sh;
      if (sh > sh_limitH)
        sh = sh_limitH;
    }
    else if (avl < avr)
    {
      sh = --sh;
      if (sh < sh_limitL)
        sh = sh_limitL;
    }
    hori.write(sh);
    Serial.print(sh);
    Serial.print(" ");
  }

  if (-toler > dvert || dvert > toler)
  {
    if (avt > avd)
    {
      sv = ++sv;
      if (sv > sv_limitH)
        sv = sv_limitH;
    }
    if (avt < avd)
    {
      sv = --sv;
      if (sv < sv_limitL)
        sv = sv_limitL;
    }
    vert.write(sv);
    Serial.print(sv);
    Serial.print(" ");
  }
  Serial.println(" ");
  delay(10);
}
