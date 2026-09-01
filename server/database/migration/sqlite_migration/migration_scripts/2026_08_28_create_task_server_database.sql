-- Включение поддержки внешних ключей
PRAGMA foreign_keys = ON;

-- ============================================================
-- Таблица пользователей. Хранит учётные данные пользователей.
-- 
-- id - Уникальный идентификатор пользователя.
-- username - Уникальный логин пользователя.
-- created_at - Дата и время регистрации пользователя.
-- ============================================================
CREATE TABLE users (
    id INTEGER PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    created_at TEXT NOT NULL,
    CONSTRAINT users_username_uq UNIQUE (username),
    CONSTRAINT users_username_chk CHECK(TRIM(username) <> ''),
    CONSTRAINT users_created_at_chk CHECK(TRIM(created_at) <> '')
); 

-- =====================================================================
-- Таблица задач. Хранит задачи, созданные пользователями.
-- 
-- id - Уникальный идентификатор задачи.
-- user_id - Идентификатор пользователя задачи.
-- title - VARCHAR(255) Заголовок задачи.
-- description - Подробное описание задачи. 
-- status - Текущий статус задачи.
-- created_at - Дата и время создания задачи в формате
-- =====================================================================
CREATE TABLE tasks (
    id INTEGER PRIMARY KEY,
    user_id INTEGER NOT NULL,
    title VARCHAR(255) NOT NULL,
    description TEXT,
    status VARCHAR(255) NOT NULL,
    created_at TEXT NOT NULL,
    CONSTRAINT tasks_user_id_fk FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
    CONSTRAINT tasks_title_chk CHECK(TRIM(title) <> ''),
    CONSTRAINT tasks_status_chk CHECK (status IN ('Completed', 'InProgress', 'Canceled')),
    CONSTRAINT tasks_created_at_chk CHECK(TRIM(created_at) <> '')
);