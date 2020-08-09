CREATE TYPE against_type AS ENUM('rab', 'inf');

CREATE TABLE vaccinations(
    vac_id BIGSERIAL NOT NULL PRIMARY KEY,
    against against_type NOT NULL,
    reg_num VARCHAR(20) NOT NULL,
    vac_date DATE NOT NULL,
    next_vac DATE NOT NULL,
    animal INT NOT NULL,
    vet INT NOT NULL
);
