#include "Definitions.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Logger.h"
#include "PlainTextLogger.h"
#include "Configuration.h"

//! Constructor
PlainTextLogger::PlainTextLogger( const string& loggerName ):Logger( loggerName ){
}

//! Tells the logger to begin logging.
void PlainTextLogger::open( const char[] ){
	if( fileName == "" ) { // set a default value
		cout << "Using default log file name." << endl;
		fileName = "Log.txt";
	}

	logFile.open( fileName.c_str(), ios::out );

	// Print the header message
	if( headerMessage != "" ){
		parseHeader( headerMessage );
		logFile << headerMessage << endl << endl;
	}
}

//! Tells the logger to finish logging.
void PlainTextLogger::close(){
	logFile.close();
}

//! Logs a single message.
void PlainTextLogger::logCompleteMessage( const int line, const string& file, const WarningLevel warningLevelIn, const string& message ) {
	
	stringstream buffer;
	bool printColon = false;

	// Print the tabs.
	if ( printLogNest ) {
		for ( int nest = 0; nest < currentNestLevel; nest++ ) {
			for ( int space = 0; space < logTabSize; space++ ) {
				buffer << " ";
			}
		}
	}
	
	// Print the date.
	if ( printLogDateStamp ) {
		buffer << getDateString() << " ";
		printColon = true;
	}
	
	// Print the timestamp.
	if ( printLogTimeStamp ) {
		buffer << getTimeString() << " ";
		printColon = true;
	}
	
	// Print the warning level
	if ( printLogWarningLevel ) {
		buffer << "Level " << warningLevelIn << " ";
		printColon = true;
	}
	
	// Print the file name.
	if ( printLogFileName ) {
		printColon = true;
		if ( printLogFullPath ) {
			buffer << file;
		}
		else {
			buffer << getFileNameFromPath( file );
		}
	}
	
	// Print the line number
	if ( printLogLineNumber ) {
		printColon = true;
		buffer << "(" << line << ")";
	}
	
	if( printColon ){
		buffer << ":";
	}

	// Print the message
	buffer << message;
	
	string fullMessage;
	fullMessage = buffer.str();

	// Decide whether to print the message
	if ( warningLevelIn >= minLogWarningLevel ){
		logFile << fullMessage << endl;
	}

	if ( warningLevelIn >= minToScreenWarningLevel ) {
		cout << "Log Message: " <<  fullMessage << endl;
	}
}
