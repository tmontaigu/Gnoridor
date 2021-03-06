#ifndef GNORIDOR_DEFINE_H
#define GNORIDOR_DEFINE_H

#define NUMBER_OF_WALLS 9
#define NUMBER_OF_ROWS 9
#define NUMBER_OF_COLS 9


typedef enum {
	Up, Down, Left, Right
}Direction;

typedef enum {
	Up_border, Bottom_border, Left_border, Right_border,
	Up_left_corner, Bottom_left_corner, Up_right_corner, Bottom_right_corner,
	Not_border
}Border_type;

typedef enum {
	Horizontal, Vertical
}WallOrientation;
#endif
