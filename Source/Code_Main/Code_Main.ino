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
      Forward(1);
      // read U/S Sensor 1
       US1IsUnder = IsSensorUnder(1);
      if (US1IsUnder) {
        discoverPhase = us1Under;
      }
      break;
     case us1Under:
       Forward(1);
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
       Forward(1);
       centringAdjustment++;
       // Read U/S sensor 2
       US2IsUnder = IsSensorUnder(2);
       if (US2IsUnder) {
        discoverPhase = centring;
       }
       break;
     case us2Under:
       Forward(1);
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
       Backwards(centringAdjustment/2);
       discoverPhase = centred;
       break;
     case centred:
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

