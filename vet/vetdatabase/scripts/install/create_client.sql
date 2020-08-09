CREATE TABLE clients(
	cli_id SERIAL NOT NULL PRIMARY KEY,
	contacts JSON NOT NULL,
	address INT NOT NULL,
	passport INT NOT NULL
);
