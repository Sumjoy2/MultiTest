// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MTPlayer.generated.h"

struct FInputActionValue;
class UCapsuleComponent;
class UStaticMeshComponent;
class UCameraComponent;

class UInputMappingContext;
class UInputAction;

UCLASS()
class MULTITEST_API AMTPlayer : public AActor
{
	GENERATED_BODY()
// Components
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCapsuleComponent> CollisionCapsule;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> Camera;
	
// Inputs
protected:
	// Default input mapping context
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UInputMappingContext> DefaultPlayerMapping;
	
	// Horizontal movement input action
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> MovementInput;
	// Interaction input action
	// TODO: use an interface for this
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InteractInput;
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = true))
	FVector Position;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = true))
	float MovementMult;
	
public:
	// Sets default values for this actor's properties
	AMTPlayer();
	
	// Setup the enhanced input system
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Movement)
	void Move(const FInputActionValue& Value);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
