#include <dht.h>
#include <stdio.h>

#define DEBUG           0
#define LOG(message)    if(DEBUG) { Serial.println(message); }

#define SENSOR_PIN      2

//The Temperature or the humidity cannot change faster than this value
#define DELTA           5000  //ms

dht gSensor;

struct readOut {
  char *name;
  char *symbol;
  double value = 0;
  unsigned long lastModification = 0;
};

int hasChanged(readOut &r, double &v) {
  unsigned long currentTime = millis();
  if ((int)r.value != (int)v && (currentTime - r.lastModification) > DELTA) {
    r.value = v;
    r.lastModification = currentTime;
    return 1;
  } else {
    LOG("[INFO]:\tNo change!");
    return 0;
  }
}

void preattyPrint(readOut &r);

readOut gTemperature;
readOut gHumidity;

void setup(){
  Serial.begin(115200);
  gTemperature.name = "Temperature";
  gTemperature.symbol = "°C";

  gHumidity.name = "Humidity";
  gHumidity.symbol = "%";
}

void loop()
{
  int chk = gSensor.read11(SENSOR_PIN);

  if(chk == DHTLIB_OK) {
    unsigned long currentTime = millis();
        
    double temp = gSensor.temperature;
    if(hasChanged(gTemperature, temp)) {
      preattyPrint(gTemperature);
    }
   
    double hum = gSensor.humidity;
    if(hasChanged(gHumidity, hum)) {
      preattyPrint(gHumidity);
    }
  } else {
    LOG("[ERROR]:\tFailed to read from sensor!")
  }

  delay(1000);
}

void preattyPrint(readOut &r) {
  char buffer[100];
  sprintf(buffer, "%s:\t%d%s", r.name, (int)r.value, r.symbol);
  Serial.println(buffer);
}
