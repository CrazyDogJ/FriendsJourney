// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SceneViewExtension.h"

class FUnderwaterViewExtension : public FSceneViewExtensionBase
{
public:
	FUnderwaterViewExtension(const FAutoRegister& AutoRegister)
		: FSceneViewExtensionBase(AutoRegister) {}
 
	UWorldSubsystem* OuterSubsystem = nullptr;
	
	// 保证排在 Water 扩展之后执行，具体数值按 SceneViewExtension.h 的排序规则和 Water 扩展的优先级来定
	virtual int32 GetPriority() const override { return 1000; }
 
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {}
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override {}
};
