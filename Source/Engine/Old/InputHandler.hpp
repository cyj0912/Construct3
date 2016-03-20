#pragma once
#include <vector>

namespace mf {

enum MouseKey
{
	MK_LEFT,
	MK_RIGHT
};

enum InputEvent
{
	ENTER_PEN_EDIT_MODE,
	SAVE_PEN,
	SAVE_SCENE,
	DROP_A_POINT,
	W_DOWN,
	A_DOWN,
	S_DOWN,
	D_DOWN,
	W_UP,
	A_UP,
	S_UP,
	D_UP
};

std::string SerializeFirstScene();
void DeserializeFirstScene();
void CursorSet(int x, int y);

class InputEventListener
{
public:
	virtual void OnEvent(int e) = 0;
};

class InputHandler {
public:
	void InjectKeyEvent(char keyAscii, char action)
	{
		if (keyAscii == 0x1B)
			Exit();
		if (keyAscii == 'Z' && action == 'D')
			SendToListeners(ENTER_PEN_EDIT_MODE);
		if (keyAscii == 'X' && action == 'D')
			SendToListeners(SAVE_PEN);
		if (keyAscii == 'C' && action == 'D')
		{
			std::string s = SerializeFirstScene();
			SendToListeners(SAVE_SCENE);
		}
		if (keyAscii == 'W' && action == 'D')
		{
			SendToListeners(W_DOWN);
		}
		if (keyAscii == 'A' && action == 'D')
		{
			SendToListeners(A_DOWN);
		}
		if (keyAscii == 'S' && action == 'D')
		{
			SendToListeners(S_DOWN);
		}
		if (keyAscii == 'D' && action == 'D')
		{
			SendToListeners(D_DOWN);
		}
		if (keyAscii == 'W' && action == 'U')
		{
			SendToListeners(W_UP);
		}
		if (keyAscii == 'A' && action == 'U')
		{
			SendToListeners(A_UP);
		}
		if (keyAscii == 'S' && action == 'U')
		{
			SendToListeners(S_UP);
		}
		if (keyAscii == 'D' && action == 'U')
		{
			SendToListeners(D_UP);
		}
		if (keyAscii == 'O' && action == 'U')
		{
			SerializeFirstScene();
		}
		if (keyAscii == 'P' && action == 'U')
		{
			DeserializeFirstScene();
		}
	}

	void InjectMouseEvent(int button, char action)
	{
		if (button == MK_LEFT && action == 'D')
			SendToListeners(DROP_A_POINT);
	}

	void InjectMouseMove(int x, int y)
	{
		CursorSet(x, y);
	}

	void SendToListeners(int i)
	{
		for (auto l : Listeners)
			l->OnEvent(i);
	}

	void EraseFromListener(InputEventListener* p)
	{
		for (std::vector<InputEventListener*>::iterator iter = Listeners.begin(); iter != Listeners.end();
		++iter)
		{
			if(*iter == p)
			{
				Listeners.erase(iter);
				break;
			}
		}
	}

	std::vector<InputEventListener*> Listeners;
};

InputHandler GlobalInputHandler;

}
