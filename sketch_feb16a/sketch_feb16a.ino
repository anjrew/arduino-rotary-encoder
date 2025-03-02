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
  Serial.println(encoderPos);
  delay(100);
}

void updateEncoder() {
  // Read both channels
  int MSB = digitalRead(pinA);  // most significant bit
  int LSB = digitalRead(pinB);  // least significant bit
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;
  
  // Determine rotation direction using a state transition table:
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    encoderPos++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    encoderPos--;
    
  lastEncoded = encoded;
}