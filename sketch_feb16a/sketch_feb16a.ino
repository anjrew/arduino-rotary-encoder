volatile int encoderPos = 0;
volatile int lastEncoded = 0;
const int pinA = 2; // Yellow wire, Channel A (CLK)
const int pinB = 3; // Blue wire, Channel B (DT)

void setup() {
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), updateEncoder, CHANGE);
  Serial.begin(9600);
}

void loop() {
  // Serial.println(encoderPos);
  delay(100);
}

void updateEncoder() {
  // Read both channels
  int MSB = digitalRead(pinA);  // most significant bit
  int LSB = digitalRead(pinB);  // least significant bit
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;
  

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