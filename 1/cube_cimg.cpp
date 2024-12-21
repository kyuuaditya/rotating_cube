#include <math.h>
#include <stdio.h>
#include <time.h>

#include <iostream>

#include "CImg.h"
using namespace cimg_library;

int main() {
    clock_t starttime = clock();

    CImg<unsigned char> img(800, 600, 1, 3, 0);
    // 800x600 image with 3 color channels (RGB)
    CImgDisplay display(img, "3D Projection");

    int height = img.height();
    int width = img.width();

    // viewer distance from the screen
    float viewer_x = 0.0f;
    float viewer_y = 5.0f;
    float viewer_z = 0.0f;

    // note that scree is always perpendicular to the viewer
    // these cordinates are of centre.
    float screen_x = 0.0f;
    float screen_y = 4.0f;
    float screen_z = 0.0f;
    // to be kept a factor of desired resolution of the screen.
    // for 800x600
    float screen_height = 3.0f;
    float screen_width = 4.0f;

    float viewer_to_screen =
        (double)sqrt((viewer_x - screen_x) * (viewer_x - screen_x) +
                     (viewer_y - screen_y) * (viewer_y - screen_y) +
                     (viewer_z - screen_z) * (viewer_z - screen_z));

    float R = 2.0f;  // big radius
    float d = 1.0f;  // small radius
    float O = 0.0f;  // theta
    float t = 0.0f;  // phi
    float A = 0.0f;  // angle_A
    float B = 0.0f;  // angle_B

    float x, y, z, L, xd, yd, zd;

    // int height = 50;
    // int width = 160;

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

    // A = 0.0;
    // B = 0.0;

    // float count = 0.0;
    // float facing = 0.0;

    // int iterations = 0;
    // float total_time = 0;
    clock_t time_start = clock();
    int run = 1;
    while (!display.is_closed()) {
        // while (run) {
        img.fill(0);
        // // uncomment this next part to stop after first iteration.
        // run = run - 1;

        // iterations++;
        // for (float i = 0; i < 6.28; i += 0.07) {
        //     for (float j = 0; j < 6.28; j += 0.02) {

        // reduced dots
        for (float j = 0; j < 6.28; j += 0.08) {
            for (float i = 0; i < 6.28; i += 0.28) {
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
                    xd = (double)(x - viewer_x) * viewer_to_screen /
                         abs(y - viewer_y);
                    zd = (double)(z - viewer_z) * viewer_to_screen /
                         abs(y - viewer_y);
                    // facing++;
                    // int screen_x = static_cast<int>((xd + 1) * 400);
                    // int screen_z = static_cast<int>((zd + 1) * 300);
                    // see all data
                    // std::cout << x << " " << y << " " << z << " " << xd << "
                    // "
                    //           << zd << " " << L << " " << L / (viewer_y - y)
                    //           << std::endl;

                    if (xd < screen_width / 2 && xd > -screen_width / 2 &&
                        zd < screen_height / 2 && zd > -screen_height / 2) {
                        img(xd * width / 4 + screen_width * width / 8,
                            zd * height / 4 + screen_height * height / 8, 0) =
                            255 * L / (viewer_y - y) * 2;
                        img(xd * width / 4 + screen_width * width / 8,
                            zd * height / 4 + screen_height * height / 8, 1) =
                            255 * L / (viewer_y - y) * 2;
                        img(xd * width / 4 + screen_width * width / 8,
                            zd * height / 4 + screen_height * height / 8, 2) =
                            255 * L / (viewer_y - y) * 2;
                        // std::cout << "in" << std::endl;
                        // std::cout << xd << " " << zd << std::endl;
                        // std::cout << (int)((xd + screen_width / 2) * 100) <<
                        // " "
                        //           << (int)((zd + screen_height / 2) * 100)
                        //           << std::endl;
                        // unsigned char color[] = {255 * L, 255 * L,
                        //                          255 * L};  // White color
                        // img.draw_point(screen_x, screen_y, color);
                    }

                    // unsigned char color[] = {255 * L, 255 * L,
                    //                          255 * L};  // White color
                    // img.draw_point(screen_x, screen_y, color);
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
        display.display(img);
        // display.wait(16);
        A += 0.007;
        B += 0.007;
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