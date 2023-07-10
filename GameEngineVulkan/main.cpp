#include "Engine.h"

int main()
{
	Engine* engine = Engine::GetInstance();
	engine->setInfo(800, 600, "Test Title");
	engine->initEngine();
	engine->mainLoop();
}
