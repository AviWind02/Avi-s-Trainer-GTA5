#include "pch.h"



namespace core {
    namespace renderer::image {


        bool IsValidImageExtension(const std::string& extension)
        {
            std::string ext = extension;
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            return (ext == ".jpg" || ext == ".jpeg" || ext == ".png");
        }

        void LoadImages(const std::string& directoryPath, std::vector<dximage>& imageResources)
        {
            for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
            {
                if (entry.is_regular_file())
                {
                    std::string filePath = entry.path().string();
                    std::string fileName = entry.path().stem().string();
                    std::string extension = entry.path().extension().string();
                    if (IsValidImageExtension(extension))
                    {
                        ID3D11ShaderResourceView* texture = nullptr;
                        int width, height;
                        if (LoadTextureFromFile(filePath.c_str(), &texture, &width, &height))
                        {
                            imageResources.push_back(dximage{ texture, fileName });
                            //LOG << "Loaded image: " << fileName;
                        }
                        else
                        {
                            LOG_TAG("WARN") << "Failed to load image: " << fileName;
                        }
                    }
                }
            }

        }
    }
}