#include "DatabaseManager.h"
#include "MainWindow.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    DatabaseManager dbManager;
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    tabWidget->addTab(createTableView("halls"), "Залы");
    tabWidget->addTab(createTableView("exhibits"), "Экспонаты");
    tabWidget->addTab(createTableView("visitors"), "Посетители");
    tabWidget->addTab(createTableView("employees"), "Сотрудники");
    tabWidget->addTab(createTableView("tours"), "Экскурсии");
    tabWidget->addTab(createTableView("finance"), "Финансы");

    // Кнопки для добавления, редактирования и удаления
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *addButton = new QPushButton("Добавить", this);
    QPushButton *editButton = new QPushButton("Редактировать", this);
    QPushButton *deleteButton = new QPushButton("Удалить", this);

    layout->addWidget(addButton);
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    setMenuWidget(widget);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addRecord);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editRecord);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteRecord);

    setWindowTitle("Учёт работы музея");
    resize(800, 600);
}

MainWindow::~MainWindow() {}

QTableView* MainWindow::createTableView(const QString &tableName) {
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->select();

    QTableView *view = new QTableView;
    view->setModel(model);
    view->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    return view;
}

void MainWindow::addRecord() {
    QTableView *currentView = qobject_cast<QTableView*>(tabWidget->currentWidget());
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(currentView->model());

    if (model) {
        model->insertRow(model->rowCount());
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить запись.");
    }
}

void MainWindow::editRecord() {
    QTableView *currentView = qobject_cast<QTableView*>(tabWidget->currentWidget());
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(currentView->model());

    if (model) {
        int row = currentView->currentIndex().row();
        if (row >= 0) {
            model->submitAll();
        } else {
            QMessageBox::warning(this, "Ошибка", "Выберите запись для редактирования.");
        }
    }
}

void MainWindow::deleteRecord() {
    QTableView *currentView = qobject_cast<QTableView*>(tabWidget->currentWidget());
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(currentView->model());

    if (model) {
        int row = currentView->currentIndex().row();
        if (row >= 0) {
            model->removeRow(row);
            model->submitAll();
        } else {
            QMessageBox::warning(this, "Ошибка", "Выберите запись для удаления.");
        }
    }
}
