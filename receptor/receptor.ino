const int sensorPin = 4;  // select the input pin for ldr
int sensorValue = 0;      // variable to store the value coming from the sensor
int a, f;                 // flags

void setup() {
  Serial.begin(115200);  //sets serial port for communication
}
void loop() {

  sensorValue = analogRead(sensorPin);  // read the value from the sensor
  if (sensorValue > 1000)               // calculating the number of dots and dashes
  {
    for (int i = 0; i <= 13; i++) {
      sensorValue = analogRead(sensorPin);
      if (sensorValue > 1000) {
        a++;  //calculating the number of dots and dashes in the character
        delay(200);
      } else {
        f++;  // calculating the number of spaces in dots and dashes
        delay(200);
      }
    }
  }

  //Checking the set of dots, dashes and spaces

  if (a == 4 && f == 10) {
    Serial.print("A");
  }
  if (a == 6 && f == 8) {
    Serial.print("B");
  }
  if (a == 8 && f == 6) {
    Serial.print("C");
  }
  if (a == 5 && f == 9) {
    Serial.print("D");
  }
  if (a == 1 && f == 13) {
    Serial.print("E");
  }
  if (a == 2 && f == 12) {
    Serial.print("I");
  }
  if (a == 10 && f == 4) {
    Serial.print("J");
  }
  if (a == 7 && f == 7) {
    Serial.print("G");
  }
  if (a == 9 && f == 5) {
    Serial.print("O");
  }
  if (a == 3 && f == 11) {
    Serial.print("S");
  }
  f = a = 0;
  delay(200);
}

// Verificador de que el LDR funcione
/* #define LDR 4

void setup() {
  Serial.begin(9600);
  delay(1000);
  }

void loop(){
  int LDR_val = analogRead(LDR);
  Serial.println(LDR_val);
  delay(200);
} */
