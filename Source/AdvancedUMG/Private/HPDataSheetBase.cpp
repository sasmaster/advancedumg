// Fill out your copyright notice in the Description page of Project Settings.


#include "HPDataSheetBase.h"

#include "Components/VerticalBox.h"
#include "Components/DynamicEntryBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"

#include "HPSheetHeaderCellBase.h"
#include "HPSheetCellBase.h"



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
		RowEditor = CreateWidget<UHPSheetRowEditorBase>(GetOwningPlayer(), RowEditorWidgetClass);
		check(RowEditor);
		RowEditor->AddToViewport(100);
		RowEditor->SetVisibility(ESlateVisibility::Collapsed);

		RowEditor->AddRowButt->OnClicked.AddDynamic(this, &UHPDataSheetBase::OnAddRowButtonClicked);
		RowEditor->RemoveRowButt->OnClicked.AddDynamic(this, &UHPDataSheetBase::OnRemoveRowButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No entry for RowEditorWidgetClass in DataSheet properties!"));
	}

	 
	this->OnVisibilityChanged.AddDynamic(this, &UHPDataSheetBase::OnDataSheetVisibilityChanged);
}

void UHPDataSheetBase::OnAddRowButtonClicked()
{
	AddRow(RowEditor->ClickedRow);
}

void UHPDataSheetBase::OnRemoveRowButtonClicked()
{
	DeleteRow(RowEditor->ClickedRow);
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

	auto sheetRow = Cast<UHPSheetRowBase>(CreateWidget(this, SheetRowWidgetClass));
	sheetRow->ParentSheet = this;
	//generate cells:
	const auto numCells = SheetheaderBox->GetAllEntries().Num();
	for (int32 i = 0; i < numCells; i++)
	{
		auto cell = Cast<UHPSheetCellBase>(sheetRow->rowDataBox->CreateEntry());
		cell->EditableText->SetText(FText::FromString("---"));
		cell->ParentRow = sheetRow;
		cell->ParentSheet = this;
	}

	//insdrt the row in the index we want in the copyed array
	auto existingRows = SheetBox->GetAllChildren(); // InsertChildAt(rowIndex, rowWidget);
	existingRows.Insert(sheetRow, rowIndex);

	SheetBox->ClearChildren();
	 //put updated array into box and update their indices:
	const int32 numRows = existingRows.Num();
	for (int32 i = 0; i < numRows; i++)
	{
		sheetRow = Cast<UHPSheetRowBase>(existingRows[i]);
		sheetRow->RowIndex = i;
		SheetBox->AddChild(sheetRow);
	}
}

void UHPDataSheetBase::DeleteRow(int32 rowIndex)
{
	
	if (SheetBox->RemoveChildAt(rowIndex))
	{
		const auto allRows = SheetBox->GetAllChildren();
		for (int32 i = 0; i < allRows.Num(); ++i)
		{
			auto sheetRow = Cast<UHPSheetRowBase>(allRows[i]);
			sheetRow->RowIndex = i;
		}
	}
}

void UHPDataSheetBase::GenerateDataSheetFromCSV(const FString& csvPath)
{

	//TODO:
}

