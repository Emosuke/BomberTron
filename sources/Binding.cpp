#include <fstream>
#include "Binding.hpp"

Binding::Binding()
{
	this->index = 0;
	this->size = 0;
	arrow[0] = {"arrow_up", 40};
	arrow[1] = {"arrow_down", 38};
	arrow[2] = {"arrow_left", 39};
	arrow[3] = {"arrow_right", 37};
}

bool Binding::setFile(const std::string &filepath)
{
	std::ifstream fileopen(filepath);

	if (fileopen.is_open() == true) {
		this->filepath = filepath;
		return true;
	}
	return false;
}

std::string Binding::getFile() const
{
	return (this->filepath);
}

void Binding::run()
{
	std::string line;

	this->file = new std::ifstream(this->filepath);
	if (this->file->is_open() == false) {
		delete this->file;
		return;
	}
	while (getline(*(this->file), line)) {
		if (line.size() == 0)
			break;
		else if (line == "[KEY]" || line == "[JOYSTICK]") {
			this->storage.resize(this->storage.size() + 1);
			this->storage[this->storage.size() - 1].first = line;
		} else
			this->parseLine(line);
	}
	this->file->close();
	delete this->file;
}

int Binding::scanForArrow(const std::string &line, const size_t pos)
{
        uint32_t i;

	for (i = 0; i < this->arrow.size(); i += 1) {
		if (line.find(this->arrow[i].first) == 0)
			break;
	}
	for (uint32_t i = 0; i < this->commands.size(); i += 1) {
		if (line.find(this->commands[i], pos) != std::string::npos) {
			this->storage[this->storage.size() - 1].second[i] =
			this->arrow[i].second;
		}
	}
	return (0);
}

void Binding::parseLine(const std::string &line)
{
	size_t pos = line.find('=');

	if (pos == std::string::npos)
		return;
	else if (pos != 1) {
		scanForArrow(line, pos);
		return;
	}
	for (uint32_t i = 0; i < this->commands.size(); i += 1) {
		if (line.find(this->commands[i], pos) != std::string::npos) {
			this->storage[this->storage.size() - 1].second[i] =
			std::toupper(line[0]);
		}
	}
}

std::pair<std::string, std::array<char, 5>> Binding::getBinding()
{
	int pos = this->index;

	this->index = (this->index + 1) % this->storage.size();
	return (this->storage[pos]);
}

std::pair<std::string, std::array<char, 5>> &Binding::operator[](uint32_t pos)
{
	return (this->storage[pos]);
}