// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPSheetRowEditorBase.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDUMG_API UHPSheetRowEditorBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		class UButton* AddRowButt = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		class UButton* RemoveRowButt = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = HPSheetRowEditorBase)
		int32 ClickedRow = -1;
};
