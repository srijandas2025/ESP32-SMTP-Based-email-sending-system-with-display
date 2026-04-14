# ESP32-SMTP-Based-email-sending-system-with-display
ESP32-based smart alert system with TFT display and button-triggered email notifications using SMTP.
# ⚡ Email Alert System (ESP32 + TFT + Email)

A smart IoT-based alert system built using ESP32 that sends an email notification when a button is pressed and displays real-time system logs on a TFT display.

---

## 🚀 Features
- 📩 Send email using SMTP (Gmail)
- 🔘 Button-triggered alert system
- 🖥️ TFT display shows live logs (like Serial Monitor)
- ⚡ One press = one email (debounced system)
- 🔐 Secure login using App Password
- 💡 Real-time feedback on display

---

## 🛠️ Components Used
- ESP32 Development Board
- 1.8" ST7735 TFT Display
- Push Button
- Jumper Wires

---

## 🔌 Circuit Connections

### 📺 TFT Display
| TFT Pin | ESP32 Pin |
|--------|----------|
| VCC | 3.3V |
| GND | GND |
| CLK | GPIO 18 |
| SDA | GPIO 23 |
| RS (DC) | GPIO 2 |
| RST | GPIO 4 |
| CS | GPIO 5 |

### 🔘 Push Button
| Button | ESP32 |
|--------|------|
| One side | GPIO 19 |
| Other side | GND |

---

## ⚙️ Step-by-Step Setup Guide

### 🔹 Step 1: Install Arduino IDE
Download and install Arduino IDE.

---

### 🔹 Step 2: Install ESP32 Board
1. Open Arduino IDE  
2. Go to File → Preferences  
3. Add this URL:
https://dl.espressif.com/dl/package_esp32_index.json  
4. Go to Tools → Board → Board Manager  
5. Search ESP32 and install  

---

### 🔹 Step 3: Install Libraries
Install these from Library Manager:
- ESP Mail Client (by Mobizt)
- Adafruit GFX
- Adafruit ST7735

---

### 🔹 Step 4: Hardware Connections
Connect TFT and button as shown above.

---

### 🔹 Step 5: Gmail Setup
1. Enable 2-Step Verification  
2. Go to Security → App Passwords  
3. Generate 16-digit password  

⚠️ Use App Password, not Gmail password  

---

### 🔹 Step 6: Update Code

```cpp
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define AUTHOR_EMAIL "YOUR_EMAIL"
#define AUTHOR_PASSWORD "YOUR_APP_PASSWORD"

#define RECIPIENT_EMAIL "RECEIVER_EMAIL"
