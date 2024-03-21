INSERT INTO disciplina (nome, descrizione)
VALUES
    ('Karate', 'Arte marziale giapponese basata su colpi di pugno e calci.'),
    ('Judo', 'Sport da combattimento giapponese incentrato sulle prese e le proiezioni.'),
    ('Taekwondo', 'Arte marziale coreana con un enfasi sui calci acrobatici.'),
    ('Jiu-Jitsu', 'Disciplina di lotta e sottomissione di origine giapponese e brasiliana.'),
    ('Aikido', "Arte marziale giapponese incentrata sulla difesa e l'uso della forza dell'avversario.");

INSERT INTO corso (nome, giorni, ora_inizio, ora_fine, prezzo_mensile, num_partecipanti, id_disciplina)
VALUES
    ('Corso di Karate Base', 'Lunedi, Mercoledi, Venerdi', '10:00:00', '11:00:00', 35.00, 0, 1),
    ('Corso di Karate Avanzato', 'Lunedi, Mercoledi, Venerdi', '11:00:00', '13:00:00', 50.00, 0, 1),
    ('Corso di Judo Base', 'Martedi, Giovedi', '17:30:00', '18:30:00', 35.00, 0, 2),
    ('Corso di Judo Avanzato', 'Martedi, Giovedi', '18:30:00', '20:30:00', 50.00, 0, 2),
    ('Corso di Taekwondo', 'Lunedi, Mercoledi', '15:00:00', '16:30:00', 40.00, 0, 3),
    ('Corso di Jiu-Jitsu Base', 'Lunedi, Mercoledi, Venerdi', '19:00:00', '20:00:00', 35.00, 0, 4),
    ('Corso di Jiu-Jitsu Avanzato', 'Lunedi, Mercoledi, Venerdi', '20:00:00', '22:00:00', 50.00, 0, 4),
    ('Corso di Aikido Base', 'Venerdi, Sabato', '15:00:00', '16:30:00', 35.00, 0, 5),
    ('Corso di Aikido Avanzato', 'Venerdi, Sabato', '16:30:00', '18:30:00', 50.00, 0, 5),
    ('Corso Agonistico Fighting', 'Martedi, Giovedi', '15:30:00', '16:30:00', 20.00, 0, 4),
    ('Corso Agonistico Duo System', 'Martedi, Giovedi', '16:30:00', '17:30:00', 20.00, 0, 4),
    ('Corso Agonistico Grappling', 'Martedi, Giovedi', '11:30:00', '12:30:00', 20.00, 0, 4);

INSERT INTO tesserato (cf, nome, cognome, luogo_nascita, data_nascita)
VALUES
    ('ABC12345A1234567', 'Mario', 'Rossi', 'Milano', '1990-05-10'),
    ('DEF67890B2345678', 'Laura', 'Bianchi', 'Roma', '1985-07-15'),
    ('GHI12345C3456789', 'Luigi', 'Verdi', 'Napoli', '1992-03-20'),
    ('JKL67890D4567890', 'Anna', 'Marrone', 'Palermo', '1988-09-25'),
    ('MNO12345E5678901', 'Giovanni', 'Neri', 'Firenze', '1994-01-05'),
    ('PQR67890F6789012', 'Francesca', 'Rosa', 'Bologna', '1986-11-30'),
    ('STU12345G7890123', 'Roberto', 'Gialli', 'Torino', '1991-08-08'),
    ('VWX67890H8901234', 'Elisa', 'Azzurri', 'Genova', '1989-12-18'),
    ('YZA12345I9012345', 'Paolo', 'Viola', 'Venezia', '1993-04-03'),
    ('BCD67890J0123456', 'Martina', 'Arancione', 'Bari', '1987-06-12'),
    ('EFG12345K1234567', 'Andrea', 'Celeste', 'Cagliari', '1995-02-28'),
    ('HIJ67890L2345678', 'Simona', 'Magenta', 'Catania', '1990-10-22'),
    ('KLM12345M3456789', 'Riccardo', 'Turchese', 'Trieste', '1984-07-07'),
    ('NOP67890N4567890', 'Luisa', 'Indaco', 'Verona', '1997-09-14'),
    ('PQR12345O5678901', 'Marco', 'Grigio', 'Modena', '1992-03-01'),
    ('STU67890P6789012', 'Chiara', 'Marrone', 'Reggio Calabria', '1986-05-24'),
    ('VWX12345Q7890123', 'Davide', 'Verdi', 'Lecce', '1994-01-29'),
    ('YZA67890R8901234', 'Silvia', 'Rosa', 'Ancona', '1988-11-16'),
    ('BCD12345S9012345', 'Alessio', 'Blu', 'Pisa', '1993-08-03'),
    ('EFG67890T0123456', 'Elena', 'Arancione', 'Brescia', '1985-12-12');

