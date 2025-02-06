#include "ImageProcessor.h" // ImageProcessor 클래스 선언이 있는 헤더 파일을 포함

#include <fstream>
#include <cmath>
// #include <algorithm>
#include <iostream>

// 생성자 구현
ImageProcessor::ImageProcessor(int height, int tpad, int w_ratio, int s_ratio, int row_size, int rows[])
    : height(height), tpad(tpad), w_ratio(w_ratio), s_ratio(s_ratio), row_size(row_size), rows(rows, rows + row_size)
{
    if (height + tpad > row_size || height < 0 || tpad < 0)
    {
        throw std::invalid_argument("Error: height + tpad must not be greater than row_size || height or tpad value is not greater than 0!");
    }
    else if (s_ratio >= 360 || w_ratio >= 360)
    {
        throw std::invalid_argument("Error: s_ratio or w_ratio must not be greater than 360 degree!");
    }
}

// 행 크기 계산
void ImageProcessor::Calc_rows()
{
    cal_rows.resize(height);

    for (int i = tpad; i < height + tpad; i++)
    {
        cal_rows[i - tpad] = std::round(rows[i] * ((double)w_ratio / 360));
        if (cal_rows[i - tpad] <= 0)
        {
            throw std::invalid_argument("Error: cal_rows value is incorrect!");
        }
        std::cout << "cal_rows[" << (i - tpad) << "] = " << cal_rows[i - tpad] << std::endl;
    }
}

// 계산된 행 크기 출력
void ImageProcessor::PrintCalRows()
{
    for (int val : cal_rows)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// 이미지 축소 함수
void ImageProcessor::Mask(std::vector<uint8_t> &rgb_array, int original_width, int original_height)
{
    if (rgb_array.size() != original_width * original_height * 3)
    {
        throw std::invalid_argument("Error: RGB array size does not match given width and height!");
    }

    // 세로 축소
    std::vector<uint8_t> temp_rgb(height * original_width * 3);
    float y_ratio = static_cast<float>(original_height) / height;

    for (int i = 0; i < height; i++)
    {
        int start_y = static_cast<int>(i * y_ratio);
        int end_y = static_cast<int>((i + 1) * y_ratio);

        for (int j = 0; j < original_width; j++)
        {
            int r_sum = 0, g_sum = 0, b_sum = 0;
            int count = 0;

            for (int y = start_y; y < end_y; y++)
            {
                int index = (y * original_width + j) * 3;
                r_sum += rgb_array[index];
                g_sum += rgb_array[index + 1];
                b_sum += rgb_array[index + 2];
                count++;
            }

            int dst_index = (i * original_width + j) * 3;
            temp_rgb[dst_index] = r_sum / count;
            temp_rgb[dst_index + 1] = g_sum / count;
            temp_rgb[dst_index + 2] = b_sum / count;
        }
    }

    // 가로 축소
    int cal_rows_sum = 0;
    for (int i = 0; i < height; i++)
    {
        cal_rows_sum += cal_rows[i];
    }
    std::cout << cal_rows_sum << std::endl;
    std::vector<uint8_t> resized_rgb(height * cal_rows_sum * 3); // 임시 RGB 배열 생성
    int dst_ago = 0;
    int dst_index = 0;

    for (int i = 0; i < height; i++)
    {

        int current_width = cal_rows[i]; // 각 줄마다 너비 설정
        float x_ratio = static_cast<float>(original_width) / current_width;

        for (int j = 0; j < current_width; j++)
        {
            int start_x = static_cast<int>(j * x_ratio);
            int end_x = static_cast<int>((j + 1) * x_ratio);

            int r_sum = 0, g_sum = 0, b_sum = 0;
            int count = 0;

            for (int x = start_x; x < end_x; x++)
            {
                int index = (i * original_width + x) * 3;
                r_sum += temp_rgb[index];
                g_sum += temp_rgb[index + 1];
                b_sum += temp_rgb[index + 2];
                count++;
            }

            dst_index = //current값이 계속 달라지므로 그걸 반영해야함
            resized_rgb[dst_index] = r_sum / count;
            resized_rgb[dst_index + 1] = g_sum / count;
            resized_rgb[dst_index + 2] = b_sum / count;
        }

    }

    // 축소된 RGB 데이터를 저장
    this->resized_rgb = std::move(resized_rgb);
    std::ofstream outFile("resized_rgb.txt");
    for (size_t i = 0; i < resized_rgb.size(); i += 3)
    {
        outFile << static_cast<int>(resized_rgb[i]) << " "
                << static_cast<int>(resized_rgb[i + 1]) << " "
                << static_cast<int>(resized_rgb[i + 2]) << "\n";
    }
    outFile.close();
}
