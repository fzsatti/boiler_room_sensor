# boiler_room_sensor

This code is created to be uploaded to a Node MCU with integrated display and connected to two DS18b20 temperature sensors.

It gets the time in my time zone, the two temperatures from the two sensors, then displays it in every second, and sens to firebase realtime database in every 30 seconds.

In order to use it, make a copy of `env.h.example` as `env.h` and set yor credentials.
 
