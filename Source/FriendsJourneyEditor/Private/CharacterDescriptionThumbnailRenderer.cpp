// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDescriptionThumbnailRenderer.h"

#include "CharacterDescriptionDataAsset.h"

bool UCharacterDescriptionThumbnailRenderer::CanVisualizeAsset(UObject* Object)
{
	return IsValid(GetThumbnailTextureFromObject(Object));
}

void UCharacterDescriptionThumbnailRenderer::GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth,
	uint32& OutHeight) const
{
	Super::GetThumbnailSize(GetThumbnailTextureFromObject(Object), Zoom, OutWidth, OutHeight);
}

void UCharacterDescriptionThumbnailRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height,
	FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily)
{
	Super::Draw(GetThumbnailTextureFromObject(Object), X, Y, Width, Height, RenderTarget, Canvas, bAdditionalViewFamily);
}

UTexture2D* UCharacterDescriptionThumbnailRenderer::GetThumbnailTextureFromObject(UObject* Object)
{
	const UCharacterDescriptionDataAsset* CharacterDesc = Cast<UCharacterDescriptionDataAsset>(Object);
	if (!CharacterDesc)
	{
		return nullptr;
	}

	if (UTexture2D* SlateBrushTexture = Cast<UTexture2D>(CharacterDesc->DisplayIcon.GetResourceObject()))
	{
		SlateBrushTexture->BlockOnAnyAsyncBuild();
		return SlateBrushTexture;
	}
 
	return nullptr;
}
