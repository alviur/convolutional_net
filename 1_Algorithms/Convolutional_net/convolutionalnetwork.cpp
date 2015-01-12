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
                           int numberFeatureMaps4,int classes)
{


    cv::Mat featureSample1,featureSample2,featureSample3,featureSample4;
    featureSample1.create(inputImage.rows,inputImage.cols,CV_32F);

    for(int n=0;n<featureSample1.rows;n++)
    {
        for(int m=0;m<featureSample1.cols;m++)
        {
            featureSample1.at<float>(n,m)=0.0;

        }

    }





    featureSample2.create(inputImage.rows/2,inputImage.cols/2,CV_32F);

    for(int n=0;n<featureSample2.rows;n++)
    {
        for(int m=0;m<featureSample2.cols;m++)
        {
            featureSample2.at<float>(n,m)=0.0;

        }

    }
    featureSample3.create(inputImage.rows/4,inputImage.cols/4,CV_32F);
    featureSample4.create(inputImage.rows/8,inputImage.cols/8,CV_32F);

    output.assign(classes,0.0);


    //Set number of feature maps per layer

//    for(int i=0;i<numberFeatureMaps1;i++)
//    {
//        layer1.push_back(featureSample1);

//    }

    for(int i=0;i<numberFeatureMaps2;i++)
    {
        layer2.push_back(featureSample2);

    }

    layer1.assign(numberFeatureMaps1,featureSample1);//create a vector with numberFeatureMaps1 cv::Mat
    layer2.assign(numberFeatureMaps2,featureSample2);//create a vector with numberFeatureMaps1 cv::Mat
    layer3.assign(numberFeatureMaps3,featureSample3);//create a vector with numberFeatureMaps1 cv::Mat
    layer4.assign(numberFeatureMaps4,featureSample4);//create a vector with numberFeatureMaps1 cv::Mat


    //set weight fo each feature map
    cv::Mat weigtSample1,weightOut1;

    vector<cv::Mat>   weightOut;
    vector<cv::Mat>   weighLayer2;

    weigtSample1.create(5,5,CV_32F);
    weigtSample1.setTo(cv::Scalar(0));
    weightOut1.create(4,4,CV_32F);


    weightsLayer1.assign(numberFeatureMaps1,weigtSample1);
//    for(int i=0;i<numberFeatureMaps1;i++)
//    {
//        weightsLayer1.push_back(weigtSample1);
//    }



    for(int i=0;i<numberFeatureMaps2;i++)
    {
    weighLayer2.push_back(weigtSample1);
    }

    for(int i=0;i<numberFeatureMaps1;i++)
    {
    weightsLayer2.push_back(weighLayer2);
    }


    for(int i=0;i<numberFeatureMaps3;i++)
    {
    weightsLayer3.push_back(weigtSample1);
    }

    for(int i=0;i<numberFeatureMaps4;i++)
    {
    weightsLayer4.push_back(weigtSample1);
    }

    for(int i=0;i<numberFeatureMaps2;i++)
    {
    weightOut.push_back(weightOut1);
    }

    for(int i=0;i<classes;i++)
    {
    weightsOut.push_back(weightOut);
    }



}




/***************************************************************************************************
Method: fowardPropagation
Author: Alexander Gómez villa
Description: Evaluation algorithm

***************************************************************************************************/

