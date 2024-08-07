#include <EasyMFRC522.h>
#include <RfidDictionaryView.h>

//Tech Trends Shameer
//RFID Security System with LCD  

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

 
#define SS_PIN 10
#define RST_PIN 9
 
#define LED_G 5 // define green LED pin
#define LED_R 4 // define red LED pin

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

LiquidCrystal_I2C lcd(0x27, 16, 2); 
void setup() 
{
  
 // pinMode(buzzer, OUTPUT);
 lcd.print("alskdj");
  pinMode(LED_G, OUTPUT);
pinMode(LED_R, OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.begin(16, 2);


  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Tech Trends");
  lcd.setCursor(5,1);
  lcd.print("Shameer");
  delay(3000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("RFID Security");
  lcd.setCursor(5,1);
  lcd.print("System");
  delay(3000);
  display();
}
void loop() 
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
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "83 C1 F0 FA") //Change the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
     digitalWrite(LED_G, HIGH);
     digitalWrite(LED_R, LOW);
    lcd.clear();
    lcd.print("Authorized Access");
    delay(3000);
    lcd.clear();
    digitalWrite(LED_G, LOW);
    display();
  }
  else if (content.substring(1) == "41 FE 6C 1C") //Change the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access - Astik Raj");
    Serial.println();
     digitalWrite(LED_G, HIGH);
     digitalWrite(LED_R, LOW);
    lcd.clear();
    lcd.print("Authorized Access");
    delay(3000);
    lcd.clear();
    digitalWrite(LED_G, LOW);
    display();
  }
  else if (content.substring(1) == "41 D4 14 1C") //Change the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access - V Sai Tarun");
    Serial.println();
     digitalWrite(LED_G, HIGH);
     digitalWrite(LED_R, LOW);
    lcd.clear();
    lcd.print("Authorized Access");
    delay(3000);
    lcd.clear();
    digitalWrite(LED_G, LOW);
    display();
  }
  else if (content.substring(1) == "31 9D 26 1C") //Change the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access - Smaran Lal Shreshta");
    Serial.println();
     digitalWrite(LED_G, HIGH);
     digitalWrite(LED_R, LOW);
    lcd.clear();
    lcd.print("Authorized Access");
    delay(3000);
    lcd.clear();
    digitalWrite(LED_G, LOW);
    display();
  }
  else if (content.substring(1) == "31 66 93 1C") //Change the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access - Anagha Burli");
    Serial.println();
     digitalWrite(LED_G, HIGH);
     digitalWrite(LED_R, LOW);
    lcd.clear();
    lcd.print("Authorized Access");
    delay(3000);
    lcd.clear();
    digitalWrite(LED_G, LOW);
    display();
  }
   else if (content.substring(1) == "31 48 3B 1C") //Change the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access - Shivam Ji");
    Serial.println();
     digitalWrite(LED_G, HIGH);
     digitalWrite(LED_R, LOW);
    lcd.clear();
    lcd.print("Authorized Access");
    delay(3000);
    lcd.clear();
    digitalWrite(LED_G, LOW);
    display();
  }
 
 else   {
    Serial.println(" Access denied");
  
    lcd.clear();
   
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    lcd.print("Access denied");
    
    delay(3000);
    lcd.clear();
   
    digitalWrite(LED_R, LOW);
    display();

      
  }
} 

void display()
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Swipe the Card");
}