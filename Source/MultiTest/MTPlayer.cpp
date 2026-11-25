// Fill out your copyright notice in the Description page of Project Settings.


#include "MTPlayer.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
AMTPlayer::AMTPlayer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Component"));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

void AMTPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementInput, ETriggerEvent::Triggered, this, &AMTPlayer::Move);
	}
}

// Called when the game starts or when spawned
void AMTPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	Position = GetActorLocation();
}

void AMTPlayer::Move(const FInputActionValue& Value)
{
	FVector MoveAmt = Value.Get<FVector>();
	
	FVector NewPos = Position + (MoveAmt * MovementMult) * GetWorld()->GetDeltaSeconds();
	SetActorLocation(NewPos);
	Position = NewPos;
}

// Called every frame
void AMTPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}