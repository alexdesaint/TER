#ifndef HTMLgenerator_hpp
#define HTMLgenerator_hpp

#include <list>
#include <array>

class HTMLgenerator {
public:
	static const char page_vide[];
	static char str[10000];
	static char* getCode(std::list<std::array<uint32_t, 10>> temps);
};

#endif /* end of include guard: HTMLgenerator_hpp */
