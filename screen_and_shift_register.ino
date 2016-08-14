#include <Wire.h>


//int dataout = 2;
//int SRCLK   = 3;
//int RCLK    = 4;

int bit0 = 3;
int bit1 = 4;
int bit2 = 5;
int bit3 = 6;
int bit4 = 9;
int bit5 = 10;
int bit6 = 11;
int bit7 = 12;

String inputString = "";
bool stringComplete;

int _data_pins[8] = {bit0, bit1, bit2, bit3, bit4, bit5, bit6, bit7};

int enable  = 8;
int RS      = 7;

void RSon() {
  delay(1);
  digitalWrite(RS, 1);
}

void RSoff() {
  delay(1);
  digitalWrite(RS, 0);
}

void enableScreen() {
  delay(1);
  digitalWrite(enable, 1);
}

void disableScreen() {
  delay(1);
  digitalWrite(enable, 0);
}

void pulseEnable() {
  enableScreen();
  disableScreen();
}

void pulseSRCLK() {
  delay(1);
  //digitalWrite(SRCLK, 1);
  delay(1);
  //digitalWrite(SRCLK, 0);
}

void pulseRCLK() {
  delay(1);
  //digitalWrite(RCLK,b 1);
  delay(1);
  //digitalWrite(RCLK, 0);
}

void clearScreen() {
  delay(1);
  writeCommand(0x01);
  pulseEnable();
}

void writeChar(char thisisachar) {
  delay(1);
  writeCommand(thisisachar);
  delay(1);
}

void writeString(String string) {
  for(int i = 0; i < string.length(); i++) {
    writeChar(string[i]);
  }
}

void writeCommand(char thisisachar) {
  /*Serial.print(thisisachar & 128);
  bit7 = (thisisachar & 128);
  Serial.print(thisisachar & 64);
  bit6 = (thisisachar & 64);
  Serial.print(thisisachar & 32);
  bit5 = (thisisachar & 32);
  Serial.print(thisisachar & 16);
  bit4 = (thisisachar & 16);
  Serial.print(thisisachar & 8);
  bit3 = (thisisachar & 8);
  Serial.print(thisisachar & 4);
  bit2 = (thisisachar & 4);
  Serial.print(thisisachar & 2);
  bit1 = (thisisachar & 2);
  Serial.print(thisisachar & 1);
  bit0 = (thisisachar & 1);
  Serial.print(thisisachar);
  Serial.println();
  */
  //Serial.println(thisisachar);
  for (int i = 0; i < 8; i++) {
    digitalWrite(_data_pins[i], (thisisachar >> i) & 0x01);
  }
  pulseEnable();
}

/*void writeCommand(char thisisachar) {
  delay(50);
  Serial.print(thisisachar);
  /*for(int i = 0; i < 8; i++) {
    if(thisisachar & (1 << i)) {
      Serial.print(1);
      digitalWrite(dataout, 1);
    } else {
      Serial.print(0);
      digitalWrite(dataout, 0);
    }
    pulseSRCLK();
  }*/

  /*shiftOut(dataout, SRCLK, MSBFIRST, thisisachar);
  pulseRCLK();
  delay(50);
}*/

 void setup() {
  //pinMode(dataout, OUTPUT);
  //pinMode(SRCLK, OUTPUT);
  //pinMode(RCLK, OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(RS, OUTPUT);
  pinMode(bit0, OUTPUT);
  pinMode(bit1, OUTPUT);
  pinMode(bit2, OUTPUT);
  pinMode(bit3, OUTPUT);
  pinMode(bit4, OUTPUT);
  pinMode(bit5, OUTPUT);
  pinMode(bit6, OUTPUT);
  pinMode(bit7, OUTPUT);
  
  pinMode(A0, INPUT);


  Serial.begin(9600);

  delay(1);
  RSoff();

  delay(1);
  writeCommand(0x38);
  pulseEnable();
  delay(1);
  writeCommand(0x38);
  pulseEnable();
  
  delay(1);
  writeCommand(0x0C);
  pulseEnable();
  
  delay(1);
  writeCommand(0x01);
  pulseEnable();
  
  delay(1);
  //writeCommand(0x06);
  pulseEnable();
  
  delay(1);
  writeCommand(0xC0);
  pulseEnable();
  
  RSon();
  writeString("hello world!");
  delay(500);
  Wire.begin(0x63);
  Wire.beginTransmission(0x63);
  Wire.write(0x40);
  int output = 1024;
  Wire.write(output / 16);
  Wire.write((output % 16) << 4);
  Wire.endTransmission();
  delay(10);
}

void loop() {  
  float maxv = ((float)analogRead(A2));
  float analog = ((float)analogRead(A0)/1007.00) * 4280;
  RSoff();
  delay(1);
  clearScreen();
  delay(1);
  RSon();
//  writeCommand(0x02);
//  pulseEnable();
//  delay(6);
//  writeCommand(0xC0);
//  pulseEnable();
  delay(1);
  writeString(String(analog) +  " mV");
  Serial.println(String(analog) + " mV");
  delay(200);
}

String numberstring;

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    //writeChar(inChar);
    // add it to the inputString:
    inputString += inChar;

    if(isDigit(inChar)) {
      numberstring += inChar;
      //Serial.println(inChar);
    }
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
    delay(5);

    //Serial.println("hi");
  }
    //if(inChar == '\n') {
      //Serial.println(numberstring);
      //Serial.println(inputString);
    
      int number = 0;
      /*for(int i = numberstring.length() - 1; i >= 0; i--) {
        number += atoi(numberstring[i]) * pow(10, i + 1);
        Serial.println(atoi(numberstring[i]), pow(10, i + 1));
      }*/
    //Serial.println(inputString.toInt());


    int numbertest = inputString.toInt();
    if(numbertest > -1 && numbertest < 4096) {
      Wire.begin(0x63);
      Wire.beginTransmission(0x63);
      Wire.write(0x40);
      Wire.write(numbertest / 16);
      Wire.write((numbertest % 16) << 4);
      Wire.endTransmission(); 
    }
    
    numberstring = "";
    inputString = "";
    number = 0;
      
   // }
}












