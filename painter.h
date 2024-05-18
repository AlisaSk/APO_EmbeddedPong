#ifndef PAINTER_H
#define PAINTER_H

#include "ball.h"
#include "racket.h"

void draw_word(int x, int y, char* word, int offset,  unsigned short color, int scale);
void draw_pixel_big(int x, int y, unsigned short color, int scale);
void draw_char(int x, int y, char ch, unsigned short color, int scale);
void draw_pixel(int x, int y, unsigned short color);
void highlightCurrentChoice(int x, int y, int w, int h, unsigned short backgroundColor, unsigned short textColor);
void drawRacket(Racket* racket, unsigned short color);
void drawBall(Ball* ball, unsigned short color);
void renderLCD();
void drawBackground(unsigned short color); 
void drawRectangle(unsigned short color1, unsigned short color2);
void drawScores(int score1, int score2);

#endif