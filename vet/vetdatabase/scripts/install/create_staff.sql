CREATE TYPE edu_level_type AS ENUM('resident', 'middle', 'postgraduate', 'specialist', 'bachelor');

CREATE TABLE staff(
	staff_id SERIAL NOT NULL PRIMARY KEY,
	passport INT NOT NULL,
	position INT NOT NULL,
	edu_level edu_level_type NOT NULL,
	fire_date DATE NOT NULL,
	employ_date DATE NOT NULL
);
