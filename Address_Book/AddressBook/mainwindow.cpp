#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    splitter = new QSplitter(Qt::Horizontal, this);

    leftWidget = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

    addButton = new QPushButton("add");
    removeButton = new QPushButton("remove");
    editButton = new QPushButton("edit");

    leftLayout->addWidget(addButton);
    leftLayout->addWidget(removeButton);
    leftLayout->addWidget(editButton);
    leftLayout->addStretch();

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addEntry);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeEntry);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editEntry);

    QWidget *rightWidget = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);

    listWidget = new QListWidget;
    rightLayout->addWidget(listWidget);

    nameEdit = new QLineEdit;
    nameEdit->setPlaceholderText("name");

    phoneEdit = new QLineEdit;
    phoneEdit->setPlaceholderText("phone number");

    emailEdit = new QLineEdit;
    emailEdit->setPlaceholderText("email");

    rightLayout->addWidget(nameEdit);
    rightLayout->addWidget(phoneEdit);
    rightLayout->addWidget(emailEdit);

    connect(listWidget, &QListWidget::itemClicked, this, &MainWindow::onListItemClicked);

    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);
    splitter->setStretchFactor(1, 1);

    setCentralWidget(splitter);
    setWindowTitle("Addres Book");
    resize(600, 400);

    loadFile();
}

MainWindow::~MainWindow() {
    saveFile();
}

void MainWindow::addEntry() {
    QString name = nameEdit->text();
    QString phone = phoneEdit->text();
    QString email = emailEdit->text();

    if (!name.isEmpty() && !phone.isEmpty() && !email.isEmpty()) {
        QString entry = name + " | " + phone + " | " + email;
        listWidget->addItem(entry);

        nameEdit->clear();
        phoneEdit->clear();
        emailEdit->clear();
    } else {
        QMessageBox::warning(this, "error", "All fields must be filled in!");
    }
}

void MainWindow::removeEntry() {
    QListWidgetItem *item = listWidget->currentItem();
    if (item) {
        delete item;
    } else {
        QMessageBox::warning(this, "error", "Select the entry to delete!");
    }
}

void MainWindow::editEntry() {
    QListWidgetItem *item = listWidget->currentItem();
    if (item) {
        QString name = nameEdit->text();
        QString phone = phoneEdit->text();
        QString email = emailEdit->text();

        if (!name.isEmpty() && !phone.isEmpty() && !email.isEmpty()) {
            item->setText(name + " | " + phone + " | " + email);
        } else {
            QMessageBox::warning(this, "error", "All fields must be filled in to edit!");
        }
    } else {
        QMessageBox::warning(this, "error", "Select a record to edit!");
    }
}

void MainWindow::onListItemClicked() {
    QListWidgetItem *item = listWidget->currentItem();
    if (item) {
        QStringList parts = item->text().split(" | ");
        if (parts.size() == 3) {
            nameEdit->setText(parts[0]);
            phoneEdit->setText(parts[1]);
            emailEdit->setText(parts[2]);
        }
    }
}

void MainWindow::loadFile() {
    QFile file("/Users/haykpipoyan/Desktop/address_book.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        listWidget->addItem(line);
    }
    file.close();
}

void MainWindow::saveFile() {
    QFile file("/Users/haykpipoyan/Desktop/address_book.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < listWidget->count(); ++i) {
        out << listWidget->item(i)->text() << "\n";
    }
    file.close();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    saveFile();
    event->accept();
}

