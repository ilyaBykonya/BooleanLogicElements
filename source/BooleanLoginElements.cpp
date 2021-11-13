#include "BooleanLoginElements.h"

//====================================================================

Fasting::Fasting(bool value)
	:Fasting([value]() { return value; })
	{
	}
Fasting::Fasting(Fasting& source)
	: _outputSelector{ source._outputSelector }
	{
	}
Fasting::Fasting(function<bool()>&& selector)
	: _outputSelector(selector)
	{
	}
bool Fasting::value() const
{
	return _outputSelector();
}

AbstractSingleSlotValve::AbstractSingleSlotValve(const Fasting& fasting)
{
	resetInputValve(fasting);
}
void AbstractSingleSlotValve::resetInputValve(const Fasting& fasting)
{
	setInputValve(fasting, 0);
}

AbstractDoubleSlotValve::AbstractDoubleSlotValve(const Fasting& leftFasting, const Fasting& rightFasting)
{
	resetLeftInputValve(leftFasting);
	resetRightInputValve(rightFasting);
}
void AbstractDoubleSlotValve::resetLeftInputValve(const Fasting& fasting)
{
	setInputValve(fasting, 0);
}
void AbstractDoubleSlotValve::resetRightInputValve(const Fasting& fasting)
{
	setInputValve(fasting, 1);
}

//====================================================================

NotValve::NotValve(const Fasting& fasting)
	:AbstractSingleSlotValve{ fasting }
	{
	}
AndValve::AndValve(const Fasting& leftFasting, const Fasting& rightFasting)
	: AbstractDoubleSlotValve{ leftFasting, rightFasting }
	{
	}
OrValve::OrValve(const Fasting& leftFasting, const Fasting& rightFasting)
	:AbstractDoubleSlotValve{ leftFasting, rightFasting }
	{
	}
NotAndValve::NotAndValve(const Fasting& leftFasting, const Fasting& rightFasting)
	:AbstractDoubleSlotValve{ leftFasting, rightFasting }
	{
	}
NotOrValve::NotOrValve(const Fasting& leftFasting, const Fasting& rightFasting)
	:AbstractDoubleSlotValve{ leftFasting, rightFasting }
	{
	}
XorValve::XorValve(const Fasting& leftFasting, const Fasting& rightFasting)
	:AbstractDoubleSlotValve{ leftFasting, rightFasting }
	{
	}

//====================================================================

bool NotValve::calculateExpression() const
{
	//А шо. Не только петухон может булевую логику словами делать)))
	return not _inputValves[0].value();
}
bool AndValve::calculateExpression() const
{
	return _inputValves[0].value() and _inputValves[1].value();
}
bool OrValve::calculateExpression() const
{
	return _inputValves[0].value() or _inputValves[1].value();
}
bool NotAndValve::calculateExpression() const
{
	return not(_inputValves[0].value() and _inputValves[1].value());
}
bool NotOrValve::calculateExpression() const
{
	return not(_inputValves[0].value() or _inputValves[1].value());
}
bool XorValve::calculateExpression() const
{
	return _inputValves[0].value() != _inputValves[1].value();
}

//====================================================================