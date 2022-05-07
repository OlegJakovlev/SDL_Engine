#include "TextureConfigurator.h"
#include <iostream>

TextureConfigurator::TextureConfigurator(const std::string& texturesPath) : Configurator(texturesPath) {
}

TextureConfigurator::~TextureConfigurator() {
    TextureLocator::ReleaseTextureManager();
}

void TextureConfigurator::LoadConfiguration() {
    TextureManager* textureManager = new TextureManager();
    TextureLocator::LinkTextureManager(textureManager);

    if (std::filesystem::is_empty(configPath)) GraphicsLogger::Instance().LogWarning("Texture path folder " + configPath + " is empty");

    // Iterate over the directory elements recursively (skip symlinks and insuffiecient permissions directories)
    for (const std::filesystem::directory_entry& entry :
        std::filesystem::recursive_directory_iterator(configPath, std::filesystem::directory_options::skip_permission_denied))
    {
        // Check if directory_entry is file
        if (!std::filesystem::is_regular_file(entry)) continue;

        // Check if file does have an extension
        if (std::filesystem::path(entry.path()).extension() == "") continue;

        // Unzip archive, but do not replace local files
        /*
        if (std::filesystem::path(entry.path()).extension() == ".zip") {
        }
        */

        textureManager->AddTexture(entry.path().generic_string());
    }
}
