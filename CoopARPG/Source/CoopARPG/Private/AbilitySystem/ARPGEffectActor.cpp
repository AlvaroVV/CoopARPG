// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ARPGEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "Components/SphereComponent.h"
#include "Misc/MapErrors.h"


// Sets default values
AARPGEffectActor::AARPGEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComp);
	
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComp->SetupAttachment(GetRootComponent());
}


// Called when the game starts or when spawned
void AARPGEffectActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARPGEffectActor::OnOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AARPGEffectActor::OnEndOverlap);
}

void AARPGEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//TODO: Change this to apply a GE. Using const_cast as a hack.
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);
	if (ASCInterface)
	{
		const UARPGAttributeSet* AttSet = Cast<UARPGAttributeSet> (ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UARPGAttributeSet::StaticClass()));
		UARPGAttributeSet* MutableAttSet = const_cast<UARPGAttributeSet*>(AttSet);
		MutableAttSet->SetHealth(AttSet->GetHealth() + 25.0f);
		MutableAttSet->SetMana(AttSet->GetMana() - 5.0f);
		SetLifeSpan(0.1);
	}
}

void AARPGEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
