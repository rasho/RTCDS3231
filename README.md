# Biblioteka za RTC senzor

Ova biblioteka omogućava upravljanje i očitavanje RTC (Real-Time Clock) senzora na Arduino platformi. Konkretno, biblioteka je prilagođena za korišćenje sa DS3231 RTC senzorom.

## Instalacija

1. Preuzmite biblioteku:
   - Kliknite na zeleno dugme "Code" na GitHub stranici projekta
   - Izaberite opciju "Download ZIP" za preuzimanje biblioteke kao ZIP arhivu
2. U Arduino IDE-u idite na **Sketch > Include Library > Add .ZIP Library...**
3. Izaberite preuzetu ZIP arhivu biblioteke
4. Instalacija će se završiti, a biblioteka će biti dostupna u vašem Arduino projektu

## Korišćenje biblioteke

1. Uključite biblioteku u vaš Arduino kod dodavanjem linije `#include <RTCsenzor.h>`
2. Kreirajte objekat klase `SenzorRTC` za upravljanje RTC senzorom
3. Koristite metode objekta za postavljanje vremena, datuma, alarma, itd.

```cpp
#include <RTCsenzor.h>

SenzorRTC rtc;

void setup() {
  Serial.begin(9600);
  rtc.pocetak();
}

void loop() {
  uint8_t sati, minuti, sekunde;
  rtc.dohvatiVreme(sati, minuti, sekunde);

  Serial.print("Trenutno vreme: ");
  Serial.print(sati);
  Serial.print(":");
  Serial.print(minuti);
  Serial.print(":");
  Serial.println(sekunde);

  delay(1000);
}
```

## Primeri

Uključeni su i primeri koji demonstriraju različite funkcionalnosti biblioteke. Možete ih pronaći u wikistranici(#https://github.com/rasho/RTCDS3231/wiki/Primeri-koda)

## Autori

Ova biblioteka je razvijena od strane Radenko Bogdanovic. Ako imate pitanja ili povratne informacije, slobodno me kontaktirajte na rasho984@gmail.com.

## Licenca

Ova biblioteka je objavljena pod MIT licencom.
