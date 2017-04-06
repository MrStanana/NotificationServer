CREATE USER 'notify'@'localhost' IDENTIFIED BY 'notificarsql';
GRANT SELECT,INSERT,UPDATE,DELETE,CREATE,DROP ON notify.* TO 'notify'@'localhost';

DROP TABLE IF EXISTS plays;
DROP TABLE IF EXISTS alert;
DROP TABLE IF EXISTS games;
DROP TABLE IF EXISTS users;

CREATE TABLE users (
    id		INT AUTO_INCREMENT PRIMARY KEY,
    user	VARCHAR(50)		NOT NULL UNIQUE,
    mail	VARCHAR(200)	NOT NULL UNIQUE,
    pass	VARCHAR(50)		NOT NULL,
    salt	VARCHAR(5)		NOT NULL,
    t		DATETIME,
)

CREATE TABLE games (
    id		INT AUTO_INCREMENT PRIMARY KEY,
	first	INT NOT NULL,
    second	INT NOT NULL,
    ended	BIT DEFAULT 0,
    winner	INT,
    t		DATETIME
)

CREATE TABLE alert (
    game	INT REFERENCES games (id) ON UPDATE CASCADE ON DELETE CASCADE,
    player	INT REFERENCES users (id) ON UPDATE CASCADE ON DELETE CASCADE,
	PRIMARY KEY (game, player)
)

CREATE TABLE plays (
    game	INT REFERENCES games (id) ON UPDATE CASCADE ON DELETE CASCADE,
    player	INT REFERENCES users (id) ON UPDATE CASCADE ON DELETE CASCADE,
    x		INT NOT NULL,
    y		INT NOT NULL,
    t		DATETIME,
	PRIMARY KEY (game, x, y)
)
