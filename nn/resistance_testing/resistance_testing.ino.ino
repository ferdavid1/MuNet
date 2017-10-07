int resPin = A0;
int res = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  res = analogRead(resPin);
  Serial.println(res);
  delay(100);
} 
