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

	// widgets created in the editor and bound
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		class UVerticalBox* SheetBox = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	    class UDynamicEntryBox* SheetheaderBox = nullptr;

	UHPDataSheetBase(const FObjectInitializer& ObjectInitializer);

	bool Initialize()override final;

	 UPROPERTY(EditAnywhere, Category = HPDataSheetBase)
	 TSubclassOf<UUserWidget> RowEditorWidgetClass;

	 UFUNCTION(BlueprintCallable, Category = HPDataSheetBase)
	 void ShowRowEditor(bool val);

	 UFUNCTION(BlueprintCallable, Category = HPDataSheetBase)
		 void AddRow(int32 rowIndex);

	 UFUNCTION(BlueprintCallable, Category = HPDataSheetBase)
		 void DeleteRow(int32 rowIndex);

	 UFUNCTION(BlueprintPure, Category = HPDataSheetBase)
		 UUserWidget* GetRowEditor()
	 {
		 return RowEditor;
	 }
	
};
