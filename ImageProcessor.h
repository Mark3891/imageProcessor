#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cstdint>

class ImageProcessor
{
public:
    // 생성자: 이미지 크기 및 파라미터 초기화
    ImageProcessor(int height, int tpad, int w_ratio, int s_ratio, int row_size, int rows[]);

    // 행 크기 계산 및 출력 함수
    void Calc_rows();

    // 계산된 행 크기 출력 함수
    void PrintCalRows();

    // 이미지 축소 (세로, 가로 평균값을 사용하여 RGB 배열을 조작)
    void Mask(std::vector<uint8_t> &rgb_array, int original_width, int original_height);

    // 축소된 RGB 데이터를 파일에 저장
    void SaveResizedRGBToFile(const std::string &file_name);

    // 축소된 RGB 데이터 반환
    const std::vector<uint8_t>& GetResizedRGB() const { return resized_rgb; }

private:
    int height;                      // 최종 이미지 높이
    int tpad;                        // 상단 패딩
    int w_ratio;                     // 가로 축소 비율 (0 ~ 360)
    int s_ratio;                     // 세로 축소 비율 (0 ~ 360)
    int row_size;                    // 원본 행 개수
    std::vector<int> rows;           // 원본 행 값들 (각 세로 행의 가로 크기)
    std::vector<int> cal_rows;       // 계산된 가로 크기 리스트 (축소 후)
    std::vector<uint8_t> resized_rgb; // 최종 축소된 이미지 RGB 데이터
};

#endif // IMAGE_PROCESSOR_H
