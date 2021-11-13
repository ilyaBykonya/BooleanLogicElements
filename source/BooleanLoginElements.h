#pragma once
#include <functional>
#include <array>
using namespace std;
//====================================================================
//Вспомогательные и абстрактные элементы
class Fasting
{
private:
	function<bool()> _outputSelector;

public:
	Fasting() = default;
	Fasting(bool value);
	Fasting(Fasting& source);
	Fasting(function<bool()>&& selector);
	bool value() const;
};

template<size_t amountOfInputValves>
class AbstractValve: public Fasting
{
protected:
	array<Fasting, amountOfInputValves> _inputValves;
	void setInputValve(const Fasting& fasting, size_t index)
	{
		_inputValves[index] = fasting;
	}
	
public:
	AbstractValve()
		:Fasting(function<bool()>{ bind(&AbstractValve::calculateExpression, this) })
		{
		}
	virtual ~AbstractValve() = default;

	virtual bool calculateExpression() const = 0;//Логика вентиля
	bool operator()() const
	{
		return calculateExpression();
	}
};
class AbstractSingleSlotValve : public AbstractValve<1>
{
public:
	AbstractSingleSlotValve() = default;
	AbstractSingleSlotValve(const Fasting & fasting);
	void resetInputValve(const Fasting& fasting);
};
class AbstractDoubleSlotValve : public AbstractValve<2>
{
public:
	AbstractDoubleSlotValve() = default;
	AbstractDoubleSlotValve(const Fasting& leftFasting, const Fasting& rightFasting);
	void resetLeftInputValve(const Fasting& fasting);
	void resetRightInputValve(const Fasting& fasting);
};

//====================================================================
//Конкретные вентили
struct NotValve : public AbstractSingleSlotValve
{
	NotValve() = default;
	NotValve(const Fasting& fasting);
	virtual bool calculateExpression() const override;
};
struct AndValve : public AbstractDoubleSlotValve
{
	AndValve() = default;
	AndValve(const Fasting& leftFasting, const Fasting& rightFasting);
	virtual bool calculateExpression() const override;
};
struct OrValve : public AbstractDoubleSlotValve
{
	OrValve() = default;
	OrValve(const Fasting& leftFasting, const Fasting& rightFasting);
	virtual bool calculateExpression() const override;
};
struct NotAndValve : public AbstractDoubleSlotValve
{
	NotAndValve() = default;
	NotAndValve(const Fasting& leftFasting, const Fasting& rightFasting);
	virtual bool calculateExpression() const override;
};
struct NotOrValve : public AbstractDoubleSlotValve
{
	NotOrValve() = default;
	NotOrValve(const Fasting& leftFasting, const Fasting& rightFasting);
	virtual bool calculateExpression() const override;
};
struct XorValve : public AbstractDoubleSlotValve
{
	XorValve() = default;
	XorValve(const Fasting& leftFasting, const Fasting& rightFasting);
	virtual bool calculateExpression() const override;
};

//====================================================================
//Чтобы не писать каждый раз суффикс *Valve
using Not = NotValve;
using And = AndValve;
using Or = OrValve;
using NotAnd = NotAndValve;
using NotOr = NotOrValve;
using Xor = XorValve;
//====================================================================