
#include <iostream>
#include <string>
#include <vector>
#include "Image_Class.h"
#include <cstdlib>
#include <random>
#include <cmath>

using namespace std;

bool isValidFormat(const string& filename) {
    vector<string> validExtensions = { ".jpg", ".jpeg", ".png", ".bmp" };
    size_t dotPos = filename.find_last_of(".");
    if (dotPos != string::npos) {
        string ext = filename.substr(dotPos);
        for (const string& validExt : validExtensions) {
            if (ext == validExt) {
                return true;
            }
        }
    }
    return false;
}

//  Grayscale_Conversion function
void Grayscale_Conversion(Image& image) {



    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;

            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg = avg / 3;

            image.setPixel(i, j, 0, avg);
            image.setPixel(i, j, 1, avg);
            image.setPixel(i, j, 2, avg);
        }
    }

}

void  Flip_Image(Image& pic)
{


    int width = pic.width;
    int height = pic.height;
    string choice;
    cout << "1) Horizontal flib\n2) Virtecal flib: \n";
    while (true)
    {


        cin >> choice;
        if (choice == "1") {
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width / 2; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        int fliped = pic(j, i, k);
                        pic(j, i, k) = pic(width - 1 - j, i, k);
                        pic(width - 1 - j, i, k) = fliped;
                    }
                }
            }
            break;
        }

        else if (choice == "2")
        {
            for (int i = 0; i < height / 2; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        int fliped = pic(j, i, k);
                        pic(j, i, k) = pic(j, height - 1 - i, k);
                        pic(j, height - 1 - i, k) = fliped;
                    }
                }
            }
            break;

        }
        else {
            cout << "Please enter 1 for horizontal flip or 2 for vertical flip: ";
            continue;
        }
    }



}

//  Invert_Image function
void Invert_Image(Image& image) {





    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {  // Assuming 3 channels (RGB)
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }

}



void black_white(Image& pic)
{


    for (int i = 0; i < pic.width; i++)
    {
        for (int j = 0; j < pic.height; j++)
        {
            int avg = 0;
            for (int k = 0; k < 3; k++)
            {
                avg += pic(i, j, k);

            }
            avg = avg / 3;
            if (avg > 127)
            {
                for (int k = 0; k < 3; k++)
                {
                    pic(i, j, k) = 255;
                }
            }
            else if (avg <= 127)
            {
                for (int k = 0; k < 3; k++)
                {
                    pic(i, j, k) = 0;
                }

            }
        }
    }

}


void darkenImage(Image& image)
{

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int currentVal = image(i, j, k);
                int newValue = currentVal / 2; // Darken each channel by half
                image.setPixel(i, j, k, newValue);
            }
        }
    }
}

void lightenImage(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int currentVal = image(i, j, k);
                int newValue = min(255, currentVal + 50); // Increase brightness by adding 50
                image.setPixel(i, j, k, newValue);
            }
        }
    }
}

void Darken_and_Lighten(Image& image)
{



    int choice;
    while (true)
    {
        string choice;
        cout << "1) Darken your photo\n";
        cout << "2) Lighten your photo\n=> ";
        cin >> choice;


        if (choice == "1") {
            darkenImage(image);
            break;
        }
        else if (choice == "2") {
            lightenImage(image);
            break;
        }
        else {
            cout << "Invalid choice.\n";
            continue;


        }
    }



}



void  Crop_Images(Image& pic)
{

    int x, y;
    cout << "Enter the starting point (upper left corner of the part to keep)" << endl;
    cout << "x , y " << endl;
    cin >> x >> y;
    while (true)
    {
        if (cin.fail())
        {
            cout << "enter  valid start points." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> x >> y;
        }
        else if (x > pic.width || y > pic.height)
        {
            cout << "enter start points smaller than image dimensions" << endl;
            cin >> x >> y;
        }
        else
        {
            break;
        }

    }

    int w, h;
    cout << "Enter the dimensions of the new image\n";
    cout << "width , hight ";
    cin >> w >> h;
    while (true)
    {

        if (cin.fail())
        {
            cout << "enter  valid dimenstions." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> w >> h;
        }
        else if ((w + x > pic.width) || (h + y > pic.height))
        {
            cout << "enter  valid dimenstions. " << endl;
            cin >> x >> y;
        }
        else
        {
            break;
        }
    }

    Image croped(w, h);



    for (int i = 0; i < w; ++i)
    {

        for (int j = 0; j < h; ++j)
        {

            croped(i, j, 0) = pic(i + x, j + y, 0);
            croped(i, j, 1) = pic(i + x, j + y, 1);
            croped(i, j, 2) = pic(i + x, j + y, 2);

        }
    }
    pic = croped;




}


