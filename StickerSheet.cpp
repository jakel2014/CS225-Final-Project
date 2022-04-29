#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
	base_img = picture;
	cursor_ = 0;
	images_.resize(max);
}

StickerSheet::~StickerSheet() {
}

StickerSheet::StickerSheet(const StickerSheet &other) {
	// TODO
	base_img = other.base_img;
	cursor_ = other.cursor_;
	images_ = other.images_;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
	// TODO
	if (this != &other) {
		base_img = other.base_img;
		cursor_ = other.cursor_;
		images_ = other.images_;
	}
	return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
	images_.resize(max);
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
	if (cursor_ + 1 > images_.size())
		return -1;
	struct sticker s = { &sticker, x, y };
	images_[cursor_] = s;
//	std::cout << "size: " << images_.size() << std::endl; // DEBUG
	cursor_++;
	return cursor_ - 1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (index < 0 || index >= images_.size())
		return false; // invalid index
	if (!images_[index].img)
		return false; // invalid index
	images_[index].x = x;
	images_[index].y = y;
	return true;
}

void StickerSheet::removeSticker(unsigned index) {
	if (index < 0 || index >= images_.size())
		return; // invalid index
	if (!images_[index].img)
		return; // invalid index
	images_.erase(images_.begin() + index);
	cursor_ -= 1;
}

Image * StickerSheet::getSticker(unsigned index) {
	// TODO
	if (index < 0 || index >= images_.size())
		return NULL; // invalid index
	if (!images_[index].img)
		return NULL; // invalid index
	return images_[index].img;
}

Image StickerSheet::render() const {
	Image comp = base_img;

	for (unsigned lyr = 0; lyr < images_.size(); lyr++) {
		if (!images_[lyr].img)
			continue;
		unsigned startx = images_[lyr].x,
		         starty = images_[lyr].y;
		unsigned w = images_[lyr].img->width(),
		         h = images_[lyr].img->height();
		unsigned xmax = startx + w,
		         ymax = starty + h;
		// extend composite boundaries if necessary
		if (xmax > comp.width())
			comp.resize(xmax, comp.height());
		if (ymax > comp.height())
			comp.resize(comp.width(), ymax);
		// deposit the sticker image onto composite
		for (unsigned x = 0; x < w; x++) {
			for (unsigned y = 0; y < h; y++) {
				cs225::HSLAPixel &stkr_px = images_[lyr].img->getPixel(x, y);
				if (stkr_px.a != 0.) {
					cs225::HSLAPixel &comp_px = comp.getPixel(startx + x, starty + y);
					comp_px = stkr_px;
				}
			}
		}
	}

	return comp;
}

void StickerSheet::debug() {
	for (unsigned lyr = 0; lyr < images_.size(); lyr++) {
		std::cout << "Layer " << lyr << std::endl;
		if (images_[lyr].img)
			std::cout << "\tImage: " << images_[lyr].img << std::endl;
		else
			std::cout << "\t(no image)" << std::endl;
		std::cout << "\tposition = " << images_[lyr].x << ", " << images_[lyr].y << std::endl;
	}
}
