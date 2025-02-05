#include <iostream>
#include <vector>

class ImageProcessor {
private:
    int height;
    int tpad;
    int w_ratio;
    int s_ratio;
    int row_size;
    std::vector<int> rows; // 벡터 사용
    std::vector<int> cal_rows;

public:
    // 생성자
    ImageProcessor(int height, int tpad, int w_ratio, int s_ratio, int row_size, int rows[])
        : height(height), tpad(tpad), w_ratio(w_ratio), s_ratio(s_ratio), row_size(row_size), rows(rows, rows + row_size) {}

   

    void Calc_rows() {
        cal_rows.resize(height); 

        for (int i = tpad; i < height+tpad; i++) {
            cal_rows[i - tpad] = std::round(rows[i] * ((double)w_ratio / 360)); // 반올림 적용
            std::cout << "cal_rows[" << (i - tpad) << "] = " << cal_rows[i - tpad] << std::endl;
        }
    }
     // 행을 출력하는 함수 (테스트용)
    void PrintRows() {
        std::cout << height << " " << tpad << " "<< row_size<< std::endl;
        for (int val : cal_rows) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    int sphere_rows[] = {
    314, 319, 325, 330, 334, 338, 342, 345, 348, 351, 
    353, 355, 356, 358, 358, 359, 359, 359, 359, 358, 
    356, 357, 355, 353, 351, 347, 345, 342, 337, 335, 
    331, 326, 320, 316, 311, 306, 299, 293, 286, 279, 
    272, 263, 255, 246, 235, 224, 211, 199, 187, 172, 
    157, 141, 126, 104
};
    //Test용 설정값
    int height = 10;
    int tpad=3;
    int w_ratio=90; //표현하고자 하는 디스플레이 비율 크기
    int s_ratio=90; // 표현하고자 하는 디스플레이 시작 위치 비율
    int row_size = sizeof(sphere_rows) / sizeof(sphere_rows[0]);

    ImageProcessor img(height, tpad, w_ratio, s_ratio, row_size, sphere_rows);
    img.Calc_rows();
    img.PrintRows();

    return 0;
}
