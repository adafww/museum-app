#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTabWidget *tabWidget;
    QTableView* createTableView(const QString &tableName);

    // Добавьте объявления этих методов
    void addRecord();
    void editRecord();
    void deleteRecord();
};

#endif // MAINWINDOW_H
