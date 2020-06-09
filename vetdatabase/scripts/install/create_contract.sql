CREATE TABLE contract(
	contr_id BIGSERIAL NOT NULL PRIMARY KEY,
	code VARCHAR(20) NOT NULL,
	conclusion_date DATE NOT NULL,
	last_update_date DATE NOT NULL,
	"owner" INT NOT NULL,
	valid_until DATE NOT NULL
);
