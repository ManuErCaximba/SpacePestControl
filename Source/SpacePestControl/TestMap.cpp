// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMap.h"

// Sets default values
ATestMap::ATestMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	// Creamos el mesh del mapa y lo hago el componente principal de la clase
	MapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MapMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MapMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));
	RootComponent = MapMesh;

	// Cargamos el material que usara el mesh
	UMaterial* MapMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/Assets/Materials/M_TestMap"));

	//Creamos cuatro paredes invisibles para que el personaje no salga del mapa
	IWTop = CreateDefaultSubobject<UBoxComponent>(TEXT("IWTop"));
	IWRight = CreateDefaultSubobject<UBoxComponent>(TEXT("IWRight"));
	IWLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("IWLeft"));
	IWBottom = CreateDefaultSubobject<UBoxComponent>(TEXT("IWBottom"));

	IWTop->SetupAttachment(RootComponent);
	IWBottom->SetupAttachment(RootComponent);
	IWLeft->SetupAttachment(RootComponent);
	IWRight->SetupAttachment(RootComponent);

	IWTop->BodyInstance.SetCollisionProfileName("BlockAll");
	IWBottom->BodyInstance.SetCollisionProfileName("BlockAll");
	IWLeft->BodyInstance.SetCollisionProfileName("BlockAll");
	IWRight->BodyInstance.SetCollisionProfileName("BlockAll");

	IWTop->SetMobility(EComponentMobility::Static);
	IWBottom->SetMobility(EComponentMobility::Static);
	IWLeft->SetMobility(EComponentMobility::Static);
	IWRight->SetMobility(EComponentMobility::Static);

	IWTop->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	IWBottom->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	IWLeft->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	IWRight->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));

	// Creamos valores por defecto para el mesh para que mantenga la proporcion por pixeles
	FTransform MeshTransform = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector(0.0f, 0.5f, 0.0f),
		FVector(1.92f, 1.87f, 1.0f)
	);

	MapMesh->SetMobility(EComponentMobility::Static);
	MapMesh->SetWorldTransform(MeshTransform);

	// Creamos valores por defecto para el mesh para que mantenga la proporcion por pixeles
	FTransform IWTopTransform = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector(0.0f, -33.957218f, 15.0f),
		FVector((1 / 1.92f) * 92.0f, (1 / 1.87f) * 1.0f, 15.0f)
	);

	FTransform IWBottomTransform = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector(0.0f, 47.326202f, 15.0f),
		FVector((1 / 1.92f) * 92.0f, (1 / 1.87f) * 1.0f, 15.0f)
	);

	FTransform IWLeftTransform = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector(-47.395832f, 6.684492f, 15.0f),
		FVector((1 / 1.92f) * 1.0f, (1 / 1.87f) * 75.0f, 15.0f)
	);

	FTransform IWRightTransform = FTransform
	(
		FQuat(0.0f, 0.0f, 0.0f, 0.0f),
		FVector(47.395832f, 6.684492f, 15.0f),
		FVector((1 / 1.92f) * 1.0f, (1 / 1.87f) * 75.0f, 15.0f)
	);

	IWTop->SetRelativeTransform(IWTopTransform);
	IWBottom->SetRelativeTransform(IWBottomTransform);
	IWLeft->SetRelativeTransform(IWLeftTransform);
	IWRight->SetRelativeTransform(IWRightTransform);

	// Colocamos el mesh, el material y los valores por defecto al componente principal de la clase
	if (MapMeshAsset.Succeeded())
	{
		MapMesh->SetStaticMesh(MapMeshAsset.Object);
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
