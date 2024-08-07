
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
const int ledPin = 5;  // LED connected to digital pin 13
const int ledP=4;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledP, OUTPUT); // initialize the digital pin as an output
  while (!Serial);
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  lcd.init();            // initialize the LCD
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("IDS OFFICE");
  delay(3000);
  lcd.setCursor(1, 0);
  lcd.print("Fingerprint id");
  lcd.setCursor(4, 1);
  lcd.print(" sensor");

  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  } else {
    Serial.println("Waiting for a valid finger...");
    Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
}

void loop() {
  if (finger.getImage() == FINGERPRINT_OK) {
    getFingerprintID();
    delay(1000); // Optional delay to avoid repeated prints for the same fingerprint
  }
}

uint8_t getFingerprintID() {
  uint8_t p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    Serial.print("Found ID #"); Serial.print(finger.fingerID);
    Serial.print(" with confidence of "); Serial.println(finger.confidence);

    // Display fingerprint information on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Finger ID: ");
    lcd.print(finger.fingerID);
    lcd.setCursor(0, 1);
   /* lcd.print("Confidence: ");
    lcd.print(finger.confidence);*/
    if(finger.fingerID==2)
    {
      lcd.print("Astik Raj");
    }
    if(finger.fingerID==3)
    {
      lcd.print("V Sai Tarun");
    }
    if(finger.fingerID==8)
    {
      lcd.print("Smaran Lal");
    }

    // Turn on the LED for 3 seconds
    digitalWrite(ledPin, HIGH);
    delay(3000);
    digitalWrite(ledPin, LOW);

    // Clear the LCD after 3 seconds
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Fingerprint id");
    lcd.setCursor(0, 1);
    lcd.print("     sensor     ");
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");

    // Display "Did not match" message on LCD
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print(" Fingerprint");
    lcd.setCursor(1, 1);
    lcd.print("Did not match");
    digitalWrite(ledP,HIGH);
    delay(3000);
    digitalWrite(ledP,LOW);

    // Clear the LCD after 3 seconds
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Fingerprint id");
    lcd.setCursor(0, 1);
    lcd.print("     sensor     ");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  return finger.fingerID;
}