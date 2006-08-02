// - ------------------------------------------------------------------------------------------ - //
// String //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Util_String_H__
#define __Util_String_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
namespace String {
// - ------------------------------------------------------------------------------------------ - //
	const char Slash = '/';
	const char OtherSlash = '\\';
	const char Dot = '.';
	const std::string Empty("");

	// - -------------------------------------------------------------------------------------- - //
	// Return the File-Name part of a string //
	inline std::string FileName( const std::string& _FileName ) {
		// Find the last slash //
		size_t SlashPos = _FileName.rfind( Slash );
		
		if ( SlashPos == std::string::npos ) {
			// Slash not found //
			return _FileName;
		}
		
		// Return the entire string after the slash position //
		return _FileName.substr( SlashPos + 1 );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the Directory part of a string, excluding the slash //
	inline std::string Directory( const std::string& _FileName ) {
		// Find the last slash //
		size_t SlashPos = _FileName.rfind( Slash );
		
		if ( SlashPos == std::string::npos ) {
			// Slash not found //
			return Empty;
		}
		
		// Return the entire string before the slash position //
		return _FileName.substr( 0, SlashPos - 0 );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Return the Directory part of a string, including the slash //
	inline std::string DirectorySlash( const std::string& _FileName ) {
		// Find the last slash //
		size_t SlashPos = _FileName.rfind( Slash );
		
		if ( SlashPos == std::string::npos ) {
			// Slash not found //
			return Empty;
		}
		
		// Return the entire string before the slash position //
		return _FileName.substr( 0, SlashPos + 1 - 0 );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Return the base name (filename without extensions) of the filename //
	inline std::string BaseName( const std::string& _FileName ) {
		std::string WorkString = String::FileName( _FileName );
			
		// Find the first dot //
		size_t DotPos = WorkString.find( Dot );
		
		if ( DotPos == std::string::npos ) {
			// Dot not found //
			return WorkString;
		}
		
		// Return the entire string before the first period //
		return WorkString.substr( 0, DotPos - 0 );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the text before the first '_' //
	inline std::string PriorBaseName( const std::string& _FileName ) {
		std::string WorkString = String::FileName( _FileName );
			
		// Find the first underscore //
		size_t UnderscorePos = WorkString.find( '_' );
		
		if ( UnderscorePos == std::string::npos ) {
			// Dot not found //
			return WorkString;
		}
		
		// Return the entire string before the first period //
		return WorkString.substr( 0, UnderscorePos - 0 );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the Extensions //
	inline std::string Extension( const std::string& _FileName ) {
		std::string WorkString = String::FileName( _FileName );
			
		// Find the first dot //
		size_t DotPos = WorkString.find( Dot );
		
		if ( DotPos == std::string::npos ) {
			// Dot not found //
			return Empty;
		}
		
		// Return the entire string after and including the first period //
		return WorkString.substr( DotPos );
	}
	
	// - -------------------------------------------------------------------------------------- - //
	// Return the last extension in the filename //
	inline std::string LastExtension( const std::string& _FileName ) {
		std::string WorkString = String::FileName( _FileName );
			
		// Find the first dot //
		size_t DotPos = WorkString.rfind( Dot );

		if ( DotPos == std::string::npos ) {
			// Dot not found //
			return Empty;
		}
	
		// Return the entire string after the last period //
		return WorkString.substr( DotPos );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return all but the last extension in the filename //
	inline std::string NoLastExtension( const std::string& _FileName ) {
		std::string WorkString = String::FileName( _FileName );
			
		// Find the first dot //
		size_t DotPos = WorkString.find( Dot );

		if ( DotPos == std::string::npos ) {
			// Dot not found //
			return Empty;
		}
	
		// Return the entire string after the first period, up until the last period //
		return WorkString.substr( DotPos, WorkString.rfind( Dot ) - DotPos );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Replaces all slashes in a string with the system correct form of slash //
	inline std::string SystemSlash( const std::string& _FileName ) {
		std::string WorkString = _FileName;
		
		// For all characters in the string, replace all "Other" slashes with the system slashes //
		for( size_t idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[ idx ] == OtherSlash )
				WorkString[ idx ] = Slash;
		}
		
		// Return our slash updated string //
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Replaces all slashes in a string with the incorrect system slash //
	inline std::string NotSystemSlash( const std::string& _FileName ) {
		std::string WorkString = _FileName;
		
		// For all characters in the string, replace all system slashes with the "Other" slashes //
		for( size_t idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[ idx ] == Slash )
				WorkString[ idx ] = OtherSlash;
		}
		
		// Return our slash updated string //
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Replaces all Windows slashes with Unix slashes //
	// ** NOTE ** : Only recommended for platform concious tools!  Don't use this in game code! //
	inline std::string UnixSlash( const std::string& _FileName ) {
		std::string WorkString = _FileName;
		
		// For all characters in the string, replace all Windows slashes with Unix slashes //
		for( size_t idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[ idx ] == '\\' )
				WorkString[ idx ] = '/';
		}
		
		// Return our slash updated string //
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Replaces all Unix slashes with Windows slashes //
	// ** NOTE ** : Only recommended for platform concious tools!  Don't use this in game code! //
	inline std::string WindowsSlash( const std::string& _FileName ) {
		std::string WorkString = _FileName;
		
		// For all characters in the string, replace all Unix slashes with Windows slashes //
		for( size_t idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[ idx ] == '/' )
				WorkString[ idx ] = '\\';
		}
		
		// Return our slash updated string //
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Converts lower case letters in a string to upper case //
	inline std::string UpperCase( const std::string& _FileName ) {
		std::string WorkString = _FileName;
		
		// For all characters in the string, offset characters in the lower case range to be upper//
		for( size_t idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[ idx ] >= 'a' )
				if ( WorkString[ idx ] <= 'z' )
					WorkString[ idx ] += 'A' - 'a';
		}
		
		// Return our slash updated string //
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Converts upper case letters in a string to lower case //
	inline std::string LowerCase( const std::string& _FileName ) {
		std::string WorkString = _FileName;
		
		// For all characters in the string, offset characters in the upper case range to be lower//
		for( size_t idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[ idx ] >= 'A' )
				if ( WorkString[ idx ] <= 'Z' )
					WorkString[ idx ] -= 'A' - 'a';
		}
		
		// Return our slash updated string //
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
	// - -------------------------------------------------------------------------------------- - //
	// Only returns sub-extensions, not the final extension //
	inline bool HasExtension( const std::string& _FileName, const std::string& _Pattern ) {
		return String::Extension( _FileName ).find( _Pattern + "." ) != std::string::npos;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Like above, but returns if any extension from filenames or directory names contains pattern
	inline bool HasAnyExtension( const std::string& _FileName, const std::string& _Pattern ) {
		if ( _FileName.find( _Pattern + Dot ) != std::string::npos )
			return true;
		if ( _FileName.find( _Pattern + Slash ) != std::string::npos )
			return true;
		return false;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return's true if a directory is found in a string //
	inline bool HasDirectory( const std::string& _FileName, const std::string& _Pattern ) {
		std::string Pattern = _Pattern;

		// If the last character in the pattern isn't a slash //
		if ( _Pattern[ _Pattern.size() - 1 ] != Slash )
			// Append a slash //
			Pattern += Slash;
		
		// Find the directory name pattern //
		size_t DirPos = String::Directory( _FileName ).find( Pattern );
		
		// If pattern not found //
		if ( DirPos == std::string::npos )
			return false;
		
		// If string was found at the beginning, then our pattern was matched in full //
		if ( DirPos == 0 )
			return true;
		
		// If the previous character is a slash, then our pattern was matched in full //
		if ( _FileName[DirPos - 1] == Slash )
			return true;
		
		// Not a full match //
		return false;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// Todo: Add Command line argument parsing code ... either here or elsewhere //

// - ------------------------------------------------------------------------------------------ - //
}; // namespace String //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_String_H__ //
// - ------------------------------------------------------------------------------------------ - //
