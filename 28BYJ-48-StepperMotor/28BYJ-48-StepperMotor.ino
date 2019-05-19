// Arduino stepper motor control code

#include <Stepper.h> // Include the header file

// Define Variables
// ########################################

// Number of Revolutions Required
float RevolutionsRequired = 15;

// Speed of Motor
int vel = 1200;

// Variable that is entered via Serial Port. 1 for elevating, 2 for descending.
int val;

// Variable that checks which was the last entry.
int counter_check;
// ########################################

// Number of steps per internal motor revolution
const float STEPS_PER_REV = 32;

// Amount of Gear Reduction
const float  GEAR_RED = 64;

// Number of stepts per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;

// Number of Steps required
float STEPS = RevolutionsRequired * STEPS_PER_OUT_REV;

// create an instance of the stepper class using the steps and pins
Stepper stepper(STEPS_PER_REV, 8, 10, 9, 11); // Defines steps and pins


void setup() {
  Serial.begin(9600);
  stepper.setSpeed(vel);
}


void loop() {
  if (Serial.available())
  {
    val = Serial.parseInt();

    Serial.println(val);
    if (val == 1 && counter_check != 1)
    {
      stepper.step(STEPS);
      counter_check = val;
    }

    else if (val == 2 && counter_check != 2)
    {
      stepper.step(-STEPS);
      counter_check = val;
    }
    Serial.println(counter_check);
  }
}