void Resizing_Images(Image& pic)
{

    double oldW = pic.width;
    double oldH = pic.height;
    int newW, newH;
    cout << "enter the dimentions of the new image\n";
    cout << "width , hight ";
    cin >> newW >> newH;
    while (true)
    {

        if (cin.fail())
        {
            cout << "enter valid dimenstions." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> newW >> newH;
        }
        else
        {
            break;
        }

    }
    Image  resized(newW, newH);
    for (float i = 0; i < newW; i++)
    {
        for (float j = 0; j < newH; j++)
        {
            resized(i, j, 0) = round(pic(i * (oldW / newW), j * (oldH / newH), 0));
            resized(i, j, 1) = round(pic(i * (oldW / newW), j * (oldH / newH), 1));
            resized(i, j, 2) = round(pic(i * (oldW / newW), j * (oldH / newH), 2));

        }
    }
    pic = resized;




}




void processImage(Image& image) {

    // Convert image to black and white
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int avg = 0;
            for (int k = 0; k < image.channels; k++) {
                avg += image.getPixel(i, j, k);
            }
            avg /= image.channels; // Divide by the number of channels
            if (avg > 127) {
                for (int k = 0; k < image.channels; k++) {
                    image.setPixel(i, j, k, 0); // Set as black
                }
            }
            else {
                for (int k = 0; k < image.channels; k++) {
                    image.setPixel(i, j, k, 255); // Set as white
                }
            }
        }
    }

    // Sobel operator for edge detection
    Image result(image.width, image.height);
    // Sobel kernels
    int kernelX[3][3] = { {-1, 0, 1},
                          {-2, 0, 2},
                          {-1, 0, 1} };
    int kernelY[3][3] = { {-1, -2, -1},
                          {0,  0,  0},
                          {1,  2,  1} };

    // Convolve image with the Sobel kernels
    for (int y = 1; y < image.height - 1; ++y) {
        for (int x = 1; x < image.width - 1; ++x) {
            int sumX = 0, sumY = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        // Apply the Sobel operator on each channel
                        sumX += image.getPixel(x + i, y + j, k) * kernelX[i + 1][j + 1];
                        sumY += image.getPixel(x + i, y + j, k) * kernelY[i + 1][j + 1];
                    }
                }
            }
            // Calculate magnitude of the gradient
            int magnitude = abs(sumX) + abs(sumY);
            // Assign the magnitude to all channels of the result image
            result.setPixel(x, y, 0, magnitude);
            result.setPixel(x, y, 1, magnitude);
            result.setPixel(x, y, 2, magnitude);
        }
    }

    // Invert colors (make background white and lines black)
    for (int i = 0; i < result.width; i++) {
        for (int j = 0; j < result.height; j++) {
            for (int k = 0; k < result.channels; k++) {
                // Invert the pixel value
                result.setPixel(i, j, k, 255 - result.getPixel(i, j, k));
            }
        }
    }
    image = result;

}





