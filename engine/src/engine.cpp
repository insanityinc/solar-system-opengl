#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "tinyxml2.h"
#include "model.h"

using namespace std;
using namespace tinyxml2;

vector<model*> models;
//camera variables
float camX, camY, camZ, speed;
//type of drawing (dots lines or triangles)
int line;
//draw or not the axis
bool axis;

void drawAxis(){
    glEnable( GL_LINE_SMOOTH );
    glLineWidth( 1 );
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1000, 0, 0);
        glVertex3f(1000, 0, 0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0, -1000, 0);
        glVertex3f(0, 1000, 0);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0, 0, -1000);
        glVertex3f(0, 0, 1000);
    glEnd();
}

void drawModels(){

    glBegin(GL_TRIANGLES);
        for(int i=0; i < models.size(); i+=1) {
            for(int j=0; j < models[i]->getSize(); j+=6) {
                point* a = models[i]->getPoint(j);
                point* b = models[i]->getPoint(j+1);
                point* c = models[i]->getPoint(j+2);
                glColor3f(1.0f,0.0f,0.0f);
                glVertex3f(a->getX(), a->getY(), a->getZ());
                glVertex3f(b->getX(), b->getY(), b->getZ());
                glVertex3f(c->getX(), c->getY(), c->getZ());

                if(!models[i]->getPoint(j+3)) break;
                point* d = models[i]->getPoint(j+3);
                point* e = models[i]->getPoint(j+4);
                point* f = models[i]->getPoint(j+5);
                glColor3f(0.0f,0.0f,1.0f);
                glVertex3f(d->getX(), d->getY(), d->getZ());
                glVertex3f(e->getX(), e->getY(), e->getZ());
                glVertex3f(f->getX(), f->getY(), f->getZ());
            }
        }
    glEnd();
}

void renderScene() {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              0.0f,0.0f,0.0f,
              0.0f,0.1f,0.0f);

    // put the geometric transformations here

    // put drawing instructions here
    glPolygonMode(GL_FRONT_AND_BACK,line);
    if(axis) drawAxis();
    drawModels();
    // End of frame
    glutSwapBuffers();
}

// Responsible for our Window Reshaping
void changeSize(int w, int h) {
    if (h == 0)
        h = 1;
    float ratio = w * 1.0f / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void read3d(string filename){

    string line;
    model* newModel = new model();
    point *p;
    ifstream file(filename);

    if (file.fail()) {
        cout << "Couldn't find file: " + filename;
    } else {
        while (getline(file, line)) {
            p = new point(line);
            newModel->pushPoint(p);
        }
    }
    file.close();
    models.push_back(newModel);
}

void readXML(string filepath) {

    XMLDocument docxml;

    if (!(docxml.LoadFile(filepath.c_str()))) {

        XMLElement* root = docxml.FirstChildElement();

        for(XMLElement *element = root -> FirstChildElement(); element!=NULL; element=element->NextSiblingElement()){

            string file = element -> Attribute("file");
            cout << file << endl;
            read3d(file);
        }
    }
    else {
        cout << "XML file not found..." << endl;
    }
}

void basicKeyboard(unsigned char key, int x, int y) {
    switch (key){
        case 'p' :
            line = GL_POINT;
            break;
        case 'l' :
            line = GL_LINE;
            break;
        case 'o' :
            line = GL_FILL;
            break;
        case 'q' :
            camX += speed;
            break;
        case 'a' :
            camX -= speed;
            break;
        case 'w' :
            camY += speed;
            break;
        case 's' :
            camY -= speed;
            break;
        case 'e' :
            camZ += speed;
            break;
        case 'd' :
            camZ -= speed;
            break;
        case '+' :
            speed += 0.5f;
            break;
        case '-' :
            speed -= 0.5f;
            break;
        case 'x' :
            axis = !axis;
            break;
        default:break;
    }
    glutPostRedisplay();
}

void help(){
    cout << "#____________________________________ENGINE [GUIDE__]________________________________ #" << endl;
    cout << "'q' " << endl;
}

int main(int argc, char **argv) {
    camX = 5.0f;
    camY = 5.0f;
    camZ = 5.0f;

    speed = 2.0f;

    line = GL_FILL;

    axis = true;

    if(argc > 1) readXML(argv[1]);

    // put GLUT init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("SolarSystem-OpenGL");


    // put callback registration here
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    //glutSpecialFunc(keyboardspecial);
    glutKeyboardFunc(basicKeyboard);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main loop
    glutMainLoop();

    return 1;
}