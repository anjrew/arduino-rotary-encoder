volatile int encoderPos = 0;
volatile int lastEncoded = 0;
const int pinA = 2; // Yellow wire, Channel A (CLK)
const int pinB = 3; // Blue wire, Channel B (DT)
volatile bool expectedAHigh = 0; // If true line A was expected high

void setup() {
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinA), updatePinA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), updatePinB, CHANGE);
  Serial.begin(9600);
}

void loop() {
  // Serial.println(encoderPos);
  delay(100);
}

void updatePinA() {
  Serial.println("Line A changed");
}

void updatePinB() {
  Serial.println("Line B changed");
}

void updateEncoder() {
  // Read both channels
  int MSB = digitalRead(pinA);  // most significant bit
  int LSB = digitalRead(pinB);  // least significant bit
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;
  
  // Determine rotation direction using a state transition table:

  lastEncoded = encoded;

  bool incrementing = encoderPos > lastEncoded;

  if (incrementing)
  {
    encoderPos++;
  }
  else
  {
     encoderPos--;
  }


  Serial.print("Position: ");
  Serial.println(encoderPos);
  Serial.print("MSB: ");
    Serial.print(MSB);
    Serial.print(", LSB: ");
    Serial.print(LSB);
    Serial.print(", encoded: ");
    Serial.print(encoded);
    Serial.print(", sum: ");
    Serial.println(sum);
    if(encoderPos > lastEncoded) Serial.println("Incrementing position");
    else if(encoderPos < lastEncoded) Serial.println("Decrementing position");
}