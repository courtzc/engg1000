bool obstacleExists = false;
void Discover();
void Lift();
void Carry();
void Drop();
void Complete();

#include <stdIO>;
#define sensordistance;

enum Mode
{
  discover,
  lift,
  carry,
  drop,
  complete
};

Mode phase;

void setup() {
  // put your setup code here, to run once:

   phase = discover;
   
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

void Discover() {
  println("discovering...");
  delay(1000); //enter discover code here
  /*
   * move forward until under pallet
   * drive forward until both sensor 1 and 2 distance < sensordistance
   * do, until this and this
   * stop motors when this is true
   * 
   */
  phase = lift;
}

void Lift() {
  println("lifting...");
  delay(1000); //enter lift code here
  /*
   * 
   */
  phase = carry;
}

void Carry(bool obstacle) {
  println("carrying...");
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
  println("dropping...");
  delay(1000);
  phase = complete;
}

void Complete() {
  println("delivered.");
}

