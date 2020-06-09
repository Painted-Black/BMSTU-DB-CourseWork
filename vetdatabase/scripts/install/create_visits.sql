CREATE TYPE owner_dynamics_type AS ENUM('stably', 'worse', 'better');

CREATE TABLE visits(
    vis_id BIGSERIAL NOT NULL PRIMARY KEY,
    doctor INT NOT NULL,
    animal INT NOT NULL,
    ambulatury BOOLEAN NOT NULL,
    visit_date DATE NOT NULL,
    owner_dynamics owner_dynamics_type NOT NULL,
    history_disease TEXT NOT NULL,
    cur_state INT NOT NULL,
    diagnosis TEXT NOT NULL,
    recommendations TEXT NOT NULL,
    next_visit DATE NOT NULL,
    prescribings JSON NOT NULL,
    initial BOOLEAN NOT NULL,
    note TEXT NOT NULL
);