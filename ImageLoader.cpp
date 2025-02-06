#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ImageLoader::ImageLoader(const char* filename) {
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 3);

    if (!data) {
        throw std::runtime_error("Error: Failed to load image!");
    }

    rgb_data.assign(data, data + (width * height * 3));
    stbi_image_free(data);
}

void ImageLoader::printImageSize() const {
    std::cout << "📏 Image Size: " << width << " x " << height << std::endl;
}

void ImageLoader::maskImage(const std::vector<int>& cal_rows, int numrow) {
    if (numrow <= 0) {
        throw std::invalid_argument("Error: numrow must be greater than 0!");
    }
    
    

    
}


void ImageLoader::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open output file!");
    }

    file << "Width: " << width << ", Height: " << height << "\n";

    for (size_t i = 0; i < rgb_data.size(); i += 3) {
        file << (int)rgb_data[i] << " "      
             << (int)rgb_data[i + 1] << " "  
             << (int)rgb_data[i + 2] << "\n"; 
    }

    file.close();
    std::cout << "✅ RGB data saved to " << filename << std::endl;
}
