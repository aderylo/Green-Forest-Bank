#ifndef PHONE_NUMBERS_VECTOR_H
#define PHONE_NUMBERS_VECTOR_H

#include <stddef.h>

#define UNDEFINE -1
#define SUCCESS 0

typedef struct vector vector;

/** @brief Inicjalizuje pusty vector.
 * Udostępnia wskaźnik na pusty vector.
 * @return Wskaźnik na pusty vector. Wartość NULL, jeśli
 *         wystąpiły problemy z allokowaniem pamięci.
 */
vector *vectorInit();

/** @brief Zwraca liczbę przechowywanych elementów w wektorze.
 * @param[in] v – wskaźnik na wektor;
 * @return Liczbe elementów przechowywanych w @p v.
 */
size_t vectorSize(vector *v);

/** @brief Zwraca wskaznik na element pod dannym indeksem.
 * @param[in] v – wskaźnik na wektor;
 * @param[in] idx – indeks elementu;
 * @return Zwraca wskaznik na element znajdujący się na idx miejscu w
 * wektorze @param v. NULL, jeżeli ten element to NULL bądź jeżeli pod
 * zadanym ideksem nie ma żadnego elementu.
 */
void *vectorGet(vector *v, size_t idx);

/** @brief Dodaje element na koniec wektora.
 * Konkretnie to dodaje wskaznik na element na koniec wektora.
 * @param[in] v – wskaźnik na wektor;
 * @param[in] item – wskaznik na element.
 * @return Zwraca wartość UNDEFINED (-1) jeżeli nie udało się dodać elementu do wektora.
 * W przeciwnym wypadku zwraca SUCCESS (0).
 */
int vectorPushBack(vector *v, void *item);

/** @brief Zmienia wartość pod indeksem.
 * Zmienia wskaźnik na element pod danym indeksem na nowy podany jako @p item.
 * @param[in] v – wskaźnik na wektor;
 * @param[in] item – wskaznik na element.
 * @return Zwraca wartość UNDEFINED (-1) jeżeli nie udało się zmienić elementu w wektorze.
 * W przeciwnym wypadku zwraca SUCCESS (0).
 */
int vectorSet(vector *v, size_t index, void *item);

/** @brief Usuwa element z wektora.
 * Usuwa wkaznik na element wektora, który znajduje się pod indeksem @p idx. Funkcja usuwa
 * wskaznik wyłącznie z struktury wektora, nie czyści pamięci na jaką wskaźnik wskazuje.
 * @param[in] v – wskaźnik na wektor;
 * @param[in] idx – indeks.
 * @return Zwraca wartość UNDEFINED (-1) jeżeli nie udało usunąć element z pamięci wekora.
 * W przeciwnym wypadku zwraca SUCCESS (0).
 */
int vectorRemove(vector *v, size_t idx);

/** @brief Usuwa wektor.
 * Usuwa strukturę włącznie z wskaznikiem na nią  (@p v). Funkcja ta nie
 * czyści pamięci swoich elementów, tylko i wyłącznie własną.
 * @param[in] v – wskaźnik na wektor;
 * @return Zwraca wartość UNDEFINED (-1) jeżeli nie udało usunąć element z pamięci wekora.
 * W przeciwnym wypadku zwraca SUCCESS (0).
 */
int vectorFree(vector *v);

/** @brief Zwraca wskaznik na początek wektora.
 * Zwraca wskaznik na początek wektora analogicznie do funkcji .begin() w cpp.
 * Robi to tak aby można było się iterować po zawartosci wektora np. sortując.
 * @param[in] v – wskaźnik na wektor;
 * @return Zwraca wskaznik na początek wektora, jeżeli wektor jest pusty to
 * zwraca NULL.
 */
void **vectorBegin(vector *v);

/** Czyści z pamięci całkowicie wektor przechowujący elementy
 * zwalnialne za pomocą @param destructor.
 * @param v wektor zawierający elementy o współdzielące jeden destruktor.
 * @param destructor Wspólny destruktor dla wszystkich elementów w wektorze.
 * @return Zwraca wartość UNDEFINED (-1) jeżeli nie udało się zwolnić pamięć po wektorze i jego
 * elementach. W przeciwnym wypadku zwraca SUCCESS (0).
 */
int vectorPurge(vector *v, void (*destructor)(void *));

vector *strToVec(char *string, char *whitespace);


#endif  // PHONE_NUMBERS_VECTOR_H
