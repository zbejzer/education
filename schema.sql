-- ==========================================
-- Tworzenie Tabel
-- ==========================================

CREATE TABLE klient (
    id SERIAL PRIMARY KEY,
    imie VARCHAR(100) NOT NULL,
    nazwisko VARCHAR(100) NOT NULL,
    email VARCHAR(200) NOT NULL,
    CONSTRAINT chk_klient_email CHECK (email LIKE '%_@__%.__%')
);


CREATE TABLE producent (
    id SERIAL PRIMARY KEY,
    nazwa VARCHAR(50) NOT NULL
);


CREATE TABLE filament_material (
    id SERIAL PRIMARY KEY,
    nazwa VARCHAR(20) NOT NULL
);


CREATE TABLE model (
    id SERIAL PRIMARY KEY,
    klient_id INT NOT NULL REFERENCES klient(id),
    nazwa TEXT NOT NULL,
    format VARCHAR(10),
    wysokosc INT,
    szerokosc INT,
    dlugosc INT,
    plik BYTEA,
    CONSTRAINT chk_model_dimensions CHECK (wysokosc >= 0 AND szerokosc >= 0 AND dlugosc >= 0)
);


CREATE TABLE filament_kolor (
    id SERIAL PRIMARY KEY,
    producent_id INT NOT NULL REFERENCES producent(id),
    nazwa VARCHAR(50) NOT NULL,
    ral VARCHAR(7),
    CONSTRAINT chk_filament_ral CHECK (length(ral) >= 4)
);


CREATE TABLE drukarka_model (
    id SERIAL PRIMARY KEY,
    producent_id INT NOT NULL REFERENCES producent(id),
    nazwa TEXT NOT NULL,
    pole_wysokosc INT,
    pole_szerokosc INT,
    pole_dlugosc INT,
    CONSTRAINT chk_drukarka_model_volume CHECK (pole_wysokosc > 0 AND pole_szerokosc > 0 AND pole_dlugosc > 0)
);


CREATE TABLE filament (
    id SERIAL PRIMARY KEY,
    kolor_id INT NOT NULL REFERENCES filament_kolor(id),
    material_id INT NOT NULL REFERENCES filament_material(id),
    cena REAL,
    masa REAL,
    CONSTRAINT chk_filament_cena CHECK (cena >= 0),
    CONSTRAINT chk_filament_masa CHECK (masa > 0)
);


CREATE TABLE drukarka (
    id SERIAL PRIMARY KEY,
    model_id INT NOT NULL REFERENCES drukarka_model(id)
);


CREATE TABLE filament_szpula (
    id SERIAL PRIMARY KEY,
    filament_id INT NOT NULL REFERENCES filament(id)
);


CREATE TABLE zlecenie (
    id SERIAL PRIMARY KEY,
    klient_id INT NOT NULL REFERENCES klient(id),
    model_id INT NOT NULL REFERENCES model(id),
    filament_id INT NOT NULL REFERENCES filament(id),
    termin DATE,
    wplyniecie TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    cena REAL,
    CONSTRAINT chk_zlecenie_cena CHECK (cena >= 0),
    CONSTRAINT chk_zlecenie_dates CHECK (termin >= wplyniecie::DATE)
);


CREATE TABLE historia_wydruk (
    id SERIAL PRIMARY KEY,
    zlecenie_id INT NOT NULL REFERENCES zlecenie(id),
    drukarka_id INT NOT NULL REFERENCES drukarka(id),
    szpula_id INT NOT NULL REFERENCES filament_szpula(id),
    sukces BOOLEAN,
    rozpoczecie TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    zakonczenie TIMESTAMP WITH TIME ZONE,
    masa REAL,
    CONSTRAINT chk_historia_wydruk_times CHECK (zakonczenie >= rozpoczecie),
    CONSTRAINT chk_historia_wydruk_masa CHECK (masa >= 0)
);

-- ==========================================
-- Wprowadzenie Danych
-- ==========================================

INSERT INTO klient (imie, nazwisko, email) VALUES ('Jan', 'Kowalski', 'jan.kowalski@gmail.com');
INSERT INTO klient (imie, nazwisko, email) VALUES ('Patrycja', 'Nowak', 'patrycja.nowak@hotmail.com');
INSERT INTO klient (imie, nazwisko, email) VALUES ('Piotr', 'Wiśniewski', 'piotrw@proton.com');
INSERT INTO klient (imie, nazwisko, email) VALUES ('Maria', 'Wójcik', 'm.wojcik@onet.pl');
INSERT INTO klient (imie, nazwisko, email) VALUES ('Adam', 'Kamiński', 'ak@op.pl');

