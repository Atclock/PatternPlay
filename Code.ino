#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

byte switches[5]= {2,3,4,5,6};
byte redLights[5]= {7,8,9,10,11};
byte greenLights[5]= {12,13,A0,A1,A3};
byte buzzer = A2;
// index 0 for Nose
// index 1 for Right Hand
// index 2 for Right Leg
// index 3 for Left Leg
// index 4 for Left Hand
byte sequence[5];
byte memory[5];
byte level=1;
int COUNTER=0;
bool correct;
int tonesFreq[5] = {262,330,392,523,659};
unsigned long startTime;
unsigned long endTime;
unsigned long duration[5];
unsigned long sum = 0;
unsigned long average = 0;
byte roundIndex = 0;


void setup() {

   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED init failed!"));
    while (true);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  displayMessage("Starting new game");
  
  for (byte i = 0; i < 5; i++) {
    pinMode(switches[i], INPUT_PULLUP);
    pinMode(redLights[i], OUTPUT);
    pinMode(greenLights[i], OUTPUT);
  }
  pinMode(buzzer, OUTPUT);



  for (byte i = 0; i < 5; i++) {
    tone(buzzer, tonesFreq[i], 400);
    setColor(i, 255, 0);
    delay(300);
    setColor(i, 0, 0);
  }
 
    for (byte i = 0; i < 5; i++) {
    sequence[i] = random(0, 5);
    memory[i] = 6;
  }
  delay(1000);
}

void loop() {
  
  correct = true;
  
  showSequence(level);

  startTime = millis();

  for (byte i = 0; i < level; i++) {
    memory[i] = waitForPress();  

    if (memory[i] != sequence[i]) {
      correct = false;
      break;
    }
  }
   endTime = millis();
   unsigned long Taken = endTime-startTime;

  if (correct) {
    successFlash(level);

    duration[roundIndex] = Taken;
    roundIndex++;
    
    level++;
    if (level > 5) {
    for (byte i = 0; i < 5; i++) {
      sequence[i] = random(0, 5);
      memory[i] = 6;
  }

    for (byte i=0; i<5 ; i++)
      sum += duration[i];
      average = sum / 5;
      COUNTER++;
  showResultsScreen(average,COUNTER);
      level = 1;       
    }

  } else {
    errorFlash(level);
    level = 1;
  }
  delay(700);
}

void setColor(byte i, byte greenValue, byte redValue) {
  analogWrite(greenLights[i], 255 - greenValue);
  analogWrite(redLights[i], 255 - redValue);
}

byte waitForPress() {
  
  while (true) {
  
    for (byte i = 0; i < 5; i++) {
      if (digitalRead(switches[i]) == LOW) {
        delay(50);                            
        while (digitalRead(switches[i]) == LOW);
        return i;
      }
    }
  }
}

void showSequence(byte upTo) {
  for (byte i=0;i<upTo;i++) {

    byte index = sequence[i];

    setColor(index, 255, 0);                    
    tone(buzzer, tonesFreq[index], 500);       
    delay(500);

    setColor(index, 0, 0);                      
    delay(200);
  }
}

void displayMessage(const char* msg) {
  display.clearDisplay();
  display.setCursor(0, 20);
  display.println(msg);
  display.display();
}

void successFlash(byte count) {
  for (byte i = 0; i < count; i++) {
    setColor(sequence[i], 255, 0);
  }
  delay(1000);
  for (byte i = 0; i < count; i++) {
    setColor(sequence[i], 0, 0);
  }
}

void errorFlash(byte count) {
  for (byte i = 0; i < count; i++) {
    setColor(sequence[i], 0, 255);
  }
  tone(buzzer,100,1000);
  delay(1000);
  for (byte i = 0; i < count; i++) {
    setColor(sequence[i], 0, 0);
  }
  COUNTER = 0;
  display.clearDisplay();
  display.print(COUNTER);
  display.display();
  
}
void showResultsScreen(unsigned long avgTime, int COUNTER) {
  display.clearDisplay();

  // Title cuz why not lwk that looks awesome (I will never be able to test it they took my stuff)
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 2);    
  display.println("Results");

  // Line under title
  display.drawLine(0, 22, 127, 22, SSD1306_WHITE);

  // Average time counter
  display.setTextSize(1);
  display.setCursor(5, 28);
  display.println("Average Time:");

  display.setTextSize(2);
  display.setCursor(5, 40);
  display.print(avgTime);
  display.print(" ms");

  // Streak Counter
  display.setTextSize(1);
  display.setCursor(5, 58);
  display.print("Streak: ");

  display.setTextSize(1);
  display.print(COUNTER);

  display.display();
}
