CREATE TABLE animals_medical_records(
    anim_id SERIAL NOT NULL PRIMARY KEY,
    name VARCHAR(64) NOT NULL,
    breed TEXT NOT NULL,
    species TEXT NOT NULL,
    sex sex_type NOT NULL,
    castrated BOOLEAN NOT NULL DEFAULT('f'),
    birth DATE NOT NULL,
    other_data TEXT NOT NULL,
    color TEXT NOT NULL,
    specil_signs TEXT NOT NULL,
    registr_date DATE NOT NULL,
    last_visit DATE NOT NULL,
    chip_id INT NOT NULL,
    contract INT NOT NULL,
    rel_path_to_photo VARCHAR(255) NOT NULL
);