void UHPDataSheetBase::GenerateDataSheetForActor(const FString& actorId)
{
	TMap<FString,UVPDynamicActorData> demoData;//this is how the pers map looks in Personalizer.h

	UVPDynamicActorData entry = {};
	entry.actor = nullptr; //must be populated in real world scenario
	entry.actorType = EUVPActorType::StaticMesh;


	entry.props.Emplace();
	UVPDynamicActorData::DynamicPropsMap& propsMap = entry.props[0];
	//add unique prop fpr StaticMesh:

	propsMap.Add("gltf_file",{ EUVPDynamicPropType::ActorProp,EUVPDynamicPropDataType::FilePath, "coke.gltf" });
 
	//add some mat props:

	{//color param
		UVPDynamicPropValue matProp = {};
		matProp.propType = EUVPDynamicPropType::MaterialProp;
		matProp.propDataType = EUVPDynamicPropDataType::Color;
		FColor color(255, 255, 0, 255);
		matProp.uival = color.ToPackedRGBA(); 
		propsMap.Add("baseColor",matProp);
	}

	{//texture param
		UVPDynamicPropValue matProp = {};
		matProp.propType = EUVPDynamicPropType::MaterialProp;
		matProp.propDataType = EUVPDynamicPropDataType::FilePath;
		matProp.sval = "textures/albedo.png";
		propsMap.Add("colorMap",matProp);
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
	for (const auto &entry : actorData->props[0])
	{
	  auto headerCell = Cast<UHPSheetHeaderCellBase>(SheetheaderBox->CreateEntry());
	  check(headerCell);
	  headerCell->ButtonText->SetText(FText::FromString(entry.Key));
	 
	}

	const auto& headerEntries = SheetheaderBox->GetAllEntries();
	//generate sheet rows:

	SheetBox->ClearChildren();

	//generate row per UVPDynamicPropValue in props array
	for (const auto& propsMap : actorData->props)
	{
	 
		auto rowWidget = Cast<UHPSheetRowBase>(CreateWidget(this, SheetRowWidgetClass));
		rowWidget->RowIndex = 0;
		rowWidget->ParentSheet = this;
		SheetBox->AddChild(rowWidget);
		uint32 cellIndexInRow = 0;

		//const auto& propArray = propEntry.Value;

		for (const auto& propEntry : propsMap)
		{
			auto cell = Cast<UHPSheetCellBase>(rowWidget->rowDataBox->CreateEntry());
			const UVPDynamicPropValue& propValue =  propEntry.Value;
			switch (propValue.propDataType)
			{
			case EUVPDynamicPropDataType::FilePath:
				cell->EditableText->SetText(FText::FromString(propValue.sval));
				break;
			case EUVPDynamicPropDataType::Color:

				cell->EditableText->SetText(FText::FromString(FColor(propValue.uival).ToHex()));
				break;
			case EUVPDynamicPropDataType::ScalarFloat:
				cell->EditableText->SetText(FText::FromString(FString::SanitizeFloat(propValue.fval)));
				break;
			case EUVPDynamicPropDataType::ScalarInt:
				cell->EditableText->SetText(FText::FromString(FString::FromInt(propValue.uival)));
				break;
			case EUVPDynamicPropDataType::Vector4:
				cell->EditableText->SetText(FText::FromString(FVector4(propValue.vval[0], propValue.vval[1], propValue.vval[2], propValue.vval[3]).ToString()));
				//	cell->EditableText->SetText(FText::Format(FTextFormat::FromString("r:%,g:%,b:%,a:%"), color.R, color.G, color.B, color.A));
				break;
			default:
				check(0);
			}

			cell->CellDataKey = FString::Format(TEXT("{0}{1}"),
				{
					Cast<UHPSheetHeaderCellBase>(headerEntries[cellIndexInRow])->ButtonText->Text.ToString(),
					FString::FromInt(rowWidget->RowIndex)
				});
			cell->ParentRow = rowWidget;
			cell->ParentSheet = this;
			cell->actorType = actorData->actorType;
			cell->actorPtr = actorData->actor; //we want to reflect change in runtime on the actor while cell data is edited
			cell->propType = propValue.propType;
			cell->propName = propEntry.Key;

			cellIndexInRow++;
		}
	}

}

void UHPDataSheetBase::GenerateDataMapFromSheet(const FString& actorId)
{

	TMap<FString, TArray<UVPDynamicActorData>> demoData;//this is how the pers map looks in Personalizer.h

	TArray<UVPDynamicActorData>& arr = demoData[actorId];

	const auto rows = SheetBox->GetAllChildren();
	for (auto rowWidget: rows)
	{
		UVPDynamicActorData dataEntry = {};
		//each row is an actor with props:
	    auto row = Cast<UHPSheetRowBase>(rowWidget);
		dataEntry.actor = nullptr;// will be provided next iteration
		dataEntry.actorType = EUVPActorType::StaticMesh;// probably need to pass in actor type as apram or cache on sheet generaion

	}
}

void UHPDataSheetBase::SetHeaderColor(FLinearColor color)
{
	const auto& entries = SheetheaderBox->GetAllEntries();
	for (auto entry: entries)
	{
		Cast<UHPSheetHeaderCellBase>(entry)->But->SetBackgroundColor(color);
	}
}

