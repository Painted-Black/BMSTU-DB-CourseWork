CREATE TABLE microchips(
    chip_id SERIAL NOT NULL PRIMARY KEY,
    chip_num VARCHAR(15) NOT NULL,
    impl_date DATE NOT NULL,
    country VARCHAR(3) NOT NULL,
    location TEXT NOT NULL
);
