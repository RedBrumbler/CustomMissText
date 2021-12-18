#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "ViewController.hpp"
#include "HMUI/Touchable.hpp"
#include "HMUI/InputFieldView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "config/config.hpp"

using namespace HMUI;
using namespace QuestUI::BeatSaberUI;
using namespace UnityEngine;

DEFINE_TYPE(CustomMissText, ViewController);

UnityEngine::UI::VerticalLayoutGroup* textLayout;

HMUI::InputFieldView* MissText;

void CustomMissText::ViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) 
{   
            layout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(get_transform());
            horizontal = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(layout->get_transform());
            get_gameObject()->AddComponent<HMUI::Touchable*>();
            UnityEngine::GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
            button = CreateUIButton(horizontal->get_transform(), "made by rxzz0#6982");  


            auto MissText = AddConfigValueStringSetting(container->get_transform(), getModConfig().MissText);
            getModConfig().MissText.AddChangeEvent([MissText](std::string value) {
                MissText->set_text(il2cpp_utils::newcsstr(value));
            });
}