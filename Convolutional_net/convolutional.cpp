#include "convolutional.h"
#include "ui_convolutional.h"

Convolutional::Convolutional(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Convolutional)
{
    ui->setupUi(this);


     filename = "mnist/t10k-images-idx3-ubyte";
     path="/home/lex/4_Deus/1_algorithms/Convolutional_net/t10k-images.idx3-ubyte";
     number_of_images = 10000;
     image_size = 28 * 28;
}

Convolutional::~Convolutional()
{
    delete ui;
}



int ReverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int) ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}



void read_Mnist(QString filename, vector<cv::Mat> &vec){
    ifstream file (filename.toStdString().c_str(), ios::binary);

    if (file.is_open())
    {

         qDebug()<<"oe";
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        file.read((char*) &n_rows, sizeof(n_rows));
        n_rows = ReverseInt(n_rows);
        file.read((char*) &n_cols, sizeof(n_cols));
        n_cols = ReverseInt(n_cols);
        for(int i = 0; i < number_of_images; ++i)
        {
            cv::Mat tp = Mat::zeros(n_rows, n_cols, CV_8UC1);
            for(int r = 0; r < n_rows; ++r)
            {
                for(int c = 0; c < n_cols; ++c)
                {
                    unsigned char temp = 0;
                    file.read((char*) &temp, sizeof(temp));
                    tp.at<uchar>(r, c) = (int) temp;
                }
            }
            vec.push_back(tp);
        }
    }
}


void read_Mnist_Label(QString filename, vector<double> &vec)
{
    ifstream file (filename.toStdString().c_str(),ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        for(int i = 0; i < number_of_images; ++i)
        {
            unsigned char temp = 0;
            file.read((char*) &temp, sizeof(temp));
            vec[i]= (double)temp;
        }
    }
}
void Convolutional::on_pushButton_released()
{
    //read MNIST iamge into OpenCV Mat vector
    vector<cv::Mat> vec;

    read_Mnist(path, vec);

    qDebug()<<vec.size()<<endl;

    imshow("1st", vec[0]);
    cv::waitKey();
}