void Merge_Images(Image& image1, Image& image2) {


    // Get the dimensions of both images
    int width1 = image1.width;
    int height1 = image1.height;
    int width2 = image2.width;
    int height2 = image2.height;

    // Determine the smaller dimensions
    int newWidth = min(width1, width2);
    int newHeight = min(height1, height2);
    Image mergedImage(newWidth, newHeight);
    cout << "Choose if you want the final photo resized or cropped:\n";

    while (true)
    {
        string choice;

        cout << "1. Resized\n";
        cout << "2. Cropped\n";
        cin >> choice;




        if (choice == "1") {
            // Resize the images
            float scaleX1 = static_cast<float>(width1) / newWidth;
            float scaleY1 = static_cast<float>(height1) / newHeight;
            float scaleX2 = static_cast<float>(width2) / newWidth;
            float scaleY2 = static_cast<float>(height2) / newHeight;

            // Merge the resized images
            for (int y = 0; y < newHeight; ++y) {
                for (int x = 0; x < newWidth; ++x) {
                    for (int c = 0; c < 3; ++c) { // Assuming RGB channels
                        int originalX1 = static_cast<int>(x * scaleX1);
                        int originalY1 = static_cast<int>(y * scaleY1);
                        int originalX2 = static_cast<int>(x * scaleX2);
                        int originalY2 = static_cast<int>(y * scaleY2);
                        int pixelValue1 = image1.getPixel(originalX1, originalY1, c);
                        int pixelValue2 = image2.getPixel(originalX2, originalY2, c);
                        int mergedPixelValue = (pixelValue1 + pixelValue2) / 2;
                        mergedImage.setPixel(x, y, c, mergedPixelValue);
                    }
                }
            }
            image1 = mergedImage;
            break;
        }
        else if (choice == "2") {
            // Crop the images
            int startX1 = (width1 - newWidth) / 2;
            int startY1 = (height1 - newHeight) / 2;
            int startX2 = (width2 - newWidth) / 2;
            int startY2 = (height2 - newHeight) / 2;

            // Merge the cropped images
            for (int y = 0; y < newHeight; ++y) {
                for (int x = 0; x < newWidth; ++x) {
                    for (int c = 0; c < 3; ++c) { // Assuming RGB channels
                        int pixelValue1 = image1.getPixel(startX1 + x, startY1 + y, c);
                        int pixelValue2 = image2.getPixel(startX2 + x, startY2 + y, c);
                        int mergedPixelValue = (pixelValue1 + pixelValue2) / 2;
                        mergedImage.setPixel(x, y, c, mergedPixelValue);

                    }
                }
            }
            image1 = mergedImage;
            break;
        }

        else {
            cout << "Invalid choice.\n";
            continue;

        }
    }
}



void addframe(Image& image)
{


    int width = image.width;
    int height = image.height;
    int frameSizeX = width * 0.01;
    int frameSizeY = height * 0.01;
    cout << "Enter frame type (simple or fancy): " << endl;
    while (true) {
        cout << "1) simple\n2) fancy" << endl << "=> ";
        string choice;
        cin >> choice;


        if (choice == "1")
        {
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    if (i < frameSizeX || i >= width - frameSizeX || j < frameSizeY || j >= height - frameSizeY)
                    {
                        image(i, j, 0) = 255;
                        image(i, j, 1) = 255;
                        image(i, j, 2) = 255;
                    }
                }
            }
            break;
        }
        else if (choice == "2")
        {
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    if (i < frameSizeX || i >= width - frameSizeX || j < frameSizeY || j >= height - frameSizeY)
                    {
                        double wave = sin(0.1 * i) * sin(0.1 * j);
                        int red = 255 * (wave + 1) / 2;
                        int green = 255 * (1 - wave) / 2;
                        image(i, j, 0) = red;
                        image(i, j, 1) = green;
                        image(i, j, 2) = 255; // Blue
                    }
                }
            }
            break;
        }
        else {
            cout << "Enter a valid frame type (simple or fancy)" << endl;
            continue;
        }
    }


}




void Rotate_Image(Image& image)
{
    cout << "Enter rotation degree (90, 180, or 270): " << endl;
    while (true)
    {
        cout << "=> ";
        string degree;

        cin >> degree;
        if (degree == "180")
        {

            int width = image.width;
            int height = image.height;

            Image rotated(width, height);
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    rotated(width - 1 - j, height - 1 - i, 0) = image(j, i, 0);
                    rotated(width - 1 - j, height - 1 - i, 1) = image(j, i, 1);
                    rotated(width - 1 - j, height - 1 - i, 2) = image(j, i, 2);
                }
            }
            image = rotated;


            break;
        }
        else if (degree == "270")
        {

            int width = image.width;
            int height = image.height;

            Image rotated(height, width);
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    rotated(j, width - 1 - i, 0) = image(i, j, 0);
                    rotated(j, width - 1 - i, 1) = image(i, j, 1);
                    rotated(j, width - 1 - i, 2) = image(i, j, 2);
                }
            }
            image = rotated;
            break;
        }
        else if (degree == "90")
        {

            int width = image.width;
            int height = image.height;
            Image rotated(height, width);

            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    rotated(height - 1 - j, i, 0) = image(i, j, 0);
                    rotated(height - 1 - j, i, 1) = image(i, j, 1);
                    rotated(height - 1 - j, i, 2) = image(i, j, 2);
                }
            }
            image = rotated;

            break;
        }
        else
        {
            cout << "Invalid degree. Please enter 90, 180, or 270." << endl;
            continue;
        }
    }
}

