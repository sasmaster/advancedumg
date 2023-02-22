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

	
public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int32 RowIndex = 0;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		class UDynamicEntryBox* rowDataBox = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = HPSheetRow)
		class UHPDataSheetBase* ParentSheet = nullptr;
};
