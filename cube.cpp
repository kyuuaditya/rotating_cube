#include <math.h>
#include <stdio.h>
#include <time.h>

// #include <fstream>
#include <iostream>

int main() {
    clock_t starttime = clock();

    // viewer distance from the screen
    float viewing_distance = 5.0f;

    float R = 3.0f;
    float d = 2.0f;
    float O = 0.0f;
    float t = 0.0f;
    float A = 0.0f;
    float B = 0.0f;

    float x, y, z, L, xd, yd;

    int height = 50;
    int width = 160;

    // std::ofstream donut;
    // std::ofstream donuti;
    // std::ofstream donut_x;
    // std::ofstream donut_y;
    // std::ofstream donut_z;
    // donut.open("donut.txt");
    // donuti.open("donuti.txt");
    // donut_x.open("donut_x.txt");
    // donut_y.open("donut_y.txt");
    // donut_z.open("donut_z.txt");

    A = 0.0;
    B = 0.0;

    // float count = 0.0;
    // float facing = 0.0;

    // int iterations = 0;
    // float total_time = 0;
    clock_t time_start = clock();
    int run = 10000;
    while (run) {
        // uncomment this next part to stop after first iteration.
        // run = run - 1;

        // iterations++;
        // for (float i = 0; i < 6.28; i += 0.07) {
        //     for (float j = 0; j < 6.28; j += 0.02) {

        // reduced dots
        for (float i = 0; i < 6.28; i += 0.28) {
            for (float j = 0; j < 6.28; j += 0.08) {
                // count++;
                O = i;
                t = j;

                float cost = cos(t);
                float sint = sin(t);
                float cosO = cos(O);
                float sinO = sin(O);
                float cosA = cos(A);
                float sinA = sin(A);
                float cosB = cos(B);
                float sinB = sin(B);

                // with reduced trignometric functions

                L = (double)cosB * (sinO * cosA + cosO * sinA * sint) -
                    cosO * cost * cosB - cosO * sint * cosA + sinO * sinA;

                if (L > 0) {
                    x = (double)(R + d * cosO) *
                            (cosB * cost + sinA * sinB * sint) -
                        d * cosA * sinB * sinO;
                    y = (double)(R + d * cosO) *
                            (cost * sinB - cosB * sinA * sint) +
                        d * cosA * cosB * sinO;
                    z = (double)cosA * (R + d * cosO) * sint + d * sinA * sinO;
                    xd = (double)x * viewing_distance / z;
                    yd = (double)y * viewing_distance / z;
                    // facing++;
                }

                // // reduced rotation
                // float cost = cos(t);
                // float sint = sin(t);
                // float cosO = cos(O);
                // float sinO = sin(O);

                // // with reduced trignometric functions
                // x = (R + d * cosO) * (cost + sint) - d * sinO;
                // y = (R + d * cosO) * (cost - sint) + d * sinO;
                // z = (R + d * cosO) * sint + d * sinO;

                // // only for testing 3d
                // donut << x << ", " << y << ", " << z << std::endl;

                // // only for testing 3d with illuminaiton
                // donuti << x << ", " << y << ", " << z << ", " << L <<
                // std::endl;

                // // only for testing 2d
                // donut_z << x << ", " << y << std::endl;
                // donut_x << y << ", " << z << std::endl;
                // donut_y << x << ", " << z << std::endl;
            }
        }
        A += 0.087;
        B += 0.087;
        // std::cout << (double)((clock() - time_start) / CLOCKS_PER_SEC) /
        //                  iterations
        //           << " " << (double)(facing / count) * 100 << " " <<
        //           std::endl;
        // count = 0;
        // facing = 0;
    }
    std::cout << (double)((clock() - time_start)) / 1000000 << std::endl;
    // donut.close();
    // donuti.close();
    // donut_x.close();
    // donut_y.close();
    // donut_z.close();
}