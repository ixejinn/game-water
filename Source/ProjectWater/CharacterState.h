// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaterGameInstance.h"
#include <chrono>
#include "CharacterState.generated.h"

class AProjectWaterCharacter;
class UCharacterMovementComponent;

UENUM(BlueprintType)
enum class EState : uint8
{
	STATE_None	UMETA(Hidden),
	STATE_Human	UMETA(DisplayName = "Human"),
	STATE_Water	UMETA(DisplayName = "Water"),
	STATE_Vapor UMETA(DisplayName = "Vapor"),
	STATE_Ice	UMETA(DisplayName = "Ice"),
	STATE_Max	UMETA(Hidden)
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType )
class PROJECTWATER_API UCharacterState : public UActorComponent
{
	GENERATED_BODY()

	TObjectPtr<AProjectWaterCharacter> Owner;
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter = GetCharacterStateChanged, BlueprintSetter = SetCharacterStateChanged)
	bool isCharacterStateChanged;

	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter = GetState, BlueprintSetter = SetState)
	EState State;

	bool LockedState[3];

	float MaxEnergy;
	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter = GetEnergy)
	float Energy;
	/*const */float EnergyRecovery, EnergyUsage;

	const std::chrono::duration<long, std::milli> EnergyCheckInterval;
	std::chrono::system_clock::time_point EnergyTimerStart;

	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter = GetExhausted)
	bool bExhausted;

public:	
	// Sets default values for this component's properties
	UCharacterState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintGetter)
	EState GetState() const { return State; }
	UFUNCTION(BlueprintSetter)
	void SetState(EState newState);

	UFUNCTION(BlueprintGetter)
	bool GetCharacterStateChanged() const { return isCharacterStateChanged; }
	UFUNCTION(BlueprintSetter)
	void SetCharacterStateChanged(bool changed) { isCharacterStateChanged = changed; }

	UFUNCTION(BlueprintCallable)
	void UnlockState(EState unlock);

	UFUNCTION(BlueprintCallable)
	bool GetLockedState(EState unlock);
	bool GetLockedState(int i) const;

	UFUNCTION(BlueprintGetter)
	float GetEnergy() const { return Energy; }

	UFUNCTION(BlueprintCallable)
	void SetEnergy(float v) { Energy = v; }

	UFUNCTION(BlueprintGetter)
	bool GetExhausted() const { return bExhausted; }

public:
	//GameInstance
	UFUNCTION(BlueprintCallable)
	void LoadStates();
};
