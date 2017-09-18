bool obstacleExists = false;
void Discover();
void Lift();
void Carry();
void Drop();
void Complete();

//CHANGE THE MOTOR PINS ACCORDING TO THE ARDUINO MEGA THIS IS FOR THE UNO
// -------------------------------------------------------
// Global Variables //Change the global variables below for the arduino mega
// -------------------------------------------------------
/*int rightMotorLogicPin1 = 11;    
int rightMotorLogicPin2 = 9;  
int leftMotorLogicPin1 = 10;    
int leftMotorLogicPin2 = 3;*/

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

// -------------------------------------------------------
// Subroutine: Initialize Motor Pins
// -------------------------------------------------------
void initializeMotorPins(){ // Change the motor pins to the ones on the arduino mega
  /*pinMode(rightMotorLogicPin1, OUTPUT);
  pinMode(rightMotorLogicPin2, OUTPUT);
  pinMode(leftMotorLogicPin1, OUTPUT);
  pinMode(leftMotorLogicPin2, OUTPUT);

  //Print the motor pin configuration for wiring
  Serial.println("Right Motor Pin 1 = 11");
  Serial.println("Right Motor Pin 2 = 9");
  Serial.println("Left Motor Pin 1 = 10");
  Serial.println("Left Motor Pin 2 = 3");*/
}

// -------------------------------------------------------
// Function: Receive Byte
// -------------------------------------------------------
char receiveCommand(){
  char incomingByte = 0;

  //See if there's incoming serial data:
  if(Serial.available()>0){
  
    //Read the oldest byte in the serial buffer:
    incomingByte = Serial.read(); 
  }
  return incomingByte;
}

// -------------------------------------------------------
// Function: Update Direction
// -------------------------------------------------------
char updateDirection(char command, char currentDirection){
   //Is this a direction; 'f' 'b' 'l' 'r'
    if(command == 'f'){
      currentDirection = 'f';
      Serial.println("Forwards");
    }
    //Just forward for now
    /*if(command == 'b'){
      currentDirection = 'b';
      Serial.println("Backwards");
    }
    if(command == 'l'){
      currentDirection = 'l';
      Serial.println("Turn Left");
    }
    if(command == 'r'){
      currentDirection = 'r';
      Serial.println("Turn Right");
    }*/
    
    return currentDirection;
}

// -------------------------------------------------------
// Function: Update Speed
// -------------------------------------------------------
int updateSpeed(char command, int pwmDutyCycle){
  //Is this a motor speed '0' - '5'
    if(command == '0'){
      pwmDutyCycle = 0;
      Serial.println("Stop");
    }
    if(command == '1'){
      pwmDutyCycle = 25;
      Serial.println("Speed = 10%");
    }
    if(command == '2'){
      pwmDutyCycle = 51;
      Serial.println("Speed = 20%");
    }
    if(command == '3'){
      pwmDutyCycle = 76;
      Serial.println("Speed = 30%");
    }
    if(command == '4'){
      pwmDutyCycle = 102;
      Serial.println("Speed = 40%");
    }
    if(command == '5'){
      pwmDutyCycle = 127;
      Serial.println("Speed = 50%");
    }
    return pwmDutyCycle;
}

// -------------------------------------------------------
// Subroutine: Set Motor Pins
// -------------------------------------------------------
void setMotorPins(int currentDirection, int pwmDutyCycle){
  //Reset all of the pins
    analogWrite(rightMotorLogicPin1, 0);
    analogWrite(rightMotorLogicPin2, 0);
    analogWrite(leftMotorLogicPin1, 0);
    analogWrite(leftMotorLogicPin2, 0);

    // Set the motor pins appropriately
    // Use the motor logic from lectures
    //CHANGE THE MOTOR PINS ACCORDING TO THE ARDUINO MEGA THIS IS FOR THE UNO
    
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

    if(currentDirection == 'f'){
      analogWrite(rightMotorLogicPin2, pwmDutyCycle);
      analogWrite(leftMotorLogicPin2, pwmDutyCycle);
    }
    
    /*if(currentDirection == 'b'){
      analogWrite(rightMotorLogicPin1, pwmDutyCycle);
      analogWrite(leftMotorLogicPin1, pwmDutyCycle);
    }

    if(currentDirection == 'l'){
      analogWrite(rightMotorLogicPin2, pwmDutyCycle);
      analogWrite(leftMotorLogicPin1, pwmDutyCycle);
    }

    if(currentDirection == 'r'){
      analogWrite(rightMotorLogicPin1, pwmDutyCycle);
      analogWrite(leftMotorLogicPin2, pwmDutyCycle);
    }*/
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Print the program details
  Serial.println("-------------------------------------");
  Serial.println("Program: Motor Controller"); 
  Serial.println("Initializing ...");

  //Call a subroutine to initialiez the motor pins
  initializeMotorPins();

  //Initialization completed successfully
  Serial.println("Initialization complete");

   phase = discover;
   discoverPhase = searching;
   
}


void loop() {
  // put your main code here, to run repeatedly:
  //THIS IS FOR SETTING SPEED AND DIRECTION
  int pwmDutyCycle = 0;
  char currentDirection = 'x'; 
  char command = 0;
  bool keyboardControl = true;
  
  // Control the motors from the keyboard
  while (keyboardControl) {
    
    // Wait for a command from the keyboard
    command = receiveCommand(); 
    
    // Update the direction of the robot
    currentDirection = updateDirection(command, currentDirection);
    
    // Update the speed of the robot
    pwmDutyCycle = updateSpeed(command, pwmDutyCycle);
    
    // Set the motor pins according to speed and direction
    setMotorPins(currentDirection, pwmDutyCycle);
    
    // Was this an exit command
    if (command == 'x') keyboardControl = false;

    //Small delay for a character to arrive 
    delay(10);
  }
  
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
   // Terminate the program
 Serial.println("bye");
 while(true);
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

