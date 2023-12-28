# Firmware




## Tasks

The robot's firmware can be broken down into 3 core parts.

<br/>

## Access Point

This firmware hosts a network Access Point with DHCP. 

Access Point configuration `(SSID, PASS)` can be found in `wifi_cred.h`, feel free to edit it.

---

<br/>

## Webserver  

Listen for Websockets connections under the `/ws` endpoint expecting buffer data and send a response.

All other endpoints are ignored.


---


<br/>

## Match Op Code & Execute

Parse incoming websocket buffers into commands & arguments.

Execute desired tasks on the esp32s3 device.

Some of the instructions bind simple `esp-idf` operations while other bind calls from `motor.c` or `ultrasound.c`

Op code information can be found [here](./OPCODES.md)

---


<br/>

