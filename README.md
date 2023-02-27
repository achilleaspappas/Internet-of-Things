# Internet of Things
Arduino and ThinkSpeak

## Components
- Arduino Uno 
- ESP-01
- 2 Resistors 1kΩ, 2kΩ

![Circuit](https://github.com/achilleaspappas/Internet-of-Things/blob/main/Circuit.png)

## Exercise - Source_Code.ino

You are invited to create a traffic light whose function will be defined by the Arduino microcontroller and
visualized on the ThingSpeak IoT platform. The traffic light should operate continuously, with the changes
of indications following the order:

- Red indication, duration >=30secs
- Green indication, duration >=30secs
- Orange indication, duration >=20secs
- Red indication, duration >=30secs
- …etc.

For this implementation, the following will be needed:
- Use of visual elements in the ThingSpeak channel to illustrate the above desired function.
- Connection of the above visual elements with a variable or variables of the channel.
- Connecting the Arduino to the nearest WiFi AP using the ESP-01.
- Arduino programming with the aim of operating the visual elements in ThingSpeak, according to the above requirements.
- Programming code which determines an orange light indicator on the traffic light every 10 minutes and this lasts for 1 minute.
