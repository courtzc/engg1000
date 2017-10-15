<<<<<<< HEAD
//-------------------------------------------------------
// ENGG1000 - Warehouse Droid Team 12
// Droid Code
// Written by Courtney Coates
// August-October 2017
//-------------------------------------------------------

//-----------------------------------------------
// Parameters to set before each run
//-----------------------------------------------

const bool obstacleExists = false;
const int loadWeight = 1;


//-----------------------------------------------
// Constants
//-----------------------------------------------

const int usSensor1Pin = 6; //check position
const int usSensor2Pin = 7; //check position
const int threshold = 100; //define threshold
const int mgSensorPin = 8; //check position
const int RIGHT = 90;
const int LEFT = -90;

//-----------------------------------------------
// Variables
//-----------------------------------------------

int loadWidth = 0;
int centringAdjustment = 0;
int sensorValue;
int distance;
int mgTagsFound = 0;
bool tagRecentlyFound = false;
bool tag1ActionComplete, tag2ActionComplete, tag3ActionComplete, tag4ActionComplete, tag5ActionComplete = false;


//-----------------------------------------------
// Defintions and Inclusions
//-----------------------------------------------

=======
bool obstacleExists = false;
void Discover();
void Lift();
void Carry();
void Drop();
void Complete();

int pwmDutyCycle;
int rightMotorLogicPin1 = 11;
int rightMotorLogicPin2 = 9;
int leftMotorLogicPin1 = 10;
int leftMotorLogicPin2 = 3;
// Set the motor pins appropriately
    // Use the motor logic from lectures
    
    // Pin1  Pin2  Motor
    //  0     0    Idle
    //  0     5v   Forward
    //  5v    0    Reverse
    //  5v    5v   Idle
    
    // RightMotor  LeftMotor  Direction
    //    For        For      Forward
    //    For        Rev      Turn Left
    //    Rev        For      Turn Right
    //    Rev        Rev      Backwards


// #include <stdIO>;
>>>>>>> ff46accb7570c61202796d486b89a97426cc5e4d
#define sensordistance;
#include <Arduino.h>
#include <MeAuriga.h>
#include <Wire.h>
#include <SoftwareSerial.h>


//-----------------------------------------------
// Defintions of Phases
//-----------------------------------------------

enum Mode
{
  discover,
  lift,
  carry,
  drop,
  complete
};


//-----------------------------------------------
// Defintions of Sub-Phases
//-----------------------------------------------

enum DiscoverMode
{
  searching,
  us1Under,
  robotWiderThanLoad,
  us2Under,
  centring,
  centred
};

enum LiftMode
{
  contracted,
  extending,
  weight1kg,
  weight2kg,
  extended,
  contracting
};

enum CarryMode
{
  waiting,
  deliveringWithoutObstacle,
  deliveringWithObstacle,
  deliveryLocation
};

enum CompleteMode
{
  incomplete,
  complete
};

//-----------------------------------------------
// Modes
//-----------------------------------------------

Mode phase;
DiscoverMode discoverPhase;
LiftMode liftPhase;
CarryMode carryPhase;
CompleteMode completePhase;

