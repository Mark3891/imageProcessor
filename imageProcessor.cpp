#include <iostream>
#include <vector>
#include <cmath>     // std::round
#include <stdexcept> // 예외 처리를 위한 std::invalid_argument

class ImageProcessor
{
private:
    int height;
    int tpad;
    int w_ratio;
    int s_ratio;
    int row_size;
    std::vector<int> rows;
    std::vector<int> cal_rows;

public:
    // 생성자
    ImageProcessor(int height, int tpad, int w_ratio, int s_ratio, int row_size, int rows[])
        : height(height), tpad(tpad), w_ratio(w_ratio), s_ratio(s_ratio), row_size(row_size), rows(rows, rows + row_size)
    {

        // 예외 처리: height + tpad가 row_size보다 크면 오류 발생
        if (height + tpad > row_size || height<0 || tpad<0)
        {
            throw std::invalid_argument("Error: height + tpad must not be greater than row_size || height or tpad value is not greater than 0!");
        }
        else if (s_ratio >= 360 || w_ratio >= 360)
        {
            throw std::invalid_argument("Error: s_ratio or w_ratio must not be greater than 360 degree!");
        }
    }

    void Calc_rows()
    {
        cal_rows.resize(height); // tpad를 고려한 크기 설정

        for (int i = tpad; i < height+tpad; i++)
        {
            cal_rows[i - tpad] = std::round(rows[i] * ((double)w_ratio / 360));
            if (cal_rows[i-tpad] <= 0)
        {
            throw std::invalid_argument("Error: cal_rows value is uncorrect!");
        }
            std::cout << "cal_rows[" << (i - tpad) << "] = " << cal_rows[i - tpad] << std::endl;
        }
    }

    // test용 함수
    void PrintCalRows()
    {
        for (int val : cal_rows)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    try
    {
        int sphere_rows[] = {
            314, 319, 325, 330, 334, 338, 342, 345, 348, 351,
            353, 355, 356, 358, 358, 359, 359, 359, 359, 358,
            356, 357, 355, 353, 351, 347, 345, 342, 337, 335,
            331, 326, 320, 316, 311, 306, 299, 293, 286, 279,
            272, 263, 255, 246, 235, 224, 211, 199, 187, 172,
            157, 141, 126, 104};

        // Test용 설정값
        int height = 10;
        int tpad = 3;    // 일부러 오류 발생시키는 값 (height + tpad > row_size)
        int w_ratio = 90; // 표현하고자 하는 디스플레이 비율 크기
        int s_ratio = 90; // 표현하고자 하는 디스플레이 시작 위치 비율
        int row_size = sizeof(sphere_rows) / sizeof(sphere_rows[0]);

        ImageProcessor img(height, tpad, w_ratio, s_ratio, row_size, sphere_rows);
        img.Calc_rows();
        img.PrintCalRows();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
