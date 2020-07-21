#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "ordinalNumber.h"
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
    shakespeareWords.getBiggerPicture();  //transfer Node pointers into a set where all words are ranked against eachother
    longest = shakespeareWords.getLongestLength(); // gets the longest word length stored in the vectorList

    shakespeare.close(); //close input stream


    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    ui->search_bar_p2->setFocusPolicy(Qt::ClickFocus);


    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(1, 1);
    shadow->setBlurRadius(5.0);
    shadow->setColor(Qt::black);
    ui->lbl_word_length->setGraphicsEffect(shadow);
    QGraphicsDropShadowEffect *shadow2 = new QGraphicsDropShadowEffect(this);
    shadow2->setOffset(1, 1);
    shadow2->setBlurRadius(5.0);
    shadow2->setColor(Qt::black);
    ui->lbl_rank->setGraphicsEffect(shadow2);
    QGraphicsDropShadowEffect *shadow3 = new QGraphicsDropShadowEffect(this);
    shadow3->setOffset(1, 1);
    shadow3->setBlurRadius(5.0);
    shadow3->setColor(Qt::black);
    ui->lbl_result->setGraphicsEffect(shadow3);
    QGraphicsDropShadowEffect *shadow4 = new QGraphicsDropShadowEffect(this);
    shadow4->setOffset(1, 1);
    shadow4->setBlurRadius(5.0);
    shadow4->setColor(Qt::black);
    ui->lbl_occurrences->setGraphicsEffect(shadow4);
    QGraphicsDropShadowEffect *shadow5 = new QGraphicsDropShadowEffect(this);
    shadow5->setOffset(1, 1);
    shadow5->setBlurRadius(5.0);
    shadow5->setColor(Qt::black);
    ui->lbl_occurrences_p2->setGraphicsEffect(shadow5);
    QGraphicsDropShadowEffect *shadow6 = new QGraphicsDropShadowEffect(this);
    shadow6->setOffset(1, 1);
    shadow6->setBlurRadius(5.0);
    shadow6->setColor(Qt::black);
    ui->lbl_frequency_p2->setGraphicsEffect(shadow6);


    // removing the spin box automatic highlighting

    connect(ui->spnbox_word_length, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged()), Qt::QueuedConnection);
    connect(ui->spnbox_rank, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged()), Qt::QueuedConnection);

    // setting result widgets to read only to avoid unnecessary highlighting
    ui->text_result->setReadOnly(true);
    ui->text_occurrences->setReadOnly(true);
    ui->text_frequency_p2->setReadOnly(true);
    ui->text_occurrences_p2->setReadOnly(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_find_clicked()
{

    int length, rank;
    length = ui->spnbox_word_length->value();
    rank = ui->spnbox_rank->value();

    if(length > longest){
        ui->text_result->setStyleSheet("QLineEdit { color: rgba(255, 255, 255, 130); border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
        ui->text_occurrences->setStyleSheet("QLineEdit { color: rgba(255, 255, 255, 130); border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
        ui->text_result->setText("Word not found...");
        ui->text_occurrences->setText("-");
    }
    else
    {
        if(rank >= shakespeareWords.getRankSize(length)){
            ui->text_result->setStyleSheet("QLineEdit { color: rgba(255, 255, 255, 130); border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
            ui->text_occurrences->setStyleSheet("QLineEdit { color: rgba(255, 255, 255, 130); border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
            ui->text_result->setText("Word not found...");
            ui->text_occurrences->setText("-");
        }
        else
        {
            pair<string, int> out = shakespeareWords.getInfo(length, rank);
            string word = out.first;
            int freq = out.second;
            ui->text_result->setStyleSheet("QLineEdit { color: white; border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
            ui->text_occurrences->setStyleSheet("QLineEdit { color: white; border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
            const QString qword = QString::fromStdString(word);
            ui->text_result->setText(qword);

            const QString qfreq = QString::number(freq);
            ui->text_occurrences->setText(qfreq);
        }
    }
}


void MainWindow::onSpinBoxValueChanged() // slot
{
    ui->spnbox_word_length->findChild<QLineEdit*>()->deselect();
    ui->spnbox_rank->findChild<QLineEdit*>()->deselect();
}



void MainWindow::on_btn_search_bar_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->search_bar_p2->clearFocus();
}

void MainWindow::on_btn_return_p2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_find_p2_clicked()
{
    QString qword = ui->search_bar_p2->text();
    string word = qword.toStdString();

    Node* searchResult = shakespeareWords.searchBarWordFinder(word);

    if(searchResult->index == -1){
        ui->text_frequency_p2->setStyleSheet("QLineEdit { color: rgba(255, 255, 255, 130); border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
        ui->text_occurrences_p2->setStyleSheet("QLineEdit { color: rgba(255, 255, 255, 130); border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
        ui->text_frequency_p2->setText("Word not found...");
        ui->text_occurrences_p2->setText("-");
    }
    else if(searchResult->index == -2){
        ui->text_frequency_p2->setStyleSheet("QLineEdit { color: rgba(255, 255, 255, 130); border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
        ui->text_occurrences_p2->setStyleSheet("QLineEdit { color: rgba(255, 255, 255, 130); border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
        ui->text_frequency_p2->setText("Word must be over 4 letters");
        ui->text_occurrences_p2->setText("-");
    }
    else{
        ui->text_frequency_p2->setStyleSheet("QLineEdit { color: white; border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
        ui->text_occurrences_p2->setStyleSheet("QLineEdit { color: white; border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #404040; selection-background-color: darkgray;}");
        int frequency = searchResult->index;
        int occurrences = searchResult->frequency;

        if(frequency == 0){
            const QString qfrequency = QString::fromStdString("Most used word overall");
            const QString qoccurrences = QString::number(occurrences);
            ui->text_frequency_p2->setText(qfrequency);
            ui->text_occurrences_p2->setText(qoccurrences);
        }
        string ordinalFreq = ordinal(frequency+1);
        const QString qfrequency = QString::fromStdString(ordinalFreq + " most used word overall");
        const QString qoccurrences = QString::number(occurrences);
        ui->text_frequency_p2->setText(qfrequency);
        ui->text_occurrences_p2->setText(qoccurrences);
    }

}
