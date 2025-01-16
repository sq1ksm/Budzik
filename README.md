Zegar z Alarmem na Arduino<br>
Opis Projektu<br>
Ten projekt to zegar z funkcją alarmu oparty na platformie Arduino Nano, który wykorzystuje wyświetlacz OLED i zegar RTC DS3231. Zegar wyświetla aktualną datę, godzinę i temperaturę na ekranie OLED. Dodatkowo, umożliwia ustawienie godziny i minuty alarmu za pomocą przycisków oraz zapisanie tych ustawień w pamięci EEPROM, dzięki czemu alarm pozostaje zapamiętany nawet po odłączeniu zasilania. Projekt jest również wyposażony w brzęczyk, który generuje dźwięk w momencie włączenia alarmu.<br>

Cechy<br>
Wyświetlanie Aktualnego Czasu i Daty:<br>
Wyświetlacz OLED prezentuje bieżącą datę, godzinę i temperaturę.<br>
Wykorzystano bibliotekę Adafruit_GFX oraz Adafruit_SSD1306 do obsługi wyświetlacza OLED.<br>
Zegar RTC DS3231 zapewnia dokładne dane dotyczące czasu i temperatury.<br>

Funkcja Alarmu:<br>
Użytkownik może ustawić godzinę i minutę alarmu za pomocą przycisków.<br>
Można włączyć i wyłączyć alarm
Ustawienia alarmu są wyświetlane na ekranie OLED w trybie konfiguracji.<br>
Kiedy aktualny czas pokrywa się z ustawionym alarmem, brzęczyk generuje dźwięk przez 15 sekund.<br>

Pamięć EEPROM:<br>
Ustawienia alarmu (godzina i minuta) są zapisywane w pamięci EEPROM.<br>
Dzięki temu alarm pozostaje zapamiętany nawet po odłączeniu zasilania.<br>

Komunikacja Szeregowa:<br>
Dane dotyczące aktualnego czasu i ustawień alarmu są wysyłane przez port szeregowy co 5 sekund, co pozwala na monitorowanie pracy zegara.<br>

Wymagane Podzespoły<br>
Arduino Nano<br>
Wyświetlacz OLED SSD1306<br>
Moduł RTC DS3231<br>
Brzęczyk piezoelektryczny<br>
2 przyciski<br>
Rezystory podciągające dla przycisków (10kΩ)<br>
Przewody połączeniowe<br>

Podłączenie<br>
Wyświetlacz OLED:<br>
GND do GND Arduino<br>
VCC do 5V Arduino<br>
SCL do A5 Arduino<br>
SDA do A4 Arduino<br>

Moduł RTC DS3231:<br>
GND do GND Arduino<br>
VCC do 5V Arduino<br>
SCL do A5 Arduino<br>
SDA do A4 Arduino<br>

Brzęczyk:<br>
Jeden pin do pinu D2 Arduino<br>
Drugi pin do GND Arduino<br>

Przyciski:<br>
Jeden pin każdego przycisku do GND Arduino<br>
Drugi pin pierwszego przycisku do pinu D3 Arduino<br>
Drugi pin drugiego przycisku do pinu D4 Arduino<br>
Drugi pin drugiego przycisku do pinu D5 Arduino<br>
Rezystory podciągające 10kΩ pomiędzy piny D3, D4, D5 a 5V Arduino<br>

Użyte Biblioteki<br>
Adafruit_GFX.h<br>
Adafruit_SSD1306.h<br>
RTClib.h<br>
EEPROM.h<br>
