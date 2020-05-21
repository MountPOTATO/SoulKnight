#include "CallBackTimeCounter.h"


bool  CallBackTimeCounter::init() {
	m_isCounting = false;
	this->scheduleUpdate();
	return true;

}

void CallBackTimeCounter::update(float delta) {
	if (m_isCounting == false) {
		return;
	}
	m_fTime += delta;
	if (m_fTime >= m_fCBTime) {
		m_func();
		m_isCounting = false;
	}
}
void CallBackTimeCounter::start(float fCBTime, std::function<void()>func) {
	m_fCBTime = fCBTime;
	m_fTime = 0;
	m_func = func;
	m_isCounting = true;
}