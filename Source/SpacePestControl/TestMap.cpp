// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMap.h"

// Sets default values
ATestMap::ATestMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MapMesh"));
	MapMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MapMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));
	//static ConstructorHelpers::FObjectFinder<UMaterial> MaterialMeshAsset(TEXT("/Game/StarterContent/Materials/M_Basic_Wall.M_Basic_Wall"));

	UMaterial* MapMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/StarterContent/Materials/M_Concrete_Tiles"));
	//static ConstructorHelpers::FObjectFinder<UTexture> MapTextureAsset(TEXT("/Game/Assets/Level/TestMap.TestMap"));

	if (MapMeshAsset.Succeeded())
	{
		MapMesh->SetStaticMesh(MapMeshAsset.Object);
		//MapMaterial->SetTextureParameterValueEditorOnly(TEXT("MapTexture"), MapTextureAsset.Object);
		MapMesh->SetMaterial(0, MapMaterial);
	}
}

// Called when the game starts or when spawned
void ATestMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

