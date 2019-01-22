#ifndef RWtab_hpp
#define RWtab_hpp

#include <cinttypes>
#include <array>


class RWtab {
    private:

    uint32_t tabToutesMesures[20][10];
    uint32_t tabToutesMesuresRead[20][10];

    uint32_t tabUneMesure[10];


    public:
        void init();

        void clearAll();
        void write(int indexTableau);
        void writeAll();
        void readAll();
        uint32_t read(int indexTableau);
        void remplirTableau(uint32_t tab[10],int index);
        void afficher();




};

#endif

