#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("470211");

    QSqlDatabase tempDb = QSqlDatabase::addDatabase("QMYSQL", "temp_connection");
    tempDb.setHostName("127.0.0.1");
    tempDb.setPort(3306);
    tempDb.setUserName("root");
    tempDb.setPassword("470211");

    if (!tempDb.open()) {
        qDebug() << "Ошибка подключения к MariaDB:" << tempDb.lastError().text();
        return;
    }

    QSqlQuery query(tempDb);
    query.exec("CREATE DATABASE IF NOT EXISTS museum_db;");
    tempDb.close();
    
    db.setDatabaseName("museum_db");
    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе museum_db:" << db.lastError().text();
        return;
    }

    qDebug() << "Подключение к MariaDB успешно!";
    createTables();
    insertTestData();
}

void DatabaseManager::createTables() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS halls (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), description TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS exhibits (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), description TEXT, date_received DATE, `condition` VARCHAR(50), hall_id INT, FOREIGN KEY (hall_id) REFERENCES halls(id) ON DELETE SET NULL)");
    query.exec("CREATE TABLE IF NOT EXISTS visitors (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), visit_date DATE, ticket_number VARCHAR(50))");
    query.exec("CREATE TABLE IF NOT EXISTS employees (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), position VARCHAR(255), work_schedule TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS tours (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), description TEXT, guide_id INT, FOREIGN KEY (guide_id) REFERENCES employees(id) ON DELETE SET NULL)");
    query.exec("CREATE TABLE IF NOT EXISTS visitor_tours (visitor_id INT, tour_id INT, PRIMARY KEY (visitor_id, tour_id), FOREIGN KEY (visitor_id) REFERENCES visitors(id) ON DELETE CASCADE, FOREIGN KEY (tour_id) REFERENCES tours(id) ON DELETE CASCADE)");
    query.exec("CREATE TABLE IF NOT EXISTS finance (id INT AUTO_INCREMENT PRIMARY KEY, date DATE, amount DECIMAL(10,2), description TEXT, visitor_id INT, FOREIGN KEY (visitor_id) REFERENCES visitors(id) ON DELETE SET NULL)");
}

void DatabaseManager::insertTestData() {
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM halls");
    if (query.next() && query.value(0).toInt() > 0) return;
    
    query.exec("INSERT INTO halls (name, description) VALUES ('Главный зал', 'Основная экспозиция'), ('Исторический зал', 'Древние артефакты')");
    query.exec("INSERT INTO exhibits (name, description, date_received, `condition`, hall_id) VALUES ('Монета Рима', 'Старинная монета', '2018-10-12', 'Отличное', 1), ('Статуя Греции', 'Мраморная статуя', '2019-05-30', 'Хорошее', 2)");
    query.exec("INSERT INTO employees (name, position, work_schedule) VALUES ('Алексей Смирнов', 'Гид', 'Пн-Пт 10:00-18:00'), ('Ольга Петрова', 'Администратор', 'Вт-Сб 09:00-17:00')");
    query.exec("INSERT INTO visitors (name, visit_date, ticket_number) VALUES ('Иван Иванов', '2025-03-25', 'A12345'), ('Мария Сидорова', '2025-03-26', 'B67890')");
    query.exec("INSERT INTO tours (name, description, guide_id) VALUES ('Обзорная экскурсия', 'Основные экспонаты', 1), ('Древний мир', 'Исторический зал', 1)");
    query.exec("INSERT INTO visitor_tours (visitor_id, tour_id) VALUES (1, 1), (2, 2)");
    query.exec("INSERT INTO finance (date, amount, description, visitor_id) VALUES ('2025-03-24', 1500.00, 'Продажа билетов', 1), ('2025-03-25', 2000.00, 'Оплата экскурсии', 2)");
}