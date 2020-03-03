// Copyright 2018 Sabre Dart Studios

#include "OWSBasicAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayTagContainer.h"
#include "GameplayEffect.h"
#include "GameplayTagsModule.h"
#include "GameplayEffectExtension.h"


UOWSBasicAttributeSet::UOWSBasicAttributeSet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool UOWSBasicAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData &Data)
{
	static UProperty *HealthProperty = FindFieldChecked<UProperty>(UOWSBasicAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UOWSBasicAttributeSet, Health));
	static UProperty *DamageProperty = FindFieldChecked<UProperty>(UOWSBasicAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UOWSBasicAttributeSet, Damage));

	return true;
}

void UOWSBasicAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	static UProperty* DamageProperty = FindFieldChecked<UProperty>(UOWSBasicAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UOWSBasicAttributeSet, Damage));
	static UProperty* HealingProperty = FindFieldChecked<UProperty>(UOWSBasicAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UOWSBasicAttributeSet, Healing));

	UProperty* ModifiedProperty = Data.EvaluatedData.Attribute.GetUProperty();


	// What property was modified?
	if (DamageProperty == ModifiedProperty)
	{
		// Treat damage as minus health
		Health -= Damage;
		Health = FMath::Clamp(Health, 0.f, MaxHealth);
		Damage = 0.f;
	}

	if (HealingProperty == ModifiedProperty)
	{
		Health += Healing;
		Health = FMath::Clamp(Health, 0.f, MaxHealth);
		Damage = 0.f;
	}
}


void UOWSBasicAttributeSet::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UOWSBasicAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOWSBasicAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOWSBasicAttributeSet, HealthRegenRate, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UOWSBasicAttributeSet, NaturalArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOWSBasicAttributeSet, PhysicalArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOWSBasicAttributeSet, BonusArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOWSBasicAttributeSet, ForceArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOWSBasicAttributeSet, MagicArmor, COND_None, REPNOTIFY_Always);
}