void Blur_Image(Image& image) {
    int width = image.width;
    int height = image.height;

    // Create a temporary image to hold the blurred result
    Image blurredImg(width, height);

    // Apply a 7x7 box filter
    auto applyBlur = [&](int x, int y) {
        int sum_r = 0, sum_g = 0, sum_b = 0;
        int count = 0;

        // Apply a 7x7 box filter
        for (int i = max(0, x - 3); i <= min(width - 1, x + 3); i++) {
            for (int j = max(0, y - 3); j <= min(height - 1, y + 3); j++) {
                sum_r += image(i, j, 0);
                sum_g += image(i, j, 1);
                sum_b += image(i, j, 2);
                count++;
            }
        }

        int avg_r = sum_r / count;
        int avg_g = sum_g / count;
        int avg_b = sum_b / count;

        avg_r = min(max(avg_r, 0), 255);
        avg_g = min(max(avg_g, 0), 255);
        avg_b = min(max(avg_b, 0), 255);

        blurredImg(x, y, 0) = avg_r;
        blurredImg(x, y, 1) = avg_g;
        blurredImg(x, y, 2) = avg_b;
        };

    // Apply blur to each pixel
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            applyBlur(i, j);
        }
    }

    // Update the original image with the blurred version
    image = blurredImg;
}

void addSunlight(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int red = image.getPixel(i, j, 0);
            int green = image.getPixel(i, j, 1);
            int blue = image.getPixel(i, j, 2);

            blue = max(0, blue - 50); // Reduce intensity of blue for warmth

            // Update pixel values
            image.setPixel(i, j, 0, red);
            image.setPixel(i, j, 1, green);
            image.setPixel(i, j, 2, blue);
        }
    }
}

void applyOldTVFilter(Image& image) {
    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(30, 50);
    uniform_int_distribution<int> disOffset(0, 5);

    // Get image dimensions
    int width = image.width;
    int height = image.height;

    // Loop through each pixel in the image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int red = image.getPixel(x, y, 0);
            int green = image.getPixel(x, y, 1);
            int blue = image.getPixel(x, y, 2);

            // Add random number from 30 to 50 to every pixel for vertical lines
            int offset = dis(gen);
            red += offset;
            green += offset;
            blue += offset;

            // Divide by 1.5
            red = max(0, min(255, static_cast<int>(red / 1.5)));
            green = max(0, min(255, static_cast<int>(green / 1.5)));
            blue = max(0, min(255, static_cast<int>(blue / 1.5)));

            // Add or subtract random number from 0 to 5 based on row parity
            if (y % 2 == 0) { // Even row
                int subtract = disOffset(gen);
                red = max(0, red - subtract);
                green = max(0, green - subtract);
                blue = max(0, blue - subtract);
            }
            else { // Odd row
                int add = disOffset(gen);
                red = min(255, red + add);
                green = min(255, green + add);
                blue = min(255, blue + add);
            }

            // Set pixel color
            image.setPixel(x, y, 0, red);
            image.setPixel(x, y, 1, green);
            image.setPixel(x, y, 2, blue);
        }
    }
}


void makePurple(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int red = image.getPixel(i, j, 0);
            int green = image.getPixel(i, j, 1);
            int blue = image.getPixel(i, j, 2);

            // Increase intensity of blue and red channel
            blue = min(255, blue + 30);
            red = min(255, red + 30);

            // Decrease intensity of green channel
            green = max(0, green - 30);

            // Update pixel values
            image.setPixel(i, j, 0, red);
            image.setPixel(i, j, 1, green);
            image.setPixel(i, j, 2, blue);
        }
    }
}

