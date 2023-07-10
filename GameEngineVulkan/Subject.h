#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
class Observer;

class Subject
{
public:
	Subject();
	~Subject();

	Subject* attach(Observer* observer);
	void detach(Observer* observer);
	void notify();

protected:
	std::vector<Observer*> observers;
};

#endif // !SUBJECT_H

