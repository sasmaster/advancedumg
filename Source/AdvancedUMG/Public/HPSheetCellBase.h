// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPSheetCellBase.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDUMG_API UHPSheetCellBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	 	class UEditableTextBox* EditableText = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = HPSheetCellBase)
		class UUserWidget* ParentRow = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = HPSheetCellBase)
		class UHPDataSheetBase* ParentSheet = nullptr;

	
};
