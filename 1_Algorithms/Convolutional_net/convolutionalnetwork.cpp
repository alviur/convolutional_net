#include "convolutionalnetwork.h"

ConvolutionalNetwork::ConvolutionalNetwork()
{
}



/***************************************************************************************************
Method: setConvolutionNetwork
Author: Alexander Gómez villa
Description: Configure topology of the net

***************************************************************************************************/


void ConvolutionalNetwork::setConvolutionNetwork(cv::Mat inputImage,int numberFeatureMaps1,int numberFeatureMaps2,int numberFeatureMaps3,
                           int numberFeatureMaps4)
{


    cv::Mat featureSample1,featureSample2,featureSample3,featureSample4;
    featureSample1.create(inputImage.rows,inputImage.cols,0);
    featureSample2.create(inputImage.rows/2,inputImage.cols/2,0);
    featureSample3.create(inputImage.rows/4,inputImage.cols/4,0);
    featureSample4.create(inputImage.rows/8,inputImage.cols/8,0);

    //Set number of feature maps per layer

    for(int i=0;i<numberFeatureMaps1;i++)
    {
        layer1.push_back(featureSample1);

    }

    for(int i=0;i<numberFeatureMaps2;i++)
    {
        layer2.push_back(featureSample2);

    }

    //layer1.assign(numberFeatureMaps1,featureSample1);//create a vector with numberFeatureMaps1 cv::Mat
    //layer2.assign(numberFeatureMaps2,featureSample2);//create a vector with numberFeatureMaps1 cv::Mat
    layer3.assign(numberFeatureMaps3,featureSample3);//create a vector with numberFeatureMaps1 cv::Mat
    layer4.assign(numberFeatureMaps4,featureSample4);//create a vector with numberFeatureMaps1 cv::Mat


    //set weight fo each feature map
    cv::Mat weigtSample1;

    weigtSample1.create(5,5,CV_32F);


    for(int i=0;i<numberFeatureMaps1;i++)
    {
        weightsLayer1.push_back(weigtSample1);
        weightsLayer2.push_back(weigtSample1);
        weightsLayer3.push_back(weigtSample1);
        weightsLayer4.push_back(weigtSample1);
    }



    for(int i=0;i<numberFeatureMaps2;i++)
    {
    weightsLayer2.push_back(weigtSample1);
    }

    for(int i=0;i<numberFeatureMaps3;i++)
    {
    weightsLayer3.push_back(weigtSample1);
    }

    for(int i=0;i<numberFeatureMaps4;i++)
    {
    weightsLayer4.push_back(weigtSample1);
    }



}




/***************************************************************************************************
Method: fowardPropagation
Author: Alexander Gómez villa
Description:

***************************************************************************************************/

int ConvolutionalNetwork::fowardPropagation(cv::Mat img_src)
{



    //Layer 1

    for(int featureMap=0;featureMap<layer1.size();featureMap++)
     {
        for(int i=0;i<layer1[featureMap].rows;i++)
        {

            for(int j=0;j<layer1[featureMap].cols;j++)
            {
                if(i+1<layer1[featureMap].rows && j+1<layer1[featureMap].cols)
                {

                    for(int n=0;n<weightsLayer1[0].rows;n++)
                    {
                        for(int m=0;m<weightsLayer1[0].cols;m++)
                        {
                            layer1[featureMap].at<float>(i,j)+=img_src.at<uchar>(i+n,j+m)*weightsLayer1[featureMap].at<float>(i+n,j+m);

                        }
                    }

                    layer1[featureMap].at<float>(i,j)=tanh(layer1[featureMap].at<float>(i,j))*255;
                    qDebug()<<"Asigne valor!!"<<i<<j<< layer1[featureMap].rows<<layer1[featureMap].cols<<featureMap<<layer1.size();
                }

            }


        }

    }


    namedWindow("Layer 1",0);
    imshow("Layer 1", layer1[0]);



    //Layer 2

int featureMapL1=0;

    for(int featureMap=0;featureMap<layer2.size();featureMap++)
     {
        for(int i=0;i<layer2[featureMap].rows;i++)
        {

            for(int j=0;j<layer2[featureMap].cols;j++)
            {
                if(i+3<layer1[featureMap].rows && j+3<layer1[featureMap].cols)
                {



                    for(int n=0;n<layer1[featureMapL1].rows;n++)
                    {
                        for(int m=0;m<layer1[featureMapL1].cols;m++)
                        {
                            n+=2;
                            m+=2;

                            //qDebug()<<"Asigne valor 2!!"<<n<<m;

                            if(featureMapL1 +2<5){
                            layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);
                            layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1+1].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);
                            layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1+2].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);

                            }

                            else if(featureMapL1+1<5)
                            {
                                layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);
                                layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);

                            }


                            else if(featureMapL1<5)
                            {
                                layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);

                            }

                            featureMapL1++;
                            if(featureMapL1>4)featureMapL1=0;

                        }
                    }

                    layer2[featureMap].at<float>(i,j)=tanh(layer2[featureMap].at<float>(i,j))*255;
                    qDebug()<<"Asigne valor 2!!"<<i<<j<< layer2[featureMap].rows<<layer2[featureMap].cols<<featureMap<<layer2.size();
                }

            }


        }

    }


    namedWindow("Layer 2",0);
    imshow("Layer 2", layer2[0]);
    namedWindow("Layer 2.1",0);
    imshow("Layer 2.1", layer2[1]);


     //Layer 3



}
