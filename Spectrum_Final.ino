//Code for Sparkfun Spectrum Analyzer with LED's lights in PWN pin's on Arduino UNO
//Credit to https://www.baldengineer.com/msgeq7-simple-spectrum-analyzer.html for the base of the code
#define RESET 5
#define Strobe 4
#define DCout 0
const int LEDpins[7] = {3,11,6,9,9,10,10};  // Here is where to assign LED's to certain Pin's 
//Pins ranging from (63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 6.25kHz, 16kHz)


void setup() {                

  for (int x=0; x<7; x++) {
    pinMode(LEDpins[x], OUTPUT);
  }
  pinMode(RESET, OUTPUT);
  pinMode(Strobe, OUTPUT);
}

void loop() {
  digitalWrite(RESET, HIGH);      // reset the MSGEQ7's counter
  delay(15);
  digitalWrite(RESET, LOW);

  for (int x = 0; x < 7; x++){
    digitalWrite(Strobe, LOW);    // output each DC value for each freq band
    delayMicroseconds(35); // to allow the output to settle
    int spectrumRead = analogRead(DCout);

    int PWMvalue = map(spectrumRead, 0, 1024, 0, 255);  // scale analogRead's value to Write's 255 max
    if (PWMvalue < 60)
      PWMvalue = PWMvalue /25;    //Noise Filter,LEDs turn off at low levels

    analogWrite(LEDpins[x], PWMvalue);
    digitalWrite(Strobe, HIGH);
  }
}
