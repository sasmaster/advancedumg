// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPSheetRowBase.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDUMG_API UHPSheetRowBase : public UUserWidget
{
	GENERATED_BODY()

		FString mRowKey; // concat of column name (from the header) and row number
public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int32 RowIndex = 0;
};
