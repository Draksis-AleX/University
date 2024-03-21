--------------------------------- MOSTRA TUTTI GLI INSEGNANTI PER OGNI DISCIPLINA --------------------------------------------

SELECT DISTINCT *
FROM tessera_atleta, tesserato, disciplina
WHERE tesserato.cf = tessera_atleta.cf AND tessera_atleta.id_disciplina = disciplina.id
	AND (tessera_atleta.qualifica = "allenatore" OR tessera_atleta.qualifica = "maestro")
ORDER BY disciplina.id

--------------------------------- MOSTRA TUTTI GLI ALLIEVI PER OGNI DISCIPLINA ------------------------------------------------

SELECT DISTINCT *
FROM tessera_atleta, tesserato, disciplina
WHERE tesserato.cf = tessera_atleta.cf AND tessera_atleta.id_disciplina = disciplina.id
	AND (tessera_atleta.qualifica = "atleta" OR tessera_atleta.qualifica = "aspirante allenatore")
ORDER BY disciplina.id

--------------------------------- MOSTRA A QUALI CORSI PARTECIPA OGNI TESSERATO -----------------------------------------------

SELECT tesserato.cf, corso.nome AS corso, corso.id AS id_corso
FROM tesserato, corso, partecipa_corso
WHERE tesserato.cf = partecipa_corso.cf AND partecipa_corso.id_corso = corso.id
ORDER BY tesserato.cf

--------------------------------- MOSTRA QUALI CORSI TIENE OGNI TESSERATO -----------------------------------------------------

SELECT tesserato.cf, corso.nome AS corso, corso.id AS id_corso
FROM tesserato, corso, tiene_corso
WHERE tesserato.cf = tiene_corso.cf AND tiene_corso.id_corso = corso.id
ORDER BY tesserato.cf

--------------------------------- MOSTRA COMPETIZIONI TERMINATE ---------------------------------------------------------------

SELECT *, DATE_ADD(competizione.orario, interval competizione.durata_minuti minute) as OrarioFine
FROM competizione
WHERE competizione.data_competizione < NOW() OR 
	DATE_ADD(competizione.orario, interval competizione.durata_minuti minute) < NOW()



