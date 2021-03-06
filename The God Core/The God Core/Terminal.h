/*************************************************************\
 * Terminal.h                                                *
 * This file was created by Jeremy Greenburg                 *
 * As part of The God Core game for the University of        *
 * Tennessee at Martin's University Scholars Organization    *
 *                                                           *
 * This file contains the declaration of the Terminal class  *
 * Which draws and manages ingame computer terminals         *
 * And has nothing to do with terminal illness I swear       *
\*************************************************************/

#ifndef TERMINAL_H
#define TERMINAL_H

#include "TwoD.h" // To inherit 2D class
#include "PoweredObject.h"

#include <cstdlib>

// For loading pictures
#include <SOIL.h>

#include "TextEngine.h" // To display text to screen

#include <string>

#include <GL\glut.h>

class Terminal : public TwoD, public PoweredObject // Inherit 2D functionality and power functionality
{
private:
	// text = what the user is typing, input = completed input
	std::string currentInput, currentText, error, file;
	std::vector<std::string> history, prompts, content;
	std::string id;
	// Where to print each item
	const double INPUT_LINE = SCREENBOTTOM / 7.0;
	const double ERROR_LINE = INPUT_LINE - 30;
	const double PROMPT_START = INPUT_LINE + 30;
	const double CONTENT_START = PROMPT_START + 100;

	GLint bTexture;

	int num;
	// Print our text
	TextEngine text;

	// Translation and rotation matrices
	double translate[3], rotate[3];

	// Draws the actual terminal
	void draw();

	// Draws a standing terminal
	void drawStanding();

	// Draws a wall mounter terminal
	void drawWallMounted();

	void processInput();

	void parseFile();

	static const char* TERM_PATH;

public:
	// Draws the 3D object in the world
	void Display();
	// Draws the 2D Terminal screen
	void DisplayScreen();
	// Shows the currently typed string
	void getText(std::string text);
	// Signifies a completed string to process
	void getInput(std::string text);
	// Returns an item in the terminal's log
	std::string getHist(int count);
	// Returns the number of items in the terminal's log
	int getHistNum();

	// Gets the translation coordinates
	double getX();
	double getY();
	double getZ();

	std::string getID();

	Terminal(const double(&_translate)[3], const double(&_rotate)[3], std::string _file, std::string _id);
	 			
};

#endif
