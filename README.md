### Config:

Edit `<arduino ide directory>/hardware/arduino/avr/cores/arduino/HardwareSerial.h`

Change:
```cpp
#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 64
```

To:
```cpp
#define SERIAL_TX_BUFFER_SIZE 256
#define SERIAL_RX_BUFFER_SIZE 256
```

Edit `<arduino ide directory>/hardware/arduino/avr/libraries/SoftwareSerial/src/SoftwareSerial.h`:

Change:
```cpp
#define _SS_MAX_RX_BUFF 64
```

To:
```cpp
#define _SS_MAX_RX_BUFF 256
```

Create `config.h`:
```cpp
#define SOFTWARE_SERIAL
#define DEBUG_MODE
#define MAX_BUFFER_SIZE 200
#define BAUD_RATE_SERIAL 9600
#define SS_RX_PIN 7
#define SS_TX_PIN 8
#define WAKEUP_PIN 2
#define MOSFET_PIN 13
#define PHONE_NUMBER "+98**********"
```