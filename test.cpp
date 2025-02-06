#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

int main()
{
    try
    {
        // 이미지 불러오기
        cv::Mat image = cv::imread("test_image.jpg");
        if (image.empty())
        {
            std::cout << "Cannot load image: test_image.jpg" << std::endl;
            return -1;
        }

        int img_width = image.cols;
        int img_height = image.rows;
        int channels = image.channels(); // 3 (BGR)

        printf("Original Image Size: Width = %d, Height = %d\n", img_width, img_height);

        // BGR -> RGB 변환
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);

        // RGB 데이터를 저장할 1차원 배열
        std::vector<uint8_t> rgb_array;
        rgb_array.reserve(img_width * img_height * 3); // RGB이므로 3배 크기

        // OpenCV Mat 데이터를 1차원 벡터로 변환
        for (int i = 0; i < img_height; i++)
        {
            for (int j = 0; j < img_width; j++)
            {
                cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
                rgb_array.push_back(pixel[0]); // R
                rgb_array.push_back(pixel[1]); // G
                rgb_array.push_back(pixel[2]); // B
            }
        }

        // RGB 배열 저장 (예: 텍스트 파일)
        std::ofstream outFile("rgb_data.txt");
        for (size_t i = 0; i < rgb_array.size(); i += 3)
        {
            outFile << static_cast<int>(rgb_array[i]) << " "
                    << static_cast<int>(rgb_array[i + 1]) << " "
                    << static_cast<int>(rgb_array[i + 2]) << "\n";
        }
        outFile.close();

        std::cout << "RGB data saved to rgb_data.txt" << std::endl;

        // 구체의 행 데이터를 정의
        int sphere_rows[] = {
            314, 319, 325, 330, 334, 338, 342, 345, 348, 351,
            353, 355, 356, 358, 358, 359, 359, 359, 359, 358,
            356, 357, 355, 353, 351, 347, 345, 342, 337, 335,
            331, 326, 320, 316, 311, 306, 299, 293, 286, 279,
            272, 263, 255, 246, 235, 224, 211, 199, 187, 172,
            157, 141, 126, 104};

        int height = 10;
        int tpad = 3;
        int w_ratio = 90;
        int s_ratio = 90;
        int row_size = sizeof(sphere_rows) / sizeof(sphere_rows[0]);

        // ImageProcessor 객체 생성
        ImageProcessor img(height, tpad, w_ratio, s_ratio, row_size, sphere_rows);
        img.Calc_rows();

        // Mask 함수 호출
        img.Mask(rgb_array, img_width, img_height);

     

        std::cout << "Test complete, resized RGB data saved." << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
