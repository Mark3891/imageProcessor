#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>

class ImageLoader {
public:
    int width, height, channels;
    std::vector<unsigned char> rgb_data;

    // 생성자
    ImageLoader(const char* filename);

    // 이미지 크기 출력
    void printImageSize() const;

    // 특정 영역을 마스킹하는 함수 (새로운 함수)
    void maskImage(const std::vector<int>& cal_rows, int numrow);

    // RGB 데이터를 파일에 저장
    void saveToFile(const std::string& filename) const;
};

#endif // IMAGELOADER_H
