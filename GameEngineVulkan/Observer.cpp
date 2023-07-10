#include "Subject.h"
#include "Observer.h"

Observer::Observer() : m_subject(nullptr)
{
}

Observer::~Observer()
{
	m_subject->detach(this);
}