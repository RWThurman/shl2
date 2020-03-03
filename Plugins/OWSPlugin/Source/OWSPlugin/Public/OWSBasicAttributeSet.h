// Copyright 2018 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UObject/ObjectMacros.h"
#include "AbilitySystemComponent.h"
#include "OWSBasicAttributeSet.generated.h"


/**
 * 
 */
UCLASS()
class OWSPLUGIN_API UOWSBasicAttributeSet : public UAttributeSet
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth, Category = "RPGAttributes")//, meta = (HideFromModifiers))			// You can't make a GameplayEffect modify Health Directly (go through)
		mutable float	MaxHealth;
	UFUNCTION()
		void OnRep_MaxHealth()
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UOWSBasicAttributeSet, MaxHealth);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "RPGAttributes", meta = (HideFromModifiers))
		mutable float	Health;
	UFUNCTION()
		void OnRep_Health() { GAMEPLAYATTRIBUTE_REPNOTIFY(UOWSBasicAttributeSet, Health); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_HealthRegenRate, Category = "RPGAttributes")
		mutable float HealthRegenRate;
	UFUNCTION()
		void OnRep_HealthRegenRate() { GAMEPLAYATTRIBUTE_REPNOTIFY(UOWSBasicAttributeSet, HealthRegenRate); }
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_NaturalArmor, Category = "RPGAttributes")
		mutable float NaturalArmor;
	UFUNCTION()
		void OnRep_NaturalArmor() { GAMEPLAYATTRIBUTE_REPNOTIFY(UOWSBasicAttributeSet, NaturalArmor); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_PhysicalArmor, Category = "RPGAttributes")
		mutable float PhysicalArmor;
	UFUNCTION()
		void OnRep_PhysicalArmor() { GAMEPLAYATTRIBUTE_REPNOTIFY(UOWSBasicAttributeSet, PhysicalArmor); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_BonusArmor, Category = "RPGAttributes")
		mutable float BonusArmor;
	UFUNCTION()
		void OnRep_BonusArmor() { GAMEPLAYATTRIBUTE_REPNOTIFY(UOWSBasicAttributeSet, BonusArmor); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ForceArmor, Category = "RPGAttributes")
		mutable float ForceArmor;
	UFUNCTION()
		void OnRep_ForceArmor() { GAMEPLAYATTRIBUTE_REPNOTIFY(UOWSBasicAttributeSet, ForceArmor); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MagicArmor, Category = "RPGAttributes")
		mutable float MagicArmor;
	UFUNCTION()
		void OnRep_MagicArmor() { GAMEPLAYATTRIBUTE_REPNOTIFY(UOWSBasicAttributeSet, MagicArmor); }
	
	/** This Damage is just used for applying negative health mods. Its not a 'persistent' attribute. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest", meta = (HideFromLevelInfos))		// You can't make a GameplayEffect 'powered' by Damage (Its transient)
		mutable float	Damage;

	/** This Healing is just used for applying positive health mods. Its not a 'persistent' attribute. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest", meta = (HideFromLevelInfos))		// You can't make a GameplayEffect 'powered' by Healing (Its transient)
		mutable float	Healing;

	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData &Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
};
