#include <SoftwareSerial.h>
#include <Servo.h> 
#include "DHT.h"
#define DHTPIN 2     
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial Bluetooth(13, 12);
Servo myservo;
int Position ;

void setup() {
  // put your setup code here, to run once:
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  Bluetooth.println("Ready for command...");
  myservo.attach(11);  
}

void loop() {
delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

    //Bluetooth.println("Comfortable level of humidity and temperature");

    Serial.print(dht.readHumidity()); Serial.print(" %\t\n");
    Serial.print(dht.readTemperature()); Serial.println(" Degree Celsius\t");
    Bluetooth.print("The Humidity and Temperature are \n");
    Bluetooth.print(dht.readHumidity()); Bluetooth.print(" %  and \t\n");
    Bluetooth.print(dht.readTemperature()); Bluetooth.println(" Degree Celcius Respectively \t");
    
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  if(Bluetooth.available()>0)
  {
  Position = Bluetooth.read();
  Position = map(Position, 0, 180, 180, 0); 
  myservo.write(Position);        
  //myservo.write(0);        
  //myservo.write(180);        
  }

}
