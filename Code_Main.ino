int loadWidth = 0;
int centringAdjustment = 0;
int usSensor1Pin = 6; //check position
int usSensor2Pin = 7; //check position
int sensorValue;
int distance;
int threshold;

bool obstacleExists = false;


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

   phase = discover;
   discoverPhase = searching;
   pinMode(usSensor1Pin, INPUT);
   pinMode(usSensor2Pin, INPUT);  
}


void loop() {
  // put your main code here, to run repeatedly:

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


void Discover() {
  Serial.println("discovering...");
  delay(1000); //enter discover code here
  
       bool US1IsUnder, US2IsUnder;


   switch(discoverPhase)
   {
     case searching:
      Forward(1);
       US1IsUnder = IsSensorUnder(usSensor1Pin);
      if (US1IsUnder) {
        discoverPhase = us1Under;
      }
      break;
     case us1Under:
       Forward(1);
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
       Forward(1);
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
       Backwards(centringAdjustment/2);
       discoverPhase = centred;
       break;
     case centred:
      phase = lift;
      break;
   }

}

bool IsSensorUnder(int sensorPin) {
      sensorValue = digitalRead(sensorPin);
     if (distance < threshold) {
      return true;
     }
     else {
      return false;
     }
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

