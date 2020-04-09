// Copyright © 2020 Jack C. Lloyd.

#pragma once

#pragma region INCLUDES

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "CI536GameModeBase.generated.h"

#pragma endregion

#pragma region CLASSES

/**
 * Game Mode Base.
 */
UCLASS()
class CI536_API ACI536GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
  virtual void BeginPlay() override;

public:
  /* The number of players (i.e., non-artificial intelligence). */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
  int PlayerControllerCount = -1;

  /* The array of player controllers (i.e., non-artificial intelligence). */
  UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
  TArray<APlayerController*> PlayerControllers;

  /* The array of player materials (i.e., red, green, blue, and yellow). */
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
  TArray<UMaterialInterface*> PlayerMaterials;
};

#pragma endregion