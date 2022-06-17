#include <Servo.h>
#include <IRremote.hpp>

#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Defining remote control buttons

#define Button_1 3125149440

#define Button_2 3108437760


#define Button_3 3091726080

#define Button_4 3141861120


#define Button_5 3208707840


#define Button_6 3158572800


#define Button_7 4161273600


#define Button_8 3927310080


#define Button_9 4127850240


#define Button_0 3860463360


#define Button_star 3910598400


#define Button_grille 4061003520

#define Button_ok 3810328320



#define DHTPIN 5     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

//REMOTE CONTROL
const int IR_RECEIVE_PIN = 13;

decode_results results;

//LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);


//SERVOMOTOR
Servo myservo;  // create servo object to control a servo twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

int potpin = 3;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int threshold = 3;
int percent_angle_inclination;  //the percentage of the angle of inclination


void setup() {

  //Initiaze servomotor

  myservo.attach(2);  // attaches the servo on pin 2 to the servo object


  //lcd.begin(16,2);

  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Syvak Yuriy");
  lcd.setCursor(1, 1);
  lcd.print("IR-22  IoT");

  //Initiaze Temperature sensor
  dht.begin();

  //Initiaze remote control
  Serial.begin(9000);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);



}

void loop() {

  //connection potentiometer to servomotor
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)



  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  percent_angle_inclination = ((val * 100) / 180); // finding percent of the angle of inclination between 0 to 1013 (0 to 180%)
  if (lcdState == 1) {

  }

  int diff = val - pos;
  diff = diff > 0 ? diff : -diff;
  if (diff > threshold)
  {
    pos = val;
    myservo.write(val);                  // sets the servo position according to the scaled value
    delay(15);
  }



  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);


  //remote control
  if (IrReceiver.decode()) {
    Serial.print("IR:");
    Serial.println(IrReceiver.decodedIRData.decodedRawData);


    switch (IrReceiver.decodedIRData.decodedRawData) {
      case Button_1:
        lcd.setCursor(8, 1);
        lcd.print("1");
        break;

      case Button_2:
        lcd.setCursor(8, 1);
        lcd.print("2");
        break;

      case Button_3:
        lcd.setCursor(8, 1);
        lcd.print("3");
        break;


      case Button_4:
        lcd.setCursor(8, 1);
        lcd.print("4");
        break;

      case Button_5:
        lcd.setCursor(8, 1);
        lcd.print("5");
        break;

      case Button_6:

        lcd.setCursor(8, 1);
        lcd.print("6");
        break;

      case Button_7:
        lcd.setCursor(8, 1);
        lcd.print("7");
        break;

      case Button_8:
        lcd.setCursor(8, 1);
        lcd.print("8");
        break;

      case Button_9:

        lcd.setCursor(8, 1);
        lcd.print("9");
        break;

      case Button_grille:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Humidity "));
        lcd.print(h);
        lcd.setCursor(0, 1);
        lcd.print(F("Temperat: "));
        lcd.print(t);
        lcd.print(F("C "));
        break;

      case Button_star:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Percentage: ");
        lcd.print(percent_angle_inclination);
        lcd.setCursor(0, 1);
        lcd.print("Speed: ");
        break;
    }

    IrReceiver.resume();
  }
}
