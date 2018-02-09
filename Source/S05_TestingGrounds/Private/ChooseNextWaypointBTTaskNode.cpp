// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypointBTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h" // TODO remove copupling



EBTNodeResult::Type UChooseNextWaypointBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get the control points
	AAIController *AIController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIController->GetPawn();
	APatrollingGuard *PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	TArray<AActor*> &PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	// set the next waypoint.
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index + 1)%PatrolPoints.Num());

	// TODO protect against empty patrol routes.

	UE_LOG(LogTemp, Warning, TEXT("AI WOKRING %i"), Index);
	return EBTNodeResult::Succeeded;
}
