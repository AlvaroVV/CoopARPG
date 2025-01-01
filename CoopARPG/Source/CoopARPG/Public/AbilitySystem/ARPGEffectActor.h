// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGEffectActor.generated.h"

class UGameplayEffect;
class USphereComponent;
class UStaticMeshComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy: uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	ApplyOnBoth,
	DoNotApply
};

UCLASS()
class COOPARPG_API AARPGEffectActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AARPGEffectActor();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category = "Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffect);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	EEffectApplicationPolicy ApplicationPolicy;
};
