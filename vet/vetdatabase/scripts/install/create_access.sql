CREATE TYPE access_level_type AS ENUM('admin', 'main', 'registry', 'vet');

CREATE TABLE access(
	acc_id SERIAL NOT NULL PRIMARY KEY,
	employee INT NOT NULL,
	login VARCHAR(64) NOT NULL,
	password BYTEA NOT NULL,
	access_level access_level_type NOT NULL
);
