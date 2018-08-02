#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDoubleValidator>
#include <string>
#include <iostream>
#include <iomanip>
#include <QDebug>
#include <cmath>
#include <math.h>
#include "mapping.h"
#include "help.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <QChar>

QStringList fieldsList;
int numFieldsGlob;
QStringList mappingStringList;
QString CSVText;
QString errorsFound;
QString headerString;
int fileOption;
int expectedNumFields;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDoubleValidator *dimensionValidator = new QDoubleValidator(0.000, 10000.000, 4);
    ui->lineEdit->setValidator(dimensionValidator);
    ui->lineEdit_3->setValidator(dimensionValidator);
    ui->lineEdit_4->setValidator(dimensionValidator);
    ui->lineEdit_5->setValidator(dimensionValidator);
    ui->lineEdit_8->setValidator(dimensionValidator);
    ui->lineEdit_9->setValidator(dimensionValidator);
    ui->lineEdit_10->setValidator(dimensionValidator);

    connect(ui->radioButton,SIGNAL(clicked()),this,SLOT(weight_selected()));
    connect(ui->radioButton_2,SIGNAL(clicked()),this,SLOT(length_selected()));

    connect(ui->pushButton,SIGNAL(released()),this,SLOT(convertUnit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(dimensionalWeight_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(girth_pressed()));

    //connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(unitConvertHelp_pressed()));
    //connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(dimCalcHelp_pressed()));
    //connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(girthCalcHelp_pressed()));

    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(button_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(button_pressed()));

    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(openFile_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(mapping_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(display_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(newFile_pressed()));
    connect(ui->pushButton_10,SIGNAL(released()),this,SLOT(help_pressed()));

    connect(ui->radioButton_45,SIGNAL(released()),this,SLOT(fileType_pressed()));
    connect(ui->radioButton_46,SIGNAL(released()),this,SLOT(fileType_pressed()));
    connect(ui->radioButton_47,SIGNAL(released()),this,SLOT(fileType_pressed()));
    connect(ui->radioButton_48,SIGNAL(released()),this,SLOT(fileType_pressed()));
    connect(ui->radioButton_49,SIGNAL(released()),this,SLOT(fileType_pressed()));

    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::weight_selected(){
    ui->radioButton_8->hide();
    ui->radioButton_9->hide();
    ui->radioButton_10->hide();
    ui->radioButton_11->hide();
    ui->radioButton_12->hide();

    ui->radioButton_3->show();
    ui->radioButton_4->show();
    ui->radioButton_5->show();
    ui->radioButton_6->show();
    ui->radioButton_7->show();

    ui->radioButton_18->hide();
    ui->radioButton_19->hide();
    ui->radioButton_20->hide();
    ui->radioButton_21->hide();
    ui->radioButton_22->hide();

    ui->radioButton_13->show();
    ui->radioButton_14->show();
    ui->radioButton_15->show();
    ui->radioButton_16->show();
    ui->radioButton_17->show();
}

void MainWindow::length_selected(){
    ui->radioButton_3->hide();
    ui->radioButton_4->hide();
    ui->radioButton_5->hide();
    ui->radioButton_6->hide();
    ui->radioButton_7->hide();

    ui->radioButton_8->show();
    ui->radioButton_9->show();
    ui->radioButton_10->show();
    ui->radioButton_11->show();
    ui->radioButton_12->show();

    ui->radioButton_13->hide();
    ui->radioButton_14->hide();
    ui->radioButton_15->hide();
    ui->radioButton_16->hide();
    ui->radioButton_17->hide();

    ui->radioButton_18->show();
    ui->radioButton_19->show();
    ui->radioButton_20->show();
    ui->radioButton_21->show();
    ui->radioButton_22->show();
}

void MainWindow::convertUnit_pressed()
{
    QPushButton * button = (QPushButton*)sender();

    QString newLabel;
    newLabel = button->text();

    double inputVal;
    QString inputString;
    inputString = ui->lineEdit->text();
    inputVal = inputString.toDouble();

    bool metricInput = true;
    bool metricOutput = true;
    double tempVal;

    QString inputUnits;
    QString outputUnits;

    if(ui->radioButton->isChecked()){ //weight and mass
        if(ui->radioButton_3->isChecked()){
            metricInput = false;
            tempVal = inputVal * 16;
            inputUnits = "Pounds";
        }
        if(ui->radioButton_4->isChecked()){
            metricInput = false;
            tempVal = inputVal;
            inputUnits = "Ounces";
        }
        if(ui->radioButton_5->isChecked()){
            metricInput = true;
            tempVal = inputVal * .001;
            inputUnits = "Milligrams";
        }
        if(ui->radioButton_6->isChecked()){
            metricInput = true;
            tempVal = inputVal;
            inputUnits = "Grams";
        }
        if(ui->radioButton_7->isChecked()){
            metricInput = true;
            tempVal = inputVal * 1000;
            inputUnits = "Kilograms";
        }
        if(ui->radioButton_13->isChecked() || ui->radioButton_14->isChecked()){
            metricOutput = false;
        }
        if(metricInput && !metricOutput){
            tempVal = tempVal * 0.03527396195;
        }
        if(!metricInput && metricOutput){
            tempVal = tempVal * 28.34952;
        }
        if(ui->radioButton_13->isChecked()){
            tempVal = tempVal / 16;
            outputUnits = "Pounds";
        }
        if(ui->radioButton_14->isChecked()){
            //tempVal = tempVal;
            outputUnits = "Ounces";
        }
        if(ui->radioButton_15->isChecked()){
            tempVal = tempVal * 1000;
            outputUnits = "Milligrams";
        }
        if(ui->radioButton_16->isChecked()){
            //tempVal = tempVal;
            outputUnits = "Grams";
        }
        if(ui->radioButton_17->isChecked()){
            tempVal = tempVal * .001;
            outputUnits = "Kilograms";
        }
    }
    if(ui->radioButton_2->isChecked()){ //length
        if(ui->radioButton_8->isChecked()){
            metricInput = false;
            tempVal = inputVal;
            inputUnits = "Inches";
        }
        if(ui->radioButton_9->isChecked()){
            metricInput = false;
            tempVal = inputVal * 12;
            inputUnits = "Feet";
        }
        if(ui->radioButton_10->isChecked()){
            metricInput = true;
            tempVal = inputVal * .1;
            inputUnits = "Millimeters";
        }
        if(ui->radioButton_11->isChecked()){
            metricInput = true;
            tempVal = inputVal;
            inputUnits = "Centimeters";
        }
        if(ui->radioButton_12->isChecked()){
            metricInput = true;
            tempVal = inputVal * 100;
            inputUnits = "Meters";
        }
        if(ui->radioButton_18->isChecked() || ui->radioButton_19->isChecked()){
            metricOutput = false;
        }
        if(metricInput && !metricOutput){
            tempVal = tempVal * .393701;
        }
        if(!metricInput && metricOutput){
            tempVal = tempVal * 2.54;
        }
        if(ui->radioButton_18->isChecked()){
            //tempVal = tempVal;
            outputUnits = "Inches";
        }
        if(ui->radioButton_19->isChecked()){
            tempVal = tempVal / 12;
            outputUnits = "Feet";
        }
        if(ui->radioButton_20->isChecked()){
            tempVal = tempVal * 10;
            outputUnits = "Millimeters";
        }
        if(ui->radioButton_21->isChecked()){
            //tempVal = tempVal;
            outputUnits = "Centimeters";
        }
        if(ui->radioButton_22->isChecked()){
            tempVal = tempVal / 100;
            outputUnits = "Meters";
        }
    }

    double outputVal = tempVal;
    QString outputString;
    outputString = QString::number(outputVal, 'g', 15); // format for output specified here
    ui->lineEdit_2->setText(outputString);

    ui->label_29->setText(inputUnits);
    ui->label_29->update();
    ui->label_29->repaint();

    ui->label_30->setText(outputUnits);
    ui->label_30->update();
    ui->label_30->repaint();
}

void MainWindow::dimensionalWeight_pressed(){
    QPushButton * button = (QPushButton*)sender();

    QString newLabel;
    newLabel = button->text();

    double length;
    double width;
    double height;

    QString lengthString;
    QString widthString;
    QString heightString;

    lengthString = ui->lineEdit_3->text();
    length = lengthString.toDouble();
    widthString = ui->lineEdit_4->text();
    width = widthString.toDouble();
    heightString = ui->lineEdit_5->text();
    height = heightString.toDouble();

    /*if(ui->radioButton_23->isChecked()){
        length = length;
        width = width;
        height = height;
    }*/
    if(ui->radioButton_24->isChecked()){
        length = length * 12;
        width = width * 12;
        height = height * 12;
    }
    if(ui->radioButton_25->isChecked()){
        length = length * 0.0393701;
        width = width * 0.0393701;
        height = height * 0.0393701;
    }
    if(ui->radioButton_26->isChecked()){
        length = length * 0.393701;
        width = width * 0.393701;
        height = height * 0.393701;
    }
    if(ui->radioButton_27->isChecked()){
        length = length * 39.3701;
        width = width * 39.3701;
        height = height * 39.3701;
    }

    // round length width height to nearest whole inch value
    length = (double)qRound(length);
    width = (double)qRound(width);
    height = (double)qRound(height);

    double dimDivisor;
    if(ui->radioButton_28->isChecked()){
        dimDivisor = 166;
    }
    if(ui->radioButton_29->isChecked()){
        dimDivisor = 194;
    }
    if(ui->radioButton_30->isChecked()){
        dimDivisor = 139;
    }
    if(ui->radioButton_31->isChecked()){
        dimDivisor = 139;
    }
    if(ui->radioButton_32->isChecked()){
        dimDivisor = 139;
    }
    if(ui->radioButton_43->isChecked()){
        dimDivisor = 139;
    }
    if(ui->radioButton_44->isChecked()){
        dimDivisor = 166;
    }

    double tempVal = (length * width * height) / dimDivisor;

    double outputValLbs = tempVal;
    double outputValKgs = tempVal * 0.453592;

    //qDebug() << outputValLbs << " " << outputValKgs;

    outputValLbs = ceil(outputValLbs);
    outputValKgs = ( qRound ( ( outputValKgs * 2 ) + 0.49999 ) / 2.0 );

    //qDebug() << outputValLbs << " " << outputValKgs;

    QString outputStringLbs;
    QString outputStringKgs;
    outputStringLbs = QString::number(outputValLbs, 'g');
    outputStringKgs = QString::number(outputValKgs, 'g');
    ui->lineEdit_6->setText(outputStringLbs);
    ui->lineEdit_7->setText(outputStringKgs);
}

void MainWindow::girth_pressed(){
    QPushButton * button = (QPushButton*)sender();

    QString newLabel;
    newLabel = button->text();

    double length;
    double width;
    double height;

    QString lengthString;
    QString widthString;
    QString heightString;

    lengthString = ui->lineEdit_8->text();
    length = lengthString.toDouble();
    widthString = ui->lineEdit_9->text();
    width = widthString.toDouble();
    heightString = ui->lineEdit_10->text();
    height = heightString.toDouble();

    QString equationUsed1;
    QString equationUsed2;
    double girthDim1;
    double girthDim2;
    if(height > length && height > width){
        equationUsed1 = "Height is the largest dimension";
        equationUsed2 = "Equation Used: Girth = ( 2 x Length ) + ( 2 x Width )";
        girthDim1 = length;
        girthDim2 = width;
    }
    else if(width > length && width > height){
        equationUsed1 = "Width is the largest dimension";
        equationUsed2 = "Equation Used: Girth = ( 2 x Length ) + ( 2 x Height )";
        girthDim1 = length;
        girthDim2 = height;
    }
    else{
        equationUsed1 = "Length is the largest dimension";
        equationUsed2 = "Equation Used: Girth = ( 2 x Width ) + ( 2 x Height )";
        girthDim1 = width;
        girthDim2 = height;
    }

    QString inputUnits;
    QString outputUnits;

    if(ui->radioButton_33->isChecked()){ // set input unit string and convert girthDim 1 and 2 to inches
        inputUnits = "Inches";
        //girthDim1 = girthDim1;
        //girthDim2 = girthDim2;
    }
    else if(ui->radioButton_34->isChecked()){
        inputUnits = "Feet";
        girthDim1 = girthDim1 * 12;
        girthDim2 = girthDim2 * 12;
    }
    else if(ui->radioButton_35->isChecked()){
        inputUnits = "Millimeters";
        girthDim1 = girthDim1 * 0.0393701;
        girthDim2 = girthDim2 * 0.0393701;
    }
    else if(ui->radioButton_36->isChecked()){
        inputUnits = "Centimeters";
        girthDim1 = girthDim1 * 0.393701;
        girthDim2 = girthDim2 * 0.393701;
    }
    else if(ui->radioButton_37->isChecked()){
        inputUnits = "Meters";
        girthDim1 = girthDim1 * 39.3701;
        girthDim2 = girthDim2 * 39.3701;
    }
    else{
        inputUnits = "Inches";
        //girthDim1 = girthDim1;
        //girthDim2 = girthDim2;
    }

    if(ui->radioButton_38->isChecked()){ // set input unit string and convert girthDim 1 and 2 to inches
        outputUnits = "Inches";
        //girthDim1 = girthDim1;
        //girthDim2 = girthDim2;
    }
    else if(ui->radioButton_39->isChecked()){
        outputUnits = "Feet";
        girthDim1 = girthDim1 / 12;
        girthDim2 = girthDim2 / 12;
    }
    else if(ui->radioButton_40->isChecked()){
        outputUnits = "Millimeters";
        girthDim1 = girthDim1 / 0.0393701;
        girthDim2 = girthDim2 / 0.0393701;
    }
    else if(ui->radioButton_41->isChecked()){
        outputUnits = "Centimeters";
        girthDim1 = girthDim1 / 0.393701;
        girthDim2 = girthDim2 / 0.393701;
    }
    else if(ui->radioButton_42->isChecked()){
        outputUnits = "Meters";
        girthDim1 = girthDim1 / 39.3701;
        girthDim2 = girthDim2 / 39.3701;
    }
    else{
        outputUnits = inputUnits;
        if(height > length && height > width){
            girthDim1 = length;
            girthDim2 = width;
        }
        else if(width > length && width > height){
            girthDim1 = length;
            girthDim2 = height;
        }
        else{
            girthDim1 = width;
            girthDim2 = height;
        }
    }

    double girth;
    girth = ( 2 * girthDim1 ) + ( 2 * girthDim2 );

    QString outputString;
    outputString = QString::number(girth, 'f', 5);

    ui->label_24->setText(equationUsed1);
    ui->label_24->update();
    ui->label_24->repaint();

    ui->label_25->setText(equationUsed2);
    ui->label_25->update();
    ui->label_25->repaint();

    ui->label_28->setText(outputUnits);
    ui->label_28->update();
    ui->label_28->repaint();

    ui->lineEdit_11->setText(outputString);
}

int *decToBinary(int num){
    int temp = num;
    static int bin[8];
    int val = 128;
    for(int i=0; i<8; ++i){
        if(temp < val){
            bin[i] = 0;
        }
        else{
            bin[i] = 1;
            temp -= val;
        }
        val = val / 2;
    }
    return bin;
}

int *b64ToBinary(int num){
    int temp = num;
    static int bin[6];
    int val = 32;
    for(int i=0; i<6; ++i){
        if(temp < val){
            bin[i] = 0;
        }
        else{
            bin[i] = 1;
            temp -= val;
        }
        val = val / 2;
    }
    return bin;
}

int binaryToVal(int *pattern, int startInd, int numBits){
    int temp = pow(2, (numBits - 1));
    int val = 0;
    for(int i=0; i<numBits; ++i){
        if(pattern[startInd + i] == 1) val += temp;
        temp = temp / 2;
    }
    return val;
}

int asciiValtoB64Val(int num)
{
    int newVal;
    switch(num){
        case 65: newVal = 0; break;
        case 66: newVal = 1; break;
        case 67: newVal = 2; break;
        case 68: newVal = 3; break;
        case 69: newVal = 4; break;
        case 70: newVal = 5; break;
        case 71: newVal = 6; break;
        case 72: newVal = 7; break;
        case 73: newVal = 8; break;
        case 74: newVal = 9; break;
        case 75: newVal = 10; break;
        case 76: newVal = 11; break;
        case 77: newVal = 12; break;
        case 78: newVal = 13; break;
        case 79: newVal = 14; break;
        case 80: newVal = 15; break;
        case 81: newVal = 16; break;
        case 82: newVal = 17; break;
        case 83: newVal = 18; break;
        case 84: newVal = 19; break;
        case 85: newVal = 20; break;
        case 86: newVal = 21; break;
        case 87: newVal = 22; break;
        case 88: newVal = 23; break;
        case 89: newVal = 24; break;
        case 90: newVal = 25; break;
        case 97: newVal = 26; break;
        case 98: newVal = 27; break;
        case 99: newVal = 28; break;
        case 100: newVal = 29; break;
        case 101: newVal = 30; break;
        case 102: newVal = 31; break;
        case 103: newVal = 32; break;
        case 104: newVal = 33; break;
        case 105: newVal = 34; break;
        case 106: newVal = 35; break;
        case 107: newVal = 36; break;
        case 108: newVal = 37; break;
        case 109: newVal = 38; break;
        case 110: newVal = 39; break;
        case 111: newVal = 40; break;
        case 112: newVal = 41; break;
        case 113: newVal = 42; break;
        case 114: newVal = 43; break;
        case 115: newVal = 44; break;
        case 116: newVal = 45; break;
        case 117: newVal = 46; break;
        case 118: newVal = 47; break;
        case 119: newVal = 48; break;
        case 120: newVal = 49; break;
        case 121: newVal = 50; break;
        case 122: newVal = 51; break;
        case 48: newVal = 52; break;
        case 49: newVal = 53; break;
        case 50: newVal = 54; break;
        case 51: newVal = 55; break;
        case 52: newVal = 56; break;
        case 53: newVal = 57; break;
        case 54: newVal = 58; break;
        case 55: newVal = 59; break;
        case 56: newVal = 60; break;
        case 57: newVal = 61; break;
        case 43: newVal = 62; break;
        case 47: newVal = 63; break;
    }
    return newVal;
}

int b64ValtoAsciiVal(int num)
{
    int newVal;
    switch(num){
        case 0: newVal = 65; break;
        case 1: newVal = 66; break;
        case 2: newVal = 67; break;
        case 3: newVal = 68; break;
        case 4: newVal = 69; break;
        case 5: newVal = 70; break;
        case 6: newVal = 71; break;
        case 7: newVal = 72; break;
        case 8: newVal = 73; break;
        case 9: newVal = 74; break;
        case 10: newVal = 75; break;
        case 11: newVal = 76; break;
        case 12: newVal = 77; break;
        case 13: newVal = 78; break;
        case 14: newVal = 79; break;
        case 15: newVal = 80; break;
        case 16: newVal = 81; break;
        case 17: newVal = 82; break;
        case 18: newVal = 83; break;
        case 19: newVal = 84; break;
        case 20: newVal = 85; break;
        case 21: newVal = 86; break;
        case 22: newVal = 87; break;
        case 23: newVal = 88; break;
        case 24: newVal = 89; break;
        case 25: newVal = 90; break;
        case 26: newVal = 97; break;
        case 27: newVal = 98; break;
        case 28: newVal = 99; break;
        case 29: newVal = 100; break;
        case 30: newVal = 101; break;
        case 31: newVal = 102; break;
        case 32: newVal = 103; break;
        case 33: newVal = 104; break;
        case 34: newVal = 105; break;
        case 35: newVal = 106; break;
        case 36: newVal = 107; break;
        case 37: newVal = 108; break;
        case 38: newVal = 109; break;
        case 39: newVal = 110; break;
        case 40: newVal = 111; break;
        case 41: newVal = 112; break;
        case 42: newVal = 113; break;
        case 43: newVal = 114; break;
        case 44: newVal = 115; break;
        case 45: newVal = 116; break;
        case 46: newVal = 117; break;
        case 47: newVal = 118; break;
        case 48: newVal = 119; break;
        case 49: newVal = 120; break;
        case 50: newVal = 121; break;
        case 51: newVal = 122; break;
        case 52: newVal = 48; break;
        case 53: newVal = 49; break;
        case 54: newVal = 50; break;
        case 55: newVal = 51; break;
        case 56: newVal = 52; break;
        case 57: newVal = 53; break;
        case 58: newVal = 54; break;
        case 59: newVal = 55; break;
        case 60: newVal = 56; break;
        case 61: newVal = 57; break;
        case 62: newVal = 43; break;
        case 63: newVal = 47; break;
    }
    return newVal;
}

void MainWindow::button_pressed()
{
    QPushButton * button = (QPushButton*)sender();

    QString newLabel;
    newLabel = button->text();

    QString inputBox;
    QString inputBoxTemp; // testing for removing = at the end
    inputBoxTemp = ui->textEditIn->toPlainText();

    bool encode;
    int trace = 0;
    if(newLabel == "Encode"){
        encode = true;
        while(inputBoxTemp[trace]!='\0'){
            inputBox[trace] = inputBoxTemp[trace];
            ++trace;
        }
    }
    else{
        bool stopLoop = true;
        encode = false;
        while(stopLoop){
            if(inputBoxTemp[trace]=='\0' || inputBoxTemp[trace]=='='){stopLoop = false;}
            if(stopLoop){inputBox[trace] = inputBoxTemp[trace];}
            ++trace;
        }
    }

    // find length of input
    int inputLength = 0;
    for(int i=0; inputBox[i]!='\0'; ++i){
        ++inputLength;
    }
    // padding length
    int paddingLen = 0;
    int totalNumBits = 0;
    int numCharsOut = 0;
    int bitsPerCharOut = 0;
    int bitsPerCharIn = 0;
    if(encode){
        if(inputLength % 3 == 2) paddingLen = 8;
        if(inputLength % 3 == 1) paddingLen = 16;
        totalNumBits = (8 * inputLength) + paddingLen;
        numCharsOut = totalNumBits / 6;
        bitsPerCharOut = 6;
        bitsPerCharIn = 8;
    }
    else{
        if(inputLength % 4 == 3) paddingLen = 6;
        if(inputLength % 4 == 2) paddingLen = 12;
        if(inputLength % 4 == 1) paddingLen = 18;
        totalNumBits = (6 * inputLength) + paddingLen;
        numCharsOut = totalNumBits / 8;
        bitsPerCharOut = 8;
        bitsPerCharIn = 6;
    }

    // create binary pattern
    int binaryPattern[totalNumBits];
    int count = 0;
    int charVal = 0;
    QChar newChar;
    for(int i=0; inputBox[i]!='\0'; ++i){
        newChar = inputBox[i];
        if(encode){charVal = newChar.toLatin1();}
        else{
            charVal = newChar.toLatin1();
            charVal = asciiValtoB64Val(charVal);
        }
        int *p;
        if(encode){p = decToBinary(charVal);}
        else{p = b64ToBinary(charVal);}

        for(int i=0; i<bitsPerCharIn; ++i){
            binaryPattern[count] = *(p+i);
            ++count;
        }
    }

    // adding 0's for padding
    for(int i=0; i<paddingLen; ++i){
        binaryPattern[count] = 0;
        ++count;
    }

    // creating new values from binary pattern
    int tempVal = 0;
    int newVals[numCharsOut];
    for(int i=0; i<numCharsOut; ++i){
        tempVal = binaryToVal(binaryPattern, i*bitsPerCharOut, bitsPerCharOut);
        newVals[i] = tempVal;
    }

    QString newChars;
    for(int i=0; i<numCharsOut; ++i){
        if(encode){newChars[i] = b64ValtoAsciiVal(newVals[i]);}
        else{
            if(newVals[i] == 0){newChars[i] = ' ';}
            else{newChars[i] = newVals[i];}
        }
    }
    if(encode){
        if(paddingLen / 8 == 2){
            newChars[numCharsOut - 1] = '=';
            newChars[numCharsOut - 2] = '=';
        }
        if(paddingLen / 8 == 1){
            newChars[numCharsOut - 1] = '=';
        }
    }

    ui->label_34->setText(newLabel + "d:");
    ui->label_34->update();
    ui->label_34->repaint();

    ui->textEditOut->setText(newChars);
    ui->textEditOut->setLineWrapMode(QTextEdit::WidgetWidth);
    ui->textEditOut->update();
    ui->textEditOut->repaint();
}

void MainWindow::fileType_pressed(){
    ui->pushButton_6->show();
}

void MainWindow::openFile_pressed()
{
    QString file_name = "";
    while(file_name.isEmpty()){
        file_name = QFileDialog::getOpenFileName(this, "Open a file", "C://");
    }
    // QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "C://");
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        close();
        QMessageBox::warning(this, "title", "improper file selected exiting program");
    }

    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);
    CSVText = text;

    int numLines = 0;
    for(int i = 0; text[i]!='\0'; ++i){
        //qDebug() << text[i];
        if(text[i]=='\xa' || text[i]=='\x0' || text[i]=='\n'){
            ++numLines;
        }
    }
    qDebug() << "Number of lines" << numLines;

    qDebug() << "Good here 1";

    QStringList list;
    QString line;
    int numFields = 0;
    for(int i = 0; text[i]!='\xa' && text[i]!='\x0' && text[i]!='\n'; ++i){
        qDebug() << text[i];
        line = line + text[i];
        if(text[i]==','){
            ++numFields; //couting number of columns
        }
    }

    qDebug() << "Good here 2";

    numFieldsGlob = numFields + 1;

    headerString = line;
    fieldsList = line.split(",");
    // ui->plainTextEdit->setPlainText(headerString);

    qDebug() << fieldsList[0];

    file.close();

    if(ui->radioButton_45->isChecked()){ // if order (mapping) display mapping button
        ui->pushButton_7->show();
        fileOption = 1; //orders
        expectedNumFields = -1;
    }
    else{ // if any other file type show display validation results button
        ui->pushButton_8->show();
    }
    if(ui->radioButton_46->isChecked()){
        fileOption = 2; //customers
        expectedNumFields = 13;
    }
    if(ui->radioButton_47->isChecked()){
        fileOption = 3; //products
        expectedNumFields = 24;
    }
    if(ui->radioButton_48->isChecked()){
        fileOption = 4; //jet products
        expectedNumFields = 29;
    }
    if(ui->radioButton_49->isChecked()){
        fileOption = 5; //inventory
        expectedNumFields = 9;
    }

    ui->radioButton_45->hide();
    ui->radioButton_46->hide();
    ui->radioButton_47->hide();
    ui->radioButton_48->hide();
    ui->radioButton_49->hide();

    // reset errors found string
    errorsFound = "";

    qDebug() << "Good here 1";

    QString temptext;
    if(numLines == 0){
        temptext = "Error: try uploading the file into Excel, downloading again as a CSV File and selecting the newly downloaded CSV File when running this application";
        ui->plainTextEdit->setPlainText(temptext);
    }
}

void MainWindow::mapping_pressed()
{
    Mapping dia;
    dia.performMapping(fieldsList, numFieldsGlob, this);
    dia.setModal(true);
    dia.exec();
}

void MainWindow::submitMapping(QStringList mappingInfo)
{
    mappingStringList = mappingInfo;
    QString mappingString;

    for(int i=0; i<mappingStringList.size(); ++i){
        qDebug() << mappingStringList[i];
    }

    int count = 0;
    for(int i = 0; CSVText[i]!='\xa' && CSVText[i]!='\x0'; ++i){
        ++count;
    }
    ++count;

    int row = 0;
    bool endOF = false;
    bool fieldError = false;
    int lineLength;
    QString currentLine;
    QStringList currentLineList;
    QString strCharsMap;
    QString expectedHeaders = "";

    // checking for proper headers
    if(expectedNumFields>0){
        if(expectedNumFields != numFieldsGlob){
            endOF = true;
            errorsFound = errorsFound + "The CSV File selected does not have the proper number of headers for the selected file type" + '\xa';
        }
        else{
            if(numFieldsGlob == 13){
                expectedHeaders = "Full Name,First Name,Last Name,Company Name,Phone Number,Email Address,Username,Address Line 1,Address Line 2,City,State,Postal Code,Country Code";
                if(headerString.size() != expectedHeaders.size()){
                    endOF = true;
                    errorsFound = errorsFound + "The CSV File selected does not contain the proper headers for a Customer Import CSV File" + '\xa';
                }
                else{
                    for(int i=0; i<headerString.size(); ++i){
                        if(expectedHeaders[i].toLower() != headerString[i].toLower()){
                            endOF = true;
                            i = headerString.size();
                            errorsFound = errorsFound + "The CSV File selected does not contain the proper headers for a Customer Import CSV File" + '\xa';
                        }
                    }
                }
            }
            if(numFieldsGlob == 24){
                expectedHeaders = "SKU,Name,WarehouseLocation,WeightOz,Category,Tag1,Tag2,Tag3,Tag4,Tag5,CustomsDescription,CustomsValue,CustomsTariffNo,CustomsCountry,ThumbnailUrl,UPC,FillSKU,Length,Width,Height,UseProductName,Active,ParentSKU,IsReturnable";
                if(headerString.size() != expectedHeaders.size()){
                    endOF = true;
                    errorsFound = errorsFound + "The CSV File selected does not contain the proper headers for a Product Import CSV File" + '\xa';
                }
                else{
                    for(int i=0; i<headerString.size(); ++i){
                        if(expectedHeaders[i].toLower() != headerString[i].toLower()){
                            endOF = true;
                            i = headerString.size();
                            errorsFound = errorsFound + "The CSV File selected does not contain the proper headers for a Product Import CSV File" + '\xa';
                        }
                    }
                }
            }
            if(numFieldsGlob == 29){
                expectedHeaders = "SKU,Name,WarehouseLocation,WeightOz,Category,Tag1,Tag2,Tag3,Tag4,Tag5,CustomsDescription,CustomsValue,CustomsTariffNo,CustomsCountry,ThumbnailUrl,UPC,FillSKU,Length,Width,Height,UseProductName,Active,ParentSKU,Description,JetBrand,JetPrice,JetMultiPackQuantity,JetCategory,JetInventoryOverride";
                if(headerString.size() != expectedHeaders.size()){
                    endOF = true;
                    errorsFound = errorsFound + "The CSV File selected does not contain the proper headers for a Jet Product Import CSV File" + '\xa';
                }
                else{
                    for(int i=0; i<headerString.size(); ++i){
                        if(expectedHeaders[i].toLower() != headerString[i].toLower()){
                            endOF = true;
                            i = headerString.size();
                            errorsFound = errorsFound + "The CSV File selected does not contain the proper headers for a Jet Product Import CSV File" + '\xa';
                        }
                    }
                }
            }
            if(numFieldsGlob == 9){
                expectedHeaders = "SKU,ProductName,Loc1,Loc2,Loc3,Loc4,Stock,ReorderThreshold,Cost";
                if(headerString.size() != expectedHeaders.size()){
                    endOF = true;
                    errorsFound = errorsFound + "The CSV File selected does not contain the proper headers for a Inventory Import CSV File" + '\xa';
                }
                else{
                    for(int i=0; i<headerString.size(); ++i){
                        if(expectedHeaders[i].toLower() != headerString[i].toLower()){
                            endOF = true;
                            i = headerString.size();
                            errorsFound = errorsFound + "The CSV File selected does not contain the proper headers for a Inventory Import CSV File" + '\xa';
                        }
                    }
                }
            }
        }
    }


    // for checking fields inside of quotation marks " "
    // fields inside quotion marks can contain commas , which would throw off .split(",");
    bool lineEnd = false;
    bool insideQuote = false;
    while( !endOF ){
        lineEnd = false;
        currentLine = "";

        while( !lineEnd ){
            if(!insideQuote && CSVText[count]=='"' && (CSVText[count-1]==',' || CSVText[count-1]=='\xa' || CSVText[count-1]=='\x0')){
                insideQuote = true;
                qDebug() << "Entering Quotes";
            }
            if(insideQuote && CSVText[count]=='"' && (CSVText[count+1]==',' || CSVText[count+1]=='\xa' || CSVText[count+1]=='\x0' || CSVText[count+1]=='\0')){
                insideQuote = false;
                qDebug() << "Exiting Quotes";
            }
            if(!insideQuote && (CSVText[count]=='\xa' || CSVText[count]=='\x0' || CSVText[count]=='\0')){
                lineEnd = true;
            }
            else{
                currentLine = currentLine + CSVText[count];
                ++count;
            }
        }
        ++count;
        qDebug() << currentLine;
        if(currentLine==""){
            endOF = true;
        }
        else{
            // validate the line based on mapping

            /*
             need to check for fields containging commas ,
             in fields inside of quotation marks " "
            */
            lineLength = 0;
            for(int i=0; currentLine[i]!='\0'; ++i){
                ++lineLength;
            }

            // start of the validation for quoted fields

            bool eofQuote = false;
            int quoteStart = 0;
            int quoteEnd = 0;
            int numQuotedFields = 0;
            int fieldTrack = 0;
            int quoteStartIndexes[numFieldsGlob];
            int quoteEndIndexes[numFieldsGlob];
            for(int i=0; i<lineLength; ++i){
                eofQuote = false;
                quoteStart = 0;
                quoteEnd = 0;

                //qDebug() << "1";

                if( (i==0 && currentLine[i]=='"') || (i!=0 && currentLine[i]=='"' && currentLine[i-1]==',' && currentLine[i+1]!='\0') ){ // if first field is in " ", possibly contains commas
                    quoteStart = i;
                    fieldTrack = i;
                    while(!eofQuote){
                        if(currentLine[fieldTrack]=='\0'){
                            eofQuote = true;
                        }
                        if(currentLine[fieldTrack]=='"' && currentLine[fieldTrack+1]==','){
                            eofQuote = true;
                            quoteEnd = fieldTrack;
                            ++numQuotedFields;
                            i = fieldTrack + 1;
                        }
                        if(currentLine[fieldTrack]=='"' && currentLine[fieldTrack+1]=='\0'){
                            eofQuote = true;
                            quoteEnd = fieldTrack;
                            ++numQuotedFields;
                            i = fieldTrack + 1;
                        }
                        ++fieldTrack;
                    }
                    if(quoteEnd>0){
                        quoteStartIndexes[numQuotedFields-1] = quoteStart;
                        quoteEndIndexes[numQuotedFields-1] = quoteEnd;
                    }
                }
                /*
                else if(currentLine[i]=='"' && currentLine[i-1]==',' && currentLine[i+1]!='\0'){

                }*/
            }

            //qDebug() << quoteStartIndexes[0];
            //qDebug() << quoteEndIndexes[0];
            //qDebug() << numQuotedFields;

            currentLineList.clear();
            QString tempString = "";
            QStringList tempStringList;

            qDebug() << "Good here 1";

            if(numQuotedFields>0){
                tempStringList.clear();

                qDebug() << "Good here 2";

                for(int i=0; i<numQuotedFields; ++i){
                    tempString = "";
                    if(quoteStartIndexes[i] == 0){
                        for(int j=0; j < quoteEndIndexes[0]; ++j){
                            tempString = tempString + currentLine[j];
                        }

                        currentLineList.append(tempString);
                    }
                    else{
                        // append fields to currentLineList up to quoteStartIndexes[i]
                        // put quoted field into tempString
                        // append tempString to currentLineList
                        if(i==0){

                            qDebug() << "Good here 3";
                            // (quoteStartIndexes[0]-1)
                            for(int j=0; j<(quoteStartIndexes[0]-1); ++j){
                                tempString = tempString + currentLine[j];
                            }

                            qDebug() << "Good here 4";

                            tempStringList = tempString.split(",");

                            qDebug() << "Good here 5";

                            foreach (QString iter, tempStringList) {
                                currentLineList.append(iter);
                            }

                            qDebug() << "Good here 6";

                            tempString = "";
                            for(int j=quoteStartIndexes[0]; j<=quoteEndIndexes[0]; ++j){
                                tempString = tempString + currentLine[j];
                            }

                            qDebug() << tempString;

                            currentLineList.append(tempString);
                        }
                        else{
                            for(int j=(quoteEndIndexes[i-1] + 1); i<quoteStartIndexes[i]; ++j){
                                tempString = tempString + currentLine[j];
                            }
                            tempStringList = tempString.split(",");
                            foreach (QString iter, tempStringList) {
                                currentLineList.append(iter);
                            }
                            tempString = "";
                            for(int j=quoteStartIndexes[i]; j<=quoteEndIndexes[i]; ++j){
                                tempString = tempString + currentLine[j];
                            }
                            currentLineList.append(tempString);
                        }
                    }
                }
                // if currentLine[( quoteEndIndexes[numQuotedFields - 1] ) + 1] != '\0'
                // aka the last quoted field added is not the last field overall
                // append the rest of the fields in the end of currentLine to currentLineList
                tempStringList.clear();
                tempString = "";
                if(currentLine[( quoteEndIndexes[numQuotedFields - 1] ) + 1] != '\0'){
                    for(int i=(( quoteEndIndexes[numQuotedFields - 1] ) + 2); currentLine[i]!='\0'; ++i){
                        tempString = tempString + currentLine[i];
                    }
                    tempStringList = tempString.split(",");
                    foreach (QString iter, tempStringList) {
                        currentLineList.append(iter);
                    }
                }
            }
            else{
                currentLineList = currentLine.split(",");
            }

            // end of the validation for quoted fields


            ++row;

            if(numFieldsGlob == currentLineList.size()){ // checking if # of fields in current line is = to # of headers

            for(int i = 0; i < numFieldsGlob; ++i){
                qDebug() << currentLineList[i];
                qDebug() << mappingStringList[i];

                mappingString = mappingStringList[i];

                fieldError = false;

                if(currentLineList[i].isEmpty()){
                    if(mappingString[5] == '1'){
                        fieldError = true;
                    }
                }
                else{
                    if(mappingString[0] == '1'){
                        fieldError = invalidInt(currentLineList[i]);
                        qDebug() << "Validating int";
                    } //int
                    if(mappingString[1] == '1'){
                        fieldError = invalidDec(currentLineList[i]);
                        qDebug() << "Validating dec";
                    } //decimal
                    if(mappingString[2] == '1'){
                        fieldError = invalidDate(currentLineList[i]);
                        qDebug() << "Validating date";
                    } //date
                    if(mappingString[3] == '1'){
                        fieldError = invalidBool(currentLineList[i]);
                        qDebug() << "Validating bool";
                    } //bool
                    if(mappingString[4] == '1'){
                        strCharsMap = "";
                        strCharsMap = strCharsMap + mappingString[6] + mappingString[7] + mappingString[8] + mappingString[9] + mappingString[10];

                        fieldError = invalidString(currentLineList[i], strCharsMap);
                        qDebug() << "Validating string";
                        qDebug() << strCharsMap;
                    } //string

                    // check if field starts w/ a single quote '
                    QString tempStr = currentLineList[i];
                    if(tempStr[0] == "'"){
                        fieldError = true;
                    }
                }


                // here check for specifics for Customer, Inventory, Product and Jet Product
                QString tempStr2 = currentLineList[i];
                if(fileOption == 2){ // customer
                    if(i == 3){
                        if(currentLineList[0].isEmpty() && currentLineList[1].isEmpty() && currentLineList[2].isEmpty() && currentLineList[3].isEmpty()){
                            errorsFound = errorsFound + "Error found in row " + QString::number(row) + " either Full Name, First Name, Last Name or Company Name required" + '\xa';
                        }
                    }

                    if(i == 12 && currentLineList[12].size() != 2 && !currentLineList[12].isEmpty()){
                        fieldError = true;
                    }

                    if(i == 0 || i == 9){ // full name check letters spaces -
                        for(int j = 0; tempStr2[j]!='\0'; ++j){
                            if(!tempStr2[j].isLetter() && !tempStr2[j].isSpace() && tempStr2[j]!='-' && tempStr2[j]!='.' && tempStr2[j]!=','){
                                fieldError = true;
                            }
                        }
                    }

                    if(i == 1 || i == 2){ // first name, last name check letters -
                        for(int j = 0; tempStr2[j]!='\0'; ++j){
                            if(!tempStr2[j].isLetter() && tempStr2[j]!='-'){
                                fieldError = true;
                            }
                        }
                    }

                    /*
                    if(i == 3){
                        for(int j = 0; tempStr2[j]!='\0'; ++j){ // check for letters digits spaces and acceptable symbols - _ . ' " /
                            if(!tempStr2[j].isLetter() && !tempStr2[j].isDigit() && !tempStr2[j].isSpace() && tempStr2[j]!='-' && tempStr2[j]!='_' && tempStr2[j]!='.' && tempStr2[j]!="'" && tempStr2[j]!='"' && tempStr2[j]!='/' && tempStr2[j]!='$' && tempStr2[j]!=':'){
                                fieldError = true;
                            }
                        }
                    }*/
                }
                if(fileOption == 3){ // product
                    if(i == 1){
                        if(currentLineList[0].isEmpty() && currentLineList[1].isEmpty()){
                            errorsFound = errorsFound + "Error found in row " + QString::number(row) + " either SKU or Name required" + '\xa';
                        }
                    }

                    if(i == 13 && currentLineList[13].size() != 2 && !currentLineList[13].isEmpty()){
                        fieldError = true;
                    }

                    /*
                    if(i == 0 || i == 16 || i == 22){ // sku check letters digits - _ .
                        for(int j = 0; tempStr2[j]!='\0'; ++j){
                            if(!tempStr2[j].isLetter() && !tempStr2[j].isDigit() && !tempStr2[j].isSpace() && tempStr2[j]!='-' && tempStr2[j]!='_' && tempStr2[j]!='.'){
                                fieldError = true;
                            }
                        }
                    }*/

                    /*
                    if(i == 1 || i == 2 || i == 4 || i == 20){
                        for(int j = 0; tempStr2[j]!='\0'; ++j){ // check for letters digits spaces and acceptable symbols - _ . ' " /
                            if(!tempStr2[j].isLetter() && !tempStr2[j].isDigit() && !tempStr2[j].isSpace() && tempStr2[j]!='-' && tempStr2[j]!='_' && tempStr2[j]!='.' && tempStr2[j]!="'" && tempStr2[j]!='"' && tempStr2[j]!='/' && tempStr2[j]!='$' && tempStr2[j]!=':'){
                                fieldError = true;
                            }
                        }
                    }*/
                }
                if(fileOption == 4){ // jet product
                    if(i == 1){
                        if(currentLineList[0].isEmpty() && currentLineList[1].isEmpty()){
                            errorsFound = errorsFound + "Error found in row " + QString::number(row) + " either SKU or Name required" + '\xa';
                        }
                    }

                    if(i == 13 && currentLineList[13].size() != 2  && !currentLineList[13].isEmpty()){
                        fieldError = true;
                    }

                    /*
                    if(i == 0){ // sku check letters digits - _ .
                        for(int j = 0; tempStr2[j]!='\0'; ++j){
                            if(!tempStr2[j].isLetter() && !tempStr2[j].isDigit() && !tempStr2[j].isSpace() && tempStr2[j]!='-' && tempStr2[j]!='_' && tempStr2[j]!='.'){
                                fieldError = true;
                            }
                        }
                    }*/

                    /*
                    if(i == 1 || i == 2 || i == 4 || i == 20 || i == 24 || i == 27 || i == 28){
                        for(int j = 0; tempStr2[j]!='\0'; ++j){ // check for letters digits spaces and acceptable symbols - _ . ' " /
                            if(!tempStr2[j].isLetter() && !tempStr2[j].isDigit() && !tempStr2[j].isSpace() && tempStr2[j]!='-' && tempStr2[j]!='_' && tempStr2[j]!='.' && tempStr2[j]!="'" && tempStr2[j]!='"' && tempStr2[j]!='/' && tempStr2[j]!='$' && tempStr2[j]!=':'){
                                fieldError = true;
                            }
                        }
                    }*/
                }
                if(fileOption == 5){ // inventory
                    if(i == 1){
                        if(currentLineList[0].isEmpty() && currentLineList[1].isEmpty()){
                            errorsFound = errorsFound + "Error found in row " + QString::number(row) + " either SKU or Name required" + '\xa';
                        }
                    }

                    /*
                    if(i == 0){ // sku check letters digits - _ .
                        for(int j = 0; tempStr2[j]!='\0'; ++j){
                            if(!tempStr2[j].isLetter() && !tempStr2[j].isDigit() && !tempStr2[j].isSpace() && tempStr2[j]!='-' && tempStr2[j]!='_' && tempStr2[j]!='.'){
                                fieldError = true;
                            }
                        }
                    }*/

                    /*
                    if(i == 1 || i == 2 || i == 3 || i == 4 || i == 5){
                        for(int j = 0; tempStr2[j]!='\0'; ++j){ // check for letters digits spaces and acceptable symbols - _ . ' " /
                            if(!tempStr2[j].isLetter() && !tempStr2[j].isDigit() && !tempStr2[j].isSpace() && tempStr2[j]!='-' && tempStr2[j]!='_' && tempStr2[j]!='.' && tempStr2[j]!="'" && tempStr2[j]!='"' && tempStr2[j]!='/' && tempStr2[j]!='$' && tempStr2[j]!=':'){
                                fieldError = true;
                            }
                        }
                    }*/
                }

                // check for invalid carriage return
                for(int j=0; tempStr2[j]!='\0'; ++j){
                    if(tempStr2[j]=='\xa' || tempStr2[j]=='\x0' || tempStr2[j]=='\n'){
                        fieldError = true;
                    }
                }

                if(fieldError){
                    errorsFound = errorsFound + "Error found in " + fieldsList[i] + " field " + "row " + QString::number(row) + " column " + QString::number(i + 1) + '\xa';
                }
            }

            } // close bracket for checking field #
            else{
                errorsFound = errorsFound + "Error found in row " + QString::number(row) + ", number of fields in row does not match the number of headers provided" + '\xa';
            }

        }
    }

    ui->pushButton_8->show();
}

void MainWindow::display_pressed()
{
    // if file option == 1 , then file was an order (mapping), validation already occurred in mapping_pressed()
    // if any other file must still validate w/o any mapping, based on CSV import templates from ShipStation

    if(fileOption == 1){
        if(errorsFound.isEmpty()){
            errorsFound = "No errors found";
        }

        errorsFound = "CSV Validation Results: \xa" + errorsFound;
        ui->plainTextEdit->setPlainText(errorsFound);
        ui->plainTextEdit->update();
        ui->plainTextEdit->repaint();
    }
    if(fileOption == 2){
        //validate customer csv
        // 13 total fields
        QStringList mapPattern = {"00001000001", "00001000001", "00001000001", "00001000001", "00001001110", "00001011010",
                                  "00001100001", "00001100001", "00001000001", "00001110110", "00001110100", "00001100001", "00001110000"}; // testing for CSV Test1 file

        this->submitMapping(mapPattern);

        if(errorsFound.isEmpty()){
            errorsFound = "No errors found";
        }

        errorsFound = "CSV Validation Results: \xa" + errorsFound;
        ui->plainTextEdit->setPlainText(errorsFound);
        ui->plainTextEdit->update();
        ui->plainTextEdit->repaint();
    }
    if(fileOption == 3){
        //validate product csv
        // 24 total fields
        QStringList mapPattern = {"00001000001", "00001000001", "00001000001", "01000000000", "00001000001", "00001000001", "00001000001",
                                  "00001000001", "00001000001", "00001000001", "00001000001", "01000000000", "10000000000", "00001010000",
                                  "00001000001", "10000000000", "00001000001", "01000000000", "01000000000", "01000000000", "00001000001",
                                  "00010000000", "00001000001", "00010000000"};

        this->submitMapping(mapPattern);

        if(errorsFound.isEmpty()){
            errorsFound = "No errors found";
        }

        errorsFound = "CSV Validation Results: \xa" + errorsFound;
        ui->plainTextEdit->setPlainText(errorsFound);
        ui->plainTextEdit->update();
        ui->plainTextEdit->repaint();
    }
    if(fileOption == 4){
        //validate jet product csv
        // 29 total fields
        QStringList mapPattern = {"00001000001", "00001000001", "00001000001", "01000000000", "00001000001", "00001000001", "00001000001",
                                  "00001000001", "00001000001", "00001000001", "00001000001", "01000000000", "10000000000", "00001010000",
                                  "00001000001", "10000000000", "00001000001", "01000000000", "01000000000", "01000000000", "00001000001",
                                  "00010000000", "00001000001", "00001000001", "00001000001", "01000000000", "10000000000", "00001000001",
                                  "00001000001"};

        this->submitMapping(mapPattern);

        if(errorsFound.isEmpty()){
            errorsFound = "No errors found";
        }

        errorsFound = "CSV Validation Results: \xa" + errorsFound;
        ui->plainTextEdit->setPlainText(errorsFound);
        ui->plainTextEdit->update();
        ui->plainTextEdit->repaint();
    }
    if(fileOption == 5){
        //validate inventory csv
        // 9 total fields
        QStringList mapPattern = {"00001000001", "00001000001", "00001000001", "00001000001", "00001000001", "00001000001", "10000000000",
                                  "10000000000", "01000000000"};

        this->submitMapping(mapPattern);

        if(errorsFound.isEmpty()){
            errorsFound = "No errors found";
        }

        errorsFound = "CSV Validation Results: \xa" + errorsFound;
        ui->plainTextEdit->setPlainText(errorsFound);
        ui->plainTextEdit->update();
        ui->plainTextEdit->repaint();
    }

    // show the validate another file button
    ui->pushButton_9->show();

    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);

    //write out to a file
    QFile outfile("validationresults.txt");
    if(outfile.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "1";
        QTextStream outStream(&outfile);
        outStream << errorsFound;
        outfile.close();
        qDebug() << "2";

        errorsFound = "A text file named validationresults.txt has been created with the validation results. The file can be found in the folder containing this application \xa" + errorsFound;
        ui->plainTextEdit->setPlainText(errorsFound);
    }
}

void MainWindow::newFile_pressed(){
    ui->setupUi(this);
    QDoubleValidator *dimensionValidator = new QDoubleValidator(0.000, 10000.000, 4);
    ui->lineEdit->setValidator(dimensionValidator);
    ui->lineEdit_3->setValidator(dimensionValidator);
    ui->lineEdit_4->setValidator(dimensionValidator);
    ui->lineEdit_5->setValidator(dimensionValidator);
    ui->lineEdit_8->setValidator(dimensionValidator);
    ui->lineEdit_9->setValidator(dimensionValidator);
    ui->lineEdit_10->setValidator(dimensionValidator);

    connect(ui->radioButton,SIGNAL(clicked()),this,SLOT(weight_selected()));
    connect(ui->radioButton_2,SIGNAL(clicked()),this,SLOT(length_selected()));

    connect(ui->pushButton,SIGNAL(released()),this,SLOT(convertUnit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(dimensionalWeight_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(girth_pressed()));

    //connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(unitConvertHelp_pressed()));
    //connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(dimCalcHelp_pressed()));
    //connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(girthCalcHelp_pressed()));

    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(button_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(button_pressed()));

    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(openFile_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(mapping_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(display_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(newFile_pressed()));
    connect(ui->pushButton_10,SIGNAL(released()),this,SLOT(help_pressed()));

    connect(ui->radioButton_45,SIGNAL(released()),this,SLOT(fileType_pressed()));
    connect(ui->radioButton_46,SIGNAL(released()),this,SLOT(fileType_pressed()));
    connect(ui->radioButton_47,SIGNAL(released()),this,SLOT(fileType_pressed()));
    connect(ui->radioButton_48,SIGNAL(released()),this,SLOT(fileType_pressed()));
    connect(ui->radioButton_49,SIGNAL(released()),this,SLOT(fileType_pressed()));

    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
}

// returns false for valid, true for invalid
bool MainWindow::invalidInt(QString field){
    bool inValid = false;

    for(int i=0; field[i]!='\0'; ++i){
        if(!field[i].isDigit()){
            inValid = true;
        }
    }

    return inValid;
}

bool MainWindow::invalidDec(QString field){
    bool inValid = false;

    int numNonDigits = 0;
    bool containsDecimal = false;
    int decimalLoc = 0;

    for(int i=0; field[i]!='\0'; ++i){
        if(!field[i].isDigit()){
            ++numNonDigits;
        }
        if(field[i] == '.'){
            containsDecimal = true;
            decimalLoc = i;
        }
    }

    if(numNonDigits >= 2){
        inValid = true;
    }
    else if(!containsDecimal && numNonDigits > 0){
        inValid = true;
    }

    return inValid;
}

bool MainWindow::invalidDate(QString field){
    bool inValid = false;

    int numSlashes = 0;
    QString field1 = ""; // was month
    QString field2 = ""; //  was day
    QString year = "";

    for(int i=0; field[i]!='\0'; ++i){
        if(field[i] == '/'){
            ++numSlashes;
        }
        else if(numSlashes == 0){
            field1 = field1 + field[i];
        }
        else if(numSlashes == 1){
            field2 = field2 + field[i];
        }
        else{
            year = year + field[i];
        }
    }

    bool isAllDigits = true;
    for(int i = 0; field1[i]!='\0'; ++i){
        if(!field1[i].isDigit()){
            isAllDigits = false;
        }
    }
    for(int i = 0; field2[i]!='\0'; ++i){
        if(!field2[i].isDigit()){
            isAllDigits = false;
        }
    }
    for(int i = 0; year[i]!='\0'; ++i){
        if(!year[i].isDigit()){
            isAllDigits = false;
        }
    }

    int field1Num;
    int field2Num;
    int monthNum = 0;
    int dayNum = 0;
    int yearNum;
    if(isAllDigits){
        field1Num = field1.toInt();
        field2Num = field2.toInt();
        yearNum = year.toInt();

        if(field1Num > 12 && field2Num > 12){
            inValid = true;
        }
        else if(field1Num > 12){
            dayNum = field1Num;
            monthNum = field2Num;
        }
        else if(field2Num > 12){
            dayNum = field2Num;
            monthNum = field1Num;
        }
        else{
            dayNum = field2Num;
            monthNum = field1Num;
        }

        if(monthNum > 12 || monthNum <= 0){
            inValid = true;
        }
        if(dayNum > 31 || dayNum <= 0){
            inValid = true;
        }
        if(year.length()!=2 && year.length()!=4){ //making sure year is either YY or YYYY
            inValid = true;
        }
        if(monthNum == 1 || monthNum == 3 || monthNum == 5 || monthNum == 7 || monthNum == 8 || monthNum == 10 || monthNum == 12){
            if(dayNum > 31){
                inValid = true;
            }
        }
        else if(monthNum == 4 || monthNum == 6 || monthNum == 9 || monthNum == 11){
            if(dayNum > 30){
                inValid = true;
            }
        }
        else{
            if(yearNum % 4 == 0){
                if(dayNum > 29){
                    inValid = true;
                }
            }
            else{
                if(dayNum > 28){
                    inValid = true;
                }
            }
        }
    }
    else{
        inValid = true;
    }

    if(numSlashes!=2){
        inValid = true;
    }

    return inValid;
}

bool MainWindow::invalidBool(QString field){
    bool inValid = false;

    int fieldLen = 0;

    QChar fieldArr[field.length() + 1];
    for(int i=0; field[i]!='\0'; ++i){
        fieldArr[fieldLen] = field[i].toLower();
        ++fieldLen;
    }
    fieldArr[fieldLen] = '\0';

    char fstr[] = {'f', 'a', 'l', 's', 'e'};
    char tstr[] = {'t', 'r', 'u', 'e'};

    bool isTrue = true;
    bool isFalse = true;

    if(fieldLen == 5){
        for(int i=0; fieldArr[i]!='\0'; ++i){
            if(fieldArr[i] != fstr[i]){
                isFalse = false;
            }
            qDebug() << fieldArr[i] << " " << fstr[i] << endl;
        }
    }

    if(fieldLen == 4){
        for(int i=0; fieldArr[i]!='\0'; ++i){
            if(fieldArr[i] != tstr[i]){
                isTrue = false;
            }
            qDebug() << fieldArr[i] << " " << tstr[i] << endl;
        }
    }

    if(fieldLen == 5 && !isFalse){
        inValid = true;
    }
    if(fieldLen == 4 && !isTrue){
        inValid = true;
    }
    if(fieldLen != 5 && fieldLen != 4){
        inValid = true;
    }

    return inValid;
}

bool MainWindow::invalidString(QString field, QString charsAllowed){
    bool inValid = false;

    if(charsAllowed[4] == '1'){
        inValid = false;
    }
    else{
        if(charsAllowed[0] == '0'){ //if letters are NOT allowed
            // if any letters then inValid = true
            for(int i=0; field[i]!='\0'; ++i){
                if(field[i].isLetter()){
                    inValid = true;
                }
            }
        }
        if(charsAllowed[1] == '0'){ //if digits are NOT allowed
            // if any digits then inValid = true
            for(int i=0; field[i]!='\0'; ++i){
                if(field[i].isDigit()){
                    inValid = true;
                }
            }
        }
        if(charsAllowed[2] == '0'){ //if spaces are NOT allowed
            // if any spaces then inValid = true
            for(int i=0; field[i]!='\0'; ++i){
                if(field[i].isSpace()){
                    inValid = true;
                }
            }
        }
        if(charsAllowed[3] == '0'){ //if symbols are NOT allowed
            // if any symbols then inValid = true
            // if any symbols = any char not a letter AND not a digit AND not a space
            for(int i=0; field[i]!='\0'; ++i){
                if(!field[i].isLetter() && !field[i].isDigit() && !field[i].isSpace()){
                    inValid = true;
                }
            }
        }
    }

    return inValid;
}

void MainWindow::help_pressed(){
    Help dia;
    dia.setModal(true);
    dia.exec();
}
