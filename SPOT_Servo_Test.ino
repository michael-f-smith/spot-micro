/*
 * Spot_Servo_Testing
 * Michael Smith
 * January 14th, 2022
 * 
 */

#include <Servo.h>
# define SPACE 32
// Front Right Servos (0)
Servo servoFR1;  // create servo object to control a servo
Servo servoFR2;
Servo servoFR3;

// Back Right Servos (1)
Servo servoBR1;
Servo servoBR2;
Servo servoBR3;

// Back Left Servos (2)
Servo servoBL1;
Servo servoBL2;
Servo servoBL3;

// Front Left Servos (3)
Servo servoFL1;
Servo servoFL2;
Servo servoFL3;

// Additional servo objects
Servo testServo;

// Function Declarations
void attachArdPins();
void attachEspPins();
void testPos();
void restPos();
void servoWrite(int,int); // This function can be used to  individually move one servo at a time (the first number is the leg joint number, the second is the leg number
void jump();
void layDown();
void shake();
void sit();
void stand();
void waitForThisChar(char);
void testJoint(int);
void moveForward();
void kneel();
void foldedKneel();
void kneel2Stand();
void preStand();
void kneel2();
void preKneel();
void preStand2();
void standLBL();
void standLBR();

// Variables
int pins[4][3] = {2,3,4,5,6,7,8,9,10,11,12,13}; // pins[leg number][joint number - 1]
const int J1 = 0;   // Joint 1 is zero
const int J2 = 1;   // Joint 2 is one
const int J3 = 2;   // Joint 3 is two
const int LFR = 0;
const int LBR = 1;
const int LBL = 2;
const int LFL = 3;


// Could make matrices holding each of the three states: open, mid, and closed

//////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);     // Open the serial port at 9600 bps
  attachArdPins();        // Turn on all servos \ 
  //attachEspPins();        // Turn on all servos / uncomment one of these depending on the board
  //layDown();
  //stand();
  //moveForward();
  //servoWrite(pins[LFR][J3],90);
  //delay(1000);
  //  servoWrite(pins[LFL][J3],90);    // Increasing LBL J3 angles raises leg
   //delay(1000);
    //servoWrite(pins[LFL][J3],90);    // Increasing LBR, J3 angle lowers leg

}

//////////////////////////////////////////////////////////////////////////////////////////////////
void loop() 
{  
    preKneel();    //kneel2Stand();
  //kneel2();
  delay(4000);

  kneel();
  delay(4000);
  standLBL();
  delay(4000);

    //testPos();
    //restPos();
    //testJoint(pins[LBR][J2]);
    //restPos();
    //layDown();
    //stand();
    //foldedKneel();
    Serial.println("Looping");
}
//////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////
//////////////////////////////////////////////
// Functions
//////////////////////////////////////////////
//////////////////////////////////////////////

// moveForward()
void moveForward()
{
    Serial.println("Lay");
  servoFR1.write(90);  // Front Right Bottom
  servoFR2.write(110);  // Front Right Middle
  servoFR3.write(170);    // Front Right Shoulder
  
  servoBR1.write(40);
  servoBR2.write(65);
  servoBR3.write(0);
  
  servoBL1.write(140);    // This one needs to be recalibrated like the BR1
  servoBL2.write(80);
  servoBL3.write(60);   /// <---------------------------------------------------------------
  
  servoFL1.write(160);
  servoFL2.write(90);
  servoFL3.write(160);
}



// Attach all servos to Arduino Mega pins
void attachArdPins()
{
  servoFR1.attach(2);  // attaches the servo on pin 9 to the servo object
  servoFR2.attach(3);  // attaches the servo on pin 9 to the servo object
  servoFR3.attach(4);
  servoBR1.attach(5);
  servoBR2.attach(6);
  servoBR3.attach(7);
  servoBL1.attach(8);
  servoBL2.attach(9);
  servoBL3.attach(10);
  servoFL1.attach(11);
  servoFL2.attach(12);
  servoFL3.attach(13);
}

// Look up PWM Pins on ESP32 and configure the following respectively
void attachEspPins()
{
  servoFR1.attach(2);  // attaches the servo on pin 9 to the servo object
  servoFR2.attach(3);  // attaches the servo on pin 9 to the servo object
  servoFR3.attach(4);
  servoBR1.attach(5);
  servoBR2.attach(6);
  servoBR3.attach(7);
  servoBL1.attach(8);
  servoBL2.attach(9);
  servoBL3.attach(10);
  servoFL1.attach(11);
  servoFL2.attach(12);
  servoFL3.attach(13);
}

