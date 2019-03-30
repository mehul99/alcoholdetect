#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
SoftwareSerial mySerial(9, 10);

int sensor=7;
int speaker=8;
int gas_value,Gas_alert_val, Gas_shut_val;
int Gas_Leak_Status;
int sms_count=0;

void setup()
{

pinMode(sensor,INPUT);
pinMode(speaker,OUTPUT);
mySerial.begin(9600);   
Serial.begin(9600);
lcd.begin(16,2);  
delay(500);

}

void loop()
{
CheckGas();
CheckShutDown();
}

void CheckGas()
{

lcd.setCursor(0,0);
lcd.print("Gas Scan - ON");
Gas_alert_val=ScanGasLevel();
if(Gas_alert_val==LOW)
{
 SetAlert(); // Function to send SMS Alerts
}}

int ScanGasLevel()
{
gas_value=digitalRead(sensor); // reads the sensor output (Vout of LM35)

return gas_value; // returns temperature value in degree celsius
}

void SetAlert()
{
digitalWrite(speaker,HIGH);  
while(sms_count<3) //Number of SMS Alerts to be sent
{  
SendTextMessage(); // Function to send AT Commands to GSM module
}
Gas_Leak_Status=1; 
lcd.setCursor(0,1);
lcd.print("Gas Alert! SMS Sent!");
}
void SendTextMessage(){
   mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919575730221\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void CheckShutDown()
{
if(Gas_Leak_Status==1)
{

Gas_shut_val=ScanGasLevel();
if(Gas_shut_val==HIGH)
{

lcd.setCursor(0,1);
lcd.print("No Gas Leaking");
digitalWrite(speaker,LOW);
sms_count=0;
Gas_Leak_Status=0;
}}}

