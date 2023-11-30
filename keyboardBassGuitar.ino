#include <Keyboard.h>

int buttonPins[12] = {A5, A4, 12, 11, 9, 8, 7, 6, 5, 4, 3, 2};
const int triggerButtonPin = A0;
const int octaveUpButtonPin = A3;
const int octaveDownButtonPin = A2;

boolean buttonState = false;

static boolean trig[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
boolean buttonStates[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int triggerVal = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Keyboard.begin();

  pinMode(octaveUpButtonPin, INPUT);
  digitalWrite(octaveUpButtonPin, HIGH);
  pinMode(octaveDownButtonPin, INPUT);
  digitalWrite(octaveDownButtonPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  changeOctave();
  typeNote(97, 0);
  typeNote(119, 1);
  typeNote(115, 2);
  typeNote(101, 3);
  typeNote(100, 4);
  typeNote(102, 5);
  typeNote(116, 6);
  typeNote(103, 7);
  typeNote(121, 8);
  typeNote(104, 9);
  typeNote(117, 10);
  typeNote(106, 11);
}

void typeNote(int key, int index) {
  buttonStates[index] = digitalRead(buttonPins[index]);
  triggerVal = analogRead(triggerButtonPin);

  if (buttonStates[index] == true) {
    trig[index] = true;
    if (triggerVal > 700 || triggerVal < 400) {
      delay(20);
      Keyboard.press(key);
      Keyboard.press(KEY_TAB);
    }
    else {
      Keyboard.release(97);
      Keyboard.release(119);
      Keyboard.release(115);
      Keyboard.release(101);
      Keyboard.release(100);
      Keyboard.release(102);
      Keyboard.release(116);
      Keyboard.release(103);
      Keyboard.release(121);
      Keyboard.release(104);
      Keyboard.release(117);
      Keyboard.release(106);

    }
  }

  else {
    Keyboard.release(97);
    Keyboard.release(119);
    Keyboard.release(115);
    Keyboard.release(101);
    Keyboard.release(100);
    Keyboard.release(102);
    Keyboard.release(116);
    Keyboard.release(103);
    Keyboard.release(121);
    Keyboard.release(104);
    Keyboard.release(117);
    Keyboard.release(106);
  }

  if (buttonStates[index] == false && trig[index] == true) {
    Keyboard.release(KEY_TAB);
    trig[index] = false;
  }
}

void changeOctave() {
  if (digitalRead(octaveUpButtonPin) == false) {
    Keyboard.press(120);
  }
  else {
    Keyboard.release(120);
  }
  
  if (digitalRead(octaveDownButtonPin) == false) {
    Keyboard.press(122);
  }
  else {
    Keyboard.release(122);
  }
}