// This sets the positions of the robot to the rest position
void restPos()
{
  servoFR1.write(180);  // Front Right Bottom
  servoFR2.write(180);  // Front Right Middle
  servoFR3.write(170);    // Front Right Shoulder
  servoBR1.write(180);
  servoBR2.write(150);
  servoBR3.write(0);
  servoBL1.write(0);    // This one needs to be recalibrated like the BR1
  servoBL2.write(0);
  servoBL3.write(0);
  servoFL1.write(0);
  servoFL2.write(0);
  servoFL3.write(170);
}


void waitForThisChar(char C)
{
  while(true) // remain here until told to break
  {
    if(Serial.available() > 0) 
    {// did something come in?
      char readChar = Serial.read();
      Serial.print(readChar);
      Serial.println(" was pressed.");
    
      if(readChar == C) // is that something the char G?
      {
        break;
      }
    }
  }
}


// This function helps to test one joint at 0, 90 and 180 degrees
void testJoint(int pin)
{
    Serial.println("Angle: 90");
    servoWrite(pin,90);  // [leg number][joint number - 1]
    Serial.print("Waiting for key press G");
    waitForThisChar('G');                       // Try this with the spacebar
    Serial.println("After key press");
    Serial.println("Angle: 0");
    servoWrite(pin,0);  // [leg number][joint number - 1]
    Serial.print("Waiting for key press G");
    waitForThisChar('G');                       // Try this with the spacebar
    Serial.println("After key press");
    Serial.println("Angle: 180");
    servoWrite(pin,180);  // [leg number][joint number - 1]
    Serial.print("Waiting for key press G");
    waitForThisChar('G');                       // Try this with the spacebar
    Serial.println("After key press");
}


// This function was to test various servo positions
void testPos()
{
  Serial.println("In testPos");
  // Front Right Leg
  //servoFR1.write(10);
  //servoFR2.write(90);
  //servoFR3.write(180);

  // Back Right Leg
  //servoBR1.write(180);
  //servoBR2.write(180);
  //servoBR3.write(); 
}





// Write to one servo at a time by selecting the leg and joint number, as well as the angle to move to
void servoWrite(int pin ,int angle)
{
  Serial.print("Moving Servo on pin: ");
  Serial.println(pin);
  testServo.attach(pin);
  testServo.write(angle);
  //delay(600);
  //testServo.detach();
}



///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
// SPOT COMMANDS
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

void jump()
{
  Serial.println("Jump");
}

void layDown()
{
  Serial.println("Lay");
  servoFR1.write(180);  // Front Right Bottom
  servoFR2.write(10);  // Front Right Middle
  servoFR3.write(90);    // Front Right Shoulder   <---- need to change this
  
  servoBR1.write(180);
  servoBR2.write(20);
  servoBR3.write(90);
  
  servoBL1.write(0);    // This one needs to be recalibrated like the BR1
  servoBL2.write(160);
  servoBL3.write(90);   /// <---------------------------------------------------------------
  
  servoFL1.write(0);
  servoFL2.write(180);
  servoFL3.write(90);
}

void kneel()
{
  Serial.println("Kneel");
  servoFR1.write(90);  // Front Right Bottom
  servoFR2.write(90);  // Front Right Middle
  servoFR3.write(90);    // Front Right Shoulder
  
  servoBR1.write(90);
  servoBR2.write(90);
  servoBR3.write(90);
  
  servoBL1.write(60);    // This one needs to be recalibrated like the BR1
  servoBL2.write(90);
  servoBL3.write(90);   /// <---------------------------------------------------------------
  
  servoFL1.write(60);
  servoFL2.write(90);
  servoFL3.write(90);
}

void foldedKneel()
{
  Serial.println("Folded Kneel");
  servoFR1.write(180);  // Front Right Bottom
  servoFR2.write(90);  // Front Right Middle
  servoFR3.write(90);    // Front Right Shoulder
  
  servoBR1.write(180);
  servoBR2.write(90);
  servoBR3.write(90);
  
  servoBL1.write(0);    // This one needs to be recalibrated like the BR1
  servoBL2.write(90);
  servoBL3.write(90);   /// <---------------------------------------------------------------
  
  servoFL1.write(0);
  servoFL2.write(90);
  servoFL3.write(90);
}


void shake()
{
  Serial.println("Shake");
}

void sit()
{
  Serial.println("Sit");
}
/*
void stand()
{
  Serial.println("Stand");
  servoFR1.write(40);  // Front Right Bottom
  servoFR2.write(90);  // Front Right Middle
  servoFR3.write(170);    // Front Right Shoulder     // When this is 170, it is inline with BR3 when that is at zero.
  servoBR1.write(40);
  servoBR2.write(65);     // This is vertical at 165
  servoBR3.write(0);   // Increasing this rotates it clockwise (downwards) [zero is our number for horizontal at the moment]
}
*/

