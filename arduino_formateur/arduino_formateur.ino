#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>

// --- Couleurs 16 bits (RGB565) ---
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define YELLOW  0xFFE0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define GREY    0x8410

// --- Broches TFT 2.4'' Shield ---
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// --- Touch Screen pins (résistif shield) ---
#define YP A3
#define XM A2
#define YM 9
#define XP 8

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define MINPRESSURE 5
#define MAXPRESSURE 1000

String buffer = "";

// Clavier layout params
const int keyX = 20;
const int keyY = 70;
const int keyW = 60;
const int keyH = 50;
const int keyGapX = 10;
const int keyGapY = 10;

// Coordonnées calibrées du tactile (valeurs relevées)
const int TS_XMIN = 204;
const int TS_XMAX = 814;
const int TS_YMIN = 215;
const int TS_YMAX = 892;

//ajouté nouvellement -------------
void afficherMessageTFT(const String &msg) {
  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(GREEN);
  tft.setCursor(10, 120);
  tft.print(msg);
  delay(2000);
  buffer = "";
  drawKeyboard();
}

// Dessine une touche (fond + label centré)
void drawKey(int x, int y, int w, int h, const String &label) {
  tft.fillRect(x, y, w, h, GREY);
  tft.drawRect(x, y, w, h, WHITE);
  tft.setTextSize(2);

  int16_t x1, y1;
  uint16_t wText, hText;
  tft.getTextBounds(label, 0, 0, &x1, &y1, &wText, &hText);

  int tx = x + (w - wText) / 2;
  int ty = y + (h - hText) / 2;
  tft.setCursor(tx, ty);
  tft.setTextColor(WHITE);
  tft.print(label);
}

// Dessine le clavier et la zone d'affichage
void drawKeyboard() {
  tft.fillScreen(BLACK);

  // Zone du buffer
  tft.fillRect(10, 10, 220, 40, BLUE);
  tft.drawRect(10, 10, 220, 40, WHITE);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(15, 20);
  tft.print(buffer);

  // 1..9
  int number = 1;
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      int x = keyX + col * (keyW + keyGapX);
      int y = keyY + row * (keyH + keyGapY);
      drawKey(x, y, keyW, keyH, String(number));
      number++;
    }
  }

  // 0, EFF, OK
  int yBottom = keyY + 3 * (keyH + keyGapY);
  drawKey(keyX, yBottom, keyW, keyH, "0");
  drawKey(keyX + (keyW + keyGapX), yBottom, keyW, keyH, "EFF");
  drawKey(keyX + 2 * (keyW + keyGapX), yBottom, keyW, keyH, "OK");
}

void setup() {
    Serial.begin(9600); // ← OBLIGATOIRE pour que Qt puisse lire
    tft.reset();
    tft.begin(0x9341);
    tft.setRotation(0);
    drawKeyboard();
}

void lireMessageQt() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n'); // Lire jusqu'au retour ligne
    if (msg != "") {
      tft.fillScreen(BLACK);                   // Efface l'écran
      tft.setTextSize(2);
      tft.setTextColor(GREEN);
      tft.setCursor(10, 120);
      tft.print(msg);                           // Affiche le message

      delay(2500);                              // Attend 1,5 s

      buffer = "";                              // Réinitialise le buffer du clavier
      drawKeyboard();                           // Réaffiche le clavier
    }
  }
}

void loop() {
  lireMessageQt(); // Vérifie si Qt envoie un message

  TSPoint p = ts.getPoint();

  // Remettre les pins en OUTPUT
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z < MINPRESSURE || p.z > MAXPRESSURE) return;

  // Map calibré avec tes valeurs
  int x = map(p.x, TS_XMIN, TS_XMAX, 0, 240);
  int y = map(p.y, TS_YMIN, TS_YMAX, 0, 320);

  // Inversions si nécessaire
  // x = 240 - x;
  // y = 320 - y;

  // Vérifie touches 1..9
  if (x >= keyX && x <= keyX + 3 * (keyW + keyGapX) - keyGapX &&
      y >= keyY && y <= keyY + 3 * (keyH + keyGapY) - keyGapY) {
    int col = (x - keyX) / (keyW + keyGapX);
    int row = (y - keyY) / (keyH + keyGapY);

     // Correction pour inversions horizontales (colonnes)
  if (col == 0) col = 2;
  else if (col == 2) col = 0;
  
    int number = row * 3 + col + 1;
    if (number >= 1 && number <= 9) {
      buffer += String(number);
      drawKeyboard();
      delay(200);
      return;
    }
  }

  // Ligne du bas
  int yBottom = keyY + 3 * (keyH + keyGapY);
  if (y >= yBottom && y <= yBottom + keyH) {
  int col = (x - keyX) / (keyW + keyGapX);

    // Correction colonnes pour tactile inversé
    if(col==0) col=2;
    else if(col==2) col=0;

    // Colonne 0 = 0
    if(col==0){
      buffer += "0";
      drawKeyboard();
      delay(200);
      return;
    }
    
    if (col == 1) {
      if (buffer.length() > 0) buffer.remove(buffer.length() - 1);
      drawKeyboard();
      delay(200);
      return;
    }


  delay(200);
if (col == 2) { // OK
    delay(100);
    Serial.println(buffer); 
    buffer = "";
    drawKeyboard();
    delay(200);
    return;
    }
  }

  delay(5);
}
