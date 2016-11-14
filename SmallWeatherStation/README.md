#SmallWeatherStation

This project aims to create a small wheather station. It currenlty reads the ambiental temperature and relative humidity from a sensor and sends it to the serial console, nothing fancy

##Hardware:
 - Arduino pro mini 5v 16 MHz
 - DHT11 basic temperature-humidity sensor

##Features
 - Serial output
 - Temperature reading
 - Humidity reading

##TODO:
 - Add a timer interrupt in which we read the values from sensors and do something different in the main loop.
 - Transmit the collected data about temperature to esp8266 module.
 - Run in low power mode. Try to run a month on external battery.
