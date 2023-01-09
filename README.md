# Internet of Things
This is an Arduino project that simulates a traffic light system on the ThingSpeak platform. This project was part of a course I did in my 8th semester.

## Prerequisites
To use the files in this repository, you will need the following:
1. ThingSpeak account
2. Arduino Uno 
3. ESP-01
4. 2 Resistors 1kΩ, 2kΩ

## Getting Started
To get started with this project, follow these steps:
1. Log in to your ThingSpeak account and create a new channel.
2. Add three fields to the channel and name them field1, field2, and field3.
3. In the Source_Code.ino file, replace the following variable values with your own:
    ```
    mySSID: Wi-Fi SSID
    
    myPassword: Wi-Fi password
    
    myWriteAPI: Write API of your ThingSpeak channel
    ```
4. Upload the code to your Arduino board and start the Serial Monitor to view the output.
5. Go to your ThingSpeak channel and verify that data is being sent from the traffic light system.

## Contents
This repository contains the following files:
1. Source_Code.ino
2. Circuit.png

## Specifications

### Functionality

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
- The following arduino circuit.

    ![Circuit](https://github.com/achilleaspappas/Internet-of-Things/blob/main/Circuit.png)

## Contributing

This is a university project so you can not contribute.

## Authors

* **[University of West Attica]** - *Provided the exersice*
* **[Achilleas Pappas]** - *Wrote the code*

## License

This project is licensed by University of West Attica as is a part of a university course. Do not redistribute.

## Acknowledgments

Thank you to **University of West Attica** and my professors for providing the resources and knowledge to complete this project.

