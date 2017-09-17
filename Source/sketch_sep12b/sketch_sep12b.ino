int sensor = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
sensor = analogRead(0)-analogRead(1);
sensor = map(sensor, -2, 40, 0, 255);
analogWrite(3, sensor);
delay(50);
}
