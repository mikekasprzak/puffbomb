// - ------------------------------------------------------------------------------------------ - //
// Keys //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Platform_Keys_H__
#define __Platform_Keys_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define KEY_OFFSET					1024

#define MOUSE_AXIS_COUNT			2
#define KEY_AXIS_COUNT				0
#define PAD_AXIS_COUNT				7

#define MOUSE_BUTTON_COUNT			4
#define KEY_BUTTON_COUNT			512
#define PAD_BUTTON_COUNT			10

#define MAX_SYSTEM_JOYSTICKS		10
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define KEY_BACKSPACE				SDLK_BACKSPACE		
#define KEY_TAB						SDLK_TAB
#define KEY_CLEAR					SDLK_CLEAR
#define KEY_ENTER					SDLK_RETURN
#define KEY_PAUSE					SDLK_PAUSE
#define KEY_ESC						SDLK_ESCAPE
#define KEY_SPACE					SDLK_SPACE
#define KEY_EXCLAIM					SDLK_EXCLAIM
#define KEY_QUOTEDBL				SDLK_QUOTEDBL
#define KEY_HASH					SDLK_HASH
#define KEY_DOLLAR					SDLK_DOLLAR
#define KEY_AMPERSAND				SDLK_AMPERSAND
#define KEY_QUOTE					SDLK_QUOTE
#define KEY_LEFTPAREN				SDLK_LEFTPAREN
#define KEY_RIGHTPAREN				SDLK_RIGHTPAREN
#define KEY_ASTERISK				SDLK_ASTERISK
#define KEY_PLUS					SDLK_PLUS
#define KEY_COMMA					SDLK_COMMA
#define KEY_MINUS					SDLK_MINUS
#define KEY_PEROID					SDLK_PERIOD
#define KEY_SLASH					SDLK_SLASH
#define KEY_0						SDLK_0
#define KEY_1						SDLK_1
#define KEY_2						SDLK_2
#define KEY_3						SDLK_3
#define KEY_4						SDLK_4
#define KEY_5						SDLK_5
#define KEY_6						SDLK_6
#define KEY_7						SDLK_7
#define KEY_8						SDLK_8
#define KEY_9						SDLK_9
#define KEY_COLON					SDLK_COLON
#define KEY_SEMICOLON				SDLK_SEMICOLON
#define KEY_LESS					SDLK_LESS
#define KEY_EQUALS					SDLK_EQUALS
#define KEY_GREATER					SDLK_GREATER
#define KEY_QUESTION				SDLK_QUESTION
#define KEY_AT						SDLK_AT
#define KEY_LEFTBRACKET				SDLK_LEFTBRACKET
#define KEY_BACKSLASH				SDLK_BACKSLASH
#define KEY_RIGHTBRACKET			SDLK_RIGHTBRACKET
#define KEY_CARET					SDLK_CARET
#define KEY_UNDERSCORE				SDLK_UNDERSCORE
#define KEY_BACKQUOTE				SDLK_BACKQUOTE
#define KEY_A						SDLK_a
#define KEY_B						SDLK_b
#define KEY_C						SDLK_c
#define KEY_D						SDLK_d
#define KEY_E						SDLK_e
#define KEY_F						SDLK_f
#define KEY_G						SDLK_g
#define KEY_H						SDLK_h
#define KEY_I						SDLK_i
#define KEY_J						SDLK_j
#define KEY_K						SDLK_k
#define KEY_L						SDLK_l
#define KEY_M						SDLK_m
#define KEY_N						SDLK_n
#define KEY_O						SDLK_o
#define KEY_P						SDLK_p
#define KEY_Q						SDLK_q
#define KEY_R						SDLK_r
#define KEY_S						SDLK_s
#define KEY_T						SDLK_t
#define KEY_U						SDLK_u
#define KEY_V						SDLK_v
#define KEY_W						SDLK_w
#define KEY_X						SDLK_x
#define KEY_Y						SDLK_y
#define KEY_Z						SDLK_z
#define KEY_DELETE					SDLK_DELETE
#define KEY_0_PAD					SDLK_KP0
#define KEY_1_PAD					SDLK_KP1
#define KEY_2_PAD					SDLK_KP2
#define KEY_3_PAD					SDLK_KP3
#define KEY_4_PAD					SDLK_KP4
#define KEY_5_PAD					SDLK_KP5
#define KEY_6_PAD					SDLK_KP6
#define KEY_7_PAD					SDLK_KP7
#define KEY_8_PAD					SDLK_KP8
#define KEY_9_PAD					SDLK_KP9
#define KEY_PERIOD_PAD				SDLK_KP_PERIOD
#define KEY_DEVIDE_PAD				SDLK_KP_DIVIDE
#define KEY_MULTIPLY_PAD			SDLK_KP_MULTIPLY
#define	KEY_MINUS_PAD				SDLK_KP_MINUS
#define KEY_PLUS_PAD				SDLK_KP_PLUS
#define KEY_ENTER_PAD				SDLK_KP_ENTER
#define KEY_EQUALS_PAD				SDLK_KP_EQUALS
#define KEY_UP						SDLK_UP
#define KEY_DOWN					SDLK_DOWN
#define KEY_RIGHT					SDLK_RIGHT
#define KEY_LEFT					SDLK_LEFT
#define KEY_INSERT					SDLK_INSERT
#define KEY_HOME					SDLK_HOME
#define KEY_END						SDLK_END
#define KEY_PGUP					SDLK_PAGEUP
#define KEY_PGDN					SDLK_PAGEDOWN
#define KEY_F1						SDLK_F1
#define KEY_F2						SDLK_F2
#define KEY_F3						SDLK_F3
#define KEY_F4						SDLK_F4
#define KEY_F5						SDLK_F5
#define KEY_F6						SDLK_F6
#define KEY_F7						SDLK_F7
#define KEY_F8						SDLK_F8
#define KEY_F9						SDLK_F9
#define KEY_F10						SDLK_F10
#define KEY_F11						SDLK_F11
#define KEY_F12						SDLK_F12
#define KEY_F13						SDLK_F13
#define KEY_F14						SDLK_F14
#define KEY_F15						SDLK_F15
#define KEY_NUMLOCK					SDLK_NUMLOCK
#define KEY_CAPSLOCK				SDLK_CAPSLOCK
#define KEY_SCRLOCK					SDLK_SCROLLOCK
#define KEY_LSHIFT					SDLK_LSHIFT
#define KEY_RSHIFT					SDLK_RSHIFT
#define KEY_LCTRL					SDLK_LCTRL
#define KEY_RCTRL					SDLK_RCTRL
#define KEY_LALT					SDLK_LALT
#define KEY_RALT					SDLK_RALT
#define KEY_LMETA					SDLK_LMETA
#define KEY_RMETA					SDLK_RMETA
#define KEY_LWINDOWS				SDLK_LSUPER
#define KEY_RWINDOWS				SDLK_RSUPER
#define KEY_MODE					SDLK_MODE
#define KEY_HELP					SDLK_HELP
#define KEY_PRINT					SDLK_PRINT
#define KEY_SYSREQ					SDLK_SYSREQ
#define KEY_BREAK					SDLK_BREAK
#define KEY_MENU					SDLK_MENU
#define KEY_POWER					SDLK_POWER
#define KEY_EURO					SDLK_EURO
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define MOUSE_1						(KEY_OFFSET + 0)
#define MOUSE_2						(KEY_OFFSET + 1)
#define MOUSE_3						(KEY_OFFSET + 2)
#define MOUSE_4						(KEY_OFFSET + 3)
#define MOUSE_5						(KEY_OFFSET + 4)
#define MOUSE_6						(KEY_OFFSET + 5)
#define MOUSE_7						(KEY_OFFSET + 6)
#define MOUSE_8						(KEY_OFFSET + 7)
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define PAD_1						(KEY_OFFSET + (1  * 32))
#define PAD_2						(KEY_OFFSET + (2  * 32))
#define PAD_3						(KEY_OFFSET + (3  * 32))
#define PAD_4						(KEY_OFFSET + (4  * 32))
#define PAD_5						(KEY_OFFSET + (5  * 32))
#define PAD_6						(KEY_OFFSET + (6  * 32))
#define PAD_7						(KEY_OFFSET + (7  * 32))
#define PAD_8						(KEY_OFFSET + (8  * 32))
#define PAD_9						(KEY_OFFSET + (9  * 32))
#define PAD_10						(KEY_OFFSET + (10 * 32))
#define PAD_11						(KEY_OFFSET + (11 * 32))
#define PAD_12						(KEY_OFFSET + (12 * 32))
#define PAD_13						(KEY_OFFSET + (13 * 32))
#define PAD_14						(KEY_OFFSET + (14 * 32))
#define PAD_15						(KEY_OFFSET + (15 * 32))
// - ------------------------------------------------------------------------------------------ - //
#define PAD_ALLPADS					PAD_12

#define PAD_KEYBOARD				PAD_13
#define PAD_MOUSE					PAD_14
#define PAD_REMOTE					PAD_15
// - ------------------------------------------------------------------------------------------ - //
#define PAD_FACE_A					0
#define PAD_FACE_B					1
#define PAD_FACE_X					2
#define PAD_FACE_Y					3

#define PAD_L						4
#define PAD_R						5

#define PAD_STICK1					6
#define PAD_STICK2					7

#define PAD_BACK					8
#define PAD_START					9

//#define PAD_SELECT					PAD_BACK
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Platform_Keys_H__ //
// - ------------------------------------------------------------------------------------------ - //
