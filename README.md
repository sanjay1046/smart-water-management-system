
# 🌊 Smart Water Management System at Home

A mini-project for monitoring and automating water usage at home using IoT and embedded systems, developed by:

- **Sanjay M** (126003230)  
- **Kiran Soorya R S** (126003133)  
- **Sherwin L** (126003244)  

> Guide: **Dr. Kuppan Chetty RM**

---

## 📌 Objective

To build a smart, sustainable system that:

- Monitors water levels in real time 🕒
- Controls motor operation automatically or manually via Blynk ⚙️
- Provides user feedback using LEDs and LCD 💡📟
- Reduces water wastage and promotes efficient usage 💧

---

## 🔧 Components Used

- ESP32 Microcontroller
- Ultrasonic Sensor (HC-SR04)
- LCD Display with I2C module
- Water Pump (5V DC)
- 4x LEDs for level indicators
- Relay Module
- 9V Battery
- Blynk IoT Platform
- Breadboard, Jumper Wires, Pipes

---

## 🧠 Working Principle

1. **Ultrasonic sensor** measures the water level in the container.
2. **ESP32** calculates the level and updates:
   - Blynk app via WiFi
   - LCD Display
   - LEDs (Very Low, Low, Medium, Full)
3. **Relay** controls the pump based on water level or user input via the app.
4. **Motor** is turned **ON/OFF** accordingly to refill water when it drops below thresholds.

---

## 🔁 System Workflow

```
1. Initialize: LCD + Blynk + WiFi + Sensor
2. Measure tank level (via ultrasonic)
3. Display level on LCD + Blynk
4. Indicate with LEDs:
   - LED1: Very Low
   - LED1 + LED2: Low
   - LED1 + LED2 + LED3: Medium
   - All LEDs: Full (Motor OFF)
5. Motor control:
   - Manual: Blynk button
   - Auto: Based on distance measured
```

---

## 💻 Screenshots

📸 **Live setup:**
![Working Setup]![Working SetUp](https://github.com/user-attachments/assets/eec8d00e-da0e-433b-8842-6dfb774a40a8)


📸 **Snapshots from simulation and testing:**
All output snapshots and visuals are placed in the [`snapshots/`](./snapshots/) directory for easy viewing.

---

## 📂 File Structure

```
smart-water-management/
├── Arduino_Code.ino         # Main source code
├── README.md                # Project documentation
├── snapshots/               # All images and working results
├── LICENSE
└── libraries.txt            # Arduino libraries required
```

---

## 🧾 Arduino Code Snippet

```cpp
#define LED1 2
#define LED2 4
#define LED3 5
#define relay 14
#define trig 12
#define echo 13

void setup() {
  pinMode(LED1, OUTPUT); pinMode(trig, OUTPUT);
  pinMode(echo, INPUT); pinMode(relay, OUTPUT);
}

void ultrasonic() {
  digitalWrite(trig, LOW); delayMicroseconds(4);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  int distance = pulseIn(echo, HIGH) / 29 / 2;
  // Control logic...
}
```

👉 Full code is in [`Arduino_Code.ino`](./water_level_monitoring_with_blynk.ino)

---

## 📱 Blynk Integration

- Real-time water level displayed
- Manual relay (motor) toggle
- LCD status: Motor ON/OFF
- Uses:  
  - Virtual pin V1 – Motor control  
  - Virtual pin V2 – Water level monitoring

---

## 📈 Results

- Efficient motor automation
- Reduced water wastage
- User-friendly interface via Blynk
- LCD provides clear system feedback

---

## 🚀 Future Scope

- Add AI/ML to predict consumption trends 🤖
- Integrate cloud dashboard for analytics ☁️📊
- Link to municipal systems for community-level optimization 🌍

---

## 📚 References

- [Blynk IoT Platform](https://blynk.io/)
- [Blynk GitHub Library](https://github.com/blynkkk/blynk-library)
- [AdTechKnow YouTube](https://www.youtube.com/@adtechknow2761)
- [TechStudyCell YouTube](https://www.youtube.com/@TechStudyCell)
