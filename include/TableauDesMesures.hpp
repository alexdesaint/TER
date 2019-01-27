#ifndef RWtab_hpp
#define RWtab_hpp

#include <cinttypes>
#include <array>
#include <list>

class TableauDesMesures
{
  private:
    uint32_t index_write, nbValue;
    std::array<uint32_t, 10> tabToutesMesures[20];

    uint32_t EEPROMReadlong(int address);
    void EEPROMWritelong(int address, uint32_t value);

  public:
    TableauDesMesures();
    void clearAll();
    void writeAll();
    void readAll();
    void remplirTableau(std::array<uint32_t, 10> tab);
    std::list<std::array<uint32_t, 10>> getTab();
};

#endif
