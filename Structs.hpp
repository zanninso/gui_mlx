#ifndef Structs_HPP
# define Structs_HPP

#define between(x, min, max) (x >= min && x <= max)

struct Point {
    int x;
    int y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

struct FontDim {
    int width;
    int height;

    FontDim(int width, int height) {
        this->width = width;
        this->height = height;
    };
};

struct	Image {
	    void	*img;
	    char	*data;
	    int		bits_per_pixel;
	    int		line_length;
	    int		endian;
        int     height;
        int     width;
};

# endif
