#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53  
#define RST_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int state = 0;
int solenoidPin = 9;
void setup() 
{
  pinMode(solenoidPin, OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  Serial2.begin(115200);
  Serial3.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put RFID Card to Scan of input password.");
  Serial.println();
}
void loop() 
{
  if (Serial3.available())
  {
    char out = Serial3.read();
    if(out=='o')
    {
      state = 0;
      Serial2.write(state);
      Serial.println(" right password. Access Granted ");
      digitalWrite(solenoidPin, LOW);
      delay(50);
      digitalWrite(solenoidPin, HIGH);
    }
    else if(out=='x')
    {
      state = 1;
      Serial2.write(state);
      Serial.println(" wrong password. Access Denied ");
      delay(5000);
    }
  }

  else
  {
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      return;
    }
    //Show UID on serial monitor
    Serial.println();
    Serial.print(" UID tag :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
       content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    Serial.println();
    
    if (content.substring(1) == "93 4C 7B 0C") //change UID of the card that you want to give access
    {
      state = 0;
      Serial2.write(state);
      Serial3.write('a');
      Serial.println(" Access Granted ");
      delay(1000);
      Serial.println(" Welcome. Have FUN. ");
      digitalWrite(solenoidPin, LOW);
      delay(50);
      digitalWrite(solenoidPin, HIGH);
    } else {
      state = 1;
      Serial2.write(state);
      Serial3.write('b');
      Serial.println(" Access Denied ");
      delay(3000);
    }
  }
} 
