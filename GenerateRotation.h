/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenerateRotation.h
 * Author: przemek
 *
 * Created on 21 stycznia 2016, 22:11
 */

#ifndef GENERATEROTATION_H
#define GENERATEROTATION_H

#include <math.h>
#include <vector>
#include <iostream>

enum ConTypes {
    START_CONNECTIONS = 0, END_CONNECTIONS = 2
};

class GenerateRotation {
public:

    GenerateRotation(double** vectors, int how_many_vectors) {
        this->inputVectors = vectors;
        this->angle = 10; // 10 stopni obrotu
        this->point_no = how_many_vectors;
    }

    double** generate() {
        int size = point_no * 3 * (360 / angle);
        double **vecs = new double*[size];
        
        double ***out = generateSkeleton();
        for (int i = 0; i < size; i++) {
            vecs[i] = new double[get_number_of_fields()];
        }

        for (int k = 0; k < point_no; k++) {
            for (int j = 0; j < 360 / angle; j++) {
                for (int i = 0; i < get_number_of_fields(); i++) {
                    vecs[k * (360 / angle) + j][i] = out[k][j][i];
                }
            }
        }

        free_3d_arr(out);

        ConTypes startConnections = START_CONNECTIONS;
        out = generateConnections(startConnections);
        for (int k = point_no; k < point_no * 2; k++) {
            for (int j = 0; j < 360 / angle; j++) {
                for (int i = 0; i < get_number_of_fields(); i++) {
                    vecs[k * (360 / angle) + j][i] = out[k - point_no][j][i];
                }
            }
        }
        
        free_3d_arr(out);

        ConTypes endConnections = END_CONNECTIONS;
        out = generateConnections(endConnections);
        for (int k = point_no * 2; k < point_no * 3; k++) {
            for (int j = 0; j < 360 / angle; j++) {
                for (int i = 0; i < get_number_of_fields(); i++) {
                    vecs[k * (360 / angle) + j][i] = out[k - 2 * point_no][j][i];
                }
            }
        }
//        printTable(vecs, point_no * 3 * (360/angle), number_of_fields);
        free_3d_arr(out);
        return vecs;
    }

    int get_number_of_fields() {
        return number_of_fields;
    }
    
    int get_angle() {
        return angle;
    }
    
    int get_vec_num() {
        return point_no;
    }
    
    void free_3d_arr(double ***out) {
        for (int k = 0; k < point_no; k++) {
            for (int j = 0; j < 360 / angle; j++) {
                delete [] out[k][j];
            }
            delete [] out[k];
        }
        delete [] out;
    }
    
    void free_2d_arr(double **out) {
        for (int k = 0; k < 3 * point_no * (360 / angle); k++) {
            delete [] out[k];
        }
        delete [] out;
    }
    
private:
    // tablica [ilosc_puntkow][4] - xpocz, zpocz, xkon, zkon
    double** inputVectors;

    // kąt obrotu
    int angle;

    // ilość puntków
    int point_no;

    // ilość wygenerowanych wektorów dla jednego wektora
    static const int number_of_fields = 9;

    // obraca jeden punkt o zadany kąt wokół osi Z

    double* rotateZ(double x, double y, double z, double angle) {
        double* points = new double[3];
        angle = angle * ((2 * 3.1415) / 360.0);
        points[0] = x * cos(angle) - y * sin(angle);
        points[1] = y * cos(angle) + x * sin(angle);
        points[2] = z;
        return points;
    }

    void printTable(double **table, int x, int y) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                std::cout << table[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    double*** generateSkeleton() {
        double ***generated_points = new double**[point_no];
        for (int i = 0; i < point_no; i++) {
            int size = 360 / angle;
            generated_points[i] = new double*[size];
            for (int j = 0; j < size; j++) {
                generated_points[i][j] = new double[number_of_fields];
            }
        }

        for (int i = 0; i < point_no; i++) {
            int counter = 0;
            for (double angle_multiplier = 0; angle_multiplier * angle < 360; angle_multiplier++) {
                double *start_points = rotateZ(inputVectors[i][0], 0, inputVectors[i][1], angle * angle_multiplier);
                double *end_points = rotateZ(inputVectors[i][2], 0, inputVectors[i][3], angle * angle_multiplier);

                generated_points[i][counter][0] = start_points[0];
                generated_points[i][counter][1] = start_points[1];
                generated_points[i][counter][2] = start_points[2];
                generated_points[i][counter][3] = end_points[0];
                generated_points[i][counter][4] = end_points[1];
                generated_points[i][counter][5] = end_points[2];
                generated_points[i][counter][6] = 255;
                generated_points[i][counter][7] = 0;
                generated_points[i][counter][8] = 0;

                delete [] start_points;
                delete [] end_points;
                counter++;
            }

        }
        return generated_points;
    }

    double*** generateConnections(ConTypes ctype) {
        double ***generated_points = new double**[point_no];
        for (int i = 0; i < point_no; i++) {
            int size = (360 / angle) + 1;
            generated_points[i] = new double*[size];
            for (int j = 0; j < size; j++) {
                generated_points[i][j] = new double[number_of_fields];
            }
        }

        double pre_start_x,
                pre_start_y,
                pre_start_z;

        for (int i = 0; i < point_no; i++) {
            int counter = 0;
            for (double angle_multiplier = 0; angle_multiplier * angle <= 360; angle_multiplier++) {
                double *start_points = rotateZ(inputVectors[i][0 + static_cast<int> (ctype)], 0, inputVectors[i][1 + static_cast<int> (ctype)], angle * angle_multiplier);

                if (angle_multiplier == 0) {
                    pre_start_x = start_points[0];
                    pre_start_y = start_points[1];
                    pre_start_z = start_points[2];

                    delete [] start_points;
                    double *start_points = rotateZ(inputVectors[i][0 + static_cast<int> (ctype)], 0, inputVectors[i][1 + static_cast<int> (ctype)], -angle);
                    generated_points[i][counter][0] = start_points[0];
                    generated_points[i][counter][1] = start_points[1];
                    generated_points[i][counter][2] = start_points[2];
                    generated_points[i][counter][3] = pre_start_x;
                    generated_points[i][counter][4] = pre_start_y;
                    generated_points[i][counter][5] = pre_start_z;
                    generated_points[i][counter][6] = 255;
                    generated_points[i][counter][7] = 0;
                    generated_points[i][counter][8] = 0;

                } else {
                    generated_points[i][counter][0] = start_points[0];
                    generated_points[i][counter][1] = start_points[1];
                    generated_points[i][counter][2] = start_points[2];
                    generated_points[i][counter][3] = pre_start_x;
                    generated_points[i][counter][4] = pre_start_y;
                    generated_points[i][counter][5] = pre_start_z;
                    generated_points[i][counter][6] = 255;
                    generated_points[i][counter][7] = 0;
                    generated_points[i][counter][8] = 0;

                    pre_start_x = start_points[0];
                    pre_start_y = start_points[1];
                    pre_start_z = start_points[2];
                }

                delete [] start_points;
                counter++;
            }

        }
        return generated_points;
    }
};


#endif /* GENERATEROTATION_H */

