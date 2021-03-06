/* RGB1
    Door
    PiR
    RGB
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Timer.h>


//define GPIO pin
#define red 13
#define green 15
#define blue 16

#define pir_pin 10
#define magDoor_pin 12

Timer timer;
int authenticate_timer;


char* rgb = "{\"deviceType\":\"LightingControl\",\"deviceCode\": \"rgb2\",\"numberOfPorts\": 1, \"lights\": [{\"portId\": 1, \"dimmable\": false, \"typeOfLight\": \"RGB\"}]}";
String rgb_id = "";

char* door = "{\"deviceType\":\"LightingControl\", \"deviceCode\": \"door2\",\"lights\": [{\"portId\": 1,\"name\": \"Door2\",\"dimmable\": false,\"typeOfLight\": \"Alarm\"}]}";
String door_id = "";

char* pir = "{\"deviceType\":\"SensorModule\",\"deviceCode\": \"pir2\",\"sensors\": [{\"name\": \"PIR2\", \"_type\": \"Pir\", \"value\": 0}]}";
String pir_id = "";


const char* ssid     = "SmartHome";
const char* password = "smarthome";

//define mqtt parameters
#define host "192.168.0.100"
#define mqtt_topic_pub "presence"
#define mqtt_topic_sub "presence"
#define mqtt_topic_lwt "lwt"
#define mqtt_user "alice"
#define mqtt_pwd "secret"
const uint16_t mqtt_port = 1883;


int delayTime = 8000;
int light = 0;
int ledValue = 0;

//MQTT client
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//Authenticate timer function
void authenticate_rgb() {
  Serial.println("authenticating rgb..");
  client.publish("authenticate", rgb);
}

void authenticate_pir() {
  Serial.println("authenticating pir..");
  client.publish("authenticate", pir);
}

void authenticate_door() {
  Serial.println("authenticating door..");
  client.publish("authenticate", door);
}


//mqtt callback function
void callback(char* topic, byte* payload, unsigned int length) {
  String rmsg = "";
  //  Serial.println("Message arrived");
  // Serial.println("Topic: " + (String)topic);
  //  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    rmsg += (char)payload[i];
  }
  Serial.println(rmsg);

  if ((String)topic == "devices/" + rgb_id) {
    char light = rmsg.charAt(0);
    if (light == '1') {
      rmsg.remove(0, 2);
      long number = strtol( rmsg.c_str(), NULL, 16);
      // Split them up into r, g, b values
      int red_8bit = number >> 16;
      int green_8bit = number >> 8 & 0xFF;
      int blue_8bit = number & 0xFF;
      int red_10bit = red_8bit * 1023 / 255;
      int green_10bit = green_8bit * 1023 / 255;
      int blue_10bit = blue_8bit * 1023 / 255;
      analogWrite(red, red_10bit);
      analogWrite(green, green_10bit);
      analogWrite(blue, blue_10bit);
    }

  } else  if ((String)topic == "authenticate/rgb2") {
    timer.stop(authenticate_timer);
    rgb_id = rmsg;
    String topic = "devices/" + rgb_id;
    client.subscribe(topic.c_str());
    Serial.println(topic.c_str());
    authenticate_timer = timer.every(1000, authenticate_pir);

  } else  if ((String)topic == "devices/" + door_id) {
    int value = rmsg.charAt(1) - '0';
    digitalWrite(magDoor_pin, value);

  } else if ((String)topic == "authenticate/pir2") {
    timer.stop(authenticate_timer);
    pir_id = rmsg;
    String topic = "devices/" + pir_id;
    client.subscribe(topic.c_str());
    Serial.println(topic.c_str());
    authenticate_timer = timer.every(1000, authenticate_door);

  } else if ((String)topic == "authenticate/door2") {
    timer.stop(authenticate_timer);
    door_id = rmsg;
    String topic = "devices/" + door_id;
    client.subscribe(topic.c_str());
    Serial.println(topic.c_str());
  }
}

// Connect to mqtt broker
void checkMqttConnection() {
  // Loop until we're reconnected
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("rgb2", "lwt", 0, false, "rgb2")) {
      Serial.println("connected");
      //client.publish("connected", "hello");\
      delay(10);
      client.subscribe("authenticate/rgb2");
      client.subscribe("authenticate/pir2");
      client.subscribe("authenticate/door2");
      authenticate_timer = timer.every(5000, authenticate_rgb);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
    }
  }
}


void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(magDoor_pin, OUTPUT);
  pinMode(pir_pin, INPUT);
  
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);

  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(host, mqtt_port);
  client.setCallback(callback);
  timer.every(3000, checkMqttConnection);
}

boolean eValue = false,  dValue = false;
boolean eValue_previous = false, dValue_previous = false;

void readPirSensorValue() {
  eValue = digitalRead(pir_pin);
  if (eValue != eValue_previous) {
    eValue_previous = eValue;
    Serial.println(eValue);
    String topic  = "devices/sensorModule/" + pir_id;
    sprintf(pir, "{\"deviceType\":\"SensorModule\",\"deviceCode\": \"pir2\",\"sensors\": [{\"name\": \"Pir2\", \"_type\": \"Pir\", \"value\": %d}]}",  eValue);
    client.publish(topic.c_str(), pir);
  }
}

void loop() {
  client.loop();
  timer.update();
  readPirSensorValue();
}
