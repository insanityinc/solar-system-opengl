#include <iomanip>
#include <iostream>
#include <cstring>
#include <cstdio>
#include "generate.h"


void generate::generatePlane(float size, string filename) {

    float dim = size/2;

    string path = "../3dfiles/" + filename;
    ofstream file (path, ofstream::out);

    unsigned int precision = 5;
    file.precision(precision);

    file << fixed << dim << " " << 0 << " " << dim << endl;
    file << fixed << dim << " " << 0 << " " << -dim << endl;
    file << fixed << -dim << " " << 0 << " " << -dim << endl;

    file << fixed << -dim << " " << 0 << " " << -dim << endl;
    file << fixed << -dim << " " << 0 << " " << dim << endl;
    file << fixed << dim  << " " << 0 << " " << dim << endl;


    //se quisermos desenhar a parte inferior do plano também
    //file << fixed << dim << " " << 0 << " " << dim << endl;
    //file << fixed << -dim << " " << 0 << " " << -dim << endl;
    //file << fixed << dim << " " << 0 << " " << -dim << endl;

    //file << fixed << -dim << " " << 0 << " " << -dim << endl;
    //file << fixed << dim  << " " << 0 << " " << dim << endl;
    //file << fixed << -dim << " " << 0 << " " << dim << endl;


    file.close();
}

void generate::generateBox(float x, float y, float z, int divs, string filename) {
    string path = "../3dfiles/" + filename;
    if(remove(path.c_str()) == 0) {
        cout << "Existent box was removed" << endl;
    }

    xySide(x, y, z, divs, filename);
    xySide(x, y, -z, divs, filename);
    yzSide(x, y, z, divs, filename);
    yzSide(-x, y, z, divs, filename);
    zxSide(x, y, z, divs, filename);
    zxSide(x, -y, z, divs, filename);

}

void generate::generateSphere(float radius, int slices, int stacks, string filename) {

    string path = "../3dfiles/" + filename;
    ofstream file (path, ofstream::out);
    unsigned int precision = 5;
    file.precision(precision);

    float alpha = 0, height = 0;
    float alphaInc = (2 * M_PI)/slices, heightInc = M_PI/stacks;
    float x1, x2, x3 , x4, x5, x6, x7, x8, x9, x10, x11, x12;
    float y1, y2, y3 , y4, y5, y6, y7, y8, y9, y10, y11, y12;
    float z1, z2, z3 , z4, z5, z6, z7, z8, z9, z10, z11, z12;

    for(int i = 0; i < stacks; i++){
        alpha = 0;
        for(int j = 0; j < slices;j++){

            /* METADE DE CIMA { DIVIDIDO EM 2 TRIANGULOS } */
            x1 = (radius*cos(height))*cos(alpha);
            y1 = (radius*sin(height));
            z1 = radius*cos(height)*sin(alpha);

            x2 = radius*cos(alpha+alphaInc)*cos(height+heightInc);
            y2 = radius*sin(height+heightInc);
            z2 = radius*sin(alpha+alphaInc)*cos(height+heightInc);

            x3 = radius*cos(alpha+alphaInc)*cos(height);
            y3 = radius*sin(height);
            z3 = radius*sin(alpha+alphaInc)*cos(height);
                /* ----------------------------------- */
            x4 = radius*cos(alpha)*cos(height);
            y4 = radius*sin(height);
            z4 = radius*sin(alpha)*cos(height);

            x5 = radius*cos(alpha)*cos(height+heightInc);
            y5 = radius*sin(height+heightInc);
            z5 = radius*sin(alpha)*cos(height+heightInc);

            x6 = radius*cos(alpha+alphaInc)*cos(height+heightInc);
            y6 = radius*sin(height+heightInc);
            z6 = radius*sin(alpha+alphaInc)*cos(height+heightInc);

            /* METADE DE BAIXO { DIVIDIDO EM 2 TRIANGULOS } */
            x7 = radius*cos(alpha)*cos(height+heightInc);
            y7 = -radius*sin(height+heightInc);
            z7 = radius*sin(alpha)*cos(height+heightInc);

            x8 = radius*cos(alpha+alphaInc)*cos(height);
            y8 = -radius*sin(height);
            z8 = radius*sin(alpha+alphaInc)*cos(height);

            x9 = radius*cos(alpha+alphaInc)*cos(height+heightInc);
            y9 = -radius*sin(height+heightInc);
            z9 = radius*sin(alpha+alphaInc)*cos(height+heightInc);
                /* ----------------------------------- */
            x10 = radius*cos(alpha)*cos(height+heightInc);
            y10 = -radius*sin(height+heightInc);
            z10 = radius*sin(alpha)*cos(height+heightInc);

            x11 = radius*cos(alpha)*cos(height);
            y11 = -radius*sin(height);
            z11 = radius*sin(alpha)*cos(height);

            x12 = radius*cos(alpha+alphaInc)*cos(height);
            y12 = -radius*sin(height);
            z12 = radius*sin(alpha+alphaInc)*cos(height);

            /* ESCRITA PARA O FICHEIRO COM NOME FILENAME */
            file << fixed << x1  << " " << y1  << " " << z1  << endl;
            file << fixed << x2  << " " << y2  << " " << z2  << endl;
            file << fixed << x3  << " " << y3  << " " << z3  << endl;
            file << fixed << x4  << " " << y4  << " " << z4  << endl;
            file << fixed << x5  << " " << y5  << " " << z5  << endl;
            file << fixed << x6  << " " << y6  << " " << z6  << endl;
            file << fixed << x7  << " " << y7  << " " << z7  << endl;
            file << fixed << x8  << " " << y8  << " " << z8  << endl;
            file << fixed << x9  << " " << y9  << " " << z9  << endl;
            file << fixed << x10 << " " << y10 << " " << z10 << endl;
            file << fixed << x11 << " " << y11 << " " << z11 << endl;
            file << fixed << x12 << " " << y12 << " " << z12 << endl;

            alpha=(j+1)*alphaInc;
        }
        height=(i+1)*heightInc;
    }
    file.close();
}

