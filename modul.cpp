#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

extern "C" {
	
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

using namespace std;

#define DBF_Version 			0		// Offset - dBASE-Version 03H dBASE III-DBF-Datei
#define DBF_Datensaetze 		4		// Offset - Zahl der Datensätze in der Datei
#define DBF_Header_laenge		8		// Offset - Headerlänge in Byte
#define DBF_Datensaetz_laenge	10		// Offset - Datensatzlänge in Byte

#define DBF3_Header_Size		12 		// dBase III (Plus) Header max 12 Bytes length
#define	Check_DBF_Version		03		// Hier wird um dBase III gearbeitet.


int Read_dBase3_Header(const char *fileName) {
	  
	ifstream FS (fileName, ifstream::binary);
    
    // detect file size
    
    // FS.seekg (0, FS.end); 		// go to end of file    
    // int length = FS.tellg();		// write size of file to var length    
    // FS.seekg (0, FS.beg);		// get to begin of file
    
        
    int length = DBF3_Header_Size;	// write size of file to var length 
	
    char * buffer = new char [length];
	
    cout << "\n" << length << " gelesene Header-Daten Zeichen... \n";    
    
    FS.read (buffer,length);
	
	cout << "\ndBase - Version\t\t:\t "<< ((unsigned int)(unsigned char)(buffer[DBF_Version]));
	cout << "\nHeaderlaenge (Bytes)\t:\t "<< ((unsigned int)(unsigned char)(buffer[DBF_Header_laenge]));
	cout << "\nZahl der Datensaetze\t:\t "<< ((unsigned int)(unsigned char)(buffer[DBF_Datensaetze]));
	cout << "\nDatensatzlaenge (Bytes)\t:\t "<< ((unsigned int)(unsigned char)(buffer[DBF_Datensaetz_laenge]));
	
	cout << endl; cout << endl;	cout << endl;	
	cout <<"Rohdaten: \n"<< endl;
	
	for (int zaehler=0; zaehler < DBF3_Header_Size; ++zaehler) cout << "|" << hex << ((unsigned int)(unsigned char)(buffer[zaehler]));
	
	cout << endl; cout << endl;	cout << endl;
	
	// if (((unsigned int)(unsigned char)(buffer[DBF_Datensaetze])) == 5)  cout << "\n!";
	
    FS.close();	
    
    return 0;
}


int check_dBase3_version(const char *fileName) {
				
		ifstream FS (fileName, ifstream::binary);    
    
		int MaxFileSize = 1; 						// write size of file to var length 	
		char * buffer = new char [MaxFileSize];   
    
		FS.read (buffer, MaxFileSize);	
		
		cout << "\n\nChecke, ob es sich um dBase Version 3 handelt? ";
	
		if ((unsigned int)(unsigned char)(buffer[DBF_Version]) == Check_DBF_Version) { 
    
		cout << "> Korrekt." << endl;
		
		}
		
		else {
			
			cout << "\n\nFehler: unbekannte/falsche dBase-Version: ("<< ((unsigned int)(unsigned char)(buffer[DBF_Version])) << ") \nEs musst eine 3. Version dBase - Datei sein."<< endl;
			cout << "\nProgramm wurde abgebrochen" << endl;
			FS.close();	
			exit (EXIT_FAILURE);
			
			}			
			
			FS.close();
			
			return 0;
		}

bool is_file_exist(const char *fileName) {
	
	ifstream infile(fileName);
	
	return infile.good();
}

int check_file (const char *fileName, const char *MSG) {	
	
	if (is_file_exist(fileName)) {
		
			cout << MSG << fileName << " exitierst"<< endl;
			
			} else 	{
				
				cout << "Fehler: " << MSG << fileName << " exitierst nicht" << endl;
				cout << "Programm wurde abgebrochen" << endl;
				
				exit (EXIT_FAILURE);
				
				}
				
				return 0;
}
			
int open_success(const char *fileName, const char *MSG) {
	
	fstream FS;
	FS.open (fileName);
	
	if (FS.is_open()) {
				
		cout << MSG << fileName << " erfolgreich geoeffnet."<< endl;
		FS.close();		
		
		}
		
		else
		
		{
			cout << "Fehler beim oeffnen der "<< MSG << fileName << endl;			
			cout << "Programm wurde abgebrochen" << endl;
				
				exit (EXIT_FAILURE);			
			}
			
			return 0;
			
}

int init_lua (const char *fileName) {
	
	lua_State * L = lua_open();
	lua_baselibopen(L);
	lua_iolibopen(L);
	lua_strlibopen(L);
	lua_mathlibopen(L);
	
	/*lua_dostring(L,
	  "a = 1;\n"
	  "b = 2;\n"
	  "a = a + b\n"
	  "print('Hallo Lua.',a);\n");*/
	  
	  
	 lua_dofile(L, fileName);
	 lua_close(L);
	 
	 return 0;

}
