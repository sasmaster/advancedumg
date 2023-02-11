// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPDataSheetBase.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDUMG_API UHPDataSheetBase : public UUserWidget
{
	GENERATED_BODY()

		UPROPERTY()
		UUserWidget* RowEditor = nullptr;

protected:

	void NativeConstruct() override final;

	UFUNCTION()
		void OnDataSheetVisibilityChanged(ESlateVisibility v);
public:

	UHPDataSheetBase(const FObjectInitializer& ObjectInitializer);

	bool Initialize()override final;

	 UPROPERTY(EditAnywhere, Category = HPDataSheetBase)
	 TSubclassOf<UUserWidget> RowEditorWidgetClass;

	 UFUNCTION(BlueprintCallable, Category = HPDataSheetBase)
	 void ShowRowEditor(bool val);

	 UFUNCTION(BlueprintPure, Category = HPDataSheetBase)
		 UUserWidget* GetRowEditor()
	 {
		 return RowEditor;
	 }
	
};
