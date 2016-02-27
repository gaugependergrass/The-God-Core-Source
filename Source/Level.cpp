/*************************************************************\
 * Level.cpp                                                 *
 * This file was created by Jeremy Greenburg                 *
 * As part of The God Core game for the University of        *
 * Tennessee at Martin's University Scholars Organization    *
 *                                                           *
 * This file contains the defintion of the Level class.      *
 * for more information, see Keyboard.h                      *
\*************************************************************/

// Class declaration
#include "Level.h"
// To use rectangles
#include "Rectangle.h"
// Vectors to plop stuff in
#include "Globals.h"
// Return codes
#include "Return.h"
// System log
#include "Logger.h"

using namespace std;

void Level::loadWalls(sqlite3 *db)
{
	walls.clear();
	// Prepared Statement
	sqlite3_stmt *stm;
	// SQL command
	string cmd;
	// Connection Error Test
	int err;
	cmd = "SELECT * FROM walls WHERE LEVEL = \"" + currLevel + "\"";

	err = sqlite3_prepare(db, cmd.c_str(), -1, &stm, 0);

	if (err != SQLITE_OK)
	{
		Logger log;
		vector<string> output = { "FATAL ERROR: failed to load walls from", currLevel };
		log.logLine(output);
		exit(STATEMENT_ERROR);
	}

	// While we still get rows of output
	while (sqlite3_step(stm) == SQLITE_ROW)
	{
		double x1, x2, x3, x4,
			y1, y2, y3, y4,
			z1, z2, z3, z4,
			r, g, b, a;
		string axis;

		x1 = sqlite3_column_double(stm, 2);
		x2 = sqlite3_column_double(stm, 3);
		x3 = sqlite3_column_double(stm, 4);
		x4 = sqlite3_column_double(stm, 5);

		y1 = sqlite3_column_double(stm, 6);
		y2 = sqlite3_column_double(stm, 7);
		y3 = sqlite3_column_double(stm, 8);
		y4 = sqlite3_column_double(stm, 9);

		z1 = sqlite3_column_double(stm, 10);
		z2 = sqlite3_column_double(stm, 11);
		z3 = sqlite3_column_double(stm, 12);
		z4 = sqlite3_column_double(stm, 13);

		r = sqlite3_column_double(stm, 14);
		g = sqlite3_column_double(stm, 15);
		b = sqlite3_column_double(stm, 16);
		a = sqlite3_column_double(stm, 17);

		axis = reinterpret_cast<const char*>(sqlite3_column_text(stm, 18));

		char ax;
		if (axis == "x") ax = 'x';
		else if (axis == "y") ax = 'y';
		else if (axis == "z") ax = 'z';
		else ax = 0;

		double verts[12] =
		{
			x1, y1, z1,
			x2, y2, z2,
			x3, y3, z3,
			x4, y4, z4
		};
		double colors[4] = { r, g, b, a };

		Rectangle rect(verts, colors, ax);

		walls.push_back(rect);
	}

	Logger log;
	vector<string> output = { "Loaded walls on", currLevel };
	log.logLine(output);

	// Deconstructs the statement
	sqlite3_finalize(stm);
}

