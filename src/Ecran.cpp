#include <Ecran.hpp>

#include "SSD1306Wire.h"

SSD1306Wire display(0x3c, D1, D2);

void Ecran::init() {
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
}

void Ecran::clear() {
  display.clear();
}

void Ecran::write(String str) {
  display.clear();
  display.drawString(0, 10, str);
  display.display();
}
