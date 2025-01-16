#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_I2C_ADDRESS 0x3C // Adres I2C dla SSD1306

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS3231 rtc; // Zmień na RTC_DS1307 jeśli używasz DS1307

const char* daysOfTheWeek[] = {"Niedziela", "Poniedzi.", "Wtorek", "Sroda", "Czwartek", "Piatek", "Sobota"};
int alarmHour = 14; // Ustawienie początkowej godziny budzika
int alarmMinute = 36;
const int buzzerPin = 2; // Używamy pinu D2 dla brzęczyka
const int buttonHourPin = 3; // Pin dla przycisku ustawienia godziny
const int buttonMinutePin = 4; // Pin dla przycisku ustawienia minut
bool alarmTriggered = false;
unsigned long alarmStartTime = 0;
unsigned long lastBuzzerToggle = 0;
unsigned long lastButtonPress = 0;
unsigned long lastSerialUpdate = 0; // Do kontrolowania wysyłania danych co 5 sekund
bool buzzerState = false;
bool settingAlarm = false;

void setup() {
  // Inicjalizacja portu szeregowego
  Serial.begin(9600);

  // Inicjalizacja RTC
  if (!rtc.begin()) {
    Serial.println("Nie można znaleźć RTC");
    while (1);
  }

  // Inicjalizacja ekranu OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Inicjalizacja brzęczyka
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // Wyłączenie brzęczyka na początku

  // Inicjalizacja przycisków
  pinMode(buttonHourPin, INPUT_PULLUP);
  pinMode(buttonMinutePin, INPUT_PULLUP);

  // Odczytanie ustawionego alarmu z EEPROM
  alarmHour = EEPROM.read(0);  // Odczyt godziny alarmu z EEPROM
  alarmMinute = EEPROM.read(1);  // Odczyt minuty alarmu z EEPROM
  
  // Sprawdzenie czy odczytane wartości są prawidłowe, jeśli nie, ustaw domyślne
  if (alarmHour > 23) alarmHour = 14;  // Domyślna godzina alarmu
  if (alarmMinute > 59) alarmMinute = 36;  // Domyślna minuta alarmu
  
  display.display();
  delay(2000); // Opóźnienie na rozruch ekranu
  display.clearDisplay();
}

void loop() {
  DateTime now = rtc.now();

  // Sprawdzenie przycisków
  if (digitalRead(buttonHourPin) == LOW) {
    alarmHour = (alarmHour + 1) % 24;
    EEPROM.write(0, alarmHour);  // Zapis godziny alarmu do EEPROM
    lastButtonPress = millis();
    settingAlarm = true;
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 25);
    display.print("Ustaw godzine: ");
    if (alarmHour < 10) display.print('0');
    display.setTextSize(2);
    display.print(alarmHour);
    display.display();
    delay(200); // Debouncing delay
  }

  if (digitalRead(buttonMinutePin) == LOW) {
    alarmMinute = (alarmMinute + 1) % 60;
    EEPROM.write(1, alarmMinute);  // Zapis minuty alarmu do EEPROM
    lastButtonPress = millis();
    settingAlarm = true;
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 25);
    display.print("Ustaw minute: ");
    if (alarmMinute < 10) display.print('0');
    display.setTextSize(2);
    display.print(alarmMinute);
    display.display();
    delay(200); // Debouncing delay
  }

  // Automatyczny powrót do normalnej pracy po 5 sekundach
  if (settingAlarm && (millis() - lastButtonPress >= 5000)) {
    settingAlarm = false;
    display.clearDisplay();
  }

  // Wyświetlanie pełnej daty, godziny i temperatury na wyświetlaczu OLED
  if (!alarmTriggered || (millis() - alarmStartTime >= 15000)) {
    if (!settingAlarm) {
      display.clearDisplay();
      
      // Zmieniony napis wyświetlany na ekranie
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print("Alarm o: ");
      display.setTextSize(1);
      if (alarmHour < 10) display.print('0');
      display.print(alarmHour);
      display.print(':');
      if (alarmMinute < 10) display.print('0');
      display.print(alarmMinute);

      display.setTextSize(1);
      display.setCursor(0, 10);
      display.print(daysOfTheWeek[now.dayOfTheWeek()]);
      display.setCursor(65, 10);
      if (now.day() < 10) display.print('0');
      display.print(now.day(), DEC);
      display.print('-');
      if (now.month() < 10) display.print('0');
      display.print(now.month(), DEC);
      display.print('-');
      display.print(now.year(), DEC);
      display.setTextSize(3);
      display.setCursor(0, 25); // Wyświetlanie godziny
      if (now.hour() < 10) display.print('0');
      display.print(now.hour(), DEC);
      display.print(':');
      if (now.minute() < 10) display.print('0');
      display.print(now.minute(), DEC);
      display.setTextSize(2);
      display.setCursor(100, 32);// pozycja wyświetlania sekund
      if (now.second() < 10) display.print('0');
      display.print(now.second(), DEC);
      display.setTextSize(1);
      display.setCursor(0, 55);
      display.print("Temperatura: ");
      display.print(rtc.getTemperature());
      display.setCursor(104, 55);
      display.print("  C");
      display.setCursor(110, 51); // Dodanie małego "o" zamiast znaku stopnia
      display.print("o");
    }
  }

  // Wysyłanie informacji przez RS232 co 5 sekund
  if (millis() - lastSerialUpdate >= 5000) {
    lastSerialUpdate = millis();
    Serial.print("Alarm o: ");
    if (alarmHour < 10) Serial.print('0');
    Serial.print(alarmHour);
    Serial.print(":");
    if (alarmMinute < 10) Serial.print('0');
    Serial.print(alarmMinute);
    Serial.print(", teraz: ");
    if (now.hour() < 10) Serial.print('0');
    Serial.print(now.hour());
    Serial.print(":");
    if (now.minute() < 10) Serial.print('0');
    Serial.print(now.minute());
    Serial.print(":");
    if (now.second() < 10) Serial.print('0');
    Serial.print(now.second());
    Serial.println();
  }

  // Sprawdzanie, czy czas zegara jest równy czasowi budzika
  if (now.hour() == alarmHour && now.minute() == alarmMinute && now.second() == 0 && !alarmTriggered) {
    alarmTriggered = true;
    alarmStartTime = millis(); // Zapisanie czasu rozpoczęcia alarmu
    lastBuzzerToggle = millis();
  }

  // Sprawdzanie, czy minęło 15 sekund od rozpoczęcia alarmu
  if (alarmTriggered) {
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(10, 25);
    display.print("ALARM!");
    display.display();

    if ((millis() - lastBuzzerToggle) >= (buzzerState ? 100 : 900)) {
      buzzerState = !buzzerState;
      digitalWrite(buzzerPin, buzzerState ? HIGH : LOW);
      lastBuzzerToggle = millis();
    }
    if ((millis() - alarmStartTime) >= 15000) {
      digitalWrite(buzzerPin, LOW); // Wyłączenie brzęczyka
      alarmTriggered = false;
      buzzerState = false;
      display.clearDisplay(); // Wyczyść ekran po zakończeniu alarmu
    }
  }

  display.display();

  delay(100); // Opóźnienie o 100 ms
}
