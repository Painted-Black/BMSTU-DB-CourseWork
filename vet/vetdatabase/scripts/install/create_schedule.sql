CREATE TYPE day_of_week_type AS ENUM('Sun', 'Mod', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat');

CREATE TABLE schedule(
    shed_id SERIAL NOT NULL PRIMARY KEY,
    employee_id INT NOT NULL,
    day_of_week day_of_week_type NOT NULL,
    "type" VARCHAR(256) NOT NULL,
    "start" TIMESTAMP NOT NULL,
    "end" TIMESTAMP NOT NULL,
    cabinet VARCHAR(5)
);
