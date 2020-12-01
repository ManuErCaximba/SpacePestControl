// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TestMap.generated.h"

UCLASS()
class SPACEPESTCONTROL_API ATestMap : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ATestMap();


	UPROPERTY(EditAnywhere)
	UBoxComponent* IWRight;

	UPROPERTY(EditAnywhere)
	UBoxComponent* IWLeft;

	UPROPERTY(EditAnywhere)
	UBoxComponent* IWBottom;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
