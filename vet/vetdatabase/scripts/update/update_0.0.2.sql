--ALTER TABLE public.schedule ALTER COLUMN "start" TYPE time USING "start"::time;
--ALTER TABLE public.schedule ALTER COLUMN "end" TYPE time USING "end"::time;

INSERT INTO passports (surname, name, patronymic, sex, birth, num, issue_date, nationality) VALUES ('Администраторов', 'Администратор', 'Администратович', 'm', '1994-04-06', '4516943943', '2014-04-09', 'Русский');

INSERT INTO position (title, salary) VALUES ('Системный администратор', 60000);

INSERT INTO staff (passport, position, edu_level, fire_date, employ_date) VALUES (1, 1, 'specialist', NULL, '2015-04-06');

INSERT INTO access (employee, login, password, access_level) VALUES (1, 'admin', 'qwerty', 'admin');

INSERT INTO schedule (employee_id, day_of_week, start, "end", cabinet) VALUES (1, 'Mon', '09:00', '18:00', 'Серверная');
INSERT INTO schedule (employee_id, day_of_week, start, "end", cabinet) VALUES (1, 'Wed', '09:00', '18:00', 'Серверная');
INSERT INTO schedule (employee_id, day_of_week, start, "end", cabinet) VALUES (1, 'Fri', '09:00', '18:00', 'Серверная');

--INSERT INTO animal_states(general, pulse, weight, ap, temperature, cfr, resp_rate) VALUES ('middle', 60, 20, '140/60', 36.7, 40, 46);
INSERT INTO addresses (country, city, street, house, flat) VALUES ('Russia', 'Moscow', 'Izmaylovskaja', '73/2', NULL);
INSERT INTO passports (surname, name, patronymic, sex, birth, num, issue_date, nationality) VALUES ('Клиентов', 'Клиент', 'Клиентович', 'm', '1993-02-06', '4546943943', '2013-02-09', 'Русский');
INSERT INTO clients (contacts, address, passport) VALUES ('{"phone" : "89993452845"}', 1, 2);
INSERT INTO contract (code, conclusion_date, last_update_date, owner, valid_until) VALUES ('32332-2020', '2019-01-02', '2019-01-02',  1, '2021-01-02');
INSERT INTO microchips (chip_num, impl_date, country, location) VALUES ('49434-2020', '2018-01-02', 'RUS' , 'Холка');
INSERT INTO animals_medical_records (name, breed, species, sex, castrated, birth, other_data, color, special_signs, registr_date, chip_id, contract, rel_path_to_photo) VALUES ('Голливуд', 'Донская', 'Конь', 'm', 'f', '1994-02-15', '', 'Рыжий', 'Вредный', '2018-02-01', 1, 1, '');
