// Copyright © 2020 Jack C. Lloyd.

#include "CI536GameModeBase.h"
#include "CI536GameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

#define MAX_PLAYERS 4

void ACI536GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	/* Access the game instance. */
	UCI536GameInstance* GameInstance = Cast<UCI536GameInstance>(GetGameInstance());

	if (IsValid(GameInstance))
	{
		PlayerControllerCount = GameInstance->PlayerControllerCount;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to access game instance!"));
	}

	/* Access the world. */
	UObject* World = Cast<UObject>(GetWorld());

	if (IsValid(World))
	{
		/* Access the initial player controller. */
		APlayerController* PlayerController = UGameplayStatics::GetPlayerControllerFromID(World, 0);

		if (IsValid(PlayerController))
		{
			PlayerControllers.Add(PlayerController);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unable to access the initial player controller!"));
		}

		/* Create the subsequent player controller(s). */
		for (int i = 1; i < PlayerControllerCount; i++)
		{
			PlayerController = UGameplayStatics::CreatePlayer(World, i, true);

			if (IsValid(PlayerController))
			{
				PlayerControllers.Add(PlayerController);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Unable to create the subsequent player controller(s)!"));
			}
		}

		if (PlayerControllers.Num() != PlayerControllerCount)
		{
			UE_LOG(LogTemp, Warning, TEXT("Incorrect number of player controllers!"));
		}

		/* Access the player starts. */
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStarts);

		/* Set the player pawn transform(s). */
		if (PlayerStarts.Num() > 0)
		{
			if (PlayerStarts.Num() == MAX_PLAYERS)
			{
				for (int i = 0; i < PlayerControllerCount; i++)
				{
					PlayerControllers[i]->GetPawn()->SetActorTransform(PlayerStarts[i]->GetTransform());
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Incorrect number of player starts!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unable to access the player starts!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to access the world!"));
	}

	/* Set the player materials. */
	if (PlayerMaterials.Num() > 0)
	{
		if (PlayerMaterials.Num() == MAX_PLAYERS)
		{
			for (int i = 0; i < PlayerControllerCount; i++)
			{
				ACharacter* Character = Cast<ACharacter>(PlayerControllers[i]->GetPawn());

				if (IsValid(Character))
				{
					USkeletalMeshComponent* SkeletalMeshComponent = Character->GetMesh();

					if (IsValid(SkeletalMeshComponent))
					{
						SkeletalMeshComponent->SetMaterial(0, PlayerMaterials[i]);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Unable to access the player mesh!"));
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Unable to access the player materials!"));
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Incorrect number of player controllers!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to access the player materials!"));
	}
}