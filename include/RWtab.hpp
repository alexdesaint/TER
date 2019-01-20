#ifndef RWtab_hpp
#define RWtab_hpp

#include <cinttypes>
#include <array>


class RWtab {
    private:

    uint32_t tab[10][20];
    uint32_t tabTest[10];
    uint32_t tabRead[10];


    public:
        void init();

        void erase();
        void write();
        uint32_t read();
        void remplirTableau(uint32_t tab[10]);
        void afficher();




};

#endif

