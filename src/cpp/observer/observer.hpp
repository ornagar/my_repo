/*
 * observer.h
 *
 *  Created on: Oct 31, 2017
 *      Author: Johnatan D
 */

#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include <algorithm>
#include <stdexcept>
#include <vector>


namespace ilrd {

template <class Event>
class CallBackBase;

template <class Event>
class Dispatcher {
public:
	Dispatcher() = default; //throws badalloc
	~Dispatcher(); // depends on user's notify_death function exceptions
	Dispatcher(const Dispatcher& other) = delete;
	Dispatcher& operator=(const Dispatcher& other) = delete;

	void notify(Event event);      // exceptions depends on user's notify functions
	void subscribe(CallBackBase<Event>* callback); //throws badalloc
	void unsubscribe(CallBackBase<Event>* callback); //throws std::invalid argument;

private :
	std::vector<CallBackBase<Event>*> m_callbacks;
};
template <class Event>
class CallBackBase {
protected:
	CallBackBase()noexcept = default ;
	virtual ~CallBackBase() noexcept;
	CallBackBase(const CallBackBase& other) = delete;
	CallBackBase& operator=(const CallBackBase& other) = delete;

private:
	void set_dispatcher(Dispatcher<Event> *dispatcher);
	friend class Dispatcher<Event>;
	virtual void notify(Event event) = 0;
	virtual void notifydeath() = 0;
	Dispatcher<Event> *m_dispatcher;
};

template <class Event, class C>
class CallBack : public CallBackBase<Event> {
public:
	typedef void (C::*NotifyMethod)(Event event);
	typedef void (C::*NotifyDeathMethod) ();

	CallBack(C *this_ptr, NotifyMethod notify, 
						  NotifyDeathMethod notify_death) noexcept;
	virtual ~CallBack() noexcept = default;
private:
	void notify(Event event) override;
	void notifydeath() override;
	C *m_this;
	NotifyMethod m_notify;
	NotifyDeathMethod m_notify_death;
};

/**********************************************************************/
template <class Event>
Dispatcher<Event>::~Dispatcher()
{
	for(auto& i : m_callbacks)
	{
		i->notifydeath();
        i->m_dispatcher->unsubscribe(i);
        i->m_dispatcher = nullptr;
	}
}

template <class Event>
void Dispatcher<Event>::notify(Event event)
{
	for(auto& i : m_callbacks)
	{
		i->notify(event);
	}
}

template <class Event>
void Dispatcher<Event>::subscribe(CallBackBase<Event>* callback)
{
	m_callbacks.insert(m_callbacks.begin(), callback);
    callback->m_dispatcher = this;
}

template <class Event>
void Dispatcher<Event>::unsubscribe(CallBackBase<Event>* callback)
{
	auto to_remove = std::find(m_callbacks.begin(), 
										   m_callbacks.end(), callback);
                                           
	if (to_remove == m_callbacks.end()) {
		throw std::invalid_argument("The requested callback was not \
														  subscribed");
	}
	m_callbacks.erase(to_remove);
}


template <class Event>
CallBackBase<Event>::~CallBackBase() noexcept
{
    if (m_dispatcher) {
        m_dispatcher->unsubscribe(this);
        m_dispatcher = nullptr;
    }
}


template <class Event, class C>
CallBack<Event, C>::CallBack(C *this_ptr, NotifyMethod notify,
						   NotifyDeathMethod notify_death) noexcept
	: m_this(this_ptr), 
	  m_notify(notify), 
	  m_notify_death(notify_death)
	  {}

template <class Event, class C>
void CallBack<Event, C>::notify(Event event)
{
	(m_this->*m_notify)(event);
}

template <class Event, class C>
void CallBack<Event, C>::notifydeath()
{
	(m_this->*m_notify_death)();
}

} /* namespace ilrd */

#endif /* OBSERVER_HPP_ */
