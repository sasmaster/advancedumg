// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPDataStructures.h"
#include "HPSheetRowBase.h"
#include "HPSheetRowEditorBase.h"
#include "HPDataSheetBase.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDUMG_API UHPDataSheetBase : public UUserWidget
{
	GENERATED_BODY()

		UPROPERTY()
		UHPSheetRowEditorBase* RowEditor = nullptr;
 
protected:

	void NativeConstruct() override final;

	//callback
	UFUNCTION()
	 void OnDataSheetVisibilityChanged(ESlateVisibility v);

	//callback
	UFUNCTION()
		void OnAddRowButtonClicked();

	//callback
	UFUNCTION()
		void OnRemoveRowButtonClicked();

	 void GeneateDataSheetA(const UVPDynamicActorData* actorData);

public:

	UHPDataSheetBase(const FObjectInitializer& ObjectInitializer);

	bool Initialize()override final;

	// widgets created in the editor and bound
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		class UVerticalBox* SheetBox = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
		class UDynamicEntryBox* SheetheaderBox = nullptr;


	/**
	* Must be set via editor
	*/
	 UPROPERTY(EditAnywhere, Category = HPDataSheetBase)
	 TSubclassOf<UHPSheetRowEditorBase> RowEditorWidgetClass;

	/**
	* Must be set via editor
	*/
	 UPROPERTY(EditAnywhere, Category = HPDataSheetBase)
		 TSubclassOf<UHPSheetRowBase> SheetRowWidgetClass;

	 /**
	 * Must be set via editor
	 */
	 UPROPERTY(EditAnywhere, Category = HPDataSheetBase)
		 TSubclassOf<UUserWidget> SheetCellWidgetClass;

	 UFUNCTION(BlueprintCallable, Category = HPDataSheetBase)
	 void ShowRowEditor(bool val);

	 UFUNCTION(BlueprintCallable, Category = HPDataSheetBase)
		 void AddRow(int32 rowIndex);

	 UFUNCTION(BlueprintCallable, Category = HPDataSheetBase)
		 void DeleteRow(int32 rowIndex);

	 UFUNCTION(BlueprintCallable, Category = HPDataSheetBase)
	 void GenerateDataSheetFromCSV(UPARAM(ref) const FString& csvPath);

	 UFUNCTION(BlueprintCallable, Category = HPDataSheetBase)
	 void GenerateDataSheetForActor(UPARAM(ref) const FString& actorId);

	 UFUNCTION(BlueprintCallable, Category = HPDataSheetBase)
		 void GenerateDataMapFromSheet(UPARAM(ref) const FString& filePath);

	 UFUNCTION(BlueprintCallable, Category = HPDataSheetBase)
		 void SetHeaderColor(FLinearColor color);



	 UFUNCTION(BlueprintPure, Category = HPDataSheetBase)
		 UUserWidget* GetRowEditor()
	 {
		 return RowEditor;
	 }
	
};
