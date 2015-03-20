#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "keymap.h"

struct PVec2f
{
	float x, y;
};

struct PVec2i
{
	int x, y;
};

//Basic input states that we can expect from most 
//application instances
struct SMouse
{
	int px,py;
	int dx,dy;
	int wheelRot;
	bool lmb;
	bool mmb;
	bool rmb;
};

#define BUTTON_PRESS			0x1
#define BUTTON_TOGGLE			0x2
#define BUTTON_PRESS_TOGGLE		0x3
#define BUTTON_PRESS_RELEASE	0x2

typedef struct 
{
	unsigned char status;	

	void ClearStatus(){status = 0;}
	void SetPress(void){status |= BUTTON_PRESS;}
	void SetToggle(void){status |= BUTTON_TOGGLE;}
	void UnsetToggle(void){status &= ~BUTTON_TOGGLE;}
	bool IsPressed(void)const{return status & BUTTON_PRESS;}
	bool IsToggledPress(void)const{return status == BUTTON_PRESS_TOGGLE;}
	bool IsToggledRelease(void)const{return status == BUTTON_PRESS_RELEASE;}

}Button;

struct Keyboard
{
	Button keys[KB_MAX];
};

struct Gamepad
{
	PVec2f leftStick, rightStick;
	float leftTrigger,rightTrigger;
	Button d_up,d_down,d_left,d_right; //dpad
	Button fb_up,fb_down,fb_left,fb_right; //face buttons
	Button start,select;
};

//not too keen on this, should just switch it to being pure C
//and maybe make a wrapper for it
class CPlatform
{
protected:
	bool		m_quit;			//
	float		m_dt;			//delta time value
	PVec2i		m_size;
	PVec2i		m_position;
	SMouse		m_mouse;
	Keyboard	m_keyboard;
	Gamepad		m_gamepad;
	bool		m_showingDebugConsole;
	void		*m_pData;		// platform specific data

	void		(*m_pConsoleCallback)(const char c);
	void		(*m_pConsoleKeyCallback)(const unsigned int key_idx);
	
public:	
	enum MultiSample
	{
		MS_0 = 0, //0ff
		MS_4 = 4,
		MS_8 = 8,
		MS_16 = 16,
		MS_32 = 32,
		MS_64 = 64,
	};
	bool Create(wchar_t* title, int glMajor, int glMinor, int width, int height, int clrBits, int alphaBits,int dphBits, int stnBits, MultiSample ms = MS_0);
	void Close(void);
	//runtime generally called once per frame
	void Tick(void);
	void UpdateBuffers(void);
	void ShowDebugConsole(void);
	void HideDebugConsole(void);

	//Get/Set
	float GetDT(void)const{return m_dt;}		
	void Quit(void)const;
	bool IsQuitting(void)const{return m_quit;}

	PVec2i&	GetSize(void){return m_size;}
	PVec2i&	GetPosition(void){return m_position;}
	SMouse& GetMouse(){return m_mouse;}
	Keyboard& GetKeyboard(){return m_keyboard;}	

	unsigned int  PosX(void)const{return m_position.x;}
	unsigned int  PosY(void)const{return m_position.y;}
	unsigned int  Width(void)const{return m_size.x;}
	unsigned int  Height(void)const{return m_size.y;}		
	const SMouse& GetMouseState() const{return m_mouse;}
	const Keyboard& GetKeyboardState() const{return m_keyboard;}
	const Gamepad& GetGamepad(unsigned int) const{return m_gamepad;}


	void SetConsoleInputCallback(void (*p_func)(const char c)){m_pConsoleCallback = p_func;}
	void SetConsoleKeyCallback(void (*p_func)(const unsigned int idx)){m_pConsoleKeyCallback= p_func;}
	void ConsoleInputCallback(const char c)	
	{
		if(m_pConsoleCallback)
			m_pConsoleCallback(c);	
	}

	void ConsoleKeyCallback(const unsigned int idx)	
	{
		if(m_pConsoleKeyCallback)
			m_pConsoleKeyCallback(idx);	
	}

	CPlatform(void);
	virtual ~CPlatform(void);


};

extern CPlatform* GetPlatform(void);

#endif //_PLATFORM_H_