#ifndef __STATE_H__
#define __STATE_H__
namespace jaw3d {

///////////////////////////////////////////////// State

class State {
public:
	State();
	virtual ~State();

	// load
	virtual void load();
	virtual void unload();

	// update
	virtual void reshape();
	virtual void display();

	// get
	UserInput* user_input();
protected:
	UserInput* m_userInput;
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
	double m_time;
	tools::fps_tracker* m_fps;
	Camera* m_camera;
	DirectionLight* m_light;
	Renderbuffer* m_renderbuffer;
};

} //jaw3d
#endif //__STATE_H__