int ConvolutionalNetwork::fowardPropagation(cv::Mat img_src)
{


    /// Layer 1

    for(int featureMap=0;featureMap<layer1.size();featureMap++)
     {

        for(int i=0;i<layer1[featureMap].rows;i++)
        {

            for(int j=0;j<layer1[featureMap].cols;j++)
            {
                if(i+weightsLayer1[0].rows-1<layer1[featureMap].rows && j+weightsLayer1[0].cols-1<layer1[featureMap].cols)
                {


                    if(i<5 && j<5)qDebug()<<"pesos"<<weightsLayer1[featureMap].at<float>(i,j);

                    //scan receptive field
                    for(int n=0;n<weightsLayer1[0].rows;n++)
                    {
                        for(int m=0;m<weightsLayer1[0].cols;m++)
                        {

                       ///qDebug()<<"pesos"<<weightsLayer1[featureMap].at<float>(n,m);
                        qDebug()<<"Neurons"<<layer1[featureMap].at<float>(i,j)<<" ";
                        ///qDebug()<<"Imagen"<<img_src.at<uchar>(i+n,j+m)*weightsLayer1[featureMap].at<float>(n,m);

//                            qDebug()<<layer1[featureMap].at<float>(i,j)<<" "<<img_src.at<uchar>(i+n,j+m)<<" "<<weightsLayer1[featureMap].at<float>(n,m);
                            layer1[featureMap].at<float>(i,j)+=img_src.at<uchar>(i+n,j+m)*weightsLayer1[featureMap].at<float>(n,m);

                        }
                    }

                    //Activation Function
                    layer1[featureMap].at<float>(i,j)=tanh(layer1[featureMap].at<float>(i,j))*255;
                   // qDebug()<<"Asigne valor!!"<<i<<j<< layer1[featureMap].rows<<layer1[featureMap].cols<<featureMap<<layer1.size();
                }

            }


        }

    }


    namedWindow("Layer 1",0);
    imshow("Layer 1", layer1[0]);



/// Layer 2

int featureMapL1=0;

    for(int featureMap=0;featureMap<layer2.size();featureMap++)
     {

            for(int i=0;i<layer2[featureMap].rows;i++)
            {

                for(int j=0;j<layer2[featureMap].cols;j++)
                {
                    if(i+3<layer1[featureMap].rows && j+3<layer1[featureMap].cols)
                    {



                        for(int n=0;n<weightsLayer2[featureMapL1][featureMap].rows;n++)
                        {

                            for(int m=0;m<weightsLayer2[featureMapL1][featureMap].cols;m++)
                            {


                                //qDebug()<<"Asigne valor 2!!"<<n<<m;

                                if(featureMapL1 +2<5){
                                layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*weightsLayer2[featureMapL1][featureMap].at<float>(n,m);
                                layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1+1].at<uchar>(i+n,j+m)*weightsLayer2[featureMapL1+1][featureMap].at<float>(n,m);
                                layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1+2].at<uchar>(i+n,j+m)*weightsLayer2[featureMapL1+2][featureMap].at<float>(n,m);

                                }

                                else if(featureMapL1+1<5)
                                {
                                    layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1-1].at<uchar>(i+n,j+m)*weightsLayer2[featureMapL1-1][featureMap].at<float>(n,m);

                                    layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*weightsLayer2[featureMapL1][featureMap].at<float>(n,m);
                                    layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1+1].at<uchar>(i+n,j+m)*weightsLayer2[featureMapL1+1][featureMap].at<float>(n,m);

                                }


                                else if(featureMapL1<5)
                                {

                                    layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1-2].at<uchar>(i+n,j+m)*weightsLayer2[featureMapL1-2][featureMap].at<float>(n,m);
                                    layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1-1].at<uchar>(i+n,j+m)*weightsLayer2[featureMapL1-1][featureMap].at<float>(n,m);

                                    layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*weightsLayer2[featureMapL1][featureMap].at<float>(n,m);

                                }



                            }
                        }

                        layer2[featureMap].at<float>(i,j)=tanh(layer2[featureMap].at<float>(i,j))*255;
                        qDebug()<<"Asigne valor 2!!"<<i<<j<< layer2[featureMap].rows<<layer2[featureMap].cols<<featureMap<<layer2.size();
                    }

                }


            }

            featureMapL1++;
            if(featureMapL1>4)featureMapL1=0;

    }


    namedWindow("Layer 2",0);
    imshow("Layer 2", layer2[0]);
    namedWindow("Layer 2.1",0);
    imshow("Layer 2.1", layer2[1]);


