#pragma once

enum class SceneName {Aufgabe1a, Aufgabe1b, Aufgabe1c, Aufgabe2a, Aufgabe2b, Aufgabe3a, Aufgabe3b, Aufgabe4a, Aufgabe5a, Other};
class Screen {
public:
	Screen(SceneName sceneName) {
		this->sceneName = sceneName;
	};
	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	~Screen() {};
protected:
	SceneName sceneName{ SceneName::Other };
private:
	
};