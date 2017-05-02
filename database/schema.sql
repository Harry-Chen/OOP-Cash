BEGIN TRANSACTION;
CREATE TABLE `User` (
                `id`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
                `username`	TEXT NOT NULL,
                `nickname`	TEXT,
                `password`	TEXT NOT NULL
            );
CREATE TABLE `Currency` (
                `id`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
                `name`	TEXT NOT NULL,
                `rate`	INTEGER NOT NULL
            );
CREATE TABLE "Category" (
                    `id`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
                    `name`	TEXT NOT NULL,
                    `uid`	INTEGER NOT NULL,
                    FOREIGN KEY(`uid`) REFERENCES User(id)
             );
CREATE TABLE "Bill" (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
	`afrom`	INTEGER NOT NULL,
	`ato`	INTEGER NOT NULL,
	`creator`	INTEGER NOT NULL,
	`category`	INTEGER NOT NULL,
	`quantity`	INTEGER NOT NULL,
	`ctime`	INTEGER NOT NULL,
	`finished`	INTEGER NOT NULL,
	`date`	INTEGER NOT NULL,
	`note`	TEXT,
	FOREIGN KEY(`afrom`) REFERENCES `Account`(`id`),
	FOREIGN KEY(`ato`) REFERENCES `Account`(`id`),
	FOREIGN KEY(`creator`) REFERENCES `User`(`id`),
	FOREIGN KEY(`category`) REFERENCES `Category`(`id`)
);
CREATE TABLE "Account" (
                `id`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
                `name`	TEXT NOT NULL,
                `uid`	INTEGER NOT NULL,
                `cid`	INTEGER NOT NULL,
                FOREIGN KEY(`uid`) REFERENCES User(id),
                FOREIGN KEY(`cid`) REFERENCES Currency(id)
             );
COMMIT;
