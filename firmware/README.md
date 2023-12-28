# Firmware

## Build & Upload Firmware

We are using the official esp-idf sdk, once installed, you can run the alias to get everything setup.

```
get_idf
```

you can then build the project with `make build` run `make upload` assuming you are in `./firmware`

---


<br/>

## Main Firmware Tasks

The esp32 car's firmware can be broken down into 3 core parts.

### Access Point

This firmware hosts a network Access Point with DHCP. 

Access Point configuration `(SSID, PASS)` can be found in `wifi_cred.h`, feel free to edit it.

---


### Webserver  

Listen for Websockets connections under the `/ws` endpoint expecting buffer data and send a response.

All other endpoints are ignored.

> NOTE: The firmware does not support encrypted websockets (wss) yet, which makes it impossible to use it from a https client. You would need to run oxenode from a local instance or upgrade the firmware to support wss.

---


### Match Op Code & Execute

Parse incoming websocket buffers into commands & arguments.

Execute desired tasks on the esp32s3 device.

Some of the instructions bind simple `esp-idf` operations while other bind calls from `motor.c` or `ultrasound.c`

Op code information can be found [here](./OPCODES.md)

---


<br/>

