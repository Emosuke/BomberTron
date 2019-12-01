#ifndef BINDING_HPP_
#define BINDING_HPP_

#include <array>
#include <string>
#include <vector>
#include <irrlicht.h>
#include <cctype>

struct bind
{
	std::string title;
	int moveUp;
	int moveDown;
	int moveRight;
	int moveLeft;
	int drop;
};

class Binding {
public:
	Binding();
	bool setFile(const std::string &);
	std::string getFile() const;
	void run();
	void parseLine(const std::string &);
	void placeBind(const std::string &, const int);
	int scanForArrow(const std::string &, const size_t);
	std::pair<std::string, std::array<char, 5>> getBinding();
	std::pair<std::string, std::array<char, 5>> &operator[](uint32_t pos);
private:
	std::string filepath;
	std::vector<std::pair<std::string,
	std::array<char, 5>>> storage;
	int size;
	int index;
	std::ifstream *file;
	const std::array<std::string, 5> commands =
	{{"=moveUp", "=moveDown", "=moveLeft",
	"=moveRight", "=drop"}};
	std::array<std::pair<std::string, int>, 4> arrow;
};

#endif
