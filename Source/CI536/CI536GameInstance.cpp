// Copyright © 2020 Jack C. Lloyd.

#include "CI536GameInstance.h"

int UCI536GameInstance::SetPlayerControllerCount(int Count)
{
  /* A minimum of 1 and a maximum of 4 players, respectively. */
  return PlayerControllerCount = Count < 1 ? 1 : Count > 4 ? 4 : Count;;
}