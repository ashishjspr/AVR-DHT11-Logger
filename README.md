# AVR-DHT11-Logger

Data logger which logs Temperature and Humidity values in Internal EEPROM.

For this I have selected Atmega128 microcontroller which has 4096 bytes of memory available for storage. It is an 8 bit microcontroller with 6 available ports.

Here,DHT11 Temperature and humidity sensor has been used. DHT pin is connected to pin 6 of PORT D. According to the datasheet, the DHT11 sensor works as follows:

 

1>Generate Request (Pulse )

2>Get Response

3>Receive DATA(40 bytes including checksum)

#Two buttons have been used for selection between Logging and Retrieval.

1>Logging:When Button1 is pressed(grounded) and Button2 open.

2>Retrieval:When Button 2 is pressed (grounded)and Button 1 open.

It has been simulated in Proteus Software. Atmega128 is being used(at 16Mhz).The hex file for this is generated using Atmel Studio 6. The values are displayed over LCD. The schematic can be found in repository(simulated in Proteus)
