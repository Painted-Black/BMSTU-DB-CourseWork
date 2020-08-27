CREATE TYPE day_of_week_type AS ENUM('Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat');

CREATE TABLE schedule(
    shed_id SERIAL NOT NULL PRIMARY KEY,
    employee_id INT NOT NULL,
    day_of_week day_of_week_type NOT NULL,
    "start" TIME NOT NULL,
    "end" TIME NOT NULL,
    cabinet VARCHAR(10)
);
