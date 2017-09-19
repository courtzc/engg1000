#include <MeAuriga.h>
#include <Wire.h>
#include <SoftwareSerial.h>

/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    EncoderMotorTestRunSpeed.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2015/11/19
 * @brief   Description: this file is sample code for Encoder Motor  device.
 *
 * Function List:
 *
 *    1. void MeEncoderMotor::begin();
 *    2. boolean MeEncoderMotor::runSpeed(float speed);
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * forfish      2015/11/19    1.0.0          add some descriptions
 * </pre>
 */

MeEncoderNew motor1(0x09, SLOT1);   //  motor at slot1 ALSO NOT SURE IF MeEncoder or MeEncoderNew ALSO NOT SURE IF BOTH FLOAT VALUE IS MEANT TO BE THE SAME
MeEncoderNew motor2(0x09, SLOT2);   //  motor at slot2 ALSO NOT SURE IF MeEncoder or MeEncoderNew

bool obstacleExists = false;
void Discover();
void Lift();
void Carry();
void Drop();
void Complete();

// #include <stdIO>;
#define sensordistance;

enum Mode
{
  discover,
  lift,
  carry,
  drop,
  complete
};

enum DiscoverMode
{
  searching,
  us1Under,
  robotWiderThanLoad,
  us2Under,
  centring,
  centred
};

Mode phase;
DiscoverMode discoverPhase;

void setup() {
  // put your setup code here, to run once:
  
  motor1.begin();
  motor2.begin();
  Serial.begin(9600);

   phase = discover;
   discoverPhase = searching;
   
}


void loop() {
  // put your main code here, to run repeatedly:
  /*
  5 Phases of the operation
  - Discover load
  - Lift
  - Carry
  - Drop
  - Complete
   */
   switch (phase)
   {
    case discover:
      Discover();
      break;
    case lift:
      Lift();
      break;
    case carry:
      Carry(obstacleExists);
      break;
    case drop:
      Drop();
      break;
    case complete:
      Complete();
      break;
   }
}

// used for centring under pallet
int loadWidth = 0;
int centringAdjustment = 0;

void Discover() {
  Serial.println("discovering...");
  delay(1000); //enter discover code here
  /*
   * move forward until under pallet
   * drive forward until both sensor 1 and 2 distance < sensordistance
   * do, until this and this
   * stop motors when this is true
   * 
   */

       bool US1IsUnder, US2IsUnder;

   switch(discoverPhase)
   {
     case searching:
      //Forward(1);
      motor1.runSpeed(150);
      motor2.runSpeed(150);
    //}
      
      // read U/S Sensor 1
       US1IsUnder = IsSensorUnder(1);
      if (US1IsUnder) {
        discoverPhase = us1Under;
      }
      break;
      
     case us1Under:
       loadWidth++;
       // read U/S sensor 1
       US1IsUnder = IsSensorUnder(1);
       // read U/S sensor 2
       US2IsUnder = IsSensorUnder(2);
       if (!US1IsUnder && ! US2IsUnder) {
        discoverPhase = robotWiderThanLoad;
       }
       if (US2IsUnder) {
        discoverPhase = us2Under;
       }
       break;
       
     case robotWiderThanLoad:
       //Forward(1);
       motor1.runSpeed(150);
       motor2.runSpeed(150);
    //}
       centringAdjustment++;
       // Read U/S sensor 2
       US2IsUnder = IsSensorUnder(2);
       if (US2IsUnder) {
        discoverPhase = centring;
       }
       break;
       
     case us2Under:
       //Forward(1);
       motor1.runSpeed(150);
       motor2.runSpeed(150);
      //}
       loadWidth++;
       centringAdjustment++;
       // read U/S sensor 1
       US1IsUnder = IsSensorUnder(1);
       // read U/S sensor 2
       US2IsUnder = IsSensorUnder(2);
       if (!US1IsUnder) {
        discoverPhase = centring;
       }
       break;
       
     case centring:
       //Backward(1);
       motor1.runSpeed(-150);
       motor2.runSpeed(-150);
    //}   
       Backwards(centringAdjustment/2);
       discoverPhase = centred;
       break;
       
     case centred:
      //Stoping the motors for no movement of the droid
      motor1.runSpeed(0);
      motor2.runSpeed(0);
      phase = lift;
      break;
   }

}

bool IsSensorUnder(int sensor)
{
  // read sensor
  // check difference
  // return distance < threshold
  return false;
}

void Forward(int distance)
{
  // do the forward thing
}

void Backwards(int distance)
{
  Forward(-1 * distance);
}

void Lift() {
  Serial.println("lifting...");
  delay(1000); //enter lift code here
  /*
   * 
   */
  phase = carry;
}

void Carry(bool obstacle) {
  Serial.println("carrying...");
  if(!obstacle) {
    //motor pins set to forward
    
  }
  /* 
   * obstacle false
   * drive forward
   * if magnet detected, increment magnet number
   * drive forward until magnet = 3
   * do
   * {
   * }
   * until()
   * 
   * do while()
   * magnet = 1, ignore magnets, drive forward
   * magnet = 2, ignore magnets, drive forward
   * magnet = 3, set phase to drop
   * 
   * obstacle true
   * drive forward
   * if magnet detected, incrememnt magnet number
   * magnet = 1, ignore magnets, turn right, drive forward
   * magnet = 2, ignore magnets, turn left, drive forward
   * magnet = 3, ignore magnets, turn left, drive forward
   * magnet = 4, ignore magnets, turn right, drive forward
   * magnet = 5, set phase to drop
   */
  delay(1000);
  phase = drop;
}

void Drop() {
  Serial.println("dropping...");
  delay(1000);
  phase = complete;
}

void Complete() {
  Serial.println("delivered.");
}

