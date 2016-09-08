#include <avr/pgmspace.h> // allows use of PROGMEM to store patterns in flash

#define CUBESIZE 4
#define PLANESIZE CUBESIZE*CUBESIZE
#define PLANETIME 3333 // time each plane is displayed in us -> 100 Hz refresh
#define TIMECONST 5 // multiplies DisplayTime to get ms 

/*
** Defining pins in array makes it easier to rearrange how cube is wired
** Adjust numbers here until LEDs flash in order - L to R, T to B
** Note that analog inputs 0-5 are also digital outputs 14-19!
** Pin DigitalOut0 (serial RX) and AnalogIn5 are left open for future apps
*/

int LEDPin[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
int LEDPinCount = 16;
int PlanePin[] = {16, 17, 18, 19};
int PlanePinCount  = 4;

// initialization
void setup()
{
  int pin; // loop counter
  // set up LED pins as output (active HIGH)
  for (pin = 0; pin < PLANESIZE; pin++) {
    pinMode( LEDPin[pin], OUTPUT );
  }
  // set up plane pins as outputs (active LOW)
  for (pin = 0; pin < CUBESIZE; pin++) {
    pinMode( PlanePin[pin], OUTPUT );
  }
}

void loop() {
  loopFor();
}

// the principles of using 4 planes and 16 pins - here we loop over each, turning on and off in turn
void loopFor()
{
  for (int thisPlane = 0; thisPlane < PlanePinCount; thisPlane++) {
    for (int thisPin = 0; thisPin < LEDPinCount; thisPin++) {

      planesOff();
      digitalWrite(LEDPin[thisPin], HIGH);
      digitalWrite(PlanePin[thisPlane], LOW);

      delay(50);

      digitalWrite(LEDPin[thisPin], LOW);
      digitalWrite(PlanePin[thisPlane], HIGH);

    }
  }
}

void planesOff() {
  for (int thisPlane = 0; thisPlane < PlanePinCount; thisPlane++) {
    digitalWrite(PlanePin[thisPlane], HIGH);
  }
}

