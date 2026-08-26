# REST API для управления задачами.

Основные возможности:
1) Обработка HTTP-запросов (GET /tasks, GET /tasks/{id}, POST /tasks, PUT /tasks/{id}, DELETE /tasks/{id})
2) Хранение задач в SQLite
3) Сериализация/десериализация JSON
4) Поддержка одновременных соединений через пулл потоков ??? или асинхронную модель ???
5) Конфигурация через файл
6) Логирование запросов

ПЛАН (В дальнейшем будет обновляться):
~~1) Настройка проекта и зависимостей (conan, Cmake, folders);~~  
~~2) Проектирование файлового логгера с возможностью severity;~~  
~~3) Реализация файлового логгера с возможностью severity;~~  
4) Юнит тесты для логгера;  
5) Проектирование структуры Task;
6) Проектирование БД;
7) Реализация CRUD операция для работы с БД;
8) Юнит тесты для CRUD операция;
9) Проектирование конфигуратора;
10) Реализация HTTP-сервера ???

# Project Build Guide

This document describes how to build the project using **CMake** and **Conan** for dependency management.

---

## Special Note: Manual Installation of `bzip2`

If the `bzip2` package is not available from the default Conan remotes you can install it manually, 
follow these steps **before** running the project's build:

```bash
# Clone the Conan Center Index (if not already present)
git clone https://github.com/conan-io/conan-center-index

# Navigate to the bzip2 recipe directory
cd conan-center-index/recipes/bzip2/all

# Create the package locally with the required user, channel, and version
conan create . --build=missing --user=x86_64 --channel=xxx --version=1.0.8