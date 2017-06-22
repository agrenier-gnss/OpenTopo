# Open Topo 

The Open Topo project is an open source project, which goal is to developpe lowcost topographic survey equipment, with the conception plans and softwares accessibles by anybody freely.  The purpose is to democratize topography and facilitate its accession by developing countries, ravage by war or natural disaster. 

## Open GNSS

### Hardware

As today, the project aim to developpe a lowcost GNSS acquisition system. Hardware will be composed of:

- Two M8P µBlox module, conceived to work together as a reference and a rover, linked by radio and producing DGNSS Data. 

- Two ESP8266 module, allowing GNSS data gathering & processing from the GNSS module, which then will be send by wifi on a computer or a phone.

- Two GNSS antenna, to receve GNSS signal on the base and the rover. Geodesic antenna seems to be the best choice for high precision GNSS.

As for now the actual hardware for developpement is: 

- Two C94-M8P µBlox board

- One ESP8266EX Demo Board

- Two geodesic antenna (reference ?)

### Software

Code for the hardware is currently developped in Arduino, and run into the ESP8266EX Board. 
Code for phone or computer will be developped in JavaScript.

