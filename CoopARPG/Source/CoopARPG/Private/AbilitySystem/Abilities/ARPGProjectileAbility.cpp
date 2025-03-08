// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARPGProjectileAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Combat/ARPGCombatComponent.h"
#include "Combat/ARPGProjectile.h"
#include "Kismet/KismetSystemLibrary.h"

void UARPGProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
		
}

void UARPGProjectileAbility::SpawnProjectile(const FVector& ProjectileTargetPoint)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)
		return;

	UARPGCombatComponent* CombatComponent = GetAvatarActorFromActorInfo()->GetComponentByClass<UARPGCombatComponent>();
	if (CombatComponent)
	{
		const FVector SocketLocation = CombatComponent->GetWeaponSocketLocation();
		FRotator Rotation = (ProjectileTargetPoint - SocketLocation).Rotation();
		Rotation.Pitch = 0.0f;

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		AARPGProjectile* Projectile = GetWorld()->SpawnActorDeferred<AARPGProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(GameplayEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
		Projectile->GE_OnCollision_SpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
	
}