void stand()
{
  Serial.println("Lay");
  servoFR1.write(20);  // Front Right Bottom
  servoFR2.write(90);  // Front Right Middle
  servoFR3.write(90);    // Front Right Shoulder
  
  servoBR1.write(40);
  servoBR2.write(90);
  servoBR3.write(90);
  
  servoBL1.write(140);    // This one needs to be recalibrated like the BR1
  servoBL2.write(90);
  servoBL3.write(90);   /// <---------------------------------------------------------------
  
  servoFL1.write(160);
  servoFL2.write(90);
  servoFL3.write(90);
}

void kneel2Stand()
{
  layDown();
  delay(2000);
  foldedKneel();
  delay(2000);
  kneel();
  delay(2000);
  stand();
  delay(2000);
  kneel();
  delay(2000);
  foldedKneel();
  delay(2000);
}

void preStand()
{
  Serial.println("Kneel");
  servoFR1.write(90);  // Front Right Bottom
  servoFR2.write(90);  // Front Right Middle
  servoFR3.write(90);    // Front Right Shoulder
  
  servoBR1.write(120);
  servoBR2.write(20);
  servoBR3.write(90);
  
  servoBL1.write(60);    // This one needs to be recalibrated like the BR1
  servoBL2.write(160);
  servoBL3.write(90);   /// <---------------------------------------------------------------
  
  servoFL1.write(60);
  servoFL2.write(90);
  servoFL3.write(90);
}

void kneel2()
{
  Serial.println("Kneel");
  servoFR1.write(90);  // Front Right Bottom
  servoFR2.write(90);  // Front Right Middle
  servoFR3.write(90);    // Front Right Shoulder
  
  servoBR1.write(180);    // 120
  servoBR2.write(20);
  servoBR3.write(90);
  
  servoBL1.write(0);    // This one needs to be recalibrated like the BR1    60
  servoBL2.write(160);
  servoBL3.write(90);   /// <---------------------------------------------------------------
  
  servoFL1.write(60);
  servoFL2.write(90);
  servoFL3.write(90);
}

void preKneel()
{
  Serial.println("Kneel");
  servoFR1.write(90);  // Front Right Bottom
  servoFR2.write(90);  // Front Right Middle
  servoFR3.write(90);    // Front Right Shoulder
  
  servoBR1.write(160);    // 120
  servoBR2.write(20);
  servoBR3.write(90);
  
  servoBL1.write(20);    // This one needs to be recalibrated like the BR1    60
  servoBL2.write(160);
  servoBL3.write(90);   /// <---------------------------------------------------------------
  
  servoFL1.write(60);
  servoFL2.write(90);
  servoFL3.write(90);
}

void preStand2()
{
  Serial.println("PreStand2");
  servoFR1.write(90);  // Front Right Bottom
  servoFR2.write(90);  // Front Right Middle
  servoFR3.write(90);    // Front Right Shoulder
  
  servoBR1.write(120);
  servoBR2.write(40);   //20
  servoBR3.write(90);
  
  servoBL1.write(60);    // This one needs to be recalibrated like the BR1
  servoBL2.write(120);    // 160
  servoBL3.write(90);   /// <---------------------------------------------------------------
  
  servoFL1.write(60);
  servoFL2.write(90);
  servoFL3.write(90);
}

void standLBL()
{
  Serial.println("Kneel");
  servoFR1.write(90);  // Front Right Bottom
  servoFR2.write(90);  // Front Right Middle
  servoFR3.write(90);    // Front Right Shoulder
  
  servoBR1.write(180);    // 120
  servoBR2.write(20);
  servoBR3.write(90);
  
  servoBL1.write(0);    // This one needs to be recalibrated like the BR1    60
  servoBL2.write(180);
  servoBL3.write(90);   /// <---------------------------------------------------------------
  
  servoFL1.write(60);
  servoFL2.write(90);
  servoFL3.write(90);
}

void standLBR()
{
  Serial.println("standLBR");
}

/*
Servo Matrix
                   [ 'Bottom_J', 'Middle_J', 'Shoulder_J' ]
Front Right (0)    [   Pin 2   ,   Pin 3   ,    Pin 4     ]
Back  Right (1)    [   Pin 5   ,   Pin 6   ,    Pin 7     ]
Back  Left  (2)    [   Pin 8   ,   Pin 9   ,    Pin 10    ]
Front Left  (3)    [   Pin 11  ,   Pin 12  ,    Pin 13    ]

*/





  //for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //  // in steps of 1 degree
  //  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //  delay(15);                       // waits 15ms for the servo to reach the position
  //}
  //for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  // myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //  delay(15);                       // waits 15ms for the servo to reach the position
  //}
