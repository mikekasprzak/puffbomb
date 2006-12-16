// - ------------------------------------------------------------------------------------------ - //
// DirectoryCache //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Util_DirectoryCache_H__
#define __Util_DirectoryCache_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>

#include <Util/String.h>

#include <dirent.h>
#include <sys/stat.h>
// - ------------------------------------------------------------------------------------------ - //
class cDirectoryCache {
public:
	std::string Name;
	std::vector< std::string > File;
	
	cDirectoryCache( const std::string& _Directory ) :
		Name( _Directory )
	{
		PopulateDir( Name, String::Empty );
	}
	
	void PopulateDir( const std::string& SearchDirectory, const std::string& Prefix ) {
		// Extract the directory part, and open the directory //
		DIR* ThisDir = opendir( SearchDirectory.c_str() );

		// Read the first entry in the directory //
		dirent* Data = readdir( ThisDir );
		
		// While we still have entries left in this directory //
		while( Data != 0 ) {
			// Full path and name of the file //
			std::string CurrentFile = SearchDirectory + String::Slash + Data->d_name;

			// Get the status of the file //
			struct _stat Status;
			_stat( CurrentFile.c_str(), &Status );
			
			// If it's a directory //
			if ( _S_ISDIR( Status.st_mode ) ) {
				// Recursively do this again, if not a dot file or folder //
				if( Data->d_name[0] != '.' ) 
					if( Data->d_name[0] != '_' ) 
						PopulateDir( CurrentFile, Prefix + Data->d_name + String::Slash );
			}
			// If it's a regular file //
			else if ( _S_ISREG( Status.st_mode ) ) {
				File.push_back( Prefix + Data->d_name );
			}
		
			// Read the next entry //
			Data = readdir( ThisDir );
		};
		
		// Close the directory //
		closedir( ThisDir );		
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_DirectoryCache_H__ //
// - ------------------------------------------------------------------------------------------ - //
