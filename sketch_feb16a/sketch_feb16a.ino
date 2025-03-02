volatile int encoderPos = 0;       // counts the number of detents (steps)
volatile int lastEncoded = 0;      // holds previous encoder state

const int pinA = 2;                // encoder channel A (CLK)
const int pinB = 3;                // encoder channel B (DT)

void setup() {
  pinMode(pinA, INPUT_PULLUP);     // use internal pull-ups
  pinMode(pinB, INPUT_PULLUP);
  Serial.begin(9600);
  
  // Attach interrupts to both encoder pins.
  attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), updateEncoder, CHANGE);
}

void loop() {
  // Print the current encoder position every 100ms.
  Serial.print("Position: ");
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
