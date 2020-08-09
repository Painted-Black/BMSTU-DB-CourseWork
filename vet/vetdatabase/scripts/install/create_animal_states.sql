CREATE TYPE general_type AS ENUM('middle', 'good', 'bad');

CREATE TABLE animal_states(
    state_id SERIAL NOT NULL PRIMARY KEY,
    general general_type NOT NULL,
    pulse INT NOT NULL,
    weight REAL NOT NULL,
    ap VARCHAR(10) NOT NULL,
    temperature REAL NOT NULL,
    cfr INT NOT NULL,
    resp_rate INT NOT NULL
);
