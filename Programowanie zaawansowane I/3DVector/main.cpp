#include <cstdio>
#include <cstdlib>

#include "Vector3D.h"

// _________________________________________________________________________________________________________________________

void Test_Vector3D();
void Test_AddVectorAndSaveDirection();
void Test_VectorProjectionToAnotherVector();
void Test_StreamsBitshiftOperators();
void Test_LongDoubleCastingOperator();
void Test_BitshiftWithAssignmentOperator();
void Test_ArraySubscriptOperator();
void Test_CopyConstruction();
void Test_CallOperator();
void Test_Set_functions();
void Test_Get_functions();
void Test_Add();
void Test_IsUnitVectorTowardsXYZ();

// *************************************************************************************************************************

int main()
{
Test_Vector3D();
puts("main() will be terminated after a keystroke.");
getchar();
return (0);
};

// *************************************************************************************************************************

void Test_Vector3D()
{
Test_AddVectorAndSaveDirection();
Test_VectorProjectionToAnotherVector();
Test_StreamsBitshiftOperators();
Test_LongDoubleCastingOperator();
Test_BitshiftWithAssignmentOperator();
Test_ArraySubscriptOperator();
Test_CopyConstruction();
Test_CallOperator();
Test_Set_functions();
Test_Get_functions();
Test_Add();
Test_IsUnitVectorTowardsXYZ();
};

// _________________________________________________________________________________________________________________________

