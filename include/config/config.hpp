#pragma once
#include "main.hpp"
#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(MissText, std::string, "Miss", "Aww, too bad!");

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(MissText);
    )
)