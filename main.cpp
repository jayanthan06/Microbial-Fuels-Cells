#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD: I2C address 0x27, 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int voltagePin = A0;   // Analog input from voltage sensor
const int ledPin = 9;        // LED to indicate MFC power
float voltage = 0.0;

void setup() {
    pinMode(ledPin, OUTPUT);
    lcd.begin();
    lcd.backlight();
    Serial.begin(9600);
    lcd.setCursor(0, 0);
    lcd.print("MFC Voltage:");
}

void loop() {
    int sensorValue = analogRead(voltagePin);

    // Convert sensor value (0–1023) to actual voltage
    voltage = sensorValue * (5.0 / 1023.0) * 5.0;  // Adjust based on your voltage sensor

    // Show voltage on LCD
    lcd.setCursor(0, 1);
    lcd.print(voltage, 2);  // Show 2 decimal places
    lcd.print(" V      ");

    // Glow LED if voltage > 0.5V
    if (voltage > 0.5) {
        digitalWrite(ledPin, HIGH);
    } else {
        digitalWrite(ledPin, LOW);
    }

    // Debug output
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");

    delay(1000);
}
