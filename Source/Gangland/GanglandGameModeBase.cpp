// Fill out your copyright notice in the Description page of Project Settings.

#include "GanglandGameModeBase.h"
#include "Player/GanglandBaseCharacter.h"
#include "Player/GanglandPlayerController.h"

AGanglandGameModeBase::AGanglandGameModeBase()
{
	DefaultPawnClass = AGanglandBaseCharacter::StaticClass();
	PlayerControllerClass = AGanglandPlayerController::StaticClass();
}
