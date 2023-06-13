#ifndef RTCSENSORSRP_H
#define RTCSENSORSRP_H

#include <Arduino.h>
#include <Wire.h>

class SenzorRTC {
public:
  SenzorRTC();
  void pocetak();
  void postaviVreme(uint8_t sati, uint8_t minuti, uint8_t sekunde);
  void postaviDatum(uint8_t dan, uint8_t mesec, uint16_t godina);
  void dohvatiVreme(uint8_t &sati, uint8_t &minuti, uint8_t &sekunde);
  void dohvatiDatum(uint8_t &dan, uint8_t &mesec, uint16_t &godina);
  void postaviAlarm(uint8_t brojAlarma, uint8_t sati, uint8_t minuti, uint8_t sekunde);
  void omoguciPrekidAlarma(uint8_t brojAlarma);
  void onemoguciPrekidAlarma(uint8_t brojAlarma);
  void omoguciKvadratniSignal(uint8_t frekvencija);
  void onemoguciKvadratniSignal();
  float dohvatiTemperaturu();

private:
  static const uint8_t ADRESA_DS3231 = 0x68;

  uint8_t decUZambo(uint8_t val);
  uint8_t zamboUDec(uint8_t val);
};

#endif
