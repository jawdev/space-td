#include "config.h"
namespace jaw3d { namespace manager {

///////////////////////////////////////////////// shaders

reflist< ShaderProgram* >* shaders::rlist = new reflist< ShaderProgram* >();
void shaders::release() { delete rlist; }
void shaders::clear() { rlist->clear(); }

//----------------- load

unsigned int shaders::load( ShaderProgram* pProgram, string label ) { return rlist->load( pProgram, label ) ;}
ShaderProgram* shaders::get( unsigned int id ) { return rlist->get( id ); }
ShaderProgram* shaders::get( string label ) { return rlist->get( label ); }

//----------------- uniform

GLint shaders::uloc( unsigned int id, string uniform ) {
	ShaderProgram* p = get( id );
	if( p == NULL ) return -1;
	return p->uloc( uniform );
}

GLint shaders::uloc( string label, string uniform ) {
	ShaderProgram* p = get( label );
	if( p == NULL ) return -1;
	return p->uloc( uniform );
}

///////////////////////////////////////////////// objects

reflist< Object* >* objects::rlist = new reflist< Object* >();
void objects::release() { delete rlist; }
void objects::clear() { rlist->clear(); }

//----------------- load

unsigned int objects::load( Object* pObj, string label ) { return rlist->load( pObj, label ); }
Object* objects::get( unsigned int id ) { return rlist->get( id ); }
Object* objects::get( string label ) { return rlist->get( label ); }

//----------------- update

void objects::update( unsigned int id, float dtime ) {
	Object* o = rlist->get( id );
	if( o != NULL ) o->update( dtime );
}
void objects::update( string name, float dtime ) {
	Object* o = rlist->get( name );
	if( o != NULL ) o->update( dtime );
}
void objects::render( unsigned int id  ) {
	Object* o = rlist->get( id );
	if( o != NULL ) o->render();
}
void objects::render( string name ) {
	Object* o = rlist->get( name );
	if( o != NULL ) o->render();
}
void objects::bind( unsigned int id ) {
	Object* o = rlist->get( id );
	if( o != NULL ) o->bind();
}
void objects::bind( string name ) {
	Object* o = rlist->get( name );
	if( o != NULL ) o->bind();
}
void objects::bind_render( unsigned int id ) {
	Object* o = rlist->get( id );
	if( o != NULL ) o->bind_render();
}
void objects::bind_render( string name ) {
	Object* o = rlist->get( name );
	if( o != NULL ) o->bind_render();
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
State* states::active = NULL;
void states::release() { delete rlist; }
void states::clear() { rlist->clear(); }

//----------------- load

unsigned int states::load( State* s, string name ) { return rlist->load( s, name ); }
State* states::get( unsigned int id ) { return rlist->get( id ); }
State* states::get( string name ) { return rlist->get( name ); }

//----------------- manage

State* states::activate( unsigned int id ) {
	if( active != NULL ) active->unload();
	active = rlist->get( id );
	active->load();
	return active;
}
State* states::activate( string label ) {
	if( active != NULL ) active->unload();
	active = rlist->get( label );
	active->load();
	return active;
}

void states::reshape( int id ) {
	if( id < 0 && active != NULL ) { active->reshape(); }
	else {
		State* s = rlist->get( (unsigned int)id );
		if( s != NULL ) s->reshape();
	}
}
void states::reshape( string label ) {
	State* s = rlist->get( label );
	if( s != NULL ) s->reshape();
}

void states::display( int id ) {
	if( id < 0 && active != NULL ) active->display();
	else {
		State* s = rlist->get( (unsigned int)id );
		if( s != NULL ) s->display();
	}
}
void states::display( string label ) {
	State* s = rlist->get( label );
	if( s != NULL ) s->display();
}

void states::key( unsigned char k, bool down, int id ) {
	if( id < 0 && active != NULL ) active->key( k, down );
	else {
		State* s = rlist->get( (unsigned int)id );
		if( s != NULL ) s->key( k, down );
	}
}
void states::key( unsigned char k, bool down, string label ) {
	State* s = rlist->get( label );
	if( s != NULL ) s->display();
}

}} //manager/jawdev
