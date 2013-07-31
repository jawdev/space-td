#ifndef __MANAGER_H__
#define __MANAGER_H__
namespace jaw3d { namespace manager {


///////////////////////////////////////////////// reflist

template< class T > struct reflist {

	~reflist() {
		labels.clear();
		items.clear();
	}

	unsigned int load( T item, string ref="NOLABEL" ) {
		labels.push_back( ref );
		items.push_back( item );
		return items.size()-1;
	}

	T get( unsigned int id ) { return items[id]; }
	T get( string s ) {
		for( unsigned int i = 0; i < labels.size(); i++ ) {
			if( labels[i].compare( s ) == 0 ) {
				return items[i];
			}
		}
		return items[0];
	}

	void clear() { items.clear(); labels.clear(); }
	unsigned int size() { return items.size(); }

	vector< string > labels;
	vector< T > items;
};

///////////////////////////////////////////////// shaders

struct shaders {
	static reflist< ShaderProgram* >* rlist;
	static void release();
	static void clear();

	// load
	static unsigned int load( ShaderProgram*, string="NOLABEL" );
	static ShaderProgram* get( unsigned int id=0 );
	static ShaderProgram* get( string name );

	// uniform
	static GLint uloc( unsigned int id, string uniform );
	static GLint uloc( string name, string uniform );
};

///////////////////////////////////////////////// objects

struct objects {
	static reflist< Object* >* rlist;
	static void release();
	static void clear();

	// load
	static unsigned int load( Object*, string="NOLABEL" );
	static Object* get( unsigned int id=0 );
	static Object* get( string name );

	// update
	static void update( unsigned int id, float dtime );
	static void update( string name, float dtime );
	static void render( unsigned int id  );
	static void render( string name );
	static void bind( unsigned int id );
	static void bind( string name );
	static void bind_render( unsigned int id );
	static void bind_render( string name );
	static void all_update( float dtime );
	static void all_bind_render();
	static void all_tick( float dtime );
};

///////////////////////////////////////////////// states

struct states {
	static reflist< State* >* rlist;
	static void release();
	static void clear();

	// load
	static unsigned int load( State*, string="NOLABEL" );
	static State* get( unsigned int id=0 );
	static State* get( string name );

	// manage
	static State* activate( unsigned int id=0 );
	static State* activate( string name );
	static void reshape( int id=-1 );
	static void reshape( string name );
	static void display( int id=-1 );
	static void display( string name );
	static void key( unsigned char k, bool down, int id=-1 );
	static void key( unsigned char k, bool down, string name );
	
	static State* active;
};

inline static void release_all() {
	shaders::release();
	objects::release();
	states::release();
}

}} //manager/jaw3d
#endif //__MANAGER_H__
