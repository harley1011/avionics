avionics
========

Rocket Controls:

Rocket will contain an arduino that will use I2C to retrieve data from a 9 DOF sensor.
The arduino will then process that data and transmit it over the serial conection which will be with an Xbee Cordinator in AT mode that will transmit the information to the ground.
The arduino will also deploy the parachute at a calculated time using the onboard sensor. 
The xbee will also be listening for a manual parachute deploy code from ground incase the parachute does not
deploy automatically.

Ground Controls:

A laptop connected to a xbee router in AT mode that will transmit any data it recieves from the laptop via
a serial connection.

