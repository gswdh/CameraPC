#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

ftdi ft;

void CamSetReg(int reg, int value);
void CamInit();
void CamTakePic();

// Image settings
const int image_y_res = 480;
const int image_x_res = 640;
unsigned long image_res = image_x_res * image_y_res;

int 		sub_smple_mode = 0,
            gain = 16,
            int_time = 10,
            delay_reg = 0;

vector<unsigned char> buffer(image_res);
vector<unsigned char> raw(65536);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    char name[] = {"GSW1G8LTV"};

    if(ft.Connect(name) == 0)
        CamInit();

    else
        cout << "Cannot connect" << endl;
}

MainWindow::~MainWindow()
{
    delete ui;

    ft.Disconnect();
}

void MainWindow::on_pushButton_takepic_clicked()
{
    CamTakePic();

    QPixmap img = QPixmap::fromImage(
        QImage(
            (unsigned char *) buffer.data(),
            image_y_res,
            image_x_res,
            QImage::Format_Grayscale8
        )
    );

    ui->label_imgprv->setPixmap(img);


}

void CamSetReg(int reg, int value)
{
    FTDIData cont_data;
    cont_data.buff_len = 2;

    cont_data.buffer[0] = (reg << 4) + ((value >> 8) & 0x0f);
    cont_data.buffer[1] = (value & 0xff);

    ft.Write(cont_data);
}

void CamInit()
{
    // Sequencer
    //CamSetReg(0, 0);

    // Y resolution (must be half required)
    CamSetReg(1, ((image_y_res / 2) - 1));

    // X resolution
    CamSetReg(2, (image_x_res - 1));

    // Integration time in sys clocks
    CamSetReg(3, int_time);

    // Sequencer delays
    CamSetReg(4, delay_reg + 2);

    // X reg start position
    CamSetReg(5, 0);

    // Y reg start position
    CamSetReg(6, 0);

    // Subsampling reg
    CamSetReg(7, (sub_smple_mode << 2) + (sub_smple_mode << 5));

    // Amplifier reg
    CamSetReg(8, gain);

    // DAC course offset
    CamSetReg(9, 115);

    // DAC fine offset
    CamSetReg(10, 110);

    // DAC black level
    CamSetReg(11, 0);

    // ADC register
    //CamSetReg(12, 2048);
}

void CamTakePic()
{
    ft.Purge();

    CamSetReg(13, 1);
    CamSetReg(13, 0);

    // Local variables
    int nbytes = 0;
    unsigned long pix_cnt = 0;
    int timeout = 0;

    while(pix_cnt != image_res)
    {
        Sleep(1);

        nbytes = ft.Read(raw.data());

        if(nbytes == 0)
        {
            if(timeout == 1000)
            {
                timeout = 0;
                break;
            }

            else timeout++;
        }

        else timeout = 0;


        //for(unsigned long j = 0; j < raw.buff_len; j++)
            //buffer[j + pix_cnt] = raw.buffer[j];


        buffer.insert(buffer.begin() + pix_cnt, raw.begin(), raw.begin() + nbytes);

        //buffer = buffer + (pix_cnt * sizeof(char));

        pix_cnt += nbytes;

        //cout << pix_cnt << endl;
    }
}
