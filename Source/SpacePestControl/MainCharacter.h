// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include "Components/InputComponent.h"
#include "Engine/BlockingVolume.h"
#include "Containers/UnrealString.h"
#include "HitBox.h"
#include "PaperFlipbookComponent.h"
#include "MainCharacter.generated.h"

UCLASS()
class SPACEPESTCONTROL_API AMainCharacter : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	AMainCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);

	//Input variables
	FVector CurrentVelocity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Attributes
	UPROPERTY(EditAnywhere)
	UCameraComponent* CharacterCamera;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MapMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;
};
