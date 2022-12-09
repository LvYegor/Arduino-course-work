#include <Wire.h> // библиотека для управления устройствами по I2C 
#include <LiquidCrystal_I2C.h> // подключаем библиотеку для QAPASS 1602
#include <TinyDHT.h>
#include <BH1750.h>

byte circle[8]{
  0b00011,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

#define BLU_1 10  
#define GRN_1 11 
#define RED_1 12

#define BLU_2 7  
#define GRN_2 8 
#define RED_2 9 

#define BLU_3 4 
#define GRN_3 5 
#define RED_3 6

bool flag = false;

BH1750 lightMeter = BH1750();

LiquidCrystal_I2C LCD(0x3F,16,2); // присваиваем имя LCD для дисплея


DHT dht(14, DHT22);

void setup() {
  LCD.init(); // инициализация LCD дисплея
  LCD.backlight(); // включение подсветки дисплея
  lightMeter.begin();
  dht.begin();
  LCD.createChar(1, circle);

  pinMode(15, INPUT);

  pinMode(GRN_1, OUTPUT); 
  
  pinMode(GRN_2, OUTPUT); 
  pinMode(RED_2, OUTPUT); 
  pinMode(BLU_2, OUTPUT); 

  pinMode(GRN_3, OUTPUT); 
  pinMode(RED_3, OUTPUT); 
  pinMode(BLU_3, OUTPUT); 
  
}

void loop() {
  if(digitalRead(15)){
    LCD.noDisplay();
    LCD.noBacklight();
      
    digitalWrite(RED_2, HIGH);
    digitalWrite(GRN_2, HIGH);
    digitalWrite(BLU_2, HIGH);

    digitalWrite(RED_3, HIGH);
    digitalWrite(GRN_3, HIGH);
    digitalWrite(BLU_3, HIGH);
    
    delay(1000);

    while(digitalRead(15) == false){}

    LCD.backlight();
    LCD.display();
    digitalWrite(GRN_1, LOW);
  }

  int humid = dht.readHumidity();

  int temp = dht.readTemperature();

  if(temp >= 22 && temp <= 30){
    digitalWrite(GRN_2, LOW);
    digitalWrite(BLU_2, HIGH);
    digitalWrite(RED_2, HIGH);
  } else if (temp < 22){
    digitalWrite(BLU_2, LOW);
    digitalWrite(RED_2, HIGH);
    digitalWrite(GRN_2, HIGH);
  } else {
    digitalWrite(RED_2, LOW);
    digitalWrite(GRN_2, HIGH);
    digitalWrite(BLU_2, HIGH);
  }

  int light = lightMeter.getLightIntensity();

  if(light < 150){
    digitalWrite(RED_3, LOW);
    digitalWrite(BLU_3, HIGH);
    digitalWrite(GRN_3, HIGH);
  } else {
    digitalWrite(GRN_3, LOW);
    digitalWrite(RED_3, HIGH);
    digitalWrite(BLU_3, HIGH);
  }
    
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Humidity: ");
  LCD.print(humid);
  LCD.print(" %");
  LCD.setCursor(0, 1);
  LCD.print("Temperature:");
  LCD.print(temp);
  LCD.print(char(1));
  LCD.print("C"); 
}