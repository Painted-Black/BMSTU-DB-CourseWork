#pragma once

#include <memory>

template <typename T>
struct Singlenton
{
	template<typename ...Args>
	static T& Init(Args&&... args)
	{
		value .reset(new T(std::forward<Args>(args)...));
		return *value;
	}

	static T& getInstance()
	{
		return *value;
	}

private:
	static std::unique_ptr<T> value;
};

template <typename T>
std::unique_ptr<T> Singlenton<T>::value;
