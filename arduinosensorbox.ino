#include <DHT.h>
#include <SPI.h>

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

//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

const int SECOND 1000
const int MINUTE 60 * SECOND

// Globales defintions
double temperature;
short pressure;
double humidity;
struct gps gps;

void setup() {

}

void loop() {
	get_data();
	struct data data = converfortransfer();

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


}
