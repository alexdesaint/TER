#ifndef HTMLgenerator_hpp
#define HTMLgenerator_hpp

#include <list>
#include <array>
#include <string>

class HTMLgenerator {
  public:
    std::string getCode(std::list<std::array<uint32_t, 10>> temps);
};

#endif /* end of include guard: HTMLgenerator_hpp */
