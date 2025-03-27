#ifndef DOG_FILTER_HPP
#define DOG_FILTER_HPP

#include <opencv2/opencv.hpp>

class DogFilter{

private:

    cv::Mat image;
    double sigma, k, p, phi, epsilon;
    bool masking;

    cv::Mat computeDog();
    cv::Mat threshold(const cv::Mat& dog, bool useMask);
    cv::Mat computeTanh(const cv::Mat& term);
    void prepareOut(const cv::Mat& threshold, cv::Mat& out);

public:

    DogFilter(const cv::Mat& input, bool flag);
    void applyFilter(cv::Mat& out);
    void setSigma(int pos);
    void setK(int pos);
    void setP(int pos);
    void setPhi(int pos);
    void setEpsilon(int pos);
    void setMasking(bool useMask);
    bool getMasking();

    ~DogFilter();
};

#endif