INSERT INTO producent (nazwa) VALUES ('Prusa Research');
INSERT INTO producent (nazwa) VALUES ('Fiberlogy');
INSERT INTO producent (nazwa) VALUES ('Devil Design');
INSERT INTO producent (nazwa) VALUES ('F3D');
INSERT INTO producent (nazwa) VALUES ('eSUN');
INSERT INTO producent (nazwa) VALUES ('Creality');
INSERT INTO producent (nazwa) VALUES ('Bambu Lab');
INSERT INTO producent (nazwa) VALUES ('Ultimaker');
INSERT INTO producent (nazwa) VALUES ('Anycubic');

INSERT INTO filament_material (nazwa) VALUES ('PLA');
INSERT INTO filament_material (nazwa) VALUES ('PETG');
INSERT INTO filament_material (nazwa) VALUES ('ABS');
INSERT INTO filament_material (nazwa) VALUES ('ASA');
INSERT INTO filament_material (nazwa) VALUES ('TPU');

INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (1, 'Prusa Orange', '2004');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (1, 'Galaxy Black', '9005');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (1, 'Silver', '9006');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (2, 'Burgundy', '3005');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (2, 'Graphite', '7024');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (2, 'Light Green', '6018');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (2, 'White', '9016');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (3, 'Super Blue', '5015');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (3, 'Ruby Red', '3003');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (3, 'Bright Yellow', '1023');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (3, 'Hot Pink', '4003');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (4, 'Deep Black', '9011');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (4, 'Military Green', '6003');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (5, 'Fire Red', '3000');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (5, 'Pine Green', '6028');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (5, 'Cold White', '9003');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (7, 'Bambu Green', '6038');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (7, 'Matte Dark Grey', '7016');
INSERT INTO filament_kolor (producent_id, nazwa, ral) VALUES (7, 'Matte Ivory White', '1013');

INSERT INTO model (klient_id, nazwa, format, wysokosc, szerokosc, dlugosc) VALUES (1, 'Benchy boat', 'stl', 48, 31, 60);
INSERT INTO model (klient_id, nazwa, format, wysokosc, szerokosc, dlugosc) VALUES (2, 'Wazon dekoracyjny', 'obj', 150, 80, 80);
INSERT INTO model (klient_id, nazwa, format, wysokosc, szerokosc, dlugosc) VALUES (2, 'Obudowa elektroniki', 'step', 30, 100, 120);
INSERT INTO model (klient_id, nazwa, format, wysokosc, szerokosc, dlugosc) VALUES (4, 'Zebatka M4', 'stl', 15, 50, 50);
INSERT INTO model (klient_id, nazwa, format, wysokosc, szerokosc, dlugosc) VALUES (5, 'Figurka Smoka', '3mf', 120, 140, 160);

INSERT INTO drukarka_model (producent_id, nazwa, pole_wysokosc, pole_szerokosc, pole_dlugosc) VALUES (1, 'i3 MK3S+', 210, 250, 210);
INSERT INTO drukarka_model (producent_id, nazwa, pole_wysokosc, pole_szerokosc, pole_dlugosc) VALUES (6, 'Ender 3 V2', 250, 220, 220);
INSERT INTO drukarka_model (producent_id, nazwa, pole_wysokosc, pole_szerokosc, pole_dlugosc) VALUES (7, 'X1-Carbon', 256, 256, 256);
INSERT INTO drukarka_model (producent_id, nazwa, pole_wysokosc, pole_szerokosc, pole_dlugosc) VALUES (8, 'S5', 300, 330, 240);
INSERT INTO drukarka_model (producent_id, nazwa, pole_wysokosc, pole_szerokosc, pole_dlugosc) VALUES (9, 'Mega S', 205, 210, 210);

INSERT INTO filament (kolor_id, material_id, cena, masa) VALUES (2, 1, 119.00, 1000);
INSERT INTO filament (kolor_id, material_id, cena, masa) VALUES (5, 2, 99.50, 850);
INSERT INTO filament (kolor_id, material_id, cena, masa) VALUES (6, 3, 85.00, 1000);
INSERT INTO filament (kolor_id, material_id, cena, masa) VALUES (11, 3, 145.00, 750);
INSERT INTO filament (kolor_id, material_id, cena, masa) VALUES (14, 5, 160.00, 500);

INSERT INTO drukarka (model_id) VALUES (1);
INSERT INTO drukarka (model_id) VALUES (2);
INSERT INTO drukarka (model_id) VALUES (3);
INSERT INTO drukarka (model_id) VALUES (4);
INSERT INTO drukarka (model_id) VALUES (5);