INSERT INTO tessera_dirigente (data_emissione, data_scadenza, carica, cf)
VALUES
    ('2023-01-15', '2024-01-15', 'presidente', 'ABC12345A1234567'),
    ('2023-02-10', '2024-02-10', 'segretario', 'DEF67890B2345678'),
    ('2023-03-05', '2024-03-05', 'consigliere', 'GHI12345C3456789'),
    ('2023-04-20', '2024-04-20', 'consigliere', 'JKL67890D4567890');

INSERT INTO tessera_atleta (data_emissione, data_scadenza, grado, qualifica, data_ultimo_passaggio, cf, id_disciplina)
VALUES
    ('2023-01-15', '2024-01-15', '5^DAN', 'maestro', '2023-11-03', 'ABC12345A1234567', 1),
    ('2023-02-10', '2024-02-10', '2^DAN', 'allenatore', '2022-11-15', 'DEF67890B2345678', 1),
    ('2023-03-05', '2024-03-05', '1^KYU', 'atleta', '2022-10-20', 'GHI12345C3456789', 1),
    ('2023-04-20', '2024-04-20', '2^KYU', 'atleta', '2022-09-25', 'JKL67890D4567890', 1),
    ('2023-05-12', '2024-05-12', '4^KYU', 'atleta', '2022-08-30', 'MNO12345E5678901', 1),
    ('2023-06-30', '2024-06-30', '5^KYU', 'atleta', '2022-07-15', 'PQR67890F6789012', 1),
    ('2023-07-22', '2024-07-22', '4^DAN', 'maestro', '2022-06-20', 'STU12345G7890123', 2),
    ('2023-08-14', '2024-08-14', '2^DAN', 'aspirante allenatore', '2022-05-10', 'VWX67890H8901234', 2),
    ('2023-09-28', '2024-09-28', '2^KYU', 'atleta', '2022-04-05', 'YZA12345I9012345', 2),
    ('2023-10-19', '2024-10-19', '4^KYU', 'atleta', '2022-03-01', 'BCD67890J0123456', 2),
    ('2023-11-30', '2024-11-30', '4^KYU', 'atleta', '2022-02-15', 'EFG12345K1234567', 2),
    ('2023-12-25', '2024-12-25', '5^KYU', 'atleta', '2022-01-10', 'HIJ67890L2345678', 2),
    ('2024-01-10', '2025-01-10', '2^DAN', 'allenatore', '2021-12-05', 'KLM12345M3456789', 3),
    ('2024-02-28', '2025-02-28', '1^KYU', 'atleta', '2021-11-20', 'NOP67890N4567890', 3),
    ('2024-03-15', '2025-03-15', '4^KYU', 'atleta', '2021-10-25', 'PQR12345O5678901', 3),
    ('2024-04-02', '2025-04-02', '5^KYU', 'atleta', '2021-09-30', 'STU67890P6789012', 3),
    ('2024-05-22', '2025-05-22', '5^DAN', 'maestro', '2021-08-15', 'VWX12345Q7890123', 4),
    ('2024-06-12', '2025-06-12', '4^DAN', 'maestro', '2021-07-20', 'YZA67890R8901234', 4),
    ('2024-07-07', '2025-07-07', '2^DAN', 'allenatore', '2021-06-25', 'BCD12345S9012345', 4),
    ('2024-08-28', '2025-08-28', '3^DAN', 'allenatore', '2021-05-30', 'EFG67890T0123456', 4),
    ('2024-09-15', '2025-09-15', '1^DAN', 'aspirante allenatore', '2021-04-15', 'ABC12345A1234567', 4),
    ('2024-10-10', '2025-10-10', '1^DAN', 'atleta', '2021-03-20', 'DEF67890B2345678', 4),
    ('2024-11-05', '2025-11-05', '4^KYU', 'atleta', '2021-02-25', 'GHI12345C3456789', 4),
    ('2024-12-20', '2025-12-20', '4^KYU', 'atleta', '2021-01-30', 'JKL67890D4567890', 4),
    ('2025-01-12', '2026-01-12', '6^KYU', 'atleta', '2020-12-25', 'MNO12345E5678901', 4),
    ('2025-02-28', '2026-02-28', '2^KYU', 'atleta', '2020-11-30', 'PQR67890F6789012', 4),
    ('2025-03-15', '2026-03-15', '6^DAN', 'maestro', '2020-11-05', 'STU12345G7890123', 5),
    ('2025-04-02', '2026-04-02', '2^DAN', 'allenatore', '2020-10-10', 'VWX67890H8901234', 5),
    ('2025-05-22', '2026-05-22', '3^KYU', 'atleta', '2020-09-15', 'YZA12345I9012345', 5),
    ('2025-06-12', '2026-06-12', '6^KYU', 'atleta', '2020-08-20', 'BCD67890J0123456', 5);

