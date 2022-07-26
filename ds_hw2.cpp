#include <iostream>
#include <iomanip>
#include <stdlib.h>
#define MAX_PIXELS 60000

using namespace std;
class Pixel
{
public:
    int row; // the row index of the pixel
    int col; // the column index of the pixel
    int val; // the intensity value of the pixel
};

class Image final // final means that this class cannot be inherited by any other class
{
public:
    int w;        // width of the Image object;
    int h;        // height of the Image object;
    int m;        // the number of non-black pixels in the Image object;
    Pixel *pixel; // an array to keep all non-black pixels in the Image object;
    Image();
    Image(int w, int h);
    ~Image();
    Image *Rotate();
    int GetValue(int row, int col);
    void SetValue(int row, int col, int val);
    Image &Subimage(int top, int bottom, int left, int right);
    int *Histogram(int top, int bottom, int left, int right);
    void ShowImg();
};

Image::Image()
{
    pixel = new Pixel[MAX_PIXELS];
    this->w = 1000;
    this->h = 1000;
    this->m = 0;
}

Image::Image(int h, int w)
{
    pixel = new Pixel[MAX_PIXELS];
    this->w = w;
    this->h = h;
    this->m = 0;
}

Image::~Image()
{
    delete[] pixel;
    w = h = m = 0;
}

Image *RandomImage(int h, int w, int n_pixels)
{
    srand(0);
    Image *img = new Image(h, w);
    int i, r, c, v;
    for (i = 0; i < n_pixels; i++)
    {
        r = rand() % h;
        c = rand() % w;
        v = rand() % 255 + 1;
        img->SetValue(r, c, v);
    }
    return img;
}

// =======================================================================
//returns a pointer to an Image object obtained from rotating the image by 90 degrees in clockwise direction
Image *Image::Rotate(){

    Image *img = new Image(w, h); // h w 相反
    for (int i = 0; i < m; i++){
        img->SetValue(pixel[i].col, h - (pixel[i].row) - 1, pixel[i].val);
    }
    return img;
}
// get the intensity value of the pixel at the position (row, col) of the Image object
int Image::GetValue(int row, int col){
    for (int i = 0; i < m; i++){
        if (pixel[i].row == row && pixel[i].col == col){
            return pixel[i].val;
        }
    }
    return 0;
}
// set the intensity value of the pixel at the position (row, col) to the specified value val
void Image::SetValue(int row, int col, int val){

    int i = 0;
    while(i < m){
        if (pixel[i].row >= row && pixel[i].col >= col){
            if((pixel[i].row == row) && (pixel[i].col == col)){
                m--;
                break;
            }
            for(int j = m; j != i; j--){
                pixel[j] = pixel[j-1];
            }
            break;
        }
        i++;
    }
    pixel[i].row = row;
    pixel[i].col = col;
    pixel[i].val = val;
    m++;
}
// returns an Image object corresponding to a sub-image with the top-left corner (top, left) and the bottom-right corner (bottom, right)
Image &Image::Subimage(int top, int bottom, int left, int right){

    int h_sub = bottom-top+1, w_sub = right-left+1;
    Image *sub_img = new Image(h_sub, w_sub);
    for(int i = 0; i < this->m; i++){
        if(pixel[i].row >= top && pixel[i].row <= bottom && pixel[i].col >= left && pixel[i].col <= right){
            sub_img->SetValue(pixel[i].row - top, pixel[i].col - left, pixel[i].val);
        }
        else if(pixel[i].row > bottom && pixel[i].col > right){
            break;
        }
    }
    return *sub_img;

}
// returns an array of integers representing the sums of pixel intensities along the image columns of the subimage specified with the top-left corner (top, left) and the bottom-right corner (bottom, right)
int *Image::Histogram(int top, int bottom, int left, int right){
    
    int column = right - left + 1;
    int *histogram = new int[column];
    Image his_img = Subimage(top, bottom, left, right);
    for(int i = 0; i < column; i++){
        histogram[i] = 0;
    }
    
    for(int i = 0; i < his_img.m; i++){
        //cout << "test" << " ";
        histogram[his_img.pixel[i].col] += his_img.pixel[i].val * his_img.pixel[i].row;
    }
    return histogram;
}
// display the image on monitor
void Image::ShowImg(){
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if(j == 0){
                cout << " ";
            }
            cout << setw(4) << GetValue(i, j) << " ";
        }
        cout << endl;
    }
}

