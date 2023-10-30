// Fill out your copyright notice in the Description page of Project Settings.

#include "GGGameModeBase.h"

#include "GGGameHUD.h"
#include "Player/GGBaseCharacter.h"
#include "Player/GGPlayerController.h"

AGGGameModeBase::AGGGameModeBase()
{
	DefaultPawnClass = AGGBaseCharacter::StaticClass();
	PlayerControllerClass = AGGPlayerController::StaticClass();
	HUDClass = AGGGameHUD::StaticClass();
}