void generate::generateCone(float radius, float height, int slices, int stacks, string filename) {

    string path = "../3dfiles/" + filename;
    ofstream file (path, ofstream::out);

    unsigned int precision = 5;
    file.precision(precision);

    float alpha, alphaInc = (2*M_PI)/slices;
    float radiusInc = radius/stacks;
    float heightInit = -height/2, heightInc = height/stacks;
    /* COORDENADAS PARA A BASE */
    float a1, a2, a3;
    float b1, b2, b3;
    float c1, c2, c3;
    /* COORDENADAS PARA O CORPO */
    float x1, x2, x3, x4, x5, x6;
    float y1, y2, y3, y4, y5, y6;
    float z1, z2, z3, z4, z5, z6;

    // BASE
    for(int i=0;i<slices;i++){

        a1 = radius*sin(alpha);     a2 = 0;             a3 = radius*sin(alpha+alphaInc);
        b1 = heightInit;            b2 = heightInit;    b3 = heightInit;
        c1 = radius*cos(alpha);     c2 = 0;             c3 = radius*cos(alpha+alphaInc);

        file << fixed << a1 << " " << b1 << " " << " " << c1 << endl;
        file << fixed << a2 << " " << b2 << " " << " " << c2 << endl;
        file << fixed << a3 << " " << b3 << " " << " " << c3 << endl;

        alpha+=alphaInc;
    }

    // CORPO
    for(int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            alpha += alphaInc;
            float newRadius = radius - radiusInc;

            x1 = radius * sin(alpha);
            y1 = heightInit;
            z1 = radius * cos(alpha);

            x2 = radius * sin(alpha + alphaInc);
            y2 = heightInit;
            z2 = radius * cos(alpha + alphaInc);

            x3 = newRadius * sin(alpha);
            y3 = heightInit + heightInc;
            z3 = newRadius * cos(alpha);


            x4 = radius * sin(alpha + alphaInc);
            y4 = heightInit;
            z4 = radius * cos(alpha + alphaInc);

            x5 = newRadius * sin(alpha + alphaInc);
            y5 = heightInit + heightInc;
            z5 = newRadius * cos(alpha + alphaInc);

            x6 = newRadius * sin(alpha);
            y6 = heightInit + heightInc;
            z6 = newRadius * cos(alpha);

            file << fixed << x1 << " " << y1 << " " << z1 << endl;
            file << fixed << x2 << " " << y2 << " " << z2 << endl;
            file << fixed << x3 << " " << y3 << " " << z3 << endl;
            file << fixed << x4 << " " << y4 << " " << z4 << endl;
            file << fixed << x5 << " " << y5 << " " << z5 << endl;
            file << fixed << x6 << " " << y6 << " " << z6 << endl;
        }
        radius -= radiusInc;
        heightInit += heightInc;
    }

    file.close();
}

