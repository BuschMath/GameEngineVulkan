#include "Observer.h"
#include "Subject.h"
#include <algorithm>

Subject::Subject()
{
}

Subject::~Subject()
{
}

Subject* Subject::attach(Observer* observer)
{
	observers.push_back(observer);

	return this;
}

void Subject::detach(Observer* observer)
{
	auto it = std::find(observers.begin(), observers.end(), observer);
	if (it != observers.end())
	{
		observers.erase(it);
	}
}

void Subject::notify()
{
	for (auto observer : observers)
	{
		observer->update();
	}
}