// Fill out your copyright notice in the Description page of Project Settings.


#include "HPDataSheetBase.h"
#include "Components/VerticalBox.h"
#include "Components/DynamicEntryBox.h"
#include "HPSheetRowBase.h"


UHPDataSheetBase::UHPDataSheetBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//PersonalizeConfigBut->OnClicked.AddDynamic(this, &UUVPMainScreenUIWidgetBase::OnPersonalizeConfigButClick);
}

void UHPDataSheetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (RowEditorWidgetClass.Get())
	{
		RowEditor = CreateWidget<UUserWidget>(GetOwningPlayer(), RowEditorWidgetClass);
		check(RowEditor);
		RowEditor->AddToViewport(100);
		RowEditor->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No entry for RowEditorWidgetClass in DataSheet properties!"));
	}

	 
	this->OnVisibilityChanged.AddDynamic(this, &UHPDataSheetBase::OnDataSheetVisibilityChanged);
}

void UHPDataSheetBase::OnDataSheetVisibilityChanged(ESlateVisibility v)
{
 
		if (v == ESlateVisibility::Collapsed || v == ESlateVisibility::Hidden)
		{
			ShowRowEditor(false);
		}
}

bool UHPDataSheetBase::Initialize() 
{
	Super::Initialize();

	return true;
}



void UHPDataSheetBase::ShowRowEditor(bool val)
{
	if (RowEditor)
	{
		 
		RowEditor->SetVisibility(val?ESlateVisibility::Visible:ESlateVisibility::Collapsed);
		if (val)
		{
			FVector2D mousePos;
			GetOwningPlayer()->GetMousePosition(mousePos.X, mousePos.Y);
			RowEditor->SetPositionInViewport(mousePos, false);
		}
	
	}
}

void UHPDataSheetBase::AddRow(int32 rowIndex)
{

	//SheetBox->InsertChildAt(rowIndex,nullptr);//this shit doesn't update the UI so it is better to regenerate

	//SheetheaderBox->Insert
	const auto allRows = SheetBox->GetAllChildren();
	for (int32 i = 0; i < allRows.Num(); ++i)
	{
		auto sheetRow = Cast<UHPSheetRowBase>(allRows[i]);
		sheetRow->RowIndex = i;
	}
}

void UHPDataSheetBase::DeleteRow(int32 rowIndex)
{
	
	SheetBox->RemoveChildAt(rowIndex);
	const auto allRows = SheetBox->GetAllChildren();
	for (int32 i = 0;i < allRows.Num();++i)
	{
		auto sheetRow = Cast<UHPSheetRowBase>(allRows[i]);
		sheetRow->RowIndex = i;
	}
}

