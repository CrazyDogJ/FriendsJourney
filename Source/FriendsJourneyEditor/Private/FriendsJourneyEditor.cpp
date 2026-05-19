#include "FriendsJourneyEditor.h"

#include "CharacterDescriptionDataAsset.h"
#include "CharacterDescriptionThumbnailRenderer.h"
#include "ThumbnailRendering/ThumbnailManager.h"

#define LOCTEXT_NAMESPACE "FFriendsJourneyEditorModule"

void FFriendsJourneyEditorModule::StartupModule()
{
	if (GIsEditor)
	{
		UThumbnailManager::Get().RegisterCustomRenderer(UCharacterDescriptionDataAsset::StaticClass(),
			UCharacterDescriptionThumbnailRenderer::StaticClass());
	}
}

void FFriendsJourneyEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FFriendsJourneyEditorModule, FriendsJourneyEditor)