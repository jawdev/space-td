#include "config.h"
namespace jaw3d { namespace manager {

///////////////////////////////////////////////// shaders

reflist< ShaderProgram* >* shaders::rlist = new reflist< ShaderProgram* >();
void shaders::release() { delete rlist; }
void shaders::clear() { rlist->clear(); }

//----------------- load

unsigned int shaders::load( ShaderProgram* pProgram, string label ) { if( SETTINGS::debug ) cout << "[DEBUG] manager::shaders::load> loading ShaderProgram (" << label << "->" << pProgram << ")" << endl; return rlist->load( pProgram, label ) ;}
ShaderProgram* shaders::get( unsigned int id ) { return rlist->get( id ); }
ShaderProgram* shaders::get( string label ) { return rlist->get( label ); }

//----------------- uniform

GLint shaders::uloc( unsigned int id, string uniform ) {
	ShaderProgram* p = get( id );
	if( p == nullptr ) return -1;
	return p->uloc( uniform );
}

GLint shaders::uloc( string label, string uniform ) {
	ShaderProgram* p = get( label );
	if( p == nullptr ) return -1;
	return p->uloc( uniform );
}

///////////////////////////////////////////////// objects

reflist< Object* >* objects::rlist = new reflist< Object* >();
void objects::release() { delete rlist; }
void objects::clear() { rlist->clear(); }

//----------------- load

unsigned int objects::load( Object* pObj, string label ) { if( SETTINGS::debug ) cout << "[DEBUG] manager::objects::load> loading Object (" << label << "->" << pObj << ")" << endl; return rlist->load( pObj, label ); }
Object* objects::get( unsigned int id ) { return rlist->get( id ); }
Object* objects::get( string label ) { return rlist->get( label ); }

//----------------- update

void objects::update( unsigned int id, float dtime ) {
	Object* o = rlist->get( id );
	if( o != nullptr ) o->update( dtime );
}
void objects::update( string name, float dtime ) {
	Object* o = rlist->get( name );
	if( o != nullptr ) o->update( dtime );
}
void objects::render( unsigned int id  ) {
	Object* o = rlist->get( id );
	if( o != nullptr ) o->render();
}
void objects::render( string name ) {
	Object* o = rlist->get( name );
	if( o != nullptr ) o->render();
}
void objects::bind( unsigned int id ) {
	Object* o = rlist->get( id );
	if( o != nullptr ) o->bind();
}
void objects::bind( string name ) {
	Object* o = rlist->get( name );
	if( o != nullptr ) o->bind();
}
void objects::bind_render( unsigned int id ) {
	Object* o = rlist->get( id );
	if( o != nullptr ) o->bind_render();
}
void objects::bind_render( string name ) {
	Object* o = rlist->get( name );
	if( o != nullptr ) o->bind_render();
}
void objects::all_update( float dtime ) {
	for( unsigned int i = 0; i < rlist->size(); i++ ) {
		rlist->get( i )->update( dtime );
	}
}
void objects::all_bind_render() {
	for( unsigned int i = 0; i < rlist->size(); i++ ) {
		rlist->get( i )->bind_render();
	}
}
void objects::all_tick( float dtime ) {
	for( unsigned int i = 0; i < rlist->size(); i++ ) {
		rlist->get( i )->update( dtime );
		rlist->get( i )->bind_render();
	}
}

///////////////////////////////////////////////// states

reflist< State* >* states::rlist = new reflist< State* >();
State* states::active = nullptr;
void states::release() { delete rlist; }
void states::clear() { rlist->clear(); }

//----------------- load

unsigned int states::load( State* s, string name ) { if( SETTINGS::debug ) cout << "[DEBUG] manager::states::load> loading State (" << name << "->" << s << ")" << endl; return rlist->load( s, name ); }
State* states::get( unsigned int id ) { return rlist->get( id ); }
State* states::get( string name ) { return rlist->get( name ); }

//----------------- manage

State* states::activate( unsigned int id ) {
	if( active != nullptr ) active->unload();
	active = rlist->get( id );
	active->load();
	return active;
}
State* states::activate( string label ) {
	if( active != nullptr ) active->unload();
	active = rlist->get( label );
	active->load();
	return active;
}

void states::reshape( int id ) {
	if( id < 0 && active != nullptr ) { active->reshape(); }
	else {
		State* s = rlist->get( (unsigned int)id );
		if( s != nullptr ) s->reshape();
	}
}
void states::reshape( string label ) {
	State* s = rlist->get( label );
	if( s != nullptr ) s->reshape();
}

void states::display( int id ) {
	if( id < 0 && active != nullptr ) active->display();
	else {
		State* s = rlist->get( (unsigned int)id );
		if( s != nullptr ) s->display();
	}
}
void states::display( string label ) {
	State* s = rlist->get( label );
	if( s != nullptr ) s->display();
}

void states::new_mouse_event( mouse_button_t b, mouse_event_t e, unsigned int x, unsigned int y, int dz, int id ) {
	if( id < 0 && active != nullptr && active->user_input() != nullptr ) active->user_input()->new_mouse_event( b, e, x, y, dz );
	else {
		State* s = rlist->get( (unsigned int)id );
		if( s != nullptr && s->user_input() != nullptr ) s->user_input()->new_mouse_event( b, e, x, y, dz );
	}
}
void states::new_mouse_event( mouse_button_t b, mouse_event_t e, unsigned int x, unsigned int y, int dz, string label ) {
	State* s = rlist->get( label );
	if( s != nullptr && s->user_input() != nullptr ) s->user_input()->new_mouse_event( b, e, x, y, dz );
}

void states::new_key_event( unsigned int k, key_event_t e, int id ) {
	if( id < 0 && active != nullptr && active->user_input() != nullptr ) active->user_input()->new_key_event( k, e );
	else {
		State* s = rlist->get( (unsigned int)id );
		if( s != nullptr && s->user_input() != nullptr ) s->user_input()->new_key_event( k, e );
	}
}
void states::new_key_event( unsigned int k, key_event_t e, string label ) {
	State* s = rlist->get( label );
	if( s != nullptr && s->user_input() != nullptr ) s->user_input()->new_key_event( k, e );
}


}} //manager/jawdev
