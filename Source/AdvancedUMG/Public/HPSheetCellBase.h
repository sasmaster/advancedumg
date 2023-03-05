// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPDataStructures.h"
#include "HPSheetCellBase.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDUMG_API UHPSheetCellBase : public UUserWidget
{
	GENERATED_BODY()

public:

	EUVPActorType actorType;
	EUVPDynamicPropType propType;
	FString  propName;// this is shader param for materials and actor prop name for actor props
	FString  CellDataKey; // concat of column name (from the header) and row number

	

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	 	class UEditableTextBox* EditableText = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = HPSheetCellBase)
		class AActor* actorPtr = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = HPSheetCellBase)
		class UUserWidget* ParentRow = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = HPSheetCellBase)
		class UHPDataSheetBase* ParentSheet = nullptr;

	
};
