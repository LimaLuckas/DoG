#include "../headers/dogFilter.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;


Mat DogFilter::computeDog(){

    // Computing the math for the Difference of Gaussians
    // Get the grayscale of the original image and confert to float32

    Mat input32f;
    cvtColor(image, input32f, COLOR_BGR2GRAY);
    input32f.convertTo(input32f, CV_32F);

    //Get the Gaussian blurs: one with standard deviation sigma
    //Another with deviation sigma*k
    Mat g1, g2;
    cv::GaussianBlur(input32f, g1, Size(), sigma);
    cv::GaussianBlur(input32f, g2, Size(), sigma * k);

    // return an weighted difference of gaussians
    return (1 + p) * g1 - p * g2;

}

Mat DogFilter::threshold(const Mat& dog, bool useMask){

    //Do a nonlinear tanh thresholding of the DoG image 
    //Set the x term for the tanh function

    Mat term = phi * (dog - epsilon);
    Mat tanhMat = computeTanh(term);

    //Make a mask and compare if the DoG blurred image luminance is lower than epsilon 
    //If it is, the luminance position in the mask will be 255, otherwise, 0
    //Convert to 32float and normalize to [0,1]

    Mat mask;
    cv::compare(dog, epsilon, mask, CMP_LT);
    mask.convertTo(mask, CV_32F, 1.0/255);
        
    //Sum element-wise a ones matrix with the mask multiplied element-wise to the tanh for thresholding
    //If you're adding a new soft thresholding, certify that operates between [-1,0] to modify the values in the threshold
    Mat thresholded = Mat::ones(dog.size(), CV_32F) + mask.mul(tanhMat);

    if (useMask) {
            
        //If useMask is true, the DoG blurred grayscaled image will be multiplied to the original colored image as a mask
        //First, the grayscale will be converted to three channels in order to be multiplied

        Mat threeChannelGray;
        cvtColor(thresholded, threeChannelGray, COLOR_GRAY2BGR);

        //Get the colored image and convert to 32float
        //normalize as well

        Mat original32f;
        image.convertTo(original32f, CV_32F, 1.0/255);
        //original32f /= 255.0;                 
            
        //multiply the original with the three channel grayscale element-wise

        thresholded = original32f.mul(threeChannelGray);
    }
    
    return thresholded;
}

//This is just one of many function implementations to apply thresholding, you can make your own and substitute!
Mat DogFilter::computeTanh(const Mat& term){
        
    //computation of the tanh function
    Mat twoTerm = 2 * term;
    Mat expTwoTerm;
    cv::exp(twoTerm, expTwoTerm);
        
    return (expTwoTerm - 1) / (expTwoTerm + 1);
}

void DogFilter::prepareOut(const Mat& thresholded, Mat& out){

    //Normalize the image and put the result on the output
    cv::normalize(thresholded, out, 0, 255, NORM_MINMAX, CV_8U);
}

//constructor
DogFilter::DogFilter(const Mat& input, bool flag) : image(input.clone()){
    sigma = 1.0;
    p = 0.0;
    k = 1.0;
    phi = 1.0;
    epsilon = 1.0;
    masking = flag;
}


void DogFilter::applyFilter(Mat& out){

    Mat dog = computeDog();

    Mat thresholded = threshold(dog, masking);

    prepareOut(thresholded, out);

}

void DogFilter::setSigma(int pos) {sigma = std::max(static_cast<double>(pos)/100.0, 0.01);}
void DogFilter::setK(int pos) {k = std::max(static_cast<double>(pos)/100.0, 0.01);}
void DogFilter::setP(int pos) {p = static_cast<double>(pos)/100.0;}
void DogFilter::setPhi(int pos) {phi = static_cast<double>(pos)/100.0;}
void DogFilter::setEpsilon(int pos) {epsilon = static_cast<double>(pos)/100.0;}
void DogFilter::setMasking(bool useMask) {masking = useMask;}
bool DogFilter::getMasking() { return masking;}

DogFilter::~DogFilter(){}