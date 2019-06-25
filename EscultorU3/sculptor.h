#include <string>
#include <iostream>
#include "vector"

#ifndef SCULPTOR_H
#define SCULPTOR_H

using namespace std;

struct Voxel {
  float r,g,b; // Colors
  float a;
// Transparency
  bool isOn; // Included or not
};

enum {

    XY,
    YZ,
    ZX
};

class Sculptor
{
protected:
  Voxel ***v;
  int nx,ny,nz;
  float r,g,b,a;

public:
  Sculptor(int _nx, int _ny, int _nz);
  ~Sculptor();
  void setColor(float _r, float _g, float _b, float alpha);
  void putVoxel(int x, int y, int z);
  void cutVoxel(int x, int y, int z);
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  void writeOFF(std::string filename);
  void writeVECT(std::string filename);

  void redimensionarMatriz(int tam);
  vector<vector<Voxel>> readPln(int dim = 0, int pln = XY);
};

#endif // SCULPTOR_H
