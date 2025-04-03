volatile int encoderPos = 0;
volatile int lastEncoded = 0;

// Pick pins carefully only  pins 0,1,2,3,7 can be used as interrupts
// Pins 2/3 are also the only pins used for I2C
// Pins 0/1 are also the only pins to be used as RX/TX UART
// const int pinA = 2; // SDA Yellow wire, Channel A (CLK)
// const int pinB = 3; // SCL Blue wire, Channel B (DT)
const int pinA = 1; // TX Yellow wire, Channel A (CLK)
// const int pinB = 0; // // Zero does not seem to work RX  Blue wire, Channel B (DT)
const int pinB = 7; // // Zero does not seem to work RX  Blue wire, Channel B (DT)

//int count = 1;

void setup() {
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(pinA), updatePinA, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(pinB), updatePinB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), updateEncoder, CHANGE);
  Serial.begin(9600);
}

void loop() {
  Serial.println(encoderPos);
  // Serial.println("IN LOOP");
  // Serial.println(count);
  // count ++;
  delay(10);
}

// void updatePinA()
// {
//   Serial.println("A Updated");
// }

// void updatePinB()
// {
//   Serial.println("B Updated"); 
// }

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