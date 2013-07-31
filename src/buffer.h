#ifndef __BUFFER_H__
#define __BUFFER_H__
namespace jaw3d {

///////////////////////////////////////////////// Renderbuffer

class Renderbuffer {
public:
	Renderbuffer();
	~Renderbuffer();
	
	// manage
	void resize( unsigned int w=0, unsigned int h=0 );
	void use();
	void blit( unsigned int=0 );

	// get
	unsigned int width();
	unsigned int height();
	GLuint gl_framebuffer();
	GLuint gl_renderbuffer( unsigned int id );
private:
	unsigned int m_width;
	unsigned int m_height;

	GLuint m_framebuffer;
	GLuint* m_renderbuffers;

	static const unsigned int COLOR = 0;
	static const unsigned int DEPTH = 1;
	static const unsigned int NUM_BUFFERS = 2;
};

}
#endif //__BUFFER_H__
