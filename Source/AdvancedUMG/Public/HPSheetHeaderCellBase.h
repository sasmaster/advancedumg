// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPSheetHeaderCellBase.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDUMG_API UHPSheetHeaderCellBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		class UTextBlock* ButtonText = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		class UButton* But = nullptr;
	    


};
