// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARPGProjectileAbility.h"

#include "Combat/ARPGCombatComponent.h"
#include "Combat/ARPGProjectile.h"
#include "Kismet/KismetSystemLibrary.h"

void UARPGProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
		
}

void UARPGProjectileAbility::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)
		return;

	UARPGCombatComponent* CombatComponent = GetAvatarActorFromActorInfo()->GetComponentByClass<UARPGCombatComponent>();
	if (CombatComponent)
	{
		const FVector SocketLocation = CombatComponent->GetWeaponSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		AARPGProjectile* Projectile = GetWorld()->SpawnActorDeferred<AARPGProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->FinishSpawning(SpawnTransform);
	}
	
}
