
//complete all the required settings for Adafruit IO
#define IO_USERNAME ""
#define IO_KEY ""

//complete all the required settings for Wi-Fi
#define WIFI_SSID ""
#define WIFI_PASS ""

#include <AdafruitIO_WiFi.h>
#include <ESP32Servo.h>
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

//  connect your Adafruit to  toggle feed
AdafruitIO_Feed *toggle = io.feed("test");

//connect your Adafruit to servo feed
AdafruitIO_Feed *servoControl = io.feed("servo");

Servo myServo;
#define servo_pin 21
#define LED_PIN 13

int pos = 0; //stores servo position

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial){delay(100);}

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

    // we are connected
  Serial.println();
  Serial.println(io.statusText());

  myServo.attach(servo_pin);
  // attach handleMessage function to handle the data when there is a change
  servoControl->onMessage(handleServoControl);
}

void handleServoControl(AdafruitIO_Data *data)
 {
  int position = data->toInt(); // slider data is an integer -> servo position
  Serial.print("Setting servo to position: ");
  Serial.println(position);
  myServo.write(position); // set the servo position
}

void loop() {
  io.run();
  //display LED status on Serial Monitor
  Serial.print("received <- ");

  if(toggle->data->toPinLevel() == HIGH){
      Serial.println("HIGH");
  }
  else{
      Serial.println("LOW");
  }
  digitalWrite(LED_PIN, toggle->data->toPinLevel()); 
  delay(5000);
}
