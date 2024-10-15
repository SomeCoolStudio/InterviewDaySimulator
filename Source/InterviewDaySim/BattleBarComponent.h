 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PlayerController.h"
#include "PaperFlipbookComponent.h"
#include "PaperCharacter.h"
#include "BattleBarComponent.generated.h"

/**
 *
 */


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERVIEWDAYSIM_API UBattleBarComponent : public UActorComponent
{ 
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBattleBarComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere, Category = "FlipBooks")
	APaperCharacter* FlipBook;

	UPROPERTY(EditAnywhere, Category = "BattleBarConfig")
	float HP;

	UPROPERTY(EditAnywhere, Category = "BattleBarConfig")
	float AttackStr;

	UPROPERTY(EditAnywhere, Category = "BattleBarConfig")
	float HPDecreaseSpeed;

	UPROPERTY(EditAnywhere, Category = "Play Marks")
	bool PassedFirstMark;

	UPROPERTY(EditAnywhere, Category = "Play Marks")
	bool PassedSecondMark;

	UPROPERTY(EditAnywhere, Category = "Play Marks")
	bool PassedThirdMark;

	UPROPERTY()
	bool DidOnce;

	UPROPERTY()
	bool AlmostMadeIt;

	UPROPERTY(EditAnywhere, Category = "FlipBooks")
	UPaperFlipbook* SleepIdleFlipBook;

	UPROPERTY(EditAnywhere, Category = "FlipBooks")
	UPaperFlipbook* AlmostAwakeFlipBook;

	UPROPERTY(EditAnywhere, Category = "FlipBooks")
	UPaperFlipbook* ReverseAlmostAwakeFlipBook;

	UPROPERTY(EditAnywhere, Category = "FlipBooks")
	UPaperFlipbook* AwakeFlipBook;

	UPROPERTY(EditAnywhere, Category = "FlipBooks")
	UPaperFlipbook* ReverseAwakeFlipBook;

	UPROPERTY(EditAnywhere, Category = "FlipBooks")
	UPaperFlipbook* FullyAwakeFlipBook;

	UPROPERTY(EditAnywhere, Category = "FlipBooks")
	UPaperFlipbook* ReverseFullyAwakeFlipBook;

	void DecreaseHealth();

public: 


	UPROPERTY(EditAnywhere, Category = "Game State")
	bool IsWin = false;

	UFUNCTION(BlueprintPure)
	float GetHealth();

	UFUNCTION(BlueprintCallable)
	void EvaluateHealthValues(float& Health);

	UFUNCTION(BlueprintPure)
	bool GetIsWin();

	UFUNCTION(BlueprintPure)
	bool GetAlmostMadeIt();

	UFUNCTION(BlueprintCallable)
	void SetAlmostMadeIt(bool& NewValue);

	UFUNCTION()
	bool CheckIfPressedSpaceBar();
};
