#include "DrawText.h"

enum status DrawText::DrawTextPNG(cs225::PNG &img, const cs225::HSLAPixel &color, unsigned int x_start, unsigned int y_start, const std::string &text)
{
	unsigned int x = x_start,
	             y = y_start;
	for (char c: text) {
		for (unsigned row = 0; row < char_height; ++row) {
			for (int8_t off = 7; off >= 0; --off) {
				if (font[c][row] & (1 << off)) {
					cs225::HSLAPixel &px = img.getPixel(x + 7 - off, y + row);
					px.l = color.l;
				}
			}
		}
		if (x + 2*char_width <= img.width())
			x += char_width;
		else if (y + 2*char_height < img.height()) { // wrap to next line
			x = x_start;
			y += char_height;
		} else
			return ERROR_DRAW_RESTRICTED; // we ran out of space at the bottom
	}
	return OK;
}

enum status DrawText::DrawTextConsole(const std::string &text)
{
	for (char c: text) {
		for (uint8_t row: font[c]) {
			printf("%02X ", row);
			for (int8_t off = 7; off >= 0; --off) {
				if (row & (1 << off))
					std::cout << 'X';
				else
					std::cout << '.';
			}
			std::cout << std::endl;
		}
	}
	return OK;
}

enum status DrawText::LoadFont(const std::string filename)
{
	std::ifstream f_font(filename);
	if (!f_font.is_open()) {
		std::cerr << __func__ << ": Could not open font file." << std::endl;
		return ERROR_FILE;
	}
	std::string line_raw;
	enum ParseState st = NONE;
	uint16_t codepoint = 0;
	while (std::getline(f_font, line_raw)) {
		size_t i = line_raw.find(ARG_SEP);
		if (st == NONE) {
			if (!line_raw.compare(0, i, "STARTCHAR"))
				st = CHAR_METADATA;
			else if (!line_raw.compare(0, i, "FONTBOUNDINGBOX")) {
				size_t i_fld_start, i_fld_end;
				std::string field;
				i_fld_start = line_raw.find_first_not_of(ARG_SEP, i);
				i_fld_end = line_raw.find_first_of(ARG_SEP, i_fld_start);
				field = line_raw.substr(i_fld_start, i_fld_end - i_fld_start);
				char_width = atoi(field.c_str());
				i_fld_start = line_raw.find_first_not_of(ARG_SEP, i_fld_end);
				i_fld_end = line_raw.find_first_of(ARG_SEP, i_fld_start);
				field = line_raw.substr(i_fld_start, i_fld_end - i_fld_start);
				char_height = atoi(field.c_str());
			}
		} else if (st == CHAR_METADATA) {
			if (!line_raw.compare(0, i, "ENCODING")) {
				size_t i_enc_no_start = line_raw.find_first_not_of(ARG_SEP, i);
				std::string enc_str = line_raw.substr(i_enc_no_start, std::string::npos);
				codepoint = atoi(enc_str.c_str());
			} else if (!line_raw.compare(0, i, "BITMAP"))
				st = CHAR_BITMAP;
			else if (!line_raw.compare(0, i, "ENDCHAR"))
				st = NONE;
		} else if (st == CHAR_BITMAP) {
			if (!line_raw.compare(0, i, "ENDCHAR")) {
				st = NONE;
				continue;
			}
			uint8_t bitmap = std::stoul(line_raw, nullptr, 16);
			//printf("%02X %02X\n", codepoint, bitmap); // DEBUG
			font[codepoint].push_back(bitmap);
		}
	}
	//std::cout << "Imported font with char. dimensions " << char_width << "x" << char_height << "." << std::endl; // DEBUG

	return OK;
}
