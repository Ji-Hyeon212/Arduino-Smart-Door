#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal.h>


DFRobotDFPlayerMini MP3Player;
SoftwareSerial MP3Module(19,18);

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

int button_1 = 13;
int button_2 = 12;
int button_3 = 11;
int button_4 = 10;
int button_5 = 9;
int button_6 = 8;
int button_7 = 7;
int button_8 = 6;
int button_9 = 5;
int button_0 = 3;
int button_reset = 4;
int button_enter = 2;

String input = "";
String answer = "1234";

int state_enter = 1;
int position = 4;

char data;

void setup() {

  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  pinMode(button_3, INPUT);
  pinMode(button_4, INPUT);
  pinMode(button_5, INPUT);
  pinMode(button_6, INPUT);
  pinMode(button_7, INPUT);
  pinMode(button_8, INPUT);
  pinMode(button_9, INPUT);
  pinMode(button_0, INPUT);
  pinMode(button_enter, INPUT);
  pinMode(button_reset, INPUT);
  
  Serial.begin(9600);
  Serial3.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Entering...");
  lcd.setCursor(0,1);
  lcd.print("Key:");
  lcd.setCursor(position, 1);

  MP3Module.begin(9600);
  MP3Player.begin(MP3Module);
  MP3Player.volume(1);

}

void loop() {
  while(state_enter) {
    data = Serial3.read();
    if(!digitalRead(button_1)){
      input = input + "1";
      lcd.write('1');
      position++;
      lcd.setCursor(position, 1);
      while(!digitalRead(button_1)){;}
    }
     else if(!digitalRead(button_2)){
      input = input + "2";
      lcd.write('2');
      position++;
      lcd.setCursor(position, 1);
      while(!digitalRead(button_2)){;}
    }
     else if(!digitalRead(button_3)){
      input = input + "3";
      lcd.write('3');
      position++;
      lcd.setCursor(position, 1);
      while(!digitalRead(button_3)){;}
    }
     else if(!digitalRead(button_4)){
      input = input + "4";
      lcd.write('4');
      position++;
      lcd.setCursor(position, 1);
      while(!digitalRead(button_4)){;}
    }
     else if(!digitalRead(button_5)){
      input = input + "5";
      lcd.write('5');
      position++;
      lcd.setCursor(position, 1);
      while(!digitalRead(button_5)){;}
    }
     else if(!digitalRead(button_6)){
      input = input + "6";
      lcd.write('6');
      position++;
      lcd.setCursor(position, 1);
      while(!digitalRead(button_6)){;}
    }
     else if(!digitalRead(button_7)){
      input = input + "7";
      lcd.write('7');
      position++;
      lcd.setCursor(position, 1);
      while(!digitalRead(button_7)){;}
    }
     else if(!digitalRead(button_8)){
      input = input + "8";
      lcd.write('8');
      position++;
      lcd.setCursor(position, 1);
      while(!digitalRead(button_8)){;}
    }
     else if(!digitalRead(button_9)){
      input = input + "9";
      lcd.write('9');
      position++;
      lcd.setCursor(position, 1);
      while(!digitalRead(button_9)){;}
    }
    else if(!digitalRead(button_0)){
      input = input + "0";
      lcd.write('0');
      position++;
      lcd.setCursor(position, 1);
      while(!digitalRead(button_0)){;}
    }
    else if(!digitalRead(button_enter)) state_enter = 0;
    else if(!digitalRead(button_reset)){
      input = "";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Entering...");
      lcd.setCursor(0,1);
      lcd.print("Key:");
      position = 4;
      lcd.setCursor(position, 1);
    }
    else if((data == 'a') || (data == 'b'))state_enter = 0;
    delay(100);
  }
   Serial.println(input);
   if((input.equals(answer)) || (data == 'a')){
     Serial.println("pass");
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Pass!!");
     Serial.print(10);
     Serial3.write('o');
     while(!state_enter){
      if(!digitalRead(button_reset))
      state_enter= 1;
      }
   }
   else if((!input.equals(answer)) || (data == 'b')){
     Serial.println("Fail");
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Fail!!");
     Serial3.write('x');
     Serial.print(11);
     MP3Player.play(1);
     while(!state_enter){
      if(!digitalRead(button_reset))
      state_enter = 1;
      }
   }
}
