/*
 * main.cpp
 * 
 * Copyright 2018 CQueens>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
*/

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
// #include <thread>

#include "modul.h"		/** 
							int Read_dBase3_Header(const char *fileName);
							int check_dBase3_version(const char *fileName);
							int check_file (const char *fileName, const char *MSG);
							int open_success(const char *fileName, const char *MSG); 
							int init_lua (const char *fileName); 							
						**/
extern "C" {
	
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

#define Datenbank 	"SPRUCH.DBF"
#define MSG_DBF3 	"Datenbankdatei (dBase III): "

#define LuaFile		"TEST.LUA"
#define MSG_LUA 	"Lua - Datei: "

#define OffsetFeld			0x20
#define	FeldHeaderEnde		0xD0

using namespace std;

void myFunktion() {

	cout << "Hallo Welt in MultiThread" << endl;

	}

int length;

int main (void) {	
	
	// thread t1 (myFunktion);
	
	// Check of file exitist, if not, abourt it.
		
	check_file(Datenbank, MSG_DBF3);		
	check_file(LuaFile, MSG_LUA);
	
	// File open success, if not, abourt it.

	open_success(Datenbank,MSG_DBF3);				
	open_success(LuaFile, MSG_LUA);
	
	// Check_dBase of Version 3? No? It's abourt here.
	
	check_dBase3_version(Datenbank);
	
	// Now, open and read the Head of dBase 3 File
	
	Read_dBase3_Header(Datenbank);		
	
	ifstream FS (Datenbank, ifstream::binary);  
	
	// FS.seekg (0, FS.beg);		// get to begin of file
    
    FS.seekg(OffsetFeld, FS.beg);	// Setze HeaderPosition
    
    length = FS.tellg();		// write size of file to var length 
    
    
	// int length = OffsetFeld+FS.tellg();	// write size of file to var length 
    
    cout << length;
    
    char * buffer = new char [5];
    FS.read (buffer,5);
    
    cout << "\n\nFeld-Header: ("<<((unsigned int)(unsigned char)(buffer[2])) << ")";
    
    FS.close();	
    
	//	init_lua(LuaFile);	
	
	// getchar();
	
  return 0;
  
}