void Test_AddVectorAndSaveDirection()
{
printf("----------------------------------------------------------------------\n"
       "                  Test_AddVectorAndSaveDirection()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1(3,1,1);
Vector3D V2(-4,6,0);
Vector3D V3(6,6,6);
Vector3D V4(-5,-4,-1.23);

printf("V1 = [%.2f,%.2f,%.2f]\n",V1.GetX(),V1.GetY(),V1.GetZ());
printf("V2 = [%.2f,%.2f,%.2f]\n",V2.GetX(),V2.GetY(),V2.GetZ());
printf("V3 = [%.2f,%.2f,%.2f]\n",V3.GetX(),V3.GetY(),V3.GetZ());
printf("V4 = [%.2f,%.2f,%.2f]\n",V4.GetX(),V4.GetY(),V4.GetZ());
putchar('\n');

V1.AddVectorAndSaveDirection(V2);
V3.AddVectorAndSaveDirection(V4);
printf("V1 = [%.2f,%.2f,%.2f] = AddVectorAndSaveDirection(V2)\n",V1.GetX(),V1.GetY(),V1.GetZ());
printf("V3 = [%.2f,%.2f,%.2f] = AddVectorAndSaveDirection(V4)\n",V3.GetX(),V3.GetY(),V3.GetZ());

puts("\n\n\nTest_AddVectorAndSaveDirection() has been ended.");
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________

void Test_VectorProjectionToAnotherVector()
{
printf("----------------------------------------------------------------------\n"
       "               Test_VectorProjectionToAnotherVector()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1(3,2,0);
Vector3D V2(3,0,0);
Vector3D V3(5,2,0);
Vector3D V4(-3,5,0);

printf("V1 = [%.2f,%.2f,%.2f]\n",V1.GetX(),V1.GetY(),V1.GetZ());
printf("V2 = [%.2f,%.2f,%.2f]\n",V2.GetX(),V2.GetY(),V2.GetZ());
printf("V3 = [%.2f,%.2f,%.2f]\n",V3.GetX(),V3.GetY(),V3.GetZ());
printf("V4 = [%.2f,%.2f,%.2f]\n",V4.GetX(),V4.GetY(),V4.GetZ());
putchar('\n');

V1.VectorProjectionToAnotherVector(V2);
V3.VectorProjectionToAnotherVector(V4);
printf("V1 = [%.2f,%.2f,%.2f] = VectorProjectionToAnotherVector(V2)\n",V1.GetX(),V1.GetY(),V1.GetZ());
printf("V3 = [%.2f,%.2f,%.2f] = VectorProjectionToAnotherVector(V3)\n",V3.GetX(),V3.GetY(),V3.GetZ());

puts("\n\n\nTest_VectorProjectionToAnotherVector() has been ended.");
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________

void Test_StreamsBitshiftOperators()
{
printf("----------------------------------------------------------------------\n"
       "                  Test_StreamsBitshiftOperators()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1(2,3,5.66);

std::cout << "V1 = " << V1 << "Magnitude(V1) = " << V1.GetModulus() << std::endl;
std::cout << std::endl << "New values of [x,y,z] awaiting..." << std::endl;
std::cin >> V1;
std::cout << "V1 = " << V1 << "Magnitude(V1) = " << V1.GetModulus() << std::endl;

std::cout << std::endl << std::endl << std::endl << "Test_StreamsBitshiftOperators() has been ended.";
getchar();
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________

void Test_LongDoubleCastingOperator()
{
printf("----------------------------------------------------------------------\n"
       "                  Test_LongDoubleCastingOperator()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1(1,2,3);

printf("V1 = [%.2f,%.2f,%.2f]\n",V1.GetX(),V1.GetY(),V1.GetZ());

printf("Sum of the coordinates = { %.2f }\n",(long double)(V1));

puts("\n\n\nTest_LongDoubleCastingOperator() has been ended.");
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________

void Test_BitshiftWithAssignmentOperator()
{
printf("----------------------------------------------------------------------\n"
       "                 Test_BitshiftWithAssignmentOperator()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1(3,1,1);
Vector3D V2(-4,6,0);
Vector3D V3(6,6,6);
Vector3D V4(-5,-4,-1.23);

printf("V1 = [%.2f,%.2f,%.2f]\n",V1.GetX(),V1.GetY(),V1.GetZ());
printf("V2 = [%.2f,%.2f,%.2f]\n",V2.GetX(),V2.GetY(),V2.GetZ());
printf("V3 = [%.2f,%.2f,%.2f]\n",V3.GetX(),V3.GetY(),V3.GetZ());
printf("V4 = [%.2f,%.2f,%.2f]\n",V4.GetX(),V4.GetY(),V4.GetZ());
putchar('\n');

V1 <<= V2;
V3 <<= V4;
printf("V1 = [%.2f,%.2f,%.2f] = V1 <<= V2\n",V1.GetX(),V1.GetY(),V1.GetZ());
printf("V3 = [%.2f,%.2f,%.2f] = V3 <<= V4\n",V3.GetX(),V3.GetY(),V3.GetZ());

V1 >>= V4;
V3 >>= V2;
printf("V1 = [%.2f,%.2f,%.2f] = V1 >>= V4\n",V1.GetX(),V1.GetY(),V1.GetZ());
printf("V3 = [%.2f,%.2f,%.2f] = V3 >>= V2\n",V3.GetX(),V3.GetY(),V3.GetZ());

puts("\n\n\nTest_BitshiftWithAssignmentOperator() has been ended.");
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________

void Test_ArraySubscriptOperator()
{
printf("----------------------------------------------------------------------\n"
       "                   Test_ArraySubscriptOperator()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1(2.0,6.66,-9.87);

printf("V1 = [%.2f,%.2f,%.2f]\n",V1.GetX(),V1.GetY(),V1.GetZ());
putchar('\n');

printf("V1['x'] = <%.17f> = Coordinate X\n",V1['x']);
printf("V1['y'] = <%.17f> = Coordinate Y\n",V1['y']);
printf("V1['z'] = <%.17f> = Coordinate Z\n",V1['z']);
printf("V1['m'] = <%.17f> = Modulus\n",V1['m']);
printf("V1['1'] = <%.17f> = Angle X towards Y (radians)\n",V1['1']);
printf("V1['1'] = <%.17f> = Angle X towards Y (degrees)\n",Vector3D::RadiansToDegrees(V1['1']));
printf("V1['2'] = <%.17f> = Angle Y towards Z (radians)\n",V1['2']);
printf("V1['2'] = <%.17f> = Angle Y towards Z (degrees)\n",Vector3D::RadiansToDegrees(V1['2']));
printf("V1['!'] = <%.17f> = Undefined\n",V1['!']);

puts("\n\n\nTest_ArraySubscriptOperator() has been ended.");
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________

void Test_CopyConstruction()
{
printf("----------------------------------------------------------------------\n"
       "                      Test_CopyConstruction()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1;
Vector3D V2(V1);
Vector3D V3(Vector3D(1,2,3));
Vector3D V4(6,6,6,1);
Vector3D V5 = Vector3D(V4) + Vector3D(6,6,6,0);

printf("Vector3D V1                                    = [%.2f,%.2f,%.2f]\n",V1.GetX(),V1.GetY(),V1.GetZ());
printf("Vector3D V2(V1)                                = [%.2f,%.2f,%.2f]\n",V2.GetX(),V2.GetY(),V2.GetZ());
printf("Vector3D V3(Vector3D(1,2,3))                   = [%.2f,%.2f,%.2f]\n",V3.GetX(),V3.GetY(),V3.GetZ());
printf("Vector3D V4(6,6,6,1)                           = [%.2f,%.2f,%.2f]\n",V4.GetX(),V4.GetY(),V4.GetZ());
printf("Vector3D V5 = Vector3D(V4) + Vector3D(6,6,6,0) = [%.2f,%.2f,%.2f]\n",V5.GetX(),V5.GetY(),V5.GetZ());
putchar('\n');

V5 = V1 + V2;
printf("V5 = V1 + V2 = [%.2f,%.2f,%.2f]\n",V5.GetX(),V5.GetY(),V5.GetZ());
printf("V1           = [%.2f,%.2f,%.2f]  <--  V1 was also updated\n",V1.GetX(),V1.GetY(),V1.GetZ());
printf("V2           = [%.2f,%.2f,%.2f]\n",V2.GetX(),V2.GetY(),V2.GetZ());
putchar('\n');

V5();
printf("V5 = V5()    = [%.2f,%.2f,%.2f]  <--  an empty call\n",V5.GetX(),V5.GetY(),V5.GetZ());

puts("\n\n\nTest_CopyConstruction() has been ended.");
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________

void Test_CallOperator()
{
printf("----------------------------------------------------------------------\n"
       "                       Test_CallOperator()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1;

printf("Vector3D V1 = [%.2f,%.2f,%.2f]\n",V1['x'],V1['y'],V1['z']);

V1();
printf("V1()        = [%.2f,%.2f,%.2f]\n",V1['x'],V1['y'],V1['z']);
V1(6,6,6);
printf("V1(6,6,6)   = [%.2f,%.2f,%.2f]\n",V1['x'],V1['y'],V1['z']);
V1(6,6,6,0);
printf("V1(6,6,6,0) = [%.2f,%.2f,%.2f]\n",V1['x'],V1['y'],V1['z']);
V1(6,6,6,1);
printf("V1(6,6,6,1) = [%.2f,%.2f,%.2f]\n",V1['x'],V1['y'],V1['z']);

puts("\n\n\nTest_CallOperator() has been ended.");
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________

void Test_Set_functions()
{
printf("----------------------------------------------------------------------\n"
       "                    Test_Set_functions()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1(6,6,6,1);

printf("V1 = [%.2f,%.2f,%.2f], |V1| = <%g>\n",V1['x'],V1['y'],V1['z'],V1['m']);
putchar('\n');

V1.SetX(12.0);
puts("V1.SetX(12.0)");
printf("V1 = [%.2f,%.2f,%.2f], |V1| = <%g>\n",V1['x'],V1['y'],V1['z'],V1['m']);
V1.SetY(-2.0);
puts("V1.SetY(-2.0)");
printf("V1 = [%.2f,%.2f,%.2f], |V1| = <%g>\n",V1['x'],V1['y'],V1['z'],V1['m']);
V1.SetZ(23.32);
puts("V1.SetZ(23.32)");
printf("V1 = [%.2f,%.2f,%.2f], |V1| = <%g>\n",V1['x'],V1['y'],V1['z'],V1['m']);
V1.SetPolarCoordinates(9,8,7,true);
puts("V1.SetPolarCoordinates(9,8,7,1)");
printf("V1 = [%.2f,%.2f,%.2f], |V1| = <%g>\n",V1['x'],V1['y'],V1['z'],V1['m']);
V1.SetVectorCoordinates(6.71,-0.99,5.91);
puts("V1.SetVectorCoordinates(6.71,-0.99,5.91)");
printf("V1 = [%.2f,%.2f,%.2f], |V1| = <%g>\n",V1['x'],V1['y'],V1['z'],V1['m']);


puts("\n\n\nTest_Set_functions() has been ended.");
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________

void Test_Get_functions()
{
printf("----------------------------------------------------------------------\n"
       "                    Test_Get_functions()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1(6,6,6,1);
double coord [3] = { 0 };
long double polar [3] = { 0 };

printf("V1 = [%.2f,%.2f,%.2f], |V1| = <%g>\n",V1['x'],V1['y'],V1['z'],V1['m']);
putchar('\n');

printf("V1.GetX()       = <%f>\n",V1.GetX());
printf("V1.GetY()       = <%f>\n",V1.GetY());
printf("V1.GetZ()       = <%f>\n",V1.GetZ());
printf("V1.GetModulus() = <%Lf>\n",V1.GetModulus());
putchar('\n');

V1.GetVectorCoordinates(coord);
V1.GetPolarCoordinates(polar);
puts("V1.GetVectorCoordinates(coord)");
puts("V1.GetPolarCoordinates(polar)");
printf("coord[0] = <%f>\ncoord[1] = <%f>\ncoord[2] = <%f>\n",coord[0],coord[1],coord[2]);
printf("polar[0] = <%Lf>\npolar[1] = <%Lf> degrees\npolar[2] = <%Lf> degress\n",
        polar[0],Vector3D::RadiansToDegrees(polar[1]),Vector3D::RadiansToDegrees(polar[2]));

puts("\n\n\nTest_Get_functions() has been ended.");
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________

void Test_Add()
{
printf("----------------------------------------------------------------------\n"
       "                         Test_Add()()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1(13,14,15);
Vector3D V2(3,4,5);
Vector3D V3(1,0,-1);


printf("V1 = [%.2f,%.2f,%.2f]\n",V1['x'],V1['y'],V1['z']);
printf("V2 = [%.2f,%.2f,%.2f]\n",V2['x'],V2['y'],V2['z']);
printf("V3 = [%.2f,%.2f,%.2f]\n",V3['x'],V3['y'],V3['z']);
putchar('\n');

V1.Add(V3);
printf("V1 = [%.2f,%.2f,%.2f]  <--  V1.Add(V3)\n",V1['x'],V1['y'],V1['z']);
V2.Add(V1,V3);
printf("V2 = [%.2f,%.2f,%.2f]  <--  V2.Add(V1,V3)\n",V2['x'],V2['y'],V2['z']);
V3.Add(V1,V2,V3);
printf("V3 = [%.2f,%.2f,%.2f]  <--  V3.Add(V1,V2,V3)\n",V3['x'],V3['y'],V3['z']);

puts("\n\n\nTest_Add() has been ended.");
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________

void Test_IsUnitVectorTowardsXYZ()
{
printf("----------------------------------------------------------------------\n"
       "                   Test_IsUnitVectorTowardsXYZ()()\n"
       "----------------------------------------------------------------------\n"
       "\n"
      );

Vector3D V1(1,0,0);
Vector3D V2(0,1,0);
Vector3D V3(0,0,1);
Vector3D V4;

V4();
V4.Add(V1,V2,V3);

printf("V1 = [%.2f,%.2f,%.2f]\n",V1['x'],V1['y'],V1['z']);
printf("V2 = [%.2f,%.2f,%.2f]\n",V2['x'],V2['y'],V2['z']);
printf("V3 = [%.2f,%.2f,%.2f]\n",V3['x'],V3['y'],V3['z']);
printf("V4 = [%.2f,%.2f,%.2f]\n",V4['x'],V4['y'],V4['z']);
putchar('\n');

printf("V1.IsUnitVectorTowardsX()   = <%d>\n",V1.IsUnitVectorTowardsX());
printf("V2.IsUnitVectorTowardsY()   = <%d>\n",V2.IsUnitVectorTowardsY());
printf("V3.IsUnitVectorTowardsZ()   = <%d>\n",V3.IsUnitVectorTowardsZ());
printf("V4.IsUnitVectorTowardsXYZ() = <%d>\n",V4.IsUnitVectorTowardsXYZ());
putchar('\n');

V4.Substract(V1,V2,V3);
printf("V4.Substract(V1,V2,V3) = V4 = [%.2f,%.2f,%.2f]\n",V4['x'],V4['y'],V4['z']);
printf("V4.IsUnitVectorTowardsY()   = <%d>\n",V4.IsUnitVectorTowardsY());
printf("V4.IsZeroVector()           = <%d>\n",V4.IsZeroVector());
V4(14,1,16);
printf("V4(14,1,16)            = V4 = [%.2f,%.2f,%.2f]\n",V4['x'],V4['y'],V4['z']);
printf("V4.IsUnitVectorTowardsY()   = <%d>\n",V4.IsUnitVectorTowardsY());

puts("\n\n\nTest_IsUnitVectorTowardsXYZ() has been ended.");
getchar();
system("cls");
};

// _________________________________________________________________________________________________________________________
