MQTT-c-pub-sub
==============
This projects builds a simple (QoS0) MQTT client and server process.
The client will send messages to a MQTT broker (e.g. mosquito) and the server will display those messages.

The build assumes you have CMake installed.

to Build:
cd build
cmake ..
make

note on OSX need

cmake -G "Unix Makefiles" ..

================ Added by karthikeyanprakash ========================

<Source>/test 
-This folder contains PUB_SUB in same program
<Source>/test1
-This folder contains Paho_mqtt test programs

To test Paho Mqtt program donwload Paho.C.Library and add the library path, Source file path in SConstruct file.

