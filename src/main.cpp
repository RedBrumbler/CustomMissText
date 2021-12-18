#include "main.hpp"
#include "GlobalNamespace/MissedNoteEffectSpawner.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "questui/shared/QuestUI.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "UnityEngine/GameObject.hpp"
#include "config/config.hpp"
#include "ViewController.hpp"

using namespace UnityEngine;

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}



// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

MAKE_HOOK_MATCH(MissedNoteEffectSpawner_Start, 
                &GlobalNamespace::MissedNoteEffectSpawner::Start, void,
                GlobalNamespace::MissedNoteEffectSpawner* self)
{
    //MissedNoteEffectSpawner_Start(self);
  /*ignore that please im not even sure if that's how i would do it   
  auto MissText = UnityEngine::GameObject::CreateGameObject("MissText")->UnityEngine::Component::AddComponent<FlyingTextSpawner>();
    MissText->set_text(il2cpp_utils::newcsstr(getModConfig().MissText.GetValue()));*/
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getModConfig().Init(info);
    getConfig().Reload();
    getConfig().Write();
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), MissedNoteEffectSpawner_Start);
    il2cpp_functions::Init();
    QuestUI::Init();
    custom_types::Register::AutoRegister();
    QuestUI::Register::RegisterMainMenuModSettingsViewController<CustomMissText::ViewController*>(modInfo);
    getLogger().info("Installed all hooks!");
    }