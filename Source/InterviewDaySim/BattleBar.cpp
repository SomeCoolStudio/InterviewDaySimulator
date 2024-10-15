

#include "BattleBar.h"

// Sets default values
ABattleBar::ABattleBar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleBar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleBar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BattleBar();

}

void ABattleBar::BattleBar()
{
	HP--;

	
}

