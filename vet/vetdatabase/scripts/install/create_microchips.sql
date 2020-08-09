CREATE TABLE microchips(
    chip_id BIGSERIAL NOT NULL PRIMARY KEY,
    chip_num VARCHAR(15) NOT NULL,
    impl_data DATE NOT NULL,
    country VARCHAR NOT NULL,
    location TEXT NOT NULL
);