# Museum App

Это приложение для учета работы музея, разработанное на C++ с использованием Qt для графического интерфейса и MariaDB для хранения данных.

## Описание

Приложение позволяет управлять следующими данными:

- Залы музея
- Экспонаты
- Посетители
- Сотрудники
- Экскурсии
- Финансовые данные

### Функционал

1. Добавление, редактирование и удаление записей.
2. Отображение данных из таблиц базы данных.
3. Подключение к базе данных MariaDB для хранения информации.

## Технологии

- C++
- Qt
- MariaDB

## Установка

### Предварительные требования

1. **C++ компилятор** (например, `g++`).
2. **Qt** (версии 5.15 или выше).
3. **MariaDB** для хранения данных.

### Установка зависимостей

1. Установите необходимые пакеты:

    ```bash
    sudo pacman -S mariadb-connector-c qt6-base cmake make
    ```

2. Установите MariaDB и создайте базу данных:

    ```bash
    sudo apt install mariadb-server
    mysql -u root -p
    CREATE DATABASE museum_db;
    ```

### Склонируйте репозиторий

1. Склонируйте репозиторий и перейдите в директорию проекта:

    ```bash
    git clone https://github.com/yourusername/museum-app.git
    cd museum-app
    mkdir build
    cd build
    cmake ..
    make
    ./museum_app
    ```