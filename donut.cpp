#include <math.h>
#include <stdio.h>
#include <time.h>

#include <iomanip>
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
    float viewer_y = 4.0f;
    float viewer_z = 0.0f;

    // note that scree is always perpendicular to the viewer
    // these cordinates are of centre.
    float screen_x = 0.0f;
    float screen_y = 3.0f;
    float screen_z = 0.0f;
    // to be kept a factor of desired resolution of the screen.
    // for 800x600
    float screen_height = 4.0f;
    float screen_width = 4.0f;

    float viewer_to_screen =
        (double)sqrt((viewer_x - screen_x) * (viewer_x - screen_x) +
                     (viewer_y - screen_y) * (viewer_y - screen_y) +
                     (viewer_z - screen_z) * (viewer_z - screen_z));

    // light source
    float light_x = 0.0f;
    float light_y = -5.0f;
    float light_z = -5.0f;

    // donut dimentions
    float R = 2.5f;  // big radius
    float d = 1.0f;  // small radius
    float O = 0.0f;  // theta
    float t = 0.0f;  // phi
    float A = 0.0f;  // angle_A
    float B = 0.0f;  // angle_B

    // sphere cordinates
    float sphere_x = 0.0f;
    float sphere_y = 0.0f;
    float sphere_z = 0.0f;
    float radius_sphere = 0.5f;

    float x, y, z, cx, cy, cz, L, S, xd, yd, zd;

    float max_L = 0.0f;

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

    // A = 0.2;
    // B = 0.7;

    // float count = 0.0;
    // float facing = 0.0;

    std::cout << std::fixed << std::setprecision(2);

    // int iterations = 0;
    // float total_time = 0;
    int run = 1;
    while (!display.is_closed()) {
        // while (run) {
        img.fill(0);
        // // uncomment this next part to stop after first iteration.
        // run = run - 1;

        clock_t time_start = clock();

        // for (float j = 0; j < 6.28; j += 0.08) {
        //     for (float i = 0; i < 6.28; i += 0.08) {
        //         O = i;
        //         t = j;
        //     }
        // }

        // iterations++;
        float cosA = cos(A);
        float sinA = sin(A);
        float cosB = cos(B);
        float sinB = sin(B);
        for (float j = 0; j < 6.28; j += 0.02) {
            t = j;
            float cost = cos(t);
            float sint = sin(t);

            cx = R * cosB * cost + sinB * R * sinA * sint;
            cy = R * sinA * cosB * sint - R * sinB * cost;
            cz = R * cosA * sint;

            for (float i = 0; i < 6.28; i += 0.07) {
                O = i;
                // reduced dots
                // for (float j = 0; j < 6.28; j += 0.2) {
                //     for (float i = 0; i < 6.28; i += 0.6) {
                // count++;

                float cosO = cos(O);
                float sinO = sin(O);

                // with reduced trignometric functions

                // ! 3rd line I changed sin to cos a
                // surface normal with respect to old light source
                // surface normal with respect to light source
                L = (double)((cosO * cost * cosB +
                              sinB * (sinO * cosA + cosO * sint * sinA)) *
                                 light_x +
                             (cosB * (sinO * cosA + cosO * sinA * sint) -
                              cosO * cost * cosB) *
                                 light_y +
                             (cosO * sint * cosA - sinO * sinA) * light_z) /
                    sqrt(light_x * light_x + light_y * light_y +
                         light_z * light_z);

                // //condition to limit the visibility
                // if (S >= 0) {
                if (1) {
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

                    S = (double)(((x - cx) * (x - light_x)) +
                                 ((y - cy) * (y - light_y)) +
                                 ((z - cz) * (z - light_z)));
                    // S = (double)5;
                    // if (xd > max_L) {
                    //     max_L = xd;
                    // }

                    // facing++;
                    // int screen_x = static_cast<int>((xd + 1) * 400);
                    // int screen_z = static_cast<int>((zd + 1) * 300);
                    // see all data
                    // std::cout
                    //     << "X:" << x << " Y:" << y << " Z:" << z << " xd:" <<
                    //     xd
                    //     << " zd:" << zd << " L:" << L << " S:" << S
                    //     << " L:" << (y / (2 * (R + d)) + 0.5) << std::endl;

                    // coloring
                    if (1) {
                        // if (S > 0) {
                        // if (xd < screen_width / 2 && xd > -screen_width / 2
                        // &&
                        //     zd < screen_height / 2 && zd > -screen_height /
                        //     2) { img(xd * width / 4 + screen_width * width /
                        //     8,
                        //         zd * height / 4 + screen_height * height / 8,
                        //         0) = 255 * L;
                        //     img(xd * width / 4 + screen_width * width / 8,
                        //         zd * height / 4 + screen_height * height / 8,
                        //         1) = 255 * L;
                        //     img(xd * width / 4 + screen_width * width / 8,
                        //         zd * height / 4 + screen_height * height / 8,
                        //         2) = 255 * L;
                        // }

                        // std::cout << "in" << std::endl;
                        // std::cout << xd << " " << zd << std::endl;
                        // std::cout << (int)((xd + screen_width / 2) *
                        // 100)
                        // << " "
                        //           << (int)((zd + screen_height / 2) *
                        //           100)
                        //           << std::endl;
                        // unsigned char color[] = {255 * L, 255 * L,
                        //                          255 * L};  // White
                        //                          color
                        // img.draw_point(screen_x, screen_y, color);

                        // coloring
                        if (xd < screen_width / 2 && xd > -screen_width / 2 &&
                            zd < screen_height / 2 && zd > -screen_height / 2) {
                            img(xd * width / 4 + screen_width * width / 8,
                                zd * height / 4 + screen_height * height / 8,
                                0) = 255 * (y / (2 * (R + d)) + 0.5);
                            img(xd * width / 4 + screen_width * width / 8,
                                zd * height / 4 + screen_height * height / 8,
                                1) = 255 * (y / (2 * (R + d)) + 0.5);
                            img(xd * width / 4 + screen_width * width / 8,
                                zd * height / 4 + screen_height * height / 8,
                                2) = 255 * (y / (2 * (R + d)) + 0.5);
                        }
                    }
                }

                // unsigned char color[] = {255 * L, 255 * L,
                //                          255 * L};  // White
                //                          color
                // img.draw_point(screen_x, screen_y, color);

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
        // render time
        std::cout << (double)((clock() - time_start)) << "ms " << std::endl;
        display.display(img);
        // display.wait(5);

        // howw fast the donut rotates
        A += 0.005;
        B += 0.003;
        // std::cout << (double)((clock() - time_start) /
        // CLOCKS_PER_SEC) /
        //                  iterations
        //           << " " << (double)(facing / count) * 100 << " " <<
        //           std::endl;
        // count = 0;
        // facing = 0;
    }
    // std::cout << (double)((clock() - time_start)) / 1000000 <<
    // std::endl; donut.close(); donuti.close(); donut_x.close();
    // donut_y.close();
    // donut_z.close();
}