class ImageProcessor {

private:
    int height;
    int tpad;
    int w_ratio;
    int s_ratio;
    int row_size;
    int rows[];

public:
    
    ImageProcessor(int height, int tpad, int w_ratio, int s_ratio, int row_size, int rows[]);
    
    int Calc_row(){return 0;}
    
   
    
};