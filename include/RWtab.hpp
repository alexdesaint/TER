#ifndef RWtab_hpp
#define RWtab_hpp

#include <cinttypes>
#include <array>


class RWtab {
    private:

    uint32_t index_write;
    uint32_t tabToutesMesures[20][10];

    uint32_t EEPROMReadlong(int address);
    void EEPROMWritelong(int address, uint32_t value);




    public:
        void init();

        void clearAll();
        void write(int indexTableau);
        void writeAll();
        void readAll();
        uint32_t read(int indexTableau);
        void remplirTableau(uint32_t tab[10]);
        void removeTab();
        void afficher();
        void reset();

        void getTabFilo(uint32_t tab[20][10]);




};

#endif

