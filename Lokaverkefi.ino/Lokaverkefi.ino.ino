
// Define pins for ultrasonic and buzzer
int const trigPin = 3;
int const echoPin = 2;
int const buzzPin = 1;

#include <Servo.h> // Sambærilegt og import í python

Servo motor; // bý til tilvik af Servo klasanum
int motor_pinni = 4; // pinninn sem ég nota til að stjórna mótornum
int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};

int tempo = 300;
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzPin, LOW);
    delayMicroseconds(tone);
  }
}
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
    motor.attach(motor_pinni); // segi servo tilvikinu hvaða pinna á að nota
    pinMode(trigPin, OUTPUT); // trig pin will have pulses output
    pinMode(echoPin, INPUT); // echo pin should be input to get pulse width
    pinMode(buzzPin, OUTPUT); // buzz pin is output to control buzzering
}

void loop()
{
    // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
    int duration, distance;
    // Output pulse with 1ms width on trigPin
    digitalWrite(trigPin, HIGH); 
    delay(1);
    digitalWrite(trigPin, LOW);
    // Measure the pulse input in echo pin
    duration = pulseIn(echoPin, HIGH);
    // Distance is half the duration devided by 29.1 (from datasheet)
    distance = (duration/2) / 29.1;
    // if distance less than 0.5 meter and more than 0 (0 or less means over range) 
    if (distance <= 100) {
      // Buzz
              for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
    delay(tempo / 2); 
  }

      
      motor.write(0); 
  } else {
      // Don't buzz
      digitalWrite(buzzPin, LOW);
      motor.write(60); // mótorinn fer lengst til vinstri
      delay(1000);
      motor.write(0); // mótorinn fer í miðjuna
      delay(1000);
      motor.write(160); // mótorinn fer lengst til hægri
      delay(1000);
    }
}