void PrintHistogram(int *hv, int start, int end){
    
    for(int i = start; i < end; i++){
        cout << hv[i] << " ";
    }
    cout << hv[end] << endl;
}
//given a sequence of numbers in a vector data , return a vector of computed values of the failure function for each vector element according to the KMP algorithm. 
int *FailureFunction(int *data, int length){
    
    int *ret = new int[length];
    for (int i = 0; i < length; i++){
        if(i == 0){
            ret[i] = -1;
        }
        else{
            int temp = ret[i - 1];
            while(*(data+i) != *(data+temp+1) && temp != -1){
                temp = ret[temp];
            }
            if(*(data+i) == *(data+temp+1)){
                ret[i] = temp + 1;
            }
            else{
                ret[i] = -1;
            }
        }
    }
    return ret;
    
}

int KMP(int start, int *pat, int length_p, int *data, int length_d, int *f){
    int p, d;
    for(int i = start, j = 0; i < length_p && j < length_d;){
        if(pat[i] == data[j]){
            i++;
            j++;
        }
        else{
            if(i == start){
                j++;
            }
            else{
                i = f[i-start-1] + 1;
            }
        }
        p = i;
        d = j;
    }
    if(p < length_p){//no same
        return false;
    }
    else{
        return d-length_p;
    }
}

void Detect(Image &img, Image &obj, int *r, int *c){
    int temp = -1;
    int *detect_obj = obj.Histogram(0, obj.h-1, 0, obj.w-1);
    int *detect_img;
    int *f = FailureFunction(detect_obj, obj.w);
    for(int i = 0; i+obj.h-1 < img.h; i++){
        detect_img = img.Histogram(i, i+obj.h-1, 0, img.w - 1);
        temp = KMP(0, detect_obj, obj.w, detect_img, img.w, f);
        if(temp != false){
            *r = i;
            *c = temp;
            break;
        }
    }
}
// =======================================================================

// =======================================================================
// The following is the template for the testing code in the Online Judge.
// =======================================================================

int main()
{
/*
    Image *img1, *rimg;

    cout << "--- Test small random generation" << endl;
    img1 = RandomImage(10, 8, 20); // generate a small Image object of 10x8 pixels with at most 20 non-black pixels.
    img1->ShowImg(); // display the generated image
    cout << "--- Test subimage" << endl;
    img1->Subimage(3, 6, 2, 5).ShowImg(); // get the specified subimage from the image
    cout << "--- Test rotating image" << endl;
    rimg = img1->Rotate(); // rotate the generated image clockwise by 90 degrees
    rimg->ShowImg();       // display the rotated image
*/
    Image *img1, img2;
    int w = 8000, h = 8000, n_pixels = 50000;
    int y1 = 120, y2 = 200, x1 = 600, x2 = 800;
    int r, c;

    cout << "--- Test super large random generation" << endl;
    img1 = RandomImage(h, w, n_pixels); // generate a super large image
    cout << "--- Test histogram computation" << endl;
    int *hv1 = img1->Histogram(y1, y2, 0, img1->w);  // compute the histogram vector for an image slice by specifying a search window
    PrintHistogram(hv1, x1, x1 + 30);                // print out a part of the histogram vector
    img2 = img1->Subimage(y1, y2, x1, x2);           // get the subimage from the specified search window
    int *hv2 = img2.Histogram(0, img2.h, 0, img2.w); // compute the histogram vector for the subimage
    PrintHistogram(hv2, 0, 30);                      // print out the histogram vector computed from the subimage
    cout << "--- Test failure function and KMP" << endl;
    int p[10] = {1, 2, 3, 1, 2, 3, 1, 3, 1, 2};                         // a shorter number sequence p
    int t[18] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 3, 1, 2, 2, 1, 2, 1, 1}; // a longer number sequence t
    int *f = FailureFunction(p, 10);                                    // compute the values of the failure function from sequence p
    for (int i = 0; i < 10; i++)                                        // display the computed values of the failure function
        cout << f[i] << " ";
    cout << endl;
    
    int pos = KMP(0, p, 10, t, 18, f); // perform the KMP algorithm using p and t
    cout << pos << endl;               // output the located position
    cout << "--- Test object detection on a super large image" << endl;
    Detect(*img1, img2, &r, &c);                           // detect the subimage img2 (object) on the super large image img1
    cout << "object found at: " << r << ", " << c << endl; // display the location of the detected object
    
    return 0;
}