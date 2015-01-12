#ifndef CONVOLUTIONALNETWORK_H
#define CONVOLUTIONALNETWORK_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <QString>
#include <QDebug>
#include <math.h>


using namespace cv;
using namespace std;

class ConvolutionalNetwork
{
public:
    ConvolutionalNetwork();


    ///Layers

    vector<cv::Mat> weights;
    //capa 1
    vector<cv::Mat> layer1;
    vector<cv::Mat> weightsLayer1;
    vector<float> biasLayer1;


    //capa 2
    vector<cv::Mat> layer2;
    vector<vector<cv::Mat> > weightsLayer2;
    vector<float> biasLayer2;

    //capa 3
    vector<cv::Mat> layer3;
    vector<cv::Mat> weightsLayer3;
    vector<float> biasLayer3;

    //capa 4
    vector<cv::Mat> layer4;
    vector<cv::Mat> weightsLayer4;
    vector<float> biasLayer4;


    //Output layer
    vector<float> output;
    vector<vector<cv::Mat> > weightsOut;

    //derivates
    std::vector<float> outputDerivates;
    vector<cv::Mat> derivatesLayer1;
    vector<cv::Mat> derivatesLayer2;
    vector<cv::Mat> derivatesLayer3;
    vector<cv::Mat> derivatesLayer4;






    ///Methods
    //void setConvolutionNetwork(int numberFeatureMaps1,int NeuronsFeatureMaps1,int numberFeatureMaps2,int NeuronsFeatureMaps2,int numberFeatureMaps3,int NeuronsFeatureMaps3,int numberFeatureMaps4,int NeuronsFeatureMaps4);
    void setConvolutionNetwork(cv::Mat inputImage, int numberFeatureMaps1, int numberFeatureMaps2, int numberFeatureMaps3,
                               int numberFeatureMaps4, int classes);
    int fowardPropagation(cv::Mat img_src);

    int backPropagation(int error, int classes, vector<int> outs,vector<cv::Mat> images);




};

#endif // CONVOLUTIONALNETWORK_H