int main() {                                      //    getline()  does not work from the second loop  //
                                                  // so if the image contain in its name a space => delete the space//
    string filename;
    Image pic;
    while (true)
    {
        try {
            cout << "Enter the filename to work on. This becomes the current image. " << endl << "=> ";
            getline(cin , filename);
            pic.loadNewImage(filename);
            break;


        }
        catch (...) {

        }
    }




    while (true) {
        cout << "1) Load a new image\n";
        cout << "2) Grayscale Conversion" << endl;
        cout << "3) Black & White" << endl;
        cout << "4) Invert Image" << endl;
        cout << "5) Merge Images " << endl;
        cout << "6) Flip Image" << endl;
        cout << "7) Rotate Image" << endl;
        cout << "8) Darken and Lighten image" << endl;
        cout << "9) Crop Images" << endl;
        cout << "10) Adding a Frame to the Picture" << endl;
        cout << "11) Detect Image Edges" << endl;
        cout << "12) Resizing Images" << endl;
        cout << "13) Blur Images" << endl;
        cout << "14) natural sunlight" << endl;
        cout << "15) TV images" << endl;
        cout << "16) purple" << endl;
        cout << "17) Save the image" << endl;
        cout << "18) EXIT" << endl;

        string choice;
        cin >> choice;

        if (choice == "18") {
            cout << "Do you want to save the current image before exit." << endl;
            while (true) {
                string choice;

                cout << "1) YES\n2) NO\n=> ";
                cin >> choice;
                if (choice == "1") {
                    pic.saveImage(filename);
                    cout << "DONE." << endl;
                    system(filename.c_str());
                    break;

                }
                else if (choice == "2") {
                    break;

                }
                else {
                    cout << "Enter a valid choice." << endl;
                    continue;
                }

            }
            cout << "thank u for using our babyphotoshop";

            break;
        }
        if (choice == "1") {
            cout << "Do you want to save the current image before loading a new one." << endl;
            while (true) {
                string choice;

                cout << "1) YES\n2) NO\n=> ";
                cin >> choice;
                if (choice == "1") {
                    pic.saveImage(filename);
                    cout << "DONE." << endl;
                    system(filename.c_str());
                    break;

                }
                else if (choice == "2") {
                    break;

                }
                else {
                    cout << "Enter a valid choice." << endl;
                    continue;
                }

            }
            while (true)
            {
                try {
                    cout << "Enter the new filename to work on. " << endl << "=> ";
                    cin >> filename;
                    pic.loadNewImage(filename);
                    break;


                }
                catch (...) {

                }
            }
        }

        else if (choice == "2") {
            Grayscale_Conversion(pic);
        }
        else if (choice == "3") {
            black_white(pic);          // dn
        }
        else if (choice == "4") {
            Invert_Image(pic);        //dn
        }
        else if (choice == "5") {
            string filename2;
            Image image2;
            while (true)
            {
                try {
                    cout << "Enter the filename of the second image. " << endl << "=> ";
                    cin >> filename2;
                    image2.loadNewImage(filename2);
                    break;


                }
                catch (...) {

                }
            }
            Merge_Images(pic, image2);
        }
        else if (choice == "6") {
            Flip_Image(pic);             //dn
        }
        else if (choice == "7") {
            Rotate_Image(pic);

        }
        else if (choice == "8") {
            Darken_and_Lighten(pic);
        }

        else if (choice == "9")
        {
            Crop_Images(pic);
        }
        else if (choice == "10") {
            addframe(pic);

        }
        else if (choice == "11") {
            processImage(pic);
        }
        else if (choice == "12") {
            Resizing_Images(pic);

        }
        else if (choice == "13") {
            Blur_Image(pic);

        }
        else if (choice == "14") {
            addSunlight(pic);
        }
        else if (choice == "15") {
            applyOldTVFilter(pic);

        }
        else if (choice == "16") {
            makePurple(pic);
        }
        else if (choice == "17") {

            while (true)
            {
                cout << "Do you want to save on the same file or change file name.\n";
                cout << "1) same file\n2) change file name" << endl << "=> ";
                string choice;
                cin >> choice;
                if (choice == "1") {
                    pic.saveImage(filename);
                    cout << "Image saved successfully." << endl;
                    system(filename.c_str()); // Show photo after processing
                    break;

                }
                else if (choice == "2") {

                    while (true)
                    {


                        string newname;
                        cout << "Enter the new file name.\n=> ";
                        cin >> newname;
                        if (!isValidFormat(newname)) {
                            cout << "Invalid file format. Please provide a valid photo format (.jpg, .jpeg, .png, .bmp)." << endl;
                            continue;
                        }

                        else
                        {
                            pic.saveImage(newname);
                            cout << "Image saved successfully." << endl;
                            system(newname.c_str()); // Show photo after processing
                            break;

                        }
                    }
                    break;
                }
                else {
                    cout << "Enter a valid choice, ";
                    continue;
                }
            }

        }
        else {
            cout << "Invalid Input" << endl;
        }
    }


}
//    getline()  does not work from the second loop  //
                                                 // so if the image contain in its name a space => delete the space//