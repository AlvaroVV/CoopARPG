// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/ARPGProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "CoopARPG/CoopARPG.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AARPGProjectile::AARPGProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComp);
	SphereComp->SetCollisionObjectType(ECC_Projectile);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->InitialSpeed = 550.f;
	ProjectileMovementComp->MaxSpeed = 550.f;
	ProjectileMovementComp->ProjectileGravityScale = 0.f;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void AARPGProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
		SetLifeSpan(ProjectileDuration);
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARPGProjectile::OnSphereOverlap);
	TrailSoundComp = UGameplayStatics::SpawnSoundAttached(TrailSound, GetRootComponent());
	
}

void AARPGProjectile::Destroyed()
{
	//Server could destroy the Projectile before clients impact
	if (!bHit)// && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		if (TrailSoundComp)
			TrailSoundComp->Stop();
	}
	
	Super::Destroyed();
}

void AARPGProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	TrailSoundComp->Stop();

	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*GE_OnCollision_SpecHandle.Data.Get());
		}
		Destroy();
	}
	else
	{
		bHit = true;
	}
	
}


