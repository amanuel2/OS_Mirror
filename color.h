#ifndef _COLOR_H_
#define _COLOR_H_ 1

/*
 * @struct RGB
 * 		Structure for RGB Color
 * 		Format.Red,Green,Blue.
 * 			@member uint8_t r; Red
 *			@member uint8_t g; Green
 *			@member uint8_t b; Blue
 *
 * @struct RGBA
 * 		Structure for RGBA Color
 * 		Format.Red,Green,Blue,Alpha.
 * 			@member uint8_t r; Red
 *			@member uint8_t g; Green
 *			@member uint8_t b; Blue
 *			@member uint8_t a; Alpha
 *
 */
typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
}RGB;

typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
}RGBA;

#endif
