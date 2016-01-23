/** 
 * @file GenerateRotation.h
 * @author Przemek
 * @brief Ten nagłówek zawiera klasę transformującą punkty z płaszczyzny 2d w bryłę obrotową.
 */

#ifndef GENERATEROTATION_H
#define GENERATEROTATION_H

#include <math.h>
#include <vector>
#include <iostream>

/**
* @enum ConTypes
* @brief Enum używany do sterowania jedną z metod klasy GenerateRotation.
* Na podstawie wartości przekazanej jako instacja tego enuma, generowane są połączenia między początkami albo końcami wektorów.
*/
enum ConTypes {
    START_CONNECTIONS = 0, END_CONNECTIONS = 2
};

/**
* @class GenerateRotation
* @brief Klasa transformująca wektory 2D w przestrzeń 3D tworząc bryłę obrotową.
* Przekazując tablicę z danymi o wektorach na płaszczyźnie można wygenerować figurę
* przestrzenną uzyskaną poprzez obrót wektora wokół osi OZ. Obrót wykonywany jest ze
* stałym krokiem PI/16 radianów (10 stopni).  
*/
class GenerateRotation {
public:
    /**
    * @brief Konstruktor GenerateRotation.
    * @param vectors dwuwymiarowa tablica wektorów w postaci: ilość_wektorów*4, drugi wymiar tablicy przechowuje dane w postaci: początek, koniec.
    * @param how_many_vectors ilość wektorów w tablicy.
    */
    GenerateRotation(double** vectors, int how_many_vectors) {
        this->inputVectors = vectors;
        this->angle = 10; // 10 stopni obrotu
        this->point_no = how_many_vectors;
    }
    
    /**
    * @brief Funkcja generująca dane o figurze 3D.
    * Przeprowadza dane z płaszczyzny i generuje po kolei: szkielet figury, połączenia miedzy początkami i końcami wektorów.
    */
    double** generate();
    
    // Helpery (bez znaczenia dla architektury nie odzwierciedlone w dokumentacji i UML)
    void free_3d_arr(double ***out);
    void free_2d_arr(double **out);
    double ***create_3d_arr();
    
    // Getery (bez znaczenia dla architektury nie odzwierciedlone w dokumentacji i UML)
    int get_number_of_fields() { return number_of_fields; }
    int get_angle() { return angle; }
    int get_vec_num() { return point_no; }

private:
    double** inputVectors; /**< Przechowuje dane narysowanej figury 2D. */
    int angle;             /**< Zadany kąt-krok z którym rysowane są figury. */
    int point_no;          /**< Ilość wygenerowanych przez użytkownika puntków. */
    static const int number_of_fields = 9; /**< Ilość pól w danych wyjściowch (9 odnosi się bezpośrednio do formatu danych programu dr Malinowskiego). */
    
    /**
    * @brief Metoda generująca połączenia między końcami figury 3D.
    * @param ctype typ połączeń, możliwe wartości to: START_CONNECTIONS i END_CONNECTIONS.
    */
    double ***generateConnections(ConTypes ctype);
    
    /**
    * @brief Metoda generująca szkielet figury 3D. 
    */
    double ***generateSkeleton();
    
    /**
    * @brief Metoda przeliczająca rotację punktu wokół osi Z, z zadanym kątem.
    * @param x współrzędna x punktu.
    * @param y współrzędna y punktu.
    * @param z współrzędna z punktu.
    * @param angle zadany kąt w stopniach. 
    */
    double *rotateZ(double x, double y, double z, double angle);
    
};

#endif /* GENERATEROTATION_H */

