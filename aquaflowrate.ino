//修改为RP PICO 版本


#include <LiquidCrystal.h>

const int rs = 9, en = 8, d4 = 4, d5 = 5, d6 = 6, d7 = 7;  //定义1602lcd屏幕硬件接口

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte interruptPin = 0;  // 使用GPIO_0 连接传感器信号

const long taketime = 1000;  // 每次测量的时间为1000毫秒

long unsigned T1;  //计时器T1

float C1 = 0;  //计数器C1

float Result = 0; //存储流量计算值

float Temp1 = 0; //即时存储

void count() {

  C1 += 1;
  // 中断内计数
}

void setup() {

  attachInterrupt(digitalPinToInterrupt(interruptPin), count, FALLING);  //指定端口下降沿触发中断
  Serial.begin(9600);
  T1 = millis();  //开始计时，time获得当前系统时间

  lcd.begin(16, 2);
  lcd.print("Result:");
  lcd.setCursor(13, 1);
  lcd.print("L/H");
}

void loop() {

  if (millis() >= T1) {

    Result = (C1 / 5) * 60;
    T1 = millis() + taketime;  //标记未来的时间点，1000ms后执行if判断，输出结果。另，降低刷新频率，可以提高分辨率
    C1 = 0;                    //输出速度结果后清零，记录下一秒的触发次数
  }

  //Temp1 = Result ;

  //if(Serial.print(Temp1) != Serial.print(Result)){
  //  lcd.setCursor(0, 1);
  //   lcd.print("            ");
  //}
  //lcd.setCursor(0, 1);
  //lcd.print("            ");
  lcd.setCursor(0, 1);
  lcd.print(Result);
  lcd.print("     ");
  //Serial.println(lcd.setCursor(0,1);lcd.print(Result));
}
