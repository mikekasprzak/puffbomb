# - -------------------------------------------------------------------------------------------- - #
GAME_TARGET		:=	PuffBOMB
CONTENT_TARGET	:=	PuffBOMB
# - -------------------------------------------------------------------------------------------- - #
PLATFORM		:=	GL
HOST_PLATFORM	:=	GL
# - -------------------------------------------------------------------------------------------- - #
PROGRAM_SUFFIX	:=	.exe
# - -------------------------------------------------------------------------------------------- - #
# Comment out this line to disable editors ----------------------------------------------------- - #
EDITOR			:=	true
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# - Development system specific macros to define ----------------------------------------------- - #
# - Example: SCREEN_W=1024  SCREEN_H=768  WINDOWED
DEFINES			:=	
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# Comment this line out to disable debug messages, logging, asserts, and other debug tools ----- - #
DEBUGGING		:=	true
# - -------------------------------------------------------------------------------------------- - #
# Set the debug logging level - The lower the level, the more messages ------------------------- - #
# - Example: 0 = all messages, 1 = all but realtime, 10 = important messages, 100 = no messages  - #
LOG_LEVEL		:=	1
# - -------------------------------------------------------------------------------------------- - #
# Comment out this line to display logging to console, else it's the file to write logs to ----- - #
CAPTURE_TARGET	:=	../../../../stdout.txt
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# - Number of CPU Threads to use for compiling ------------------------------------------------- - #
THREADS			:=	2
# - -------------------------------------------------------------------------------------------- - #
# Comment out this line to disable DISTCC distributed compiling -------------------------------- - #
#USE_DISTCC		:=	true
# - -------------------------------------------------------------------------------------------- - #
