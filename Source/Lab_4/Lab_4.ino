int LtMotPin1 = 5;
int LtMotPin2 = 6;
int RtMotPin1 = 9;
int RtMotPin2 = 10;
int pwmDutyCycle = 0;
char currentDirection = 'x';

String op="";

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Program: Motors");
Serial.println("Initialising...");
Serial.println("Right Motor Pin 1 = 5");
Serial.println("Right Motor Pin 2 = 6");
Serial.println("Left Motor Pin 1 = 9");
Serial.println("Left Motor Pin 2 = 10");
Serial.println("Initialisation complete");
}

void loop() {
  // put your main code here, to run repeatedly:

char myString[20];
int i=0;

  //Read characters from the input buffer
  if(Serial.available()>0){
  myString[20] = Serial.read();
    if (myString[20] == 'f')
      pwmDutyCycle = 0;
      op="Forwards";
    if (myString[20] == 'b')
      op="Backwards";
    if (myString[20] == 'l')
      op="Turn Left";
    if (myString[20] == 'r')
      op="Turn Right";
    if (myString[20] == '0')
      op="Stop";
    if (myString[20] == '1')
      op="Speed = 10%";
    if (myString[20] == '2')
      op="Speed = 20%";
    if (myString[20] == '3')
      op="Speed = 30%";
    if (myString[20] == '4')
      op="Speed = 40%";
    if (myString[20] == '5')
      op="Speed = 50%";
    Serial.println(op);

     myString[20] = 0;

  //Set Pins to Zero
     analogWrite(RtMotPin1, 0);
     analogWrite(RtMotPin2, 0);
     analogWrite(LtMotPin1, 0);
     analogWrite(LtMotPin2, 0);

  //Set Motor Pins for Direction
     if((currentDirection == 'b'))
      analogWrite(RtMotPin1, pwmDutyCycle);
      analogWrite(RtMotPin2, 0);
      analogWrite(LtMotPin1, pwmDutyCycle);
      analogWrite(LtMotPin2, 0);
    
     if((currentDirection == 'f'))
      analogWrite(RtMotPin1, 0);
      analogWrite(RtMotPin2, pwmDutyCycle);
      analogWrite(LtMotPin1, 0);
      analogWrite(LtMotPin2, pwmDutyCycle);

    if((currentDirection == 'l'))
      analogWrite(RtMotPin1, 0);
      analogWrite(RtMotPin2, pwmDutyCycle);
      analogWrite(LtMotPin1, pwmDutyCycle);
      analogWrite(LtMotPin2, 0);

     if((currentDirection == 'f'))
      analogWrite(RtMotPin1, pwmDutyCycle);
      analogWrite(RtMotPin2, 0);
      analogWrite(LtMotPin1, 0);
      analogWrite(LtMotPin2, pwmDutyCycle);




 
 /*if (myString[0] !=0){
  for(int i = 0; myString[i] !=0; i++){
   
   //Print the character
    Serial.print(myString[i]);

    //Increment the index
    i++;

    //Pause to allow data to come into the buffer
    delay(10);
  }
 }
 */
}
delay(1000);
}