INSERT INTO competizione (nome, tipologia, data_competizione, orario, durata_minuti, id_disciplina, num_partecipanti)
VALUES
    ('Campionato di Karate I', 'Campionato Kumite', '2022-10-22', '14:30:00', 180, 1, 0),
    ('Gara di Judo I', 'Gara', '2022-11-05', '10:00:00', 120, 2, 0),
    ('Torneo di Taekwondo I', 'Torneo', '2020-12-17', '15:45:00', 90, 3, 0),
    ('Campionato di Jiu-Jitsu I', 'Campionato Fighting', '2021-01-14', '09:00:00', 150, 4, 0),
    ('Campionato di Jiu-Jitsu II', 'Campionato Duo System', '2024-02-18', '13:00:00', 120, 4, 0),
    ('Campionato di Jiu-Jitsu III', 'Campionato Grappling', '2024-03-25', '14:30:00', 120, 4, 0),
    ('Torneo di Karate II', 'Torneo Kumite', '2024-04-29', '10:30:00', 180, 1, 0),
    ('Torneo di Judo', 'Torneo', '2024-05-13', '15:00:00', 90, 2, 0),
    ('Gara di Judo II', 'Gara', '2024-06-10', '13:30:00', 120, 2, 0),
    ('Torneo di Taekwondo II', 'Torneo', '2024-07-22', '11:00:00', 90, 3, 0);

INSERT INTO partecipa_corso (cf, id_corso)
VALUES
    ("GHI12345C3456789", 2),
    ("JKL67890D4567890", 2),
    ("MNO12345E5678901", 1),
    ("PQR67890F6789012", 1),
    ("VWX67890H8901234", 4),
    ("BCD67890J0123456", 4),
    ("EFG12345K1234567", 3),
    ("HIJ67890L2345678", 3),
    ("NOP67890N4567890", 5),
    ("PQR12345O5678901", 5),
    ("STU67890P6789012", 5),
    ("ABC12345A1234567", 7),
    ("DEF67890B2345678", 7),
    ("PQR67890F6789012", 7),
    ("GHI12345C3456789", 6),
    ("JKL67890D4567890", 6),
    ("MNO12345E5678901", 6),
    ("YZA12345I9012345", 8),
    ("BCD67890J0123456", 8),
    ("GHI12345C3456789", 10),
    ("JKL67890D4567890", 10),
    ("DEF67890B2345678", 10),
    ("PQR67890F6789012", 10),
    ("GHI12345C3456789", 11),
    ("ABC12345A1234567", 11),
    ("JKL67890D4567890", 12),
    ("PQR67890F6789012", 12);

INSERT INTO tiene_corso (cf, id_corso)
VALUES
    ("ABC12345A1234567", 1),
    ("ABC12345A1234567", 2),
    ("DEF67890B2345678", 1),
	("STU12345G7890123", 3),
    ("STU12345G7890123", 4),
    ("KLM12345M3456789", 5),
    ("YZA67890R8901234", 6),
    ("BCD12345S9012345", 6),
    ("EFG67890T0123456", 6),
    ("VWX12345Q7890123", 7),
    ("EFG67890T0123456", 7),
    ("STU12345G7890123", 8),
    ("VWX67890H8901234", 8),
    ("STU12345G7890123", 9),
    ("VWX67890H8901234", 9),
    ("VWX12345Q7890123", 10),
    ("BCD12345S9012345", 10),
    ("VWX12345Q7890123", 11),
    ("EFG67890T0123456", 11),
    ("YZA67890R8901234", 12),
    ("BCD12345S9012345", 12);

INSERT INTO partecipa_competizione (cf, id_competizione, posizionamento)
VALUES
    ("VWX67890H8901234", 9, NULL),
    ("YZA12345I9012345", 9, NULL),
    ("BCD67890J0123456", 9, NULL),
    ("GHI12345C3456789", 7, NULL),
    ("JKL67890D4567890", 7, NULL),
    ("ABC12345A1234567", 6, NULL),
    ("DEF67890B2345678", 6, NULL),
    ("GHI12345C3456789", 6, NULL),
    ("JKL67890D4567890", 6, NULL),
    ("DEF67890B2345678", 4, 1),
    ("ABC12345A1234567", 4, 2),
    ("GHI12345C3456789", 1, 1),
    ("JKL67890D4567890", 1, 2),
    ("MNO12345E5678901", 1, 3);

