// Copyright © 2020 Jack C. Lloyd.

#include "CI536Pad.h"

#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

#define CARDINALS 4

ACI536Pad::ACI536Pad()
{
 	PrimaryActorTick.bCanEverTick = false;

	/* Static Mesh */
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetMobility(EComponentMobility::Static);

	RootComponent = StaticMesh;

	/* North Arrow (Red). */
	NorthArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("North Arrow"));
	NorthArrow->SetMobility(EComponentMobility::Static);
	NorthArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NorthArrow->SetArrowColor(FLinearColor::Red);
	NorthArrow->SetHiddenInGame(false);

	/* East Arrow (Green). */
	EastArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("East Arrow"));
	NorthArrow->SetMobility(EComponentMobility::Static);
	EastArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	EastArrow->SetArrowColor(FLinearColor::Green);
	EastArrow->SetHiddenInGame(false);
	
	/* South Arrow (Blue). */
	SouthArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("South Arrow"));
	NorthArrow->SetMobility(EComponentMobility::Static);
	SouthArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SouthArrow->SetArrowColor(FLinearColor::Blue);
	SouthArrow->SetHiddenInGame(false);

	/* West Arrow (Yellow). */
	WestArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("West Arrow"));
	NorthArrow->SetMobility(EComponentMobility::Static);
	WestArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	WestArrow->SetArrowColor(FLinearColor::Yellow);
	WestArrow->SetHiddenInGame(false);
}

void ACI536Pad::BeginPlay()
{
	Super::BeginPlay();
}

void ACI536Pad::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	/* The cardinal directions North, East, South, and West (Pad). */
	ACI536Pad** pads[CARDINALS] = { &NorthPad, &EastPad, &SouthPad, &WestPad };

	/* Disallow references to self! */
	for (int i = 0; i < CARDINALS; i++)
	{
		if ((*pads[i]) == this)
		{
			(*pads[i]) = nullptr;
		}
	}

	/* Disallow duplicate references! */
	for (int i = 0; i < CARDINALS - 1; i++)
	{
		for (int j = i + 1; j < CARDINALS; j++)
		{
			if ((*pads[i]) == *pads[j])
			{
				(*pads[j]) = nullptr;
			}
		}
	}

	/* The cardinal directions North, East, South, and West (Arrow). */
	UArrowComponent** arrows[CARDINALS] = { &NorthArrow, &EastArrow, &SouthArrow, &WestArrow };

	/* Set the rotation and/or visibility of the arrows. */
	for (int i = 0; i < CARDINALS; i++)
	{
		if (*pads[i] != nullptr)
		{
			(*arrows[i])->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation
				(
					(*arrows[i])->GetComponentLocation(),
					(*pads[i])->GetActorLocation())
				);
			(*arrows[i])->SetVisibility(true);
		}
		else
		{
			(*arrows[i])->SetVisibility(false);
		}
	}
}

void ACI536Pad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACI536Pad::Lock()
{
	bIsLocked = true;
}

void ACI536Pad::Unlock()
{
	bIsLocked = false;
}

bool ACI536Pad::IsLocked() const
{
	return bIsLocked;
}