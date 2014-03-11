#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace ycg {

class Rectangle {
public:
	Rectangle();
	Rectangle(int width, int height);
	int width() const;
	int height() const;
	void setWidth(int width);
	void setHeight(int height);
	friend bool operator== (const Rectangle& lhs, const Rectangle& rhs);
private:
	int w;
	int h;
};

inline Rectangle::Rectangle() {
	w = 0;
	h = 0;
}

inline Rectangle::Rectangle(int width, int height) {
	w = width;
	h = height;
}

inline int Rectangle::width() const {
	return w;
}

inline int Rectangle::height() const {
	return h;
}

inline void Rectangle::setWidth(int width) {
	w = width;
}

inline void Rectangle::setHeight(int height) {
	h = height;
}

inline bool operator== (const Rectangle& lhs, const Rectangle& rhs) {
	return (lhs.w == rhs.w) && (lhs.h == rhs.h);
}

}  // namespace ycg
#endif // RECTANGLE_HPP
