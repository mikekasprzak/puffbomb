// - ------------------------------------------------------------------------------------------ - //
// LogLevels //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Debug_LogLevels_H__
#define __Debug_LogLevels_H__
// - ------------------------------------------------------------------------------------------ - //
#define LOG_HIGHEST_LEVEL					20
#define LOG_WORKING_CORRECTLY				1
#define LOG_IN_DEVELOPMENT					10
// - ------------------------------------------------------------------------------------------ - //

#define LOG_SUBSYSTEM_CREATE_MESSAGE		3
#define LOG_SUBSYSTEM_INFO_MESSAGE			0

#define LOG_WINDOW_FOCUS					5

#define LOG_SUBSYSTEM_MEMBER_CREATE			1

// - ------------------------------------------------------------------------------------------ - //
#define LOG_PHIZOBJECT_CREATE		LOG_SUBSYSTEM_CREATE_MESSAGE
#define LOG_PHIZOBJECT_INFO			LOG_SUBSYSTEM_INFO_MESSAGE

#define LOG_EDITOR_CREATE			LOG_SUBSYSTEM_CREATE_MESSAGE
#define LOG_EDITOR_INFO				LOG_SUBSYSTEM_INFO_MESSAGE

#define LOG_MAP_CREATE				LOG_SUBSYSTEM_CREATE_MESSAGE
#define LOG_MAP_INFO				LOG_SUBSYSTEM_INFO_MESSAGE

#define LOG_MESH_CREATE				LOG_SUBSYSTEM_CREATE_MESSAGE
#define LOG_MESH_INFO				LOG_SUBSYSTEM_INFO_MESSAGE

#define LOG_TEXTURE_CREATE			LOG_SUBSYSTEM_CREATE_MESSAGE
#define LOG_TEXTURE_INFO			LOG_SUBSYSTEM_INFO_MESSAGE

#define LOG_LOAD_MESH				LOG_IN_DEVELOPMENT
// - ------------------------------------------------------------------------------------------ - //
#define LOG_POLYOBJECT				LOG_WORKING_CORRECTLY
#define LOG_POLYOBJECT_CREATE		LOG_WORKING_CORRECTLY
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Debug_LogLevels_H__ //
// - ------------------------------------------------------------------------------------------ - //
