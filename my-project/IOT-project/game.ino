//คำศัพท์สำหรับสุ่ม
String randomWords[] = {
  "VITAL", "KANGAROO", "OYSTER", "INTELLIGENT", "DRUNK",  
};

String werd;
String jumble;
int lastKnob = -1;
bool lastPressState;

//จอ lcd
#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

byte underlineBitmap[] = {0x9F, 0x9F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80}; //เซตcursorของเส้นใต้
byte arrowBitmap[] = {0x84, 0x8E, 0x9F, 0x84, 0x84, 0x84, 0x80, 0x80}; //เซตลูกศรสำหรับชี้ตัวอักษร
byte underlineChar = 0; //เส้นใต้บอกตำแหน่งของตัวอักษร
byte upArrowChar = 1; //ลูกศรชี้ตำแหน่งตัวอักษรสำหรับสลับที่
//สร้างหัวใจ
byte heartChar[]={
  B00000,
  B00000,
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B00100
};
//ช.ช้าง
byte chChar[] = {
  B00000,
  B00000,
  B00001,
  B11010,
  B01100,
  B01010,
  B01010,
  B01110
};
//น. หนู
byte hnuChar[] = {
  B00000,
  B00000,
  B00000,
  B11010,
  B01010,
  B01010,
  B01111,
  B01011
};
//สระ ะ
byte aChar[] = {
  B00000,
  B00000,
  B00000,
  B11010,
  B11100,
  B00000,
  B11010,
  B11100
};

// pin input output
const byte button = 4; // Digital pin 4
const byte knob = A0;
#define pressedState LOW


void WaitForButtonPress() {
  while (digitalRead(4) != LOW) {
    delay(100);
  }
  delay(500); //กันสวิตช์คืนค่า
}
//ฟังก์ชั่น setup สำหรับสุ่มคำ
void SetupJumble() {
  randomSeed(analogRead(A0));
  jumble = werd;
  byte wordLen = jumble.length();
  for (byte i = 0; i < wordLen; i++) {
    int randomIndex = random(wordLen);
    byte tmp = jumble[i];
    jumble[i] = jumble[randomIndex];
    jumble[randomIndex] = tmp;
  }
  lcd.print(jumble);
}
//ฟังก์ชั่น setup จอlcd
void SetupLCD() {
  lcd.init();
  lcd.clear();
  lcd.setBacklight(HIGH);

  lcd.createChar(underlineChar, underlineBitmap);
  lcd.createChar(upArrowChar, arrowBitmap);
  lcd.createChar(2,heartChar);
  lcd.createChar(3,chChar);
  lcd.createChar(4,hnuChar);
  lcd.createChar(5,aChar);
}
//setup ปุ่มกด
void SetupInputs() {
  pinMode(button, INPUT_PULLUP);
}
//ฟังก์ชั่น สำหรับเช็ค serial และเรียกใช้ฟังก์ชั่นทั้งหมด
void setup() {
  Serial.begin(115200);
  SetupInputs();
  SetupLCD();
  NewGame();
}
//ฟังก์ชั่น สำหรับสลับคำจากคำที่สุ่มได้
void SwapLetters(byte index1, byte index2) {
  byte wordLen = werd.length();
  if (index1 >= 0 && index1 < wordLen && index2 >= 0 && index2 < wordLen) {
    byte letter1 = jumble[index1];
    jumble[index1] = jumble[index2];
    jumble[index2] = letter1;
    lcd.setCursor(0, 0);
    lcd.print(jumble);
  }
}
//ฟังก์ชั่น เลือกคำจาก randomwords จากบรรทักที่ 2
String PickRandomWord() {
  int numberOfRandomWords = sizeof(randomWords) / sizeof(String);
  Serial.print("numberOfRandomWords=");
  Serial.println(numberOfRandomWords);
  int randomWordIndex = random(numberOfRandomWords);
  return randomWords[randomWordIndex];
}
//ฟังก์ชั่น เริ่มเกมใหม่
void NewGame() {
  lcd.clear();
  werd = PickRandomWord();
  SetupJumble();
  lastKnob = -1;
}
//ฟังก์ชั่นแสดงผลบนหน้าจอเวลาชนะ
void Win() {
  lcd.setCursor(5, 1);
  lcd.write(byte(3));
  lcd.setCursor(6,1);
  lcd.write(byte(4));
  lcd.setCursor(7,1);
  lcd.write(byte(5));
  lcd.setCursor(10,1);
  lcd.write(byte(2));
  lcd.setCursor(9,1);
  lcd.write(byte(2));
  if (digitalRead(button) == pressedState) NewGame();
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  if (digitalRead(button) == pressedState) NewGame();
  delay(500);
}
//ฟังก์ชั่นใช้ตัวต้านทานปรับค่าได้เพื่อขยับ cursor
void KnobArrow() {
  bool isPressed = digitalRead(button) == pressedState;
  bool pressChanged = isPressed != lastPressState;
  if (!isPressed && jumble == werd) Win();

  int knobValue = map(analogRead(knob), 0, 1023, 0, 15);
  bool knobMoved = knobValue != lastKnob;
  if (knobMoved || pressChanged) {
    if (lastKnob != -1) {
      lcd.setCursor(lastKnob, 1);
      lcd.write(' ');
      if (isPressed) {
        SwapLetters(knobValue, lastKnob);
      }
    }
    lcd.setCursor(knobValue, 1);
    byte cursorChar = isPressed ? upArrowChar : underlineChar;
    lcd.write(cursorChar);
    lastKnob = knobValue;
    lastPressState = isPressed;
  }
  delay(50);
}

void loop() {
  KnobArrow();
}
