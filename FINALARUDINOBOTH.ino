#include <PulseSensorPlayground.h>
#include <DHT.h>

// --- Pulse Sensor Setup ---
const int pulsePin = A0;             // Pulse sensor connected to analog pin
const int LED13 = 13;                // Optional: LED to blink with heartbeat

PulseSensorPlayground pulseSensor;

// Variables to calculate average BPM
int totalBPM = 0;
int beatCount = 0;

// --- DHT11 Setup ---
#define DHTPIN 2      // Digital pin connected to DHT11
#define DHTTYPE DHT11 // DHT 11 sensor type

DHT dht(DHTPIN, DHTTYPE);

// Variables for temperature reading interval
unsigned long lastTempReadTime = 0;
const unsigned long tempInterval = 2000; // Read temperature every 2 seconds

void setup() {
  Serial.begin(9600);

  // Initialize Pulse Sensor
  pulseSensor.analogInput(pulsePin);
  pulseSensor.blinkOnPulse(LED13);      // Optional: LED blink on pulse
  pulseSensor.setThreshold(550);        // Adjust threshold if needed

  if (pulseSensor.begin()) {
    Serial.println("Pulse Sensor is ready!");
  } else {
    Serial.println("Pulse Sensor not found. Check wiring!");
  }

  // Initialize DHT11
  dht.begin();
  Serial.println("DHT11 Sensor Ready...");
}

void loop() {
  // --- Pulse Sensor Logic ---
  if (pulseSensor.sawStartOfBeat()) {
    int bpm = pulseSensor.getBeatsPerMinute();

    // Sanity filter
    if (bpm > 40 && bpm < 180) {
      totalBPM += bpm;
      beatCount++;
      int avgBPM = totalBPM / beatCount;

      Serial.print("❤️ BPM: ");
      Serial.print(bpm);
      Serial.print(" | 📊 Average BPM: ");
      Serial.println(avgBPM);
    } else {
      Serial.print("⚠️ Ignored BPM: ");
      Serial.println(bpm);
    }
  }

  // --- Temperature Sensor Logic ---
  unsigned long currentTime = millis();
  if (currentTime - lastTempReadTime >= tempInterval) {
    lastTempReadTime = currentTime;
    float temperature = dht.readTemperature(); // Read temperature in Celsius

    if (!isnan(temperature)) {
      Serial.print("🌡️ Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");
    } else {
      Serial.println("Failed to read from DHT sensor!");
    }
  }
}
