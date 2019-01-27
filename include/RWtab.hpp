#ifndef RWtab_hpp
#define RWtab_hpp

#include <cinttypes>
#include <array>
#include <list>


class RWtab {
    private:

    uint32_t index_write;
    uint32_t tabToutesMesures[20][10];

    uint32_t EEPROMReadlong(int address);
    void EEPROMWritelong(int address, uint32_t value);




    public:
        void clearAll();
        void writeAll();
        void readAll();
        void remplirTableau(uint32_t tab[10]);
        void afficher();
        void getTabFilo(uint32_t tab[20][10]);

        std::list<std::array<uint32_t, 10>> getTabLifo()




};

#endif

