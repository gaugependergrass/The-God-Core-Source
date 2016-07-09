#include <cstdlib>
#include "Trigger.h"

int Trigger::getTriggerType()
{
	return triggerType;
}

void Trigger::activateTarget()
{
	switch (targetType)
	{
		case T_TERMINAL:
		{
			Terminal* t = (Terminal*)target;
			// Activate Target
			break;
		}
		case T_SWITCH:
		{
			Switch* s = (Switch*)target;
			// Activate Target
			break;
		}
		default:
		{
			break;
		}
	}
}

bool Trigger::tryToTrigger(Terminal* input)
{
	// If this trigger is not a terminal, return false
	if (triggerType != T_TERMINAL) return false;

	Terminal* t = (Terminal*)trigger;

	// If this trigger is not the right terminal, return false
	if (t != input) return false;

	activateTarget();

	return true;
}

bool Trigger::tryToTrigger(Switch* input)
{
	// If this trigger is not a switch, return false
	if (triggerType != T_SWITCH) return false;

	Switch* s = (Switch*)trigger;

	// If this trigger is not the correct switch, return false
	if (s != input) return false;

	activateTarget();

	return true;
}

Trigger::Trigger()
{
	trigger = NULL;
	target = NULL;
	triggerType = NULL;
	targetType = T_NULL;
}

