#ifndef CONVOLUTIONAL_H
#define CONVOLUTIONAL_H

#include <QMainWindow>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <QString>
#include <QDebug>
#include <fstream>
#include "convolutionalnetwork.h"


using namespace cv;
using namespace std;

namespace Ui {
class Convolutional;
}

class Convolutional : public QMainWindow
{
    Q_OBJECT

public:
    explicit Convolutional(QWidget *parent = 0);
    ~Convolutional();


   string filename ;
   int number_of_images ;
   int image_size;
   QString path;
   ConvolutionalNetwork net;//convolutional object
   vector<cv::Mat> vec;//images




private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

private:
    Ui::Convolutional *ui;
};

#endif // CONVOLUTIONAL_H
