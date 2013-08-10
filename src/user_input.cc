#include "config.h"
namespace jaw3d {

///////////////////////////////////////////////// UserInput

UserInput::UserInput() {
	m_mouseStates = new bool[(unsigned int)mouse_button_t::_LEN];
	m_mouseEvents = new mouse_event_t[(unsigned int)mouse_event_t::_LEN];
	m_keyStates = new bool[KEY_COUNT];
	m_keyEvents = new key_event_t[(unsigned int)key_event_t::_LEN];

	for( unsigned int i = 0; i < (unsigned int)mouse_button_t::_LEN; i++ ) m_mouseStates[i] = false;
	for( unsigned int i = 0; i < KEY_COUNT; i++ ) m_keyStates[i] = false;

	m_mouseX = m_mouseY = 0;
	flush();
}

UserInput::~UserInput() {
	delete m_mouseStates;
	delete m_mouseEvents;
	delete m_keyStates;
	delete m_keyEvents;
}

void UserInput::flush() {
	for( unsigned int i = 0; i < (unsigned int)mouse_event_t::_LEN; i++ ) m_mouseEvents[i] = mouse_event_t::NONE;
	for( unsigned int i = 0; i < (unsigned int)key_event_t::_LEN; i++ ) m_keyEvents[i] = key_event_t::NONE;

	m_mouseLastX = m_mouseX;
	m_mouseLastY = m_mouseY;
	m_mouseDX = m_mouseDY = 0;
}

//----------------- update

void UserInput::new_mouse_event( mouse_button_t btn, mouse_event_t state, unsigned int x, unsigned int y, int dz ) {
	if( SETTINGS::debug ) cout << "[DEBUG] UserInput::new_mouse_event> {button=" << (int)btn << ",event=" << (int)state << ",x=" << x << ",y=" << y << ",dz=" << dz << "}" << endl;
	m_mouseX = x;
	m_mouseY = y;
	m_mouseDX = m_mouseX-m_mouseLastX;
	m_mouseDY = m_mouseY-m_mouseLastY;
	m_mouseDZ = dz;
	if( state == mouse_event_t::DOWN ) m_mouseStates[(unsigned int)btn] = true;
	else if( state == mouse_event_t::UP ) m_mouseStates[(unsigned int)btn] = false;
	m_mouseEvents[(unsigned int)btn] = state;
}

void UserInput::new_key_event( unsigned int key, key_event_t state ) {
	if( SETTINGS::debug ) cout << "[DEBUG] UserInput::new_key_event> {key=" << key << ",event=" << (int)state << "}" << endl;
	m_keyEvents[key] = state;
	if( state == key_event_t::DOWN ) m_keyStates[key] = true;
	else if( state == key_event_t::UP ) m_keyStates[key] = false;
}

//----------------- mouse

unsigned int UserInput::mouseX() { return m_mouseX; }
unsigned int UserInput::mouseY() { return m_mouseY; }
int UserInput::mouseDX() { return m_mouseDX; }
int UserInput::mouseDY() { return m_mouseDY; }
int UserInput::mouseDZ() { return m_mouseDZ; }
bool UserInput::mouse_event( mouse_button_t btn, mouse_event_t state ) { return ( m_mouseEvents[(unsigned int)btn] == state ); }

//----------------- keyboard

bool UserInput::keydown( char k ) { return keydown( (unsigned int)k ); }
bool UserInput::keydown( unsigned int k ) { return m_keyStates[k]; }
bool UserInput::key_event( char k, key_event_t state ) { return key_event( (unsigned int)k, state ); }
bool UserInput::key_event( unsigned int k, key_event_t state ) { return ( m_keyEvents[k] == state ); }

} //jaw3d
