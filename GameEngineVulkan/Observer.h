#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer
{
public:
	Observer();
	virtual ~Observer();
	virtual void update() = 0;

	void setSubject(Subject* subject) { m_subject = subject; };

protected:
	Subject* m_subject;
};

#endif // !OBSERVER_H

