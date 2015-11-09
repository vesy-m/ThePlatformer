#pragma once

template <class T>
class		CSingletonDynamicAlloc
{
public:
	static T	&getInstance()
	{
		if (!_instance)
			_instance = new T;
		return *_instance;
	}

	static void	destroy()
	{
		if (_instance)
		{
			delete _instance;
			_instance = NULL;
		}
	}

protected:
	CSingletonDynamicAlloc() {}
	~CSingletonDynamicAlloc() {}

private:
	CSingletonDynamicAlloc(CSingletonDynamicAlloc &) {}
	void		operator=(CSingletonDynamicAlloc &) {}

	static T	*_instance;
};
template<class T> T *CSingletonDynamicAlloc<T>::_instance = NULL;


template <class T>
class			CSingletonStaticAlloc
{
public:
	static T	&getInstance()
	{
		static T instance;

		return instance;
	}

protected:
	CSingletonStaticAlloc() {}
	~CSingletonStaticAlloc() {}

private:
	CSingletonStaticAlloc(CSingletonStaticAlloc &) {}
	void		operator=(CSingletonStaticAlloc &) {}
};