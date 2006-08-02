// - ------------------------------------------------------------------------------------------ - //
// An exciting friend that traverses dirs and finds files, instantly //
// - ------------------------------------------------------------------------------------------ - //
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <dirent.h>
#include <sys/stat.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
class cPattern {
public:	
	string FileMask;
//	string MakeFileSymbol;
	
	vector< string > Files;
	
	// Write a Makefile declaration containing all the files //
	void Write( ostream& OutFile ) {
//		OutFile << MakeFileSymbol << "\t:=\t\\" << endl;
//		for ( int idx = 0; idx < Files.size(); idx++ ) {
//			OutFile << "\t" << Files[ idx ] << "\t\\" << endl; 	
//		}
//		OutFile << endl;
		for ( int idx = 0; idx < Files.size(); idx++ ) {
			OutFile << "" << Files[ idx ] << " " << endl; 	
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
vector< cPattern > Pattern;
// - ------------------------------------------------------------------------------------------ - //
void PopulatePatternLists( string& Directory ) {
	DIR* Dir = opendir( Directory.c_str() );
	dirent* Entry;
	while ( Entry = readdir( Dir ) ) {
		// If first character is an _ or a . then bail //
		// Note, the . and .. directories are automatically removed thanks to this //
		if ( Entry->d_name[ 0 ] == '.' )
			continue;
		if ( Entry->d_name[ 0 ] == '_' )
			continue;
		
		// Construct a String to be passed recursivly down to find everything //
		string Str = Directory;
		Str += "/";
		Str += Entry->d_name;
		
		string FileName = Entry->d_name;
		
		
		// Get File Status (Check if it's a directory) //
		struct stat Status;
		stat( Str.c_str(), &Status );
		
		// If it is a directory, enter the directory and do this again //
		if ( S_ISDIR( Status.st_mode ) ) {
			// Though, if the pattern is a dot, then we're directory searching //
			if ( Pattern[0].FileMask == "." ) {
				Pattern[0].Files.push_back( Str );
			}
			// If it's a star-dot, then we're search for all recursively //
			else if ( Pattern[0].FileMask == "*." ) {
				Pattern[0].Files.push_back( Str );
				PopulatePatternLists( Str );
			}
			// Else we simply enter directories and search for new files recursively //
			else {
				PopulatePatternLists( Str );
			}
		}
		else {
			for( int idx = 0; idx < Pattern.size(); idx++ ) {
				if ( Pattern[idx].FileMask == "*" ) {
					Pattern[idx].Files.push_back( Str );
				}
				else if ( Pattern[idx].FileMask == "." ) {
					// Do nothing, "." is directory mode //
				}
				else if ( Pattern[idx].FileMask == "*." ) {
					// Do nothing, "*." is directory mode //
				}
				else {		
					int Pos = 0;
					if ( (Pos = FileName.find( Pattern[idx].FileMask )) != -1 ) {
						// Only if the final extension matches ( to avoid .cpp.bak like files for a .cpp search) //
						if ( Pos + Pattern[idx].FileMask.size() == FileName.size() )
							Pattern[idx].Files.push_back( Str );
					}
				}
			}
		}
	};
	
	closedir( Dir );
}
// - ------------------------------------------------------------------------------------------ - //
int Error() {
	cout << "TreeTool - v.1.4 - by Mike Kasprzak (mike@sykhronics.com)" << endl;
	cout << endl;
	cout << "Usage: TreeTool start_dir file_ext [file_ext ...]" << endl;
	cout << "  e.g. TreeTool src .cpp" << endl;
	cout << "  e.g. TreeTool Code/Engine .cpp .c .py" << endl;
	cout << endl;
	cout << "  If file_ext is *, then all files in all directories will be returned" << endl;
	cout << "  If file_ext is ., then directories will be returned" << endl;
	cout << "  If file_ext is *., then all directories will be returned" << endl;

	return 1;	
}
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	// Must have 2 or more arguments //
	if ( argc < 3 )
		return Error();
		
//	// Argument Count must be even (name + 3 args + (2 * whatever) //
//	if ( (argc & 1) == 1 )
//		return Error();
	
	string StartDir( argv[1] );
	// Bail if the start directory is not actually a directory //
	{
		struct stat Status;		
		stat( StartDir.c_str(), &Status );
		if ( !S_ISDIR( Status.st_mode ) )
			return 0;//Error();
	}
	
	// Parse the arguments //
	for ( int idx = 0; idx < (argc - 2); idx ++ ) {	
		Pattern.push_back( cPattern() );
		Pattern[ idx ].FileMask = argv[ idx + 2 ];
//		Pattern[ idx ].MakeFileSymbol = argv[ (idx * 2 ) + 3 ];
	}
	
	// Search the tree for files //
	PopulatePatternLists( StartDir );
	
	// Output the makefile style rules to stdout //
	for( int idx = 0; idx < Pattern.size(); idx++ ) {
		Pattern[idx].Write( cout );	
		cout << endl;
	}
	
	// Happy //
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
