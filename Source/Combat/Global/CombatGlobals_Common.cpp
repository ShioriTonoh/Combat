// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/CombatGlobals_Common.h"

FCombatGameplayEffectContext* UCombatGlobals_Ability::AllocGameplayEffectContext() const
{
	return new FCombatGameplayEffectContext();
}
