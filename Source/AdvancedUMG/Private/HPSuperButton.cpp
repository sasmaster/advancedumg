// Fill out your copyright notice in the Description page of Project Settings.
#include "HPSuperButton.h"
 
UHPSuperButton::UHPSuperButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UHPSuperButton::PostLoad()
{
	Super::PostLoad();
	OnClicked.AddDynamic(this, &UHPSuperButton::OnLeftDoubleMouseClick);
}

void UHPSuperButton::OnLeftDoubleMouseClick()
{
    //https://en.wikipedia.org/wiki/Double-click

	//this requires inclusion of UGameplayStatics
	//const double now = FTimespan::FromSeconds(UGameplayStatics::GetRealTimeSeconds(GetWorld())).GetTotalMilliseconds();
	//and this does not:
	const double now =  FPlatformTime::ToMilliseconds(FPlatformTime::Cycles());
	const double timeBetweenClicks = now - mStartClickTime;
	if (timeBetweenClicks < 250.0)
	{
		OnLeftMouseDoubleClicked.Broadcast();
	}
 
	mStartClickTime = now;

}

