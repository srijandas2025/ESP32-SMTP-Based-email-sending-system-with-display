#include <Arduino.h>
#include <WiFi.h>
#include <ESP_Mail_Client.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

/************ WiFi ************/
#define WIFI_SSID "YOUR_WIFI_NAME"        // Use 2.4GHz WiFi
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

/************ SMTP ************/
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "your_email@gmail.com"
#define AUTHOR_PASSWORD "your_app_password"   // Gmail App Password
#define RECIPIENT_EMAIL "receiver_email@gmail.com"

/************ TFT ************/
#define TFT_CS     5
#define TFT_RST    4
#define TFT_DC     2

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

/************ Button ************/
#define BUTTON_PIN 19

SMTPSession smtp;

/************ Button State ************/
bool lastButtonState = HIGH;
bool currentButtonState;

/************ Display + Serial ************/
void logPrint(String msg) {
  Serial.println(msg);

  static int y = 0;

  tft.setCursor(0, y);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.print(msg);

  y += 10;

  if (y > 150) {
    tft.fillScreen(ST77XX_BLACK);
    y = 0;
  }
}

/************ Send Email ************/
void sendEmail() {

  logPrint("Connecting SMTP...");

  Session_Config config;
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;

  config.time.ntp_server = "pool.ntp.org";
  config.time.gmt_offset = 5.5;

  SMTP_Message message;
  message.sender.name = "ESP32 Alert System";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "⚡ Button Press Alert";

  message.addRecipient("User", RECIPIENT_EMAIL);

  String textMsg = "Button pressed!\nESP32 system working correctly.";
  message.text.content = textMsg.c_str();

  if (!smtp.connect(&config)) {
    logPrint("SMTP Failed!");
    return;
  }

  logPrint("SMTP Connected");

  if (!MailClient.sendMail(&smtp, &message)) {
    logPrint("Send Failed!");
  } else {
    logPrint("Email Sent Successfully!");
  }
}

/************ Setup ************/
void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  /******** TFT ********/
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);

  logPrint("ESP32 Alert System ⚡");
  logPrint("Booting...");
  delay(1000);

  /******** WiFi ********/
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  logPrint("Connecting WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    logPrint(".");
  }

  logPrint("WiFi Connected!");
}

/************ Loop ************/
void loop() {

  currentButtonState = digitalRead(BUTTON_PIN);

  // Detect button press (HIGH → LOW)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    
    logPrint("Button Pressed!");
    sendEmail();
  }

  lastButtonState = currentButtonState;

  delay(50); // debounce
}