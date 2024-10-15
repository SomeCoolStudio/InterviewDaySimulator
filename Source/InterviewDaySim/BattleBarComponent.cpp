// Fill out your copyright notice in the Description page of Project Settings.



#include "BattleBarComponent.h"


// Sets default values for this component's properties
UBattleBarComponent::UBattleBarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBattleBarComponent::BeginPlay()
{
	Super::BeginPlay();

	//OnHitSpaceBar.AddDynamic(this,&UBattleBarComponent::HitSpaceBarBroadcast);

	FlipBook = Cast<APaperCharacter>(GetOwner());
	 
	if (!FlipBook)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Flipbook Found"));
	}
}


// Called every frame
void UBattleBarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DecreaseHealth();
	CheckIfPressedSpaceBar();
	EvaluateHealthValues(HP);
	//HP = HP + 1;

}


void UBattleBarComponent::DecreaseHealth()
{
	if (HP < 100)
	{
		if (HP > 0)
		{
			HP = HP - 1 * (GetWorld()->GetDeltaSeconds() * HPDecreaseSpeed);
		}

		else if (HP < 0)
		{
			HP = 0;
		}
	}

	if (HP >= 100)
	{
		IsWin = true;
	}
}

bool UBattleBarComponent::CheckIfPressedSpaceBar()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (PC->WasInputKeyJustPressed(EKeys::SpaceBar))
	{
		HP = HP + AttackStr;
		return true;
	}

	else
	{
		return false;
	}
}

float UBattleBarComponent::GetHealth()
{
	return HP;
}

bool UBattleBarComponent::GetIsWin()
{
	return IsWin;
}

bool UBattleBarComponent::GetAlmostMadeIt()
{
	return AlmostMadeIt;
}

void UBattleBarComponent::SetAlmostMadeIt(bool& NewValue)
{
	AlmostMadeIt = NewValue;
}

void UBattleBarComponent::EvaluateHealthValues(float& Health)
{
	
		if (Health > 20)
		{
			if (Health > 21 && Health < 60)
			{
				
				if (PassedSecondMark)
				{
					if (FlipBook->GetSprite()->GetFlipbook() != ReverseAwakeFlipBook)
					{
						PassedThirdMark = false;
						FlipBook->GetSprite()->SetLooping(false);
						FlipBook->GetSprite()->SetFlipbook(ReverseAwakeFlipBook);
						FlipBook->GetSprite()->Play();
					}
					//UE_LOG(LogTemp, Warning, TEXT("Awake Reverse"));

				}

				else if(!PassedSecondMark)
				{
					if (FlipBook->GetSprite()->GetFlipbook() != AlmostAwakeFlipBook)
					{
						PassedFirstMark = true;
						FlipBook->GetSprite()->SetLooping(false);
						FlipBook->GetSprite()->SetFlipbook(AlmostAwakeFlipBook);
						FlipBook->GetSprite()->Play();
					}
					//UE_LOG(LogTemp, Warning, TEXT("Almost Awake"));
				}							
			}

			if (Health > 61 && Health < 99)
			{

				if (PassedThirdMark)
				{
					if (FlipBook->GetSprite()->GetFlipbook() != ReverseFullyAwakeFlipBook)
					{
						FlipBook->GetSprite()->SetLooping(false);
						FlipBook->GetSprite()->SetFlipbook(ReverseFullyAwakeFlipBook);
						FlipBook->GetSprite()->Play();
					}
					//UE_LOG(LogTemp, Warning, TEXT("Fully Awake Reverse"));
				}

				else if(!PassedThirdMark)
				{
					if (FlipBook->GetSprite()->GetFlipbook() != AwakeFlipBook)
					{
						PassedSecondMark = true;
						AlmostMadeIt = true;
						FlipBook->GetSprite()->SetLooping(false);
						FlipBook->GetSprite()->SetFlipbook(AwakeFlipBook);
						FlipBook->GetSprite()->Play();
					}
					//UE_LOG(LogTemp, Warning, TEXT("Awake"));
				}
			}

			if (Health > 99)
			{
				if (FlipBook->GetSprite()->GetFlipbook() != FullyAwakeFlipBook)
				{
					PassedThirdMark = true;
					FlipBook->GetSprite()->SetLooping(false);
					FlipBook->GetSprite()->SetFlipbook(FullyAwakeFlipBook);
					FlipBook->GetSprite()->Play();
				}
				//UE_LOG(LogTemp, Warning, TEXT("Fully Awake"));
			}
		}

		else
		{
			if (PassedFirstMark)
			{
				if (FlipBook->GetSprite()->GetFlipbook() != ReverseAlmostAwakeFlipBook)
				{
					PassedSecondMark = false;
					FlipBook->GetSprite()->SetLooping(false);
					FlipBook->GetSprite()->SetFlipbook(ReverseAlmostAwakeFlipBook);
					FlipBook->GetSprite()->Play();
					//UE_LOG(LogTemp, Warning, TEXT("Almost Awake Reverse"));
				}

				if (FlipBook->GetSprite()->GetPlaybackPosition() >= FlipBook->GetSprite()->GetFlipbookLength())
				{
					PassedFirstMark = false;
				}

			}

			else
			{
				if (FlipBook->GetSprite()->GetFlipbook() != SleepIdleFlipBook)
				{
					FlipBook->GetSprite()->SetLooping(true);
					FlipBook->GetSprite()->SetFlipbook(SleepIdleFlipBook);
					FlipBook->GetSprite()->Play();
				}
			}
		}
}


 