void generate::xySide(float x, float y, float z, int divs, string filename){

    string path = "../3dfiles/" + filename;

    ofstream file (path, ofstream::app);

    float xInc, yInc;

    if(divs != 0){ xInc = x/divs; yInc = y/divs; }
    else { xInc = x; yInc = y; }

    float xPos = x/2, yPos = y/2, zPos = z/2;

    for(int i = 0; i < divs; i++){
        for(int j = 0; j < divs; j++){

            if(z > 0){
                file << -xPos+(j*xInc)          << " " << -yPos+(i*yInc)          << " " << zPos << endl;
                file << (-xPos + xInc)+(j*xInc) << " " << -yPos+(i*yInc)          << " " << zPos << endl;
                file << (-xPos + xInc)+(j*xInc) << " " << (-yPos + yInc)+(i*yInc) << " " << zPos << endl;

                file << -xPos+(j*xInc)          << " " << -yPos+(i*yInc)          << " " << zPos << endl;
                file << (-xPos + xInc)+(j*xInc) << " " << (-yPos + yInc)+(i*yInc) << " " << zPos << endl;
                file << -xPos+(j*xInc)          << " " << (-yPos + yInc)+(i*yInc) << " " << zPos << endl;
            }
            else{
                file << -xPos+(j*xInc)          << " " << -yPos+(i*yInc)          << " " << zPos << endl;
                file << (-xPos + xInc)+(j*xInc) << " " << (-yPos + yInc)+(i*yInc) << " " << zPos << endl;
                file << (-xPos + xInc)+(j*xInc) << " " << -yPos+(i*yInc)          << " " << zPos << endl;

                file << -xPos+(j*xInc)          << " " << -yPos+(i*yInc)          << " " << zPos << endl;
                file << -xPos+(j*xInc)          << " " << (-yPos + yInc)+(i*yInc) << " " << zPos << endl;
                file << (-xPos + xInc)+(j*xInc) << " " << (-yPos + yInc)+(i*yInc) << " " << zPos << endl;
            }


        }
    }
    file.close();
}

void generate::yzSide(float x, float y, float z, int divs, string filename) {

    string path = "../3dfiles/" + filename;
    ofstream file (path, ofstream::app);

    float yInc, zInc;

    if(divs != 0){ yInc = y/divs; zInc = z/divs; }
    else { yInc = y; zInc = z; }

    float xPos = x/2, yPos = y/2, zPos = z/2;

    for(int i = 0; i < divs; i++){
        for(int j = 0; j < divs; j++){

            if(x > 0){
                file << xPos << " " << -yPos+(i*yInc)          << " " << (-zPos + zInc)+(j*zInc) << endl;
                file << xPos << " " << -yPos+(i*yInc)          << " " << -zPos+(j*zInc)          << endl;
                file << xPos << " " << (-yPos + yInc)+(i*yInc) << " " << -zPos+(j*zInc)          << endl;

                file << xPos << " " << -yPos + (i*yInc)        << " " << (-zPos + zInc)+(j*zInc) << endl;
                file << xPos << " " << (-yPos + yInc)+(i*yInc) << " " << -zPos+(j*zInc)          << endl;
                file << xPos << " " << (-yPos + yInc)+(i*yInc) << " " << (-zPos + zInc)+(j*zInc) << endl;
            }
            else{
                file << xPos << " " << -yPos+(i*yInc)          << " " << (-zPos + zInc)+(j*zInc) << endl;
                file << xPos << " " << (-yPos + yInc)+(i*yInc) << " " << -zPos+(j*zInc)          << endl;
                file << xPos << " " << -yPos+(i*yInc)          << " " << -zPos+(j*zInc)          << endl;


                file << xPos << " " << -yPos + (i*yInc)        << " " << (-zPos + zInc)+(j*zInc) << endl;
                file << xPos << " " << (-yPos + yInc)+(i*yInc) << " " << (-zPos + zInc)+(j*zInc) << endl;
                file << xPos << " " << (-yPos + yInc)+(i*yInc) << " " << -zPos+(j*zInc)          << endl;

            }

        }
    }
    file.close();
}