void Level::loadDoors(sqlite3 *db)
{
	doors.clear();
	// Prepared Statement
	sqlite3_stmt *stm;
	// SQL command
	string cmd;
	// Connection Error Test
	int err;
	cmd = "SELECT * FROM doors WHERE LEVEL = \"" + currLevel + "\"";

	err = sqlite3_prepare(db, cmd.c_str(), -1, &stm, 0);

	if (err != SQLITE_OK)
	{
		Logger log;
		vector<string> output = { "FATAL ERROR: Can't load doors while loading", currLevel };
		log.logLine(output);

		exit(STATEMENT_ERROR);
	}

	// While we still get rows of output
	while (sqlite3_step(stm) == SQLITE_ROW)
	{
		double x1, x2, x3, x4,
			y1, y2, y3, y4,
			z1, z2, z3, z4,
			r, g, b, a;
		string id;
		string axis;

		id = reinterpret_cast<const char*>(sqlite3_column_text(stm, 0));
		x1 = sqlite3_column_double(stm, 2);
		x2 = sqlite3_column_double(stm, 3);
		x3 = sqlite3_column_double(stm, 4);
		x4 = sqlite3_column_double(stm, 5);

		y1 = sqlite3_column_double(stm, 6);
		y2 = sqlite3_column_double(stm, 7);
		y3 = sqlite3_column_double(stm, 8);
		y4 = sqlite3_column_double(stm, 9);

		z1 = sqlite3_column_double(stm, 10);
		z2 = sqlite3_column_double(stm, 11);
		z3 = sqlite3_column_double(stm, 12);
		z4 = sqlite3_column_double(stm, 13);

		r = sqlite3_column_double(stm, 14);
		g = sqlite3_column_double(stm, 15);
		b = sqlite3_column_double(stm, 16);
		a = sqlite3_column_double(stm, 17);

		a = sqlite3_column_double(stm, 17);

		axis = reinterpret_cast<const char*>(sqlite3_column_text(stm, 18));

		char ax;
		if (axis == "x") ax = 'x';
		else if (axis == "y") ax = 'y';
		else if (axis == "z") ax = 'z';
		else ax = 0;

		double verts[12] =
		{
			x1, y1, z1,
			x2, y2, z2,
			x3, y3, z3,
			x4, y4, z4
		};
		double colors[4] = { r, g, b, a };

		Rectangle rect(verts, colors, ax);

		doors.push_back(Door(rect, id));
	}

	Logger log;
	vector<string> output = { "Loaded doors on", currLevel };
	log.logLine(output);

	// Deconstructs the statement
	sqlite3_finalize(stm);
}

void Level::loadSwitches(sqlite3 *db)
{
	switches.clear();
	// Prepared Statement
	sqlite3_stmt *stm;
	// SQL command
	string cmd;
	// Connection Error Test
	int err;
	cmd = "SELECT * FROM switches WHERE LEVEL = \"" + currLevel + "\"";

	err = sqlite3_prepare(db, cmd.c_str(), -1, &stm, 0);

	if (err != SQLITE_OK)
	{
		Logger log;
		vector<string> output = { "FATAL ERROR: Can't load switches while loading", currLevel };
		log.logLine(output);

		exit(STATEMENT_ERROR);
	}

	// While we still get rows of output
	while (sqlite3_step(stm) == SQLITE_ROW)
	{
		double xt, yt, zt,
			xr, yr, zr;
		string target;
		target = reinterpret_cast<const char*>(sqlite3_column_text(stm, 2));
		xt = sqlite3_column_double(stm, 3);
		yt = sqlite3_column_double(stm, 4);
		zt = sqlite3_column_double(stm, 5);

		xr = sqlite3_column_double(stm, 6);
		yr = sqlite3_column_double(stm, 7);
		zr = sqlite3_column_double(stm, 8);

		double translate[3] = { xt, yt, zt };
		double rotate[3] = { xr, yr, zr };

		switches.push_back(Switch(translate, rotate));

		for (unsigned int i = 0; i < doors.size(); i++)
		{
			if (doors[i].getID() == target)
			{
				Logger log;
				vector<string> output = { "Binding switch to door", target };
				log.logLine(output);

				switches[switches.size() - 1].assign(doors[i]);
			}
		}
	}


	Logger log;
	vector<string> output = { "Loaded switches on", currLevel };
	log.logLine(output);

	// Deconstructs the statement
	sqlite3_finalize(stm);
}

void Level::loadLevel(std::string levelName)
{
	if (quadratic == NULL)
	{
		quadratic = gluNewQuadric();
	}

	currLevel = levelName;

	// Connection to SQL database
	sqlite3 *db;
	// 1 if error with DB
	int connectErr = sqlite3_open("Data.db", &db);

	if (connectErr != SQLITE_OK)
	{
		Logger log;
		log.logLine("FATAL ERROR: Can't access database");

		exit(DATABASE_ERROR);
	}

	loadWalls(db);
	loadDoors(db);
	loadSwitches(db);
	
	// Closes the database
	sqlite3_close(db);

}

void Level::displayLevel()
{
	for (auto i : walls)
	{
		i.Display();
	}

	for (auto i : doors)
	{
		i.Display();
	}

	for (auto i : switches)
	{
		i.Display();
	}
}