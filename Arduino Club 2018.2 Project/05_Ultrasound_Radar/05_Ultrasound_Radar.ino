int TrigPin = 12;
int EchoPin = 13;
 
void setup(){
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}
 
void loop(){
  Serial.print("Distance : ");
  Serial.print(distance());
  Serial.println(" cm");
}
 
unsigned long distance(){
  unsigned long d;
   
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
   
  d = pulseIn(EchoPin, HIGH)*0.034/2;
   
  return d;
}