void generate::zxSide(float x, float y, float z, int divs, string filename) {

    string path = "../3dfiles/" + filename;
    ofstream file (path, ofstream::app);

    float zInc, xInc;

    if(divs != 0){ zInc = z/divs; xInc = x/divs; }
    else { zInc = z; xInc = x; }

    float xPos = x/2, yPos = y/2, zPos = z/2;

    for(int i = 0; i < divs; i++){
        for(int j = 0; j < divs; j++){
            if(y > 0){
                file << -xPos + (i*xInc)          << " " << yPos << " " << -zPos + (j*zInc)          << endl;
                file << -xPos + (i*xInc)          << " " << yPos << " " << (-zPos + zInc) + (j*zInc) << endl;
                file << (-xPos + xInc) + (i*xInc) << " " << yPos << " " << (-zPos + zInc) + (j*zInc) << endl;

                file << -xPos + (i*xInc)          << " " << yPos << " " << -zPos + (j*zInc)          << endl;
                file << (-xPos + xInc) + (i*xInc) << " " << yPos << " " << (-zPos + zInc) + (j*zInc) << endl;
                file << (-xPos + xInc) + (i*xInc) << " " << yPos << " " << -zPos + (j*zInc)          << endl;
            }
            else{
                file << -xPos + (i*xInc)          << " " << yPos << " " << -zPos + (j*zInc)          << endl;
                file << (-xPos + xInc) + (i*xInc) << " " << yPos << " " << (-zPos + zInc) + (j*zInc) << endl;
                file << -xPos + (i*xInc)          << " " << yPos << " " << (-zPos + zInc) + (j*zInc) << endl;

                file << -xPos + (i*xInc)          << " " << yPos << " " << -zPos + (j*zInc)          << endl;
                file << (-xPos + xInc) + (i*xInc) << " " << yPos << " " << -zPos + (j*zInc)          << endl;
                file << (-xPos + xInc) + (i*xInc) << " " << yPos << " " << (-zPos + zInc) + (j*zInc) << endl;
            }
        }
    }
    file.close();
}


int main(int argc, char* argv[]) {

    float x, y, z, radius, height;
    int slices, stacks, divs;
    char* filename;

    generate* g = new generate();

    system("mkdir -p ../3dfiles/");

    if(argc==4 && strcmp("plane", argv[1]) == 0){

        g->generatePlane(atof(argv[2]), argv[3]);
    }

    else if ((argc==6 || argc==7) && strcmp("box", argv[1]) == 0){

        x = atof(argv[2]);
        y = atof(argv[3]);
        z = atof(argv[4]);

        if (argc==6) {

            divs = 1; filename = argv[5];
        }
        else if (argc==7) {

            divs = atoi(argv[5]);
            filename = argv[6];
        }
        g->generateBox(x, y, z, divs, filename);
    }
    else if (argc==6 && strcmp("sphere", argv[1]) == 0){

        radius = atof(argv[2]);
        slices = atoi(argv[3]);
        stacks = atoi(argv[4]);
        filename = argv[5];

        g->generateSphere(radius, slices, stacks, filename);
    }

    else if (argc==7 && strcmp("cone", argv[1]) == 0){

        radius = atof(argv[2]);
        height = atof(argv[3]);
        slices = atoi(argv[4]);
        stacks = atoi(argv[5]);
        filename = argv[6];

        g->generateCone(radius, height, slices, stacks, filename);
    }
    return 0;
}