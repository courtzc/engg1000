int led = 13;
int sensor = A2;

void setup() {
  // put your setup code here, to run once:
pinMode(13, OUTPUT);
pinMode(A2, INPUT);
digitalWrite(A2, HIGH);
}

void loop() {
  if(digitalRead(A2) == LOW)
    {
    digitalWrite(led, HIGH);
    }
  else digitalWrite(led, LOW);
}
