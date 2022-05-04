#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "cs225/PNG.h"

enum status {
	OK = 0,
	ERROR_MISC,
	ERROR_FILE,
	ERROR_DRAW_RESTRICTED,
};

class DrawText {
public:
	enum status LoadFont(const std::string filename);
	enum status DrawTextPNG(cs225::PNG &img, const cs225::HSLAPixel &color, unsigned int x, unsigned int y, const std::string &text); // NOTE: only luminance value of `color` is considered
	enum status DrawTextConsole(const std::string &text);
private:
	std::unordered_map<uint16_t, std::vector<uint8_t>> font;
	unsigned int char_width = 0, char_height = 0;
	const char ARG_SEP = ' ';
	enum ParseState {
		NONE = 0,
		CHAR_METADATA,
		CHAR_BITMAP,
	};
};
