# Websocket Op Codes

The firmware expects a set of instructions, through a websocket buffer.

All instructions can accept arguments as bytes (the bytes after the Op Code byte). The length of arguments may vary with different instructions.

This doc file mostly refers to `command.h` where the enum definition for Op codes can be found

> Some core bindings are missing, since they we're not used durring development. 

<br/>
<br/>

## GPIO Mode

Set the mode of a GPIO pin

**Arguments(1):**
- Mode of the pin (see [modes](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html#_CPPv411gpio_mode_t))

**Response(2):**
- `Ok`

**Example:**
```
0x7F 0x03
```

<br/>

## GPIO Write

write to a GPIO pin

**Arguments(1):**
- State of the Pin

**Response(2):**
- `Ok`

**Example:**
```
0x80 0x01
```

<br/>

## Motor Control Instruction

Control motors through PWM

**Arguments(2):**
- Left motor percentage from -100 to 100
- Right motor percentage from -100 to 100


**Response(2):**
- `Ok`

**Example:**
```
0xC0 -50 50
```

<br/>

## Trigger Ultrasound 

Get a distance value from the Ultrasound sensor

**Response(2):**
- MSByte of distance value
- LSByte of distance value

**Example:**
```
0xD0