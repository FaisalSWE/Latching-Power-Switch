const int buttonPin = 2;
const int latchPin = 5;
const int pwmPin = 9;

const unsigned long onDuration = 10000;
const unsigned long offDuration = 5000;
unsigned long lastButtonPress = 0;
bool isPowered = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  digitalWrite(latchPin, LOW);
  analogWrite(pwmPin, 0);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && !isPowered) {
    isPowered = true;
    lastButtonPress = millis();
    digitalWrite(latchPin, HIGH);
    analogWrite(pwmPin, 64);
    Serial.println("Power ON");
  }
  if (isPowered && millis() - lastButtonPress >= onDuration) {
    digitalWrite(latchPin, LOW);
    analogWrite(pwmPin, 0);
    isPowered = false;
    lastButtonPress = millis();
    Serial.println("Power OFF");
  }
  if (!isPowered && millis() - lastButtonPress >= offDuration) {
    isPowered = true;
    lastButtonPress = millis();
    digitalWrite(latchPin, HIGH);
    analogWrite(pwmPin, 64);
    Serial.println("Auto Power ON");
  }
}
