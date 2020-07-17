#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QGraphicsDropShadowEffect>

#include "vectorList.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Global Variables
int longest;
VectorList shakespeareWords; // making a vectorList to store all of shakespeare's words

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{

    string word;
    string l_word;
    string numbers;

    QFile shakespeare(":/extras/src/extras/shakespeare-words.txt");
    shakespeare.open(QIODevice::ReadOnly);
    QTextStream in(&shakespeare);

    while(!in.atEnd()) // get every line of input, store as word
    {
      QString qword = in.readLine();
      string word = qword.toStdString();
      Node *repeat = shakespeareWords.findExistence(word);

      // check if the word already exists to increment frequency
      // or needs a new node
      if(repeat == NULL)
        shakespeareWords.insertExistence(word);
      else
        repeat->frequency++;
    }

    shakespeareWords.sortValues();  // transfer Node pointers over to vectorList and sorts them according to frequency and lexicographic order
    longest = shakespeareWords.getLongestLength(); // gets the longest word length stored in the vectorList

    shakespeare.close(); //close input stream


    ui->setupUi(this);

    // adding a drop shadow to all QLabels
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setBlurRadius(10.0);
    shadow->setColor(Qt::black);
    ui->label->setGraphicsEffect(shadow);
    QGraphicsDropShadowEffect *shadow2 = new QGraphicsDropShadowEffect(this);
    shadow2->setOffset(0, 0);
    shadow2->setBlurRadius(10.0);
    shadow2->setColor(Qt::black);
    ui->label_2->setGraphicsEffect(shadow2);
    QGraphicsDropShadowEffect *shadow3 = new QGraphicsDropShadowEffect(this);
    shadow3->setOffset(0, 0);
    shadow3->setBlurRadius(10.0);
    shadow3->setColor(Qt::black);
    ui->label_3->setGraphicsEffect(shadow3);
    QGraphicsDropShadowEffect *shadow4 = new QGraphicsDropShadowEffect(this);
    shadow4->setOffset(0, 0);
    shadow4->setBlurRadius(10.0);
    shadow4->setColor(Qt::black);
    ui->label_4->setGraphicsEffect(shadow4);
    QGraphicsDropShadowEffect *shadow5 = new QGraphicsDropShadowEffect(this);
    shadow5->setOffset(0, 0);
    shadow5->setBlurRadius(10.0);
    shadow5->setColor(Qt::black);
    ui->label_5->setGraphicsEffect(shadow5);
    QGraphicsDropShadowEffect *shadowLine = new QGraphicsDropShadowEffect(this);
    shadowLine->setOffset(0, 0);
    shadowLine->setBlurRadius(4.0);
    shadowLine->setColor(Qt::black);
    //ui->line->setGraphicsEffect(shadowLine);

    // removing the spin box automatic highlighting
    connect(ui->spnbx_rank, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged()), Qt::QueuedConnection);
    connect(ui->spnbx_word_length, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged()), Qt::QueuedConnection);

    // setting result widgets to read only to avoid unnecessary highlighting
    ui->result_text->setReadOnly(true);
    ui->occurances_text->setReadOnly(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_find_word_clicked()
{

    int length, rank;
    length = ui->spnbx_word_length->value();
    rank = ui->spnbx_rank->value();

    if(length > longest){
           ui->result_text->setText("Word not found...");
           ui->occurances_text->setText("-");
    }
    else
    {
        if(rank >= shakespeareWords.getRankSize(length)){
            ui->result_text->setText("Word not found...");
            ui->occurances_text->setText("-");
        }
        else
        {
            pair<string, int> out = shakespeareWords.getInfo(length, rank);
            string word = out.first;
            int freq = out.second;

            const QString qword = QString::fromStdString(word);
            ui->result_text->setText(qword);

            const QString qfreq = QString::number(freq);
            ui->occurances_text->setText(qfreq);
        }
    }
}

void MainWindow::onSpinBoxValueChanged() // slot
{
    ui->spnbx_word_length->findChild<QLineEdit*>()->deselect();
    ui->spnbx_rank->findChild<QLineEdit*>()->deselect();
}


