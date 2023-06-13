#include "SenzorRTC.h"

SenzorRTC::SenzorRTC() {}

void SenzorRTC::pocetak() {
  Wire.begin();
}

void SenzorRTC::postaviVreme(uint8_t sati, uint8_t minuti, uint8_t sekunde) {
  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x00); // Adresa registra za postavljanje vremena
  Wire.write(decUZambo(sekunde) & 0x7F);  // Sekunde (bit 7 postavljen na 0 za 24-časovni format)
  Wire.write(decUZambo(minuti));  // Minuti
  Wire.write(decUZambo(sati));    // Sati
  Wire.endTransmission();
}

void SenzorRTC::postaviDatum(uint8_t dan, uint8_t mesec, uint16_t godina) {
  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x04); // Adresa registra za postavljanje datuma
  Wire.write(decUZambo(dan));    // Dan
  Wire.write(decUZambo(mesec));  // Mesec
  Wire.write(decUZambo(godina - 2000)); // Godina (2 cifre)
  Wire.endTransmission();
}

void SenzorRTC::dohvatiVreme(uint8_t &sati, uint8_t &minuti, uint8_t &sekunde) {
  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x00); // Adresa registra za čitanje vremena
  Wire.endTransmission();

  Wire.requestFrom(ADRESA_DS3231, 3); // Čitanje 3 bajta (sati, minuti, sekunde)
  sekunde = zamboUDec(Wire.read()) & 0x7F;
  minuti = zamboUDec(Wire.read());
  sati = zamboUDec(Wire.read());
}

void SenzorRTC::dohvatiDatum(uint8_t &dan, uint8_t &mesec, uint16_t &godina) {
  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x04); // Adresa registra za čitanje datuma
  Wire.endTransmission();

  Wire.requestFrom(ADRESA_DS3231, 3); // Čitanje 3 bajta (dan, mesec, godina)
  dan = zamboUDec(Wire.read());
  mesec = zamboUDec(Wire.read());
  godina = 2000 + zamboUDec(Wire.read()); // Godina (2 cifre)
}

void SenzorRTC::postaviAlarm(uint8_t brojAlarma, uint8_t sati, uint8_t minuti, uint8_t sekunde) {
  uint8_t adresaAlarma = 0x07 + (brojAlarma - 1) * 4;

  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(adresaAlarma);
  Wire.write(decUZambo(sekunde) & 0x7F);
  Wire.write(decUZambo(minuti) & 0x7F);
  Wire.write(decUZambo(sati) & 0x7F);
  Wire.endTransmission();
}

void SenzorRTC::omoguciPrekidAlarma(uint8_t brojAlarma) {
  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x0E); // Adresa kontrolnog registra
  Wire.endTransmission();

  Wire.requestFrom(ADRESA_DS3231, 1);
  uint8_t kontrolniRegistar = Wire.read();

  kontrolniRegistar |= (1 << (brojAlarma - 1));

  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x0E); // Adresa kontrolnog registra
  Wire.write(kontrolniRegistar);
  Wire.endTransmission();
}

void SenzorRTC::onemoguciPrekidAlarma(uint8_t brojAlarma) {
  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x0E); // Adresa kontrolnog registra
  Wire.endTransmission();

  Wire.requestFrom(ADRESA_DS3231, 1);
  uint8_t kontrolniRegistar = Wire.read();

  kontrolniRegistar &= ~(1 << (brojAlarma - 1));

  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x0E); // Adresa kontrolnog registra
  Wire.write(kontrolniRegistar);
  Wire.endTransmission();
}

void SenzorRTC::omoguciKvadratniSignal(uint8_t frekvencija) {
  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x0E); // Adresa kontrolnog registra
  Wire.endTransmission();

  Wire.requestFrom(ADRESA_DS3231, 1);
  uint8_t kontrolniRegistar = Wire.read();

  kontrolniRegistar |= 0x10; // Postavljanje bita 4 za omogućavanje kvadratnog signala

  switch (frekvencija) {
    case 1:
      kontrolniRegistar &= ~(0x03); // Bitovi 0 i 1 postavljeni na 0 za 1 Hz
      break;
    case 2:
      kontrolniRegistar |= 0x01; // Bit 0 postavljen na 1, bit 1 postavljen na 0 za 1.024 kHz
      break;
    case 4:
      kontrolniRegistar |= 0x02; // Bit 0 postavljen na 0, bit 1 postavljen na 1 za 4.096 kHz
      break;
    case 8:
      kontrolniRegistar |= 0x03; // Bitovi 0 i 1 postavljeni na 1 za 8.192 kHz
      break;
    default:
      break;
  }

  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x0E); // Adresa kontrolnog registra
  Wire.write(kontrolniRegistar);
  Wire.endTransmission();
}

void SenzorRTC::onemoguciKvadratniSignal() {
  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x0E); // Adresa kontrolnog registra
  Wire.endTransmission();

  Wire.requestFrom(ADRESA_DS3231, 1);
  uint8_t kontrolniRegistar = Wire.read();

  kontrolniRegistar &= ~(0x10); // Bit 4 postavljen na 0 za isključivanje kvadratnog signala

  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x0E); // Adresa kontrolnog registra
  Wire.write(kontrolniRegistar);
  Wire.endTransmission();
}

float SenzorRTC::dohvatiTemperaturu() {
  Wire.beginTransmission(ADRESA_DS3231);
  Wire.write(0x11); // Adresa registra za čitanje temperature
  Wire.endTransmission();

  Wire.requestFrom(ADRESA_DS3231, 2); // Čitanje 2 bajta (temperatura)
  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();

  int16_t temperatura = ((msb << 8) | lsb);
  temperatura >>= 6; // Skaliranje temperature

  return temperatura * 0.25; // Vrednost temperature u °C
}

uint8_t SenzorRTC::decUZambo(uint8_t val) {
  return ((val / 10 * 16) + (val % 10));
}

uint8_t SenzorRTC::zamboUDec(uint8_t val) {
  return ((val / 16 * 10) + (val % 16));
}
