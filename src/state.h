#ifndef __STATE_H__
#define __STATE_H__
namespace jaw3d {

///////////////////////////////////////////////// State

class State {
public:
	State();
	virtual ~State();

	// load
	virtual void load() = 0;
	virtual void unload() = 0;

	// update
	virtual void reshape();
	virtual void display();
private:

};

///////////////////////////////////////////////// TestArea

class TestArea : public State {
public:
	TestArea();
	~TestArea();

	// load
	void load();
	void unload();

	// update
	void reshape();
	void display();
private:
	Camera* m_camera;
	Lighting* m_lighting;
	Renderbuffer* m_renderbuffer;
};

} //jaw3d
#endif //__STATE_H__
