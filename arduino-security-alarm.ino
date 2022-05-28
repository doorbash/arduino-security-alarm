#include "config.h"
#include <LowPower.h>
#include "serial_handler.h"

SerialHandler serial;
bool sleeping = true;

void zzz() {
  SerialHandler::debug("Good Night!");
#ifdef DEBUG_MODE
  delay(1000);
#endif
  attachInterrupt(digitalPinToInterrupt(WAKEUP_PIN), wakeUp, RISING);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  detachInterrupt(digitalPinToInterrupt(WAKEUP_PIN));
}

void wakeUp() {
  SerialHandler::debug("wakeUp()");
  sleeping = false;
}

void setup() {
  pinMode(WAKEUP_PIN, INPUT);
  pinMode(MOSFET_PIN, OUTPUT);

  digitalWrite(MOSFET_PIN, LOW);

  serial.init();

  if (SERIAL_TX_BUFFER_SIZE != 256 || SERIAL_RX_BUFFER_SIZE != 256) {
    while (true) {
      SerialHandler::debug("please set hardware serial rx/tx buffer size to 256");
      delay(1000);
    }
  }
#ifdef SOFTWARE_SERIAL
  if (_SS_MAX_RX_BUFF != 256) {
    while (true) {
      SerialHandler::debug("please set software serial rx buffer size to 256");
      delay(1000);
    }
  }
#endif

  ADCSRA = 0;
  delay(10000);
}

void loop() {
  if (sleeping) {
    zzz();
    return;
  }

  SerialHandler::debug("Hello There!");
  digitalWrite(MOSFET_PIN, HIGH);

  delay(5000);

  serial.command("ATE0");
  delay(500);

  for (int i = 0; i < 4; i++) {
    serial.command("ATD%s;", PHONE_NUMBER);
    delay(5000);
  }

  delay(15000);

  serial.command("ATH");
  delay(500);

  digitalWrite(MOSFET_PIN, LOW);

  sleeping = true;
}
