// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "HPSuperButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftButtonDoubleClickedEvent);

 
/**
 * 
 */
UCLASS()
class ADVANCEDUMG_API UHPSuperButton : public UButton
{
	GENERATED_UCLASS_BODY()


private:
	double mStartClickTime = 0.0f;//in ms
	

public:

	void PostLoad() override;

	UFUNCTION()
		void OnLeftDoubleMouseClick();

	UPROPERTY(BlueprintAssignable, Category = "CellButton|Event")
		FOnLeftButtonDoubleClickedEvent OnLeftMouseDoubleClicked;
	
};
