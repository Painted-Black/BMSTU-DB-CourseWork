CREATE TYPE sex_type AS ENUM ('m', 'f', 'other');

CREATE TABLE passports(
	pass_id SERIAL NOT NULL PRIMARY KEY,
	surname VARCHAR(64) NOT NULL,
	name VARCHAR(64) NOT NULL,
	patronymic VARCHAR(64) NOT NULL,
	sex sex_type NOT NULL,
	birth DATE NOT NULL,
	num VARCHAR(10) NOT NULL,
	issue_date DATE NOT NULL,
	nationality VARCHAR(128)
);
