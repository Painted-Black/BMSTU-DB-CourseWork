DROP TABLE vaccinations;

INSERT INTO passports (surname, name, patronymic, sex, birth, num, issue_date, nationality) VALUES ('Администраторов', 'Администратор, 'Администратович, 'm', '1994-04-06', '4516943943', '2014-04-09');

INSERT INTO positions (title, salary) VALUES ('Системный администратор', 60000);

INSERT INTO staff (passport, position, edu_level, fire_date, employ_date) VALUES (1, 1, 'specialist', NULL, '2015-04-06');

INSERT INTO access (employee, login, password, access_level) VALUES (1, 'admin', 'qwerty', 'admin');

INSERT INTO schedule (employee_id, day_of_week, start, "end", cabinet) VALUES (1, 'Mon', '09:00', '18:00', 'Серверная');
INSERT INTO schedule (employee_id, day_of_week, start, "end", cabinet) VALUES (1, 'Wed', '09:00', '18:00', 'Серверная');
INSERT INTO schedule (employee_id, day_of_week, start, "end", cabinet) VALUES (1, 'Fri', '09:00', '18:00', 'Серверная');