<<<<<<< HEAD
=======
void setup() {
  // put your setup code here, to run once:
  
  //Configuration the motor pins //Check with the tutor
  pinMode(rightMotorLogicPin1, OUTPUT);
  pinMode(rightMotorLogicPin2, OUTPUT);
  pinMode(leftMotorLogicPin1, OUTPUT);
  pinMode(leftMotorLogicPin2, OUTPUT);
>>>>>>> ff46accb7570c61202796d486b89a97426cc5e4d

//-----------------------------------------------
// Inital Conditions
//-----------------------------------------------

void setup()
{
   phase = discover;
   discoverPhase = searching;
   liftPhase = contracted;
   carryPhase = waiting;
   completePhase = incomplete;
   pinMode(usSensor1Pin, INPUT);
   pinMode(usSensor2Pin, INPUT); 
   motor1.begin();
   motor2.begin();
}


<<<<<<< HEAD
//-----------------------------------------------
// Phases of Delivery 
//-----------------------------------------------

void loop()
{
=======
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
>>>>>>> ff46accb7570c61202796d486b89a97426cc5e4d
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

//-----------------------------------------------
// Discovery Phase
//-----------------------------------------------

void Discover()
{
  Serial.println("discovering...");
<<<<<<< HEAD
  delay(1000);
  
   bool US1IsUnder, US2IsUnder;
=======
  delay(1000); //enter discover code here
  /*
   * move forward until under pallet
   * drive forward until both sensor 1 and 2 distance < sensordistance
   * do, until this and this
   * stop motors when this is true
   * 
   */

       bool US1IsUnder, US2IsUnder;
>>>>>>> ff46accb7570c61202796d486b89a97426cc5e4d

   switch(discoverPhase)
   {
     case searching:
      //Forward(1);
<<<<<<< HEAD
       US1IsUnder = IsSensorUnder(usSensor1Pin);
      if (US1IsUnder)
      {
=======
      pwmDutyCycle = 127;// Motor speed for wheels at 50%
      Serial.println("Speed = 50%");
      
      /*//Reset all of the pins if you want the wheels to move left right forward back etc
      analogWrite(rightMotorLogicPin1, 0);
      analogWrite(rightMotorLogicPin2, 0);
      analogWrite(leftMotorLogicPin1, 0);
      analogWrite(leftMotorLogicPin2, 0);*/

      //if(currentDirection == 'f'){  THIS IS FOR MOVING FORWARD
      analogWrite(rightMotorLogicPin2, pwmDutyCycle); //Change pin according to arduino mega
      analogWrite(leftMotorLogicPin2, pwmDutyCycle); // Change pin according arduino mega
    //}
      
      // read U/S Sensor 1
       US1IsUnder = IsSensorUnder(1);
      if (US1IsUnder) {
>>>>>>> ff46accb7570c61202796d486b89a97426cc5e4d
        discoverPhase = us1Under;
      }
      break;
      
     case us1Under:
<<<<<<< HEAD
       //Forward(1);
=======
>>>>>>> ff46accb7570c61202796d486b89a97426cc5e4d
       loadWidth++;
       US1IsUnder = IsSensorUnder(usSensor1Pin);
       US2IsUnder = IsSensorUnder(usSensor2Pin);
         if (!US1IsUnder && !US2IsUnder)
         {
          discoverPhase = robotWiderThanLoad;
         }
         if (US2IsUnder)
         {
          discoverPhase = us2Under;
         }
       break;
       
     case robotWiderThanLoad:
       //Forward(1);
<<<<<<< HEAD
=======
       pwmDutyCycle = 127;// Motor speed for wheels at 50%
       //if(currentDirection == 'f'){  THIS IS FOR MOVING FORWARD
       analogWrite(rightMotorLogicPin2, pwmDutyCycle); //Change pin according to arduino mega
       analogWrite(leftMotorLogicPin2, pwmDutyCycle); // Change pin according arduino mega
    //}
>>>>>>> ff46accb7570c61202796d486b89a97426cc5e4d
       centringAdjustment++;
       US2IsUnder = IsSensorUnder(usSensor2Pin);
       if (US2IsUnder)
       {
        discoverPhase = centring;
       }
       break;
       
     case us2Under:
       //Forward(1);
       pwmDutyCycle = 127;// Motor speed for wheels at 50%
      //if(currentDirection == 'f'){  THIS IS FOR MOVING FORWARD
       analogWrite(rightMotorLogicPin2, pwmDutyCycle); //Change pin according to arduino mega
       analogWrite(leftMotorLogicPin2, pwmDutyCycle); // Change pin according arduino mega
      //}
       loadWidth++;
       centringAdjustment++;
       US1IsUnder = IsSensorUnder(usSensor1Pin);
       US2IsUnder = IsSensorUnder(usSensor2Pin);
       if (!US1IsUnder)
       {
        discoverPhase = centring;
       }
       break;
       
     case centring:
<<<<<<< HEAD
       //Backwards(centringAdjustment/2);
=======
       //Backward(1);
       pwmDutyCycle = 127; //Motor speed for wheels at 50%
       //if(currentDirection == 'b'){  THIS IS FOR MOVING BACKWARDs
      analogWrite(rightMotorLogicPin1, pwmDutyCycle); //Change pin according to arduino mega
      analogWrite(leftMotorLogicPin1, pwmDutyCycle); //Change pin according to arduino mega
    //}   
       Backwards(centringAdjustment/2);
>>>>>>> ff46accb7570c61202796d486b89a97426cc5e4d
       discoverPhase = centred;
       break;
       
     case centred:
      pwmDutyCycle = 0;
      phase = lift;
      break;
   }

}
   
//-----------------------------------------------
// Lifting Phase
//-----------------------------------------------

const int rotationsFor1kg = 15;
const int rotationsFor2kg = 28;

void Lift()
{
  Serial.println("lifting...");
  delay(1000); 
  
  //enter lift code here
  
  switch(liftPhase)
  {
    case contracted:
      liftPhase = extending;
      break;
      
    case extending:
      if(loadWeight == 1)
      {
        liftPhase = weight1kg;
      }
      else
      {
        liftPhase = weight2kg;
      }
    break;
    
   case weight1kg:
      //code for motors
      //lifting motors Up for rotationsFor1kg
      liftPhase = extended;
      break;
      
   case weight2kg:
      //code for motors
      //lifting motors Up for rotationsFor2kg
      liftPhase = extended;
      break;
      
   case extended:
      phase = carry;
      break;
  }

}

//-----------------------------------------------
// Carrying Phase
//-----------------------------------------------

void Carry(bool obstacle) {
  Serial.println("carrying...");

  switch(carryPhase)
  {
    case waiting:
      mgTagsFound = 0;
      tagRecentlyFound = false;
      carryPhase = obstacle ? deliveringWithObstacle : deliveringWithoutObstacle;
      break;
      
    case deliveringWithObstacle:
        if(mgSensorRead(mgSensorPin)) 
        {
          if (!tagRecentlyFound) 
          {
            mgTagsFound++;
           Serial.println(found);
          }
          else 
          {
            tagRecentlyFound = false;
          }
        
        switch (mgTagsFound)
            tagRecentlyFound = true;
          }
          
        {
          case 0:
            Forward(1);
            break;
            
          case 1:
            if(!tag1ActionComplete)
            {
              Turn(RIGHT);
              tag1ActionComplete = true;
            }
            Forward(1);
            break;
            
          case 2:
            if(!tag2ActionComplete)
            {
              Turn(LEFT);
              tag2ActionComplete = true;
            }
            Forward(1);
            break;
            
          case 3:
            if(!tag3ActionComplete)
            {
              Turn(LEFT);
              tag3ActionComplete = true;
            }
            Forward(1);
            break;
            
          case 4:
            if(!tag4ActionComplete)
            {
              Turn(RIGHT);
              tag4ActionComplete = true;
            }
            Forward(1);
            break;
            
          case 5:
            if(!tag5ActionComplete)
            {
              tag5ActionComplete = true;
              carryPhase = deliveryLocation;
            }
            break;
        }
                 
      break;
      
    case deliveringWithoutObstacle:
        if(mgSensorRead(mgSensorPin)) 
        {
          if (!tagRecentlyFound) 
          {
            mgTagsFound++;
            tagRecentlyFound = true;
          }
        }
        else 
        {
          tagRecentlyFound = false;
        }
        
        if(mgTagsFound == 3)
        {
          carryPhase = deliveryLocation;
        }
        else 
        {
          Forward(1);
        }
      break;
      
    case deliveryLocation:
      phase = drop;
      break;
      
  };
  
  if(!obstacle)
    {
      //motor pins set to forward
    }
            /*
             * LOGIC FOR CARRY PHASE
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

//-----------------------------------------------
// Dropping Phase
//-----------------------------------------------

void Drop()
{
  Serial.println("dropping...");
  delay(1000);

  switch(liftPhase)
  {
    case extended:
      liftPhase = contracting;
      break;
      
    case contracting:
    if(loadWeight == 1)
      {
        liftPhase = weight1kg;
      }
    else
      {
        liftPhase = weight2kg;
      }
    break;
    
   case weight1kg:
      //code for motors
      //lifting motors Down for rotationsFor1kg
      liftPhase = contracted;
      break;
      
   case weight2kg:
      //code for motors
      //lifting motors Down for rotationsFor2kg
      liftPhase = contracted;
      break;
      
   case contracted:
      phase = complete;
      break;
  }

}

//-----------------------------------------------
// Complete Phase
//-----------------------------------------------

void Complete()
{
  Serial.println("delivered.");
}


//---------------------------------------------
// Sensor Subroutines
//---------------------------------------------

// Ultrasonic Sensors
// TODO: U/S SENSOR READING
bool IsSensorUnder(int sensorPin)
{
  sensorValue = digitalRead(sensorPin);
  // interpret the sensor value to work out if we're under
   if (distance < threshold)
   {
    return true;
   }
   else
   {
    return false;
   }
}

// Magnetic Sensor
// TODO: MAG SENSOR READING
bool mgSensorRead(int sensorPin)
{
  sensorValue = digitalRead(sensorPin);
  // interpret the sensor value to work out if we've found a tag
  bool foundTag = true;
  return foundTag;
}


//-------------------------------------------------
// Wheel Motor Subroutines - Code in Jason's review
//-------------------------------------------------

    void Forward(int distance)
    {
      // do the forward thing
    }
    
    void Backwards(int distance)
    {
      //Forward(-1 * distance);
    }

    void Turn(int angle)
    {
      //TODO turn logic
    }


//------------------------------------------------
// Lift Motor Subroutines - Code in Jason's review
//------------------------------------------------

    void Up(int distance)
    {
      // do the forward thing
    }
    
    void Down(int distance)
    {
      //Up(-1 * distance);
    }

