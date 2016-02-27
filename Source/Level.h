/*************************************************************\
 * Level.h                                                   *
 * This file was created by Jeremy Greenburg                 *
 * As part of The God Core game for the University of        *
 * Tennessee at Martin's University Scholars Organization    *
 *                                                           *
 * This file contains the declaration of the Level class     *
 * Which loads all level assets from a sqlite database       *
 * (data.db)                                                 *
\*************************************************************/

#ifndef LEVEL_H
#define LEVEL_H

// std;:string
#include <string>
// std::vector
#include <vector>
// Rectangles for walls/doors/such else
#include "Rectangle.h"

// SQLite API
#include "sqlite3.h"

// Glut API
#include <GL\glut.h>

class Level
{
private:
	// Used to load cylinders
	GLUquadricObj *quadratic;
	// The current level being loaded
	std::string currLevel;

	// Look, the names are self-explanatory
	void loadWalls(sqlite3 *db);
	void loadDoors(sqlite3 *db);
	void loadSwitches(sqlite3 *db);
public:
	// Manages the loading of the level
	void loadLevel(std::string levelName);
	// Draws the level
	void displayLevel();
};

#endif