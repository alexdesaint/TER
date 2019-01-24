#include <Ecran.hpp>

#include "SSD1306Wire.h"

SSD1306Wire display(0x3c, D1, D2);

void Ecran::init() {
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  Serial.println("init fini");
}

void Ecran::clear() {
  display.clear();
}

void Ecran::write(String str) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 20, str);
  display.display();
}