/// Layer 3

//    int featureMapL1=0;

//        for(int featureMap=0;featureMap<layer2.size();featureMap++)
//         {
//            for(int i=0;i<layer2[featureMap].rows;i++)
//            {

//                for(int j=0;j<layer2[featureMap].cols;j++)
//                {
//                    if(i+3<layer1[featureMap].rows && j+3<layer1[featureMap].cols)
//                    {



//                        for(int n=0;n<layer1[featureMapL1].rows;n++)
//                        {
//                            for(int m=0;m<layer1[featureMapL1].cols;m++)
//                            {
//                                n+=2;
//                                m+=2;

//                                //qDebug()<<"Asigne valor 2!!"<<n<<m;

//                                if(featureMapL1 +2<5){
//                                layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);
//                                layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1+1].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);
//                                layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1+2].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);

//                                }

//                                else if(featureMapL1+1<5)
//                                {
//                                    layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);
//                                    layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);

//                                }


//                                else if(featureMapL1<5)
//                                {
//                                    layer2[featureMap].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*weightsLayer2[featureMap].at<float>(i+n,j+m);

//                                }

//                                featureMapL1++;
//                                if(featureMapL1>4)featureMapL1=0;

//                            }
//                        }

//                        layer2[featureMap].at<float>(i,j)=tanh(layer2[featureMap].at<float>(i,j))*255;
//                        qDebug()<<"Asigne valor 2!!"<<i<<j<< layer2[featureMap].rows<<layer2[featureMap].cols<<featureMap<<layer2.size();
//                    }

//                }


//            }

//        }



        /// Output Layer


        for(int c=0;c<output.size();c++)
        {

            for(int f=0;f<layer2.size();f++)
            {

                for(int i=0;i<layer2[f].rows;i++)
                {
                    for(int j=0;j<layer2[f].cols;j++)
                    {
                        output[c]+=pow((layer2[f].at<float>(i,j))-weightsOut[c][f].at<float>(i,j),2);


                    }

                }

            }


        }





}


