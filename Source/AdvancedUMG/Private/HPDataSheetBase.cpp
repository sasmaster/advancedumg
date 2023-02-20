// Fill out your copyright notice in the Description page of Project Settings.


#include "HPDataSheetBase.h"

#include "HPSheetHeaderCellBase.h"
#include "Components/VerticalBox.h"
#include "Components/DynamicEntryBox.h"
#include "Components/TextBlock.h"



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

void UHPDataSheetBase::GeneateDataSheetFromCSV(const FString& csvPath)
{

	//TODO:
}

void UHPDataSheetBase::GeneateDataSheetForActor(const FString& actorId)
{
	TMap<FString, UVPDynamicActorData> demoData;//this is how the pers map looks in Personalizer.h

	UVPDynamicActorData entry = {};
	entry.actor = nullptr; //must be populated in real world scenario
	entry.actorType = EUVPActorType::StaticMesh;

	//add unique prop fpr StaticMesh:
	entry.actorProps.Add("gltf_file", { "coke.gltf" });

	//add some mat props:

	{//color param
		UVMaterialPropValue matVal = {};
		matVal.shaderType = EUVPShaderParamType::Vector;
		FColor color(255, 255, 0, 255);
		matVal.cparam = color.ToPackedRGBA(); //will have to pack vector to integer
		entry.materialParams.Add("baseColor", matVal);
	}

	{//texture param
		UVMaterialPropValue matVal = {};
		matVal.shaderType = EUVPShaderParamType::Sampler;
		matVal.sval = "textures/albedo.png";
		entry.materialParams.Add("colorMap", matVal);
	}
	
	demoData.Add("ActorA", entry);

	GeneateDataSheetA(demoData.Find(actorId));
}

void UHPDataSheetBase::GeneateDataSheetA(const UVPDynamicActorData* actorData)
{
	if (actorData == nullptr)
	{
		return;
	}

	// geneate header entries first:

	SheetheaderBox->Reset(true);
	for (const auto &entry:actorData->actorProps)
	{
	  auto headerCell = Cast<UHPSheetHeaderCellBase>(SheetheaderBox->CreateEntry());
	  check(headerCell);
	  headerCell->ButtonText->SetText(FText::FromString(entry.Key));

	}

	for (const auto& entry : actorData->materialParams)
	{
		auto headerCell = Cast<UHPSheetHeaderCellBase>(SheetheaderBox->CreateEntry());
		check(headerCell);
		headerCell->ButtonText->SetText(FText::FromName(entry.Key));

	}

	//generate sheet rows:

	SheetBox->ClearChildren();

	//here we must generate a unique key per row/colum and store it in each row so that when exporting the table
	//to map we can retrience those
	//initial setup is just one row, need to see

	auto rowWidget =Cast<UHPSheetRowBase>(CreateWidget(this, SheetRowWidgetClass));

	SheetBox->AddChild(rowWidget);
	 
	for (const auto& entry : actorData->actorProps)
	{
		auto cell = rowWidget->rowDataBox->CreateEntry();
	
	}

	for (const auto& entry : actorData->materialParams)
	{
	 
		auto cell = rowWidget->rowDataBox->CreateEntry();

	}

}

