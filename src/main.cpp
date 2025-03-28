#include <iostream>
#include <opencv2/opencv.hpp>
#include "../headers/dogFilter.hpp"

using namespace cv;

//Callback functions used to update the filter parameters based on the sliders
void onSigmaChange(int pos, void* data){

    DogFilter* filter = static_cast<DogFilter*>(data);
    filter->setSigma(pos);  
    Mat output;
    filter->applyFilter(output);
    cv::imshow("DoG Filter", output);
}

void onKChange(int pos, void* data) {
    DogFilter* filter = static_cast<DogFilter*>(data);
    filter->setK(pos);    
    Mat output;
    filter->applyFilter(output);
    imshow("DoG Filter", output);
}

void onPChange(int pos, void* data) {
    DogFilter* filter = static_cast<DogFilter*>(data);
    filter->setP(pos);
    Mat output;
    filter->applyFilter(output);
    imshow("DoG Filter", output);
}

void onEpsilonChange(int pos, void* data) {
    DogFilter* filter = static_cast<DogFilter*>(data);
    filter->setEpsilon(pos);
    Mat output;
    filter->applyFilter(output);
    imshow("DoG Filter", output);
}

void onPhiChange(int pos, void* data) {
    DogFilter* filter = static_cast<DogFilter*>(data);
    filter->setPhi(pos);
    Mat output;
    filter->applyFilter(output);
    imshow("DoG Filter", output);
}



int main(){

    //Type your source image path below
    std::string path = "../examples/Stanczyk.jpg";
    Mat input = cv::imread(path);
    if (input.empty())
    {
        std::cerr << "Fail to reach the image path, get the right path and try again." << std::endl;
        return -1;
    }

    // true for colored blending with the filter, false for grayscale application of the filter
    DogFilter filter(input, true);

    namedWindow("DoG Filter", WINDOW_AUTOSIZE);

    //All trackbar values are divided by 100 for more granular control
    createTrackbar("Sigma", "DoG Filter", nullptr, 5000, onSigmaChange, &filter);
    createTrackbar("K", "DoG Filter", nullptr, 5000, onKChange, &filter);
    createTrackbar("P", "DoG Filter", nullptr, 5000, onPChange, &filter);
    createTrackbar("Phi", "DoG Filter", nullptr, 5000, onPhiChange, &filter);
    createTrackbar("Epsilon", "DoG Filter", nullptr, 50000, onEpsilonChange, &filter);

    setTrackbarPos("Sigma", "DoG Filter", 1);
    setTrackbarPos("K", "DoG Filter", 1);
    setTrackbarPos("P", "DoG Filter", 1);
    setTrackbarPos("Phi", "DoG Filter", 1);
    setTrackbarPos("Epsilon", "DoG Filter", 1);

    Mat output;
    filter.applyFilter(output);
    imshow("DoG Filter", output);

    //press any button on the keyboard to quit
    waitKey(0);

    return 0;
}