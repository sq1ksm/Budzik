Zegar z Alarmem na Arduino
Opis Projektu
Ten projekt to zegar z funkcją alarmu oparty na platformie Arduino Nano, który wykorzystuje wyświetlacz OLED i zegar RTC DS3231. Zegar wyświetla aktualną datę, godzinę i temperaturę na ekranie OLED. Dodatkowo, umożliwia ustawienie godziny i minuty alarmu za pomocą przycisków oraz zapisanie tych ustawień w pamięci EEPROM, dzięki czemu alarm pozostaje zapamiętany nawet po odłączeniu zasilania. Projekt jest również wyposażony w brzęczyk, który generuje dźwięk w momencie włączenia alarmu.

Cechy
Wyświetlanie Aktualnego Czasu i Daty:
Wyświetlacz OLED prezentuje bieżącą datę, godzinę i temperaturę.
Wykorzystano bibliotekę Adafruit_GFX oraz Adafruit_SSD1306 do obsługi wyświetlacza OLED.
Zegar RTC DS3231 zapewnia dokładne dane dotyczące czasu i temperatury.

Funkcja Alarmu:
Użytkownik może ustawić godzinę i minutę alarmu za pomocą przycisków.
Ustawienia alarmu są wyświetlane na ekranie OLED w trybie konfiguracji.
Kiedy aktualny czas pokrywa się z ustawionym alarmem, brzęczyk generuje dźwięk przez 15 sekund.

Pamięć EEPROM:
Ustawienia alarmu (godzina i minuta) są zapisywane w pamięci EEPROM.
Dzięki temu alarm pozostaje zapamiętany nawet po odłączeniu zasilania.

Komunikacja Szeregowa:
Dane dotyczące aktualnego czasu i ustawień alarmu są wysyłane przez port szeregowy co 5 sekund, co pozwala na monitorowanie pracy zegara.

Wymagane Podzespoły
Arduino Nano
Wyświetlacz OLED SSD1306
Moduł RTC DS3231
Brzęczyk piezoelektryczny
2 przyciski
Rezystory podciągające dla przycisków (10kΩ)
Przewody połączeniowe

Płytka stykowa

Podłączenie
Wyświetlacz OLED:
GND do GND Arduino
VCC do 5V Arduino
SCL do A5 Arduino
SDA do A4 Arduino

Moduł RTC DS3231:
GND do GND Arduino
VCC do 5V Arduino
SCL do A5 Arduino
SDA do A4 Arduino

Brzęczyk:

Jeden pin do pinu D2 Arduino
Drugi pin do GND Arduino

Przyciski:
Jeden pin każdego przycisku do GND Arduino
Drugi pin pierwszego przycisku do pinu D3 Arduino
Drugi pin drugiego przycisku do pinu D4 Arduino
Rezystory podciągające 10kΩ pomiędzy piny D3, D4 a 5V Arduino

Użyte Biblioteki
Adafruit_GFX.h
Adafruit_SSD1306.h
RTClib.h
EEPROM.h
