#ifndef __USER_INPUT_H__
#define __USER_INPUT_H__
namespace jaw3d {

///////////////////////////////////////////////// UserInput

enum class mouse_button_t { NONE, LEFT, MIDDLE, RIGHT, _LEN };
enum class mouse_event_t { NONE, DOWN, UP, MOVE, _LEN };
enum class key_event_t { NONE, DOWN, UP, _LEN };

class UserInput {
public:
	UserInput();
	~UserInput();
	void flush();

	// update
	void new_mouse_event( mouse_button_t, mouse_event_t, unsigned int x, unsigned int y, int dz=0 );
	void new_key_event( unsigned int key, key_event_t );

	// mouse
	unsigned int mouseX();
	unsigned int mouseY();
	int mouseDX();
	int mouseDY();
	int mouseDZ();
	bool mouse_event( mouse_button_t, mouse_event_t );

	// key
	bool keydown( char );
	bool keydown( unsigned int );
	bool key_event( char, key_event_t );
	bool key_event( unsigned int, key_event_t );
private:
	bool* m_mouseStates;
	mouse_event_t* m_mouseEvents;
	unsigned int m_mouseX;
	unsigned int m_mouseY;
	unsigned int m_mouseLastX;
	unsigned int m_mouseLastY;
	int m_mouseDX;
	int m_mouseDY;
	int m_mouseDZ;

	bool* m_keyStates;
	key_event_t* m_keyEvents;
private:
	static const unsigned int KEY_COUNT = 300;
};

} //jaw3d
#endif //__USER_INPUT_H__
