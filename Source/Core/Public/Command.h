#pragma once
#include <Namespace.h>

C3_NAMESPACE_BEGIN

class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void Execute() {}
	virtual void Undo() {}
};

template <typename T>
class FCallableCommand : public ICommand
{
public:
	FCallableCommand(T& callable)
	{
		Callable = callable;
	}
	void Execute() override
	{
		Callable();
	}
private:
	T Callable;
};

template <typename T>
class FCallablePtrCommand : public ICommand
{
public:
	FCallablePtrCommand()
	{
	}
	FCallablePtrCommand(T& callable)
	{
		Callable = callable;
	}
	void Execute() override
	{
		(Callable)();
	}
private:
	T Callable;
};

C3_NAMESPACE_END