INSERT INTO filament_szpula (filament_id) VALUES (1);
INSERT INTO filament_szpula (filament_id) VALUES (2);
INSERT INTO filament_szpula (filament_id) VALUES (3);
INSERT INTO filament_szpula ( filament_id) VALUES (4);
INSERT INTO filament_szpula ( filament_id) VALUES (5);
INSERT INTO filament_szpula ( filament_id) VALUES (4);
INSERT INTO filament_szpula (filament_id) VALUES (2);
INSERT INTO filament_szpula (filament_id) VALUES (2);

INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (1, 2, 3, '2026-01-10', '2026-01-05 10:00:00+02', 45.50);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (1, 4, 5, TRUE, '2026-01-05 12:00:00+02', '2026-01-05 15:15:00+02', 24.5);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (2, 3, 4, '2026-01-25', '2026-01-20 09:00:00+02', 55.00);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (2, 1, 2, FALSE, '2026-01-20 11:00:00+02', '2026-01-20 11:45:00+02', 4.2);
INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (2, 1, 2, TRUE, '2026-01-20 13:00:00+02', '2026-01-20 16:30:00+02', 31.0);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (3, 4, 5, '2026-02-15', '2026-02-10 14:00:00+02', 61.00);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (3, 5, 1, TRUE, '2026-02-10 15:30:00+02', '2026-02-10 19:00:00+02', 29.0);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (4, 5, 1, '2026-03-12', '2026-03-07 08:30:00+02', 76.50);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (4, 2, 3, TRUE, '2026-03-07 10:00:00+02', '2026-03-07 13:15:00+02', 33.5);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (5, 1, 2, '2026-03-24', '2026-03-19 11:15:00+02', 92.00);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (5, 3, 4, FALSE, '2026-03-19 13:00:00+02', '2026-03-19 13:45:00+02', 5.5);
INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (5, 3, 4, FALSE, '2026-03-19 14:45:00+02', '2026-03-19 15:30:00+02', 6.5);
INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (5, 3, 4, TRUE, '2026-03-19 16:30:00+02', '2026-03-19 19:45:00+02', 38.0);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (1, 2, 3, '2026-04-18', '2026-04-13 10:00:00+02', 107.50);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (6, 4, 5, TRUE, '2026-04-13 12:00:00+02', '2026-04-13 15:15:00+02', 42.5);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (2, 3, 4, '2026-05-10', '2026-05-05 09:00:00+02', 123.00);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (7, 5, 1, FALSE, '2026-05-05 11:00:00+02', '2026-05-05 11:45:00+02', 5.5);
INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (7, 5, 1, TRUE, '2026-05-05 12:45:00+02', '2026-05-05 16:00:00+02', 47.0);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (3, 4, 5, '2026-05-28', '2026-05-23 13:00:00+02', 135.00);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (8, 1, 2, TRUE, '2026-05-23 14:30:00+02', '2026-05-23 18:00:00+02', 49.5);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (4, 5, 1, '2026-06-14', '2026-06-09 10:00:00+02', 138.50);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (9, 2, 3, TRUE, '2026-06-09 12:00:00+02', '2026-06-09 15:15:00+02', 51.5);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (5, 1, 2, '2026-07-22', '2026-07-17 10:00:00+02', 154.00);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (10, 3, 4, FALSE, '2026-07-17 12:00:00+02', '2026-07-17 12:45:00+02', 5.5);
INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (10, 3, 4, TRUE, '2026-07-17 13:45:00+02', '2026-07-17 17:00:00+02', 56.0);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (1, 2, 3, '2026-08-19', '2026-08-14 10:00:00+02', 169.50);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (11, 4, 5, TRUE, '2026-08-14 12:00:00+02', '2026-08-14 15:15:00+02', 60.5);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (2, 3, 4, '2026-09-12', '2026-09-07 10:00:00+02', 185.00);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (12, 5, 1, FALSE, '2026-09-07 12:00:00+02', '2026-09-07 12:45:00+02', 5.5);
INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (12, 5, 1, TRUE, '2026-09-07 13:45:00+02', '2026-09-07 17:00:00+02', 65.0);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (3, 4, 5, '2026-10-11', '2026-10-06 10:00:00+02', 200.50);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (13, 1, 2, TRUE, '2026-10-06 12:00:00+02', '2026-10-06 15:15:00+02', 69.5);
INSERT INTO zlecenie (klient_id, model_id, filament_id, termin, wplyniecie, cena) VALUES (4, 5, 1, '2026-11-20', '2026-11-15 10:00:00+02', 216.00);

INSERT INTO historia_wydruk (zlecenie_id, drukarka_id, szpula_id, sukces, rozpoczecie, zakonczenie, masa) VALUES (14, 2, 3, TRUE, '2026-11-15 12:00:00+02', '2026-11-15 15:15:00+02', 74.0);