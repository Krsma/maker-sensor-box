#include <DHT.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Gpsneo.h>
#include "Sodaq_RN2483.h"

#define loraSerial Serial1
#define beePin 20

//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321


//lora keys
// USE YOUR OWN KEYS!
const uint8_t devAddr[4] =
{
	0x00, 0x00, 0x02, 0x03
};
// USE YOUR OWN KEYS!
const uint8_t appSKey[16] =
{
	0x0D, 0x0E, 0x0A, 0x0D,
	0x0B, 0x0E, 0x0E, 0x0F,
	0x0C, 0x0A, 0x0F, 0x0E,
	0x0B, 0x0A, 0x0B, 0x0E,
};
// USE YOUR OWN KEYS!
const uint8_t nwkSKey[16] =
{
	0x0D, 0x0E, 0x0A, 0x0D,
	0x0B, 0x0E, 0x0E, 0x0F,
	0x0C, 0x0A, 0x0F, 0x0E,
	0x0B, 0x0A, 0x0B, 0x0E,
};
//change keys before deployment


Gpsneo gps;

char latitud[11];
char latitudHemisphere[3];
char longitud[11];
char longitudMeridiano[3];


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

debugSerial.begin(57600);
loraSerial.begin(LoRaBee.getDefaultBaudRate());

loraBee.initABP(loraSerial,devaddr,appSKey,nwkSKey,true)

}

void loop() {

	get_data();
	struct data data = converfortransfer();

	delay(MINUTE);
	//send(1,data,16);
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
