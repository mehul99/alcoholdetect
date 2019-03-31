const int alc_senPin = 8 ;
const int redLED = 2 ;
const int greenLED = 3 ;
const int motorPin = 9 ;
int alc_status = 0;

void alert_on();
void alert_off();

void alert_on() {
  Serial.println("Alcohol detection status  : True");
  if (alc_status == 0) {
    Serial.println("Cutting off the Engine ....");
  }
  digitalWrite(motorPin , HIGH);
  digitalWrite(greenLED , LOW);
  digitalWrite(redLED   , HIGH);
  alc_status = 1;
  delay(8000);

}

void alert_off() {
  Serial.println("Alcohol detection status  : False");
  if (alc_status == 1) {
    Serial.println("Turning ON the Engine ....");
  }
  digitalWrite(motorPin , LOW );
  digitalWrite(greenLED , HIGH);
  digitalWrite(redLED   , LOW );
  alc_status == 0;
}
void setup() {

  pinMode(alc_senPin , INPUT );
  pinMode(motorPin   , OUTPUT);
  pinMode(greenLED   , OUTPUT);
  pinMode(redLED     , OUTPUT);

  Serial.begin(9600);
  Serial.println("Initializing alcohol detection unit ..........");

  digitalWrite(motorPin , LOW );
  digitalWrite(greenLED , HIGH);
  digitalWrite(redLED   , LOW );


}

void loop() {

  while (alc_senPin == HIGH) {
    alert_on();
  }

  alert_off();

}
