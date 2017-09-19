//=======================================================
// ENGG1000 - Warehouse Droid Team 12
// Droid Code
// Written by Courtney Coates('s Dad) and Jason Jeon
// September 2017
//======================================================= 

//-----------------------------------------------
// Set these parameters before each run
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

#define sensordistance;


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

//-----------------------------------------------
// Modes
//-----------------------------------------------

Mode phase;
DiscoverMode discoverPhase;
LiftMode liftPhase;
CarryMode carryPhase;


//-----------------------------------------------
// Inital Conditions
//-----------------------------------------------

void setup() {
  
   phase = discover;
   discoverPhase = searching;
   liftPhase = contracted;
   carryPhase = waiting;
   pinMode(usSensor1Pin, INPUT);
   pinMode(usSensor2Pin, INPUT);  
}


//-----------------------------------------------
// Phases of Delivery 
//-----------------------------------------------

void loop() {

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

void Discover() {
  
  Serial.println("discovering...");
  delay(1000);
  
   bool US1IsUnder, US2IsUnder;

   switch(discoverPhase)
   {
     case searching:
      //Forward(1);
       US1IsUnder = IsSensorUnder(usSensor1Pin);
      if (US1IsUnder) {
        discoverPhase = us1Under;
      }
      break;
     case us1Under:
       //Forward(1);
       loadWidth++;
       US1IsUnder = IsSensorUnder(usSensor1Pin);
       US2IsUnder = IsSensorUnder(usSensor2Pin);
       if (!US1IsUnder && !US2IsUnder) {
        discoverPhase = robotWiderThanLoad;
       }
       if (US2IsUnder) {
        discoverPhase = us2Under;
       }
       break;
     case robotWiderThanLoad:
       //Forward(1);
       centringAdjustment++;
       US2IsUnder = IsSensorUnder(usSensor2Pin);
       if (US2IsUnder) {
        discoverPhase = centring;
       }
       break;
     case us2Under:
       Forward(1);
       loadWidth++;
       centringAdjustment++;
       US1IsUnder = IsSensorUnder(usSensor1Pin);
       US2IsUnder = IsSensorUnder(usSensor2Pin);
       if (!US1IsUnder) {
        discoverPhase = centring;
       }
       break;
     case centring:
       //Backwards(centringAdjustment/2);
       discoverPhase = centred;
       break;
     case centred:
      phase = lift;
      break;
   }

}
   
//-----------------------------------------------
// Lifting Phase
//-----------------------------------------------

const int rotationsFor1kg = 15;
const int rotationsFor2kg = 28;

void Lift() {
  
  Serial.println("lifting...");
  delay(1000); //enter lift code here
  
  switch(liftPhase) {
    case contracted:
      liftPhase = extending;
      break;
    case extending:
    if(loadWeight == 1) {
      liftPhase = weight1kg;
    }
    else {
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

  switch(carryPhase) {
    case waiting:
      mgTagsFound = 0;
      tagRecentlyFound = false;
      carryPhase = obstacle ? deliveringWithObstacle : deliveringWithoutObstacle;
      break;
    case deliveringWithObstacle:
    // Dodge that
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
        
        switch (mgTagsFound)
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
    // The obstacle is a lie
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

//-----------------------------------------------
// Dropping Phase
//-----------------------------------------------

void Drop() {
  Serial.println("dropping...");
  delay(1000);

  switch(liftPhase) {
    case extended:
      liftPhase = contracting;
      break;
    case contracting:
    if(loadWeight == 1) {
      liftPhase = weight1kg;
    }
    else {
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

void Complete() {
  Serial.println("delivered.");
}



//---------------------------------------------
// Sensor Subroutines
//---------------------------------------------

// Ultrasonic Sensors
// TODO: U/S SENSOR READING
    bool IsSensorUnder(int sensorPin) {
          sensorValue = digitalRead(sensorPin);
          // interpret the sensor value to work out if we're under
         if (distance < threshold) {
          return true;
         }
         else {
          return false;
         }
    }

// Magnetic Sensor
// TODO: MAG SENSOR READING
    bool mgSensorRead(int sensorPin) {
          sensorValue = digitalRead(sensorPin);
          // interpret the sensor value to work out if we've found a tag
          bool foundTag = true;

          return foundTag;
    }




//-----------------------------------------------
// Wheel Motor Subroutines
//-----------------------------------------------

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

//-----------------------------------------------
// Lift Motor Subroutines
//-----------------------------------------------

    void Up(int distance)
    {
      // do the forward thing
    }
    
    void Down(int distance)
    {
      //Up(-1 * distance);
    }

