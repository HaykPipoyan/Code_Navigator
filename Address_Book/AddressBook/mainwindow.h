#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCloseEvent>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSplitter *splitter;
    QWidget *leftWidget;
    QListWidget *listWidget;
    QLineEdit *nameEdit;
    QLineEdit *phoneEdit;
    QLineEdit *emailEdit;

    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *editButton;

    void addEntry();
    void removeEntry();
    void editEntry();
    void loadFile();
    void saveFile();
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onListItemClicked();
};

#endif // MAINWINDOW_H

