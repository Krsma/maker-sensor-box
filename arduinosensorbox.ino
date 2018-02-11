#include <DHT.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Gpsneo.h>
#include <rn2xx3.h>
#include "ttn_keys.h"

#include "keys.h"


//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321



rn2xx3 myLora(Serial1);
Gpsneo gps;

char latitud[11];
char latitudHemisphere[3];
char longitud[11];
char longitudMeridiano[3];

int lora_data[16];

// Structure definitions
struct gps {
	float latitude;
	float longitude;
};
struct gps_small {
	int latitude;
	int longitude;
};
struct data {
  short temperature;
  short pressure;
  short humidity;
	struct gps_small gps;
};


DHT dht(DHTPIN, DHTTYPE);

const int SECOND 1000
const int MINUTE 60 * SECOND

// Globales defintions
double temperature;
short pressure;
double humidity;
struct gps gps;

void setup() {

digitalWrite(beePin, HIGH)
pinmode(beePin,OUTPUT)

Serial.begin(57600);
Serial1.begin(57600);
debugSerial.begin(57600);

initialize_radio();
delay(3000);
}

void loop() {

	get_data();
	struct data data = converfortransfer();
  //lora_data = data  conversion from data struct to array
  //myLora.txBytes(lora_data, 16);

	delay(MINUTE);
	
}
// Shortening data for easiier transfer via LoraWan
struct data converfortransfer() {

	struct data package;
  package.temperature = temperature * 100;
	package.pressure = pressure;
  package.humidity = humidity * 100;
	package.gps.latitude = gps.latitude * 10000000;
	package.gps.longitude = gps.longitude * 10000000;
	return package;
}
void get_data()
{
  // Read humidity
	humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temperature = dht.readTemperature();
  // Read pressure data

  // Read gps data
	gps.getDataGPRMC(latitud,
                    latitudHemisphere,
                    longitud,
                    longitudMeridiano);

}

void initialize_radio()
{

delay(100);
Serial1.flush();

//hweui check????

joined = myLora.initABP(DEV_ADDR, APP_SES_KEY, NWK_SES_KEY);
while(!joined)
  {
    delay(MINUTE);
    joined = myLora.init();

  }


}