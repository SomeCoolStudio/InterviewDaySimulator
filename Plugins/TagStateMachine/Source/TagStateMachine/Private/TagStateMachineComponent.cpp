// Fill out your copyright notice in the Description page of Project Settings.


#include "TagStateMachineComponent.h"

// Sets default values for this component's properties
UTagStateMachineComponent::UTagStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UTagStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SwitchState(InitialStateTag);
}


// Called every frame
void UTagStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCanTickState)
	{
		TickState(DeltaTime);
	}

	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("Current State for %s: %s"), *GetOwner()->GetName(), *StateTag.ToString()));

		if (StateHistory.Num() > 0)
		{
			for (int32 i = 0; i < StateHistory.Num(); i++)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, FString::Printf(TEXT("%s"), *StateHistory[i].ToString()));
			}
		}
	} 
	// ...
}

bool UTagStateMachineComponent::SwitchState(FGameplayTag _StateTag)
{
	if (!StateTag.MatchesTagExact(_StateTag))
	{
		bCanTickState = false;

		EndState();

		StateTag = _StateTag;
		InitState();

		bCanTickState = true;

		if (StateChangedDelegate.IsBound())
		{
			StateChangedDelegate.Broadcast(_StateTag);
		}

		return true;
	}

	else
	{
		if (bDebug)
		{
			//
			UE_LOG(LogTemp, Warning, TEXT("Couldn't switch state for %s because it is already in %s"), *GetOwner()->GetName(), *_StateTag.ToString());
		}
	}

	return false;
}

void UTagStateMachineComponent::InitState()
{
	if (InitStateDelegate.IsBound())
	{
		InitStateDelegate.Broadcast(StateTag);
	}
}

void UTagStateMachineComponent::TickState(float DeltaTime)
{
	if (TickStateDelegate.IsBound())
	{
		TickStateDelegate.Broadcast(DeltaTime, StateTag);
	}
}

void UTagStateMachineComponent::EndState()
{
	if (StateHistory.Num() >= StateHistoryLength)
	{
		StateHistory.RemoveAt(0);
	}

	StateHistory.Push(StateTag);

	if (EndStateDelegate.IsBound())
	{
		EndStateDelegate.Broadcast(StateTag);
	}
}