/***************************************************************************************************
Method: BackPropagation
Author: Alexander Gómez villa
Description: Training algorithm

***************************************************************************************************/
int ConvolutionalNetwork::backPropagation(int error,int classes,std::vector<int> outs,vector<cv::Mat> images)
{

    int iterError=2;
    int imgCounter=0;
    outputDerivates.assign(classes,0);
    while(iterError>error && imgCounter<images.size())
    {

        //calculate foward propagation
        ConvolutionalNetwork::fowardPropagation(images[imgCounter]);
        imgCounter++;


        //calculate output derivate
        for(int i=0;i<outputDerivates.size();i++)
        {
            if(i==outs[imgCounter]) outputDerivates[i]=(1-output[i])*(1-output[i])*output[i];
            else outputDerivates[i]=(-output[i])*(1-output[i])*output[i];

        }

        //New output weights


        for(int c=0;c<output.size();c++)
        {


            for(int f=0;f<layer2.size();f++)
            {


                for(int i=0;i<layer2[f].rows;i++)
                {
                    for(int j=0;j<layer2[f].cols;j++)
                    {
                        weightsOut[c][f].at<float>(i,j)=(weightsOut[c][f].at<float>(i,j)+outputDerivates[c]*(layer2[f].at<float>(i,j)));

                    }

                }

            }


        }



        //second layer derivate calculus

        for(int f=0;f<layer2.size();f++)
        {


            for(int i=0;i<layer2[f].rows;i++)
            {
                for(int j=0;j<layer2[f].cols;j++)
                {
                    for(int c=0;c<classes;c++)

                    {

                        derivatesLayer2[f].at<float>(i,j)+=outputDerivates[c]*weightsOut[c][f].at<float>(i,j);

                    }

                    derivatesLayer2[f].at<float>(i,j)=derivatesLayer2[f].at<float>(i,j)*layer2[f].at<float>(i,j);

                }
            }




        }
     //Second layer New weights


        int featureMapL1=0;

            for(int featureMap=0;featureMap<layer2.size();featureMap++)
             {

                    for(int i=0;i<weightsLayer2[featureMap][0].rows;i++)
                    {

                        for(int j=0;j<weightsLayer2[featureMap][0].cols;j++)
                        {
                            if(i+3<layer1[featureMap].rows && j+3<layer1[featureMap].cols)
                            {



                                for(int n=0;n<layer1[featureMapL1].rows;n++)
                                {

                                    n+=2;
                                    for(int m=0;m<layer1[featureMapL1].cols;m++)
                                    {

                                        m+=2;


                                        //qDebug()<<"Asigne valor 2!!"<<n<<m;

                                        if(featureMapL1 +2<5){
                                        weightsLayer2[featureMap][featureMapL1].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*derivatesLayer2[featureMap].at<float>(i,j);
                                        weightsLayer2[featureMap][featureMapL1+1].at<float>(i,j)+=layer1[featureMapL1+1].at<uchar>(i+n,j+m)*derivatesLayer2[featureMap].at<float>(i,j);
                                        weightsLayer2[featureMap][featureMapL1+2].at<float>(i,j)+=layer1[featureMapL1+2].at<uchar>(i+n,j+m)*derivatesLayer2[featureMap].at<float>(i,j);

                                        }

                                        else if(featureMapL1+1<5)
                                        {
                                            weightsLayer2[featureMap][featureMapL1].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*derivatesLayer2[featureMap].at<float>(i,j);
                                            weightsLayer2[featureMap][featureMapL1+1].at<float>(i,j)+=layer1[featureMapL1+1].at<uchar>(i+n,j+m)*derivatesLayer2[featureMap].at<float>(i,j);
                                            weightsLayer2[featureMap][featureMapL1-1].at<float>(i,j)+=layer1[featureMapL1-1].at<uchar>(i+n,j+m)*derivatesLayer2[featureMap].at<float>(i,j);

                                        }


                                        else if(featureMapL1<5)
                                        {

                                            weightsLayer2[featureMap][featureMapL1].at<float>(i,j)+=layer1[featureMapL1].at<uchar>(i+n,j+m)*derivatesLayer2[featureMap].at<float>(i,j);
                                            weightsLayer2[featureMap][featureMapL1-1].at<float>(i,j)+=layer1[featureMapL1-1].at<uchar>(i+n,j+m)*derivatesLayer2[featureMap].at<float>(i,j);
                                            weightsLayer2[featureMap][featureMapL1-2].at<float>(i,j)+=layer1[featureMapL1-2].at<uchar>(i+n,j+m)*derivatesLayer2[featureMap].at<float>(i,j);

                                        }

                                        featureMapL1++;
                                        if(featureMapL1>4)featureMapL1=0;

                                    }
                                }

                                qDebug()<<"Asigne valor 2!!"<<i<<j<< layer2[featureMap].rows<<layer2[featureMap].cols<<featureMap<<layer2.size();
                            }

                        }


                    }



            }




      //First Layer derivates


             featureMapL1=0;

                for(int featureMap=0;featureMap<layer2.size();featureMap++)
                 {

                        for(int i=0;i<weightsLayer2[featureMap][0].rows;i++)
                        {

                            for(int j=0;j<weightsLayer2[featureMap][0].cols;j++)
                            {
                                if(i+3<layer1[featureMap].rows && j+3<layer1[featureMap].cols)
                                {



                                    for(int n=0;n<layer1[featureMapL1].rows;n++)
                                    {

                                        n+=2;
                                        for(int m=0;m<layer1[featureMapL1].cols;m++)
                                        {

                                            m+=2;


                                            //qDebug()<<"Asigne valor 2!!"<<n<<m;

                                            if(featureMapL1 +2<5){

                                                derivatesLayer1[featureMap].at<float>(i,j)+= weightsLayer2[featureMap][featureMapL1].at<float>(i,j)*derivatesLayer2[featureMap].at<float>(i,j)*(layer1[featureMapL1].at<uchar>(i+n,j+m)*(1-layer1[featureMapL1].at<uchar>(i+n,j+m)));
                                                derivatesLayer1[featureMap].at<float>(i,j)+= weightsLayer2[featureMap][featureMapL1+1].at<float>(i,j)*derivatesLayer2[featureMap].at<float>(i,j)*(layer1[featureMapL1+1].at<uchar>(i+n,j+m)*(1-layer1[featureMapL1+1].at<uchar>(i+n,j+m)));
                                                derivatesLayer1[featureMap].at<float>(i,j)+= weightsLayer2[featureMap][featureMapL1+2].at<float>(i,j)*derivatesLayer2[featureMap].at<float>(i,j)*(layer1[featureMapL1+2].at<uchar>(i+n,j+m)*(1-layer1[featureMapL1+2].at<uchar>(i+n,j+m)));

                                            }

                                            else if(featureMapL1+1<5)
                                            {
                                                derivatesLayer1[featureMap].at<float>(i,j)+= weightsLayer2[featureMap][featureMapL1].at<float>(i,j)*derivatesLayer2[featureMap].at<float>(i,j)*(layer1[featureMapL1].at<uchar>(i+n,j+m)*(1-layer1[featureMapL1].at<uchar>(i+n,j+m)));
                                                derivatesLayer1[featureMap].at<float>(i,j)+= weightsLayer2[featureMap][featureMapL1+1].at<float>(i,j)*derivatesLayer2[featureMap].at<float>(i,j)*(layer1[featureMapL1+1].at<uchar>(i+n,j+m)*(1-layer1[featureMapL1+1].at<uchar>(i+n,j+m)));
                                                derivatesLayer1[featureMap].at<float>(i,j)+= weightsLayer2[featureMap][featureMapL1-1].at<float>(i,j)*derivatesLayer2[featureMap].at<float>(i,j)*(layer1[featureMapL1-1].at<uchar>(i+n,j+m)*(1-layer1[featureMapL1-1].at<uchar>(i+n,j+m)));

                                            }


                                            else if(featureMapL1<5)
                                            {

                                                derivatesLayer1[featureMap].at<float>(i,j)+= weightsLayer2[featureMap][featureMapL1].at<float>(i,j)*derivatesLayer2[featureMap].at<float>(i,j)*(layer1[featureMapL1].at<uchar>(i+n,j+m)*(1-layer1[featureMapL1].at<uchar>(i+n,j+m)));
                                                derivatesLayer1[featureMap].at<float>(i,j)+= weightsLayer2[featureMap][featureMapL1-1].at<float>(i,j)*derivatesLayer2[featureMap].at<float>(i,j)*(layer1[featureMapL1-1].at<uchar>(i+n,j+m)*(1-layer1[featureMapL1-1].at<uchar>(i+n,j+m)));
                                                derivatesLayer1[featureMap].at<float>(i,j)+= weightsLayer2[featureMap][featureMapL1-2].at<float>(i,j)*derivatesLayer2[featureMap].at<float>(i,j)*(layer1[featureMapL1-2].at<uchar>(i+n,j+m)*(1-layer1[featureMapL1-2].at<uchar>(i+n,j+m)));

                                            }


                                            featureMapL1++;
                                            if(featureMapL1>4)featureMapL1=0;
                                        }

                                    }



                                    qDebug()<<"Asigne valor 2!!"<<i<<j<< layer2[featureMap].rows<<layer2[featureMap].cols<<featureMap<<layer2.size();
                                }

                            }


                        }



                }




     //First layer new weights

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
                                        weightsLayer1[featureMap].at<float>(n,m)+=images[imgCounter].at<uchar>(i+n,j+m)*derivatesLayer1[featureMap].at<float>(i,j);

                                    }
                                }

                            }

                        }


                    }

                }



    }
}
