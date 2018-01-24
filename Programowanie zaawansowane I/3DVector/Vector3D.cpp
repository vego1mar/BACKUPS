#include "Vector3D.h"

#include <cmath>

// ________________________________________________________________________________________________________

Vector3D::Vector3D()
    : x(1.0)
    , y(1.0)
    , z(1.0)
    , modulus(CountModulus())

{
};

// ________________________________________________________________________________________________________

Vector3D::Vector3D(double _x, double _y, double _z)
{
x = _x;
y = _y;
z = _z;
modulus = CountModulus();
};

// ___________________________________________________________________

Vector3D::Vector3D(double _modulus, double _ang1, double _ang2, bool _i)
{
if (_i == true)
    {
    modulus = _modulus;
    x = CountCoordinateX(_modulus,_ang1,_ang2);
    y = CountCoordinateY(_modulus,_ang1,_ang2);
    z = CountCoordinateZ(_modulus,_ang2);
    }
else
    {
    modulus = _modulus;
    x = CountCoordinateX(_modulus,DegreesToRadians(_ang1),DegreesToRadians(_ang2));
    y = CountCoordinateY(_modulus,DegreesToRadians(_ang1),DegreesToRadians(_ang2));
    z = CountCoordinateZ(_modulus,DegreesToRadians(_ang2));
    };
};

// ________________________________________________________________________________________________________

Vector3D::~Vector3D()
{
// Clearing the memory.
x = 0.0;
y = 0.0;
z = 0.0;
modulus = 0.0;
};

// ________________________________________________________________________________________________________

Vector3D::Vector3D (const Vector3D & _vector)
    : x(_vector.x)
    , y(_vector.y)
    , z(_vector.z)
    , modulus(CountModulus())

{
};

// ________________________________________________________________________________________________________

void Vector3D::SetX(double _x)
{
x = _x;
modulus = CountModulus();
};

// ________________________________________________________________________________________________________

void Vector3D::SetY(double _y)
{
y = _y;
modulus = CountModulus();
};

// ________________________________________________________________________________________________________

void Vector3D::SetZ(double _z)
{
z = _z;
modulus = CountModulus();
};

// ________________________________________________________________________________________________________

void Vector3D::SetVectorCoordinates(double _x, double _y, double _z)
{
x = _x;
y = _y;
z = _z;
modulus = CountModulus();
};

// ________________________________________________________________________________________________________

void Vector3D::SetPolarCoordinates(long double _modulus, double _ang1, double _ang2, bool _i)
{
if (_i == true)
    {
    modulus = _modulus;
    x = CountCoordinateX(_modulus,_ang1,_ang2);
    y = CountCoordinateY(_modulus,_ang1,_ang2);
    z = CountCoordinateZ(_modulus,_ang2);
    }
else
    {
    modulus = _modulus;
    x = CountCoordinateX(_modulus,DegreesToRadians(_ang1),DegreesToRadians(_ang2));
    y = CountCoordinateY(_modulus,DegreesToRadians(_ang1),DegreesToRadians(_ang2));
    z = CountCoordinateZ(_modulus,DegreesToRadians(_ang2));
    };
};

// ________________________________________________________________________________________________________

void Vector3D::SetModulus(long double _modulus)
{
modulus = _modulus;
};

// ________________________________________________________________________________________________________

double Vector3D::GetX() const
{
return (x);
};

// ________________________________________________________________________________________________________

double Vector3D::GetY() const
{
return (y);
};

// ________________________________________________________________________________________________________

double Vector3D::GetZ() const
{
return (z);
};

// ________________________________________________________________________________________________________

long double Vector3D::GetModulus() const
{
return (modulus);
};

// ________________________________________________________________________________________________________

void Vector3D::GetVectorCoordinates(double * _array) const
{
if (_array != nullptr)
    {
    _array[0] = x;
    _array[1] = y;
    _array[2] = z;
    };
};

// ________________________________________________________________________________________________________

void Vector3D::GetPolarCoordinates(long double * _array) const
{
if (_array != nullptr)
    {
    _array[0] = this->GetModulus();
    _array[1] = this->GetAngleXToY();
    _array[2] = this->GetAngleYToZ();
    };
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator= (const Vector3D & _vector)
{
x = _vector.x;
y = _vector.y;
z = _vector.z;
modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D::operator Vector3D() const
{
return (Vector3D(0,0,0));
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator+ (const Vector3D & _vector)
{
x = x + _vector.x;
y = y + _vector.y;
z = z + _vector.z;
modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator+= (const Vector3D & _vector)
{
(*this) + (_vector);
this->modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator- (const Vector3D & _vector)
{
x = x - _vector.x;
y = y - _vector.y;
z = z - _vector.z;
modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator-= (const Vector3D & _vector)
{
(*this) - (_vector);
this->modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator*= (const Vector3D & _vector)
{
*this = CrossProduct(*this,_vector);
this->modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator* (double _constant)
{
x = _constant * x;
y = _constant * y;
z = _constant * z;
modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D::operator long double() const
{
return (x + y + z);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator~()
{
long double tmp_ = 1.0 / modulus;
x = tmp_ * x;
y = tmp_ * y;
z = tmp_ * z;
modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator()(double _x, double _y, double _z)
{
(*this) = Vector3D(_x,_y,_z);
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator() (double _modulus, double _ang1, double _ang2, bool _i)
{
(*this) = Vector3D(_modulus,_ang1,_ang2,_i);
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator() (void)
{
x = 0.0;
y = 0.0;
z = 0.0;
modulus = 0.0;
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator! ()
{
x = -(x);
y = -(y);
z = -(z);
return (*this);
};

// ________________________________________________________________________________________________________

bool Vector3D::operator== (const Vector3D & _v) const
{
return (
       ((_v.x >= (x - 0.01)) && ((_v.x <= (x + 0.01))))
       && ((_v.y >= (y - 0.01)) && ((_v.y <= (y + 0.01))))
       && ((_v.z >= (z - 0.01)) && ((_v.z <= (z + 0.01))))
       );
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::operator<<= (const Vector3D & _b)
{
this->AddVectorAndSaveDirection(_b);
return (*this);
};

// ________________________________________________________________________________________________________

const Vector3D & Vector3D::operator>>= (Vector3D & _b)
{
_b.AddVectorAndSaveDirection(*this);
return (*this);
};

// ________________________________________________________________________________________________________

const long double & Vector3D::operator[] (char _idx) const
{
long double subscript = 0.0;

switch (_idx)
    {
    case 'x' : { subscript = this->GetX();         } break;
    case 'y' : { subscript = this->GetY();         } break;
    case 'z' : { subscript = this->GetZ();         } break;
    case 'm' : { subscript = this->GetModulus();   } break;
    case '1' : { subscript = this->GetAngleXToY(); } break;
    case '2' : { subscript = this->GetAngleYToZ(); } break;
    };

return (subscript);
};

// ________________________________________________________________________________________________________

long double & Vector3D::operator[] (char _idx)
{
long double subscript = 0.0;

switch (_idx)
    {
    case 'x' : { subscript = this->GetX();         } break;
    case 'y' : { subscript = this->GetY();         } break;
    case 'z' : { subscript = this->GetZ();         } break;
    case 'm' : { subscript = this->GetModulus();   } break;
    case '1' : { subscript = this->GetAngleXToY(); } break;
    case '2' : { subscript = this->GetAngleYToZ(); } break;
    };

return (subscript);
};

// ________________________________________________________________________________________________________

void Vector3D::Add(const Vector3D & _v1)
{
(*this) + _v1;
};

// ________________________________________________________________________________________________________

void Vector3D::Add(const Vector3D & _v1, const Vector3D & _v2)
{
(*this) + _v1;
(*this) + _v2;
};

// ________________________________________________________________________________________________________

void Vector3D::Add(const Vector3D & _v1, const Vector3D & _v2, const Vector3D & _v3)
{
(*this) + _v1;
(*this) + _v2;
(*this) + _v3;
};

// ________________________________________________________________________________________________________

void Vector3D::Substract(const Vector3D & _v1)
{
(*this) - _v1;
};

// ________________________________________________________________________________________________________

void Vector3D::Substract(const Vector3D & _v1, const Vector3D & _v2)
{
(*this) - _v1;
(*this) - _v2;
};

// ________________________________________________________________________________________________________

void Vector3D::Substract(const Vector3D & _v1, const Vector3D & _v2, const Vector3D & _v3)
{
(*this) - _v1;
(*this) - _v2;
(*this) - _v3;
};

// ________________________________________________________________________________________________________

void Vector3D::Normalize()
{
~(*this);
};

// ________________________________________________________________________________________________________

void Vector3D::MultiplyByAConst(const double _cval)
{
(*this) * _cval;
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::CrossProduct(const Vector3D & _v1, const Vector3D & _v2)
{
x = (_v1.y * _v2.z) - (_v1.z * _v2.y);
y = (_v1.z * _v2.x) - (_v1.x * _v2.z);
z = (_v1.x * _v2.y) - (_v1.y * _v2.x);
modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::CrossProductWith(const Vector3D & _v2)
{
// Creating a temporal copy of the values.
double * coord_x = new double(x);
double * coord_y = new double(y);
double * coord_z = new double(z);

x = ((*coord_y) * _v2.z) - ((*coord_z) * _v2.y);
y = ((*coord_z) * _v2.x) - ((*coord_x) * _v2.z);
z = ((*coord_x) * _v2.y) - ((*coord_y) * _v2.x);
modulus = CountModulus();

// Deallocating the memory.
delete coord_x;
delete coord_y;
delete coord_z;

return (*this);
};

// ________________________________________________________________________________________________________

/*** static ***/
double Vector3D::CrossProductAsScalar(const Vector3D & _v1, const Vector3D & _v2)
{
// Declarations.
double result;
double * ang = new double;
Vector3D * tmp = new Vector3D;

// Counting the value.
(*tmp) = _v1;
(*ang) = tmp->GetAngleWithOtherVector(_v2);
(*ang) = sin(*ang);
(*ang) = (*ang) * (_v1.GetModulus()) * (_v2.GetModulus());
result = (*ang);

// Deallocating the memory.
delete tmp;
delete ang;

return (result);
};

// ________________________________________________________________________________________________________

/*** static ***/
double Vector3D::DotProduct(const Vector3D & _v1, const Vector3D & _v2)
{
return ((_v1.x * _v2.x) + (_v1.y * _v2.y) + (_v1.z * _v2.z));
};

// ________________________________________________________________________________________________________

void Vector3D::ReturnVector()
{
!(*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::InverseVector()
{
x = 1.0 / x;
y = 1.0 / y;
z = 1.0 / z;
modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

bool Vector3D::IsVectorEqualWith(const Vector3D & _v) const
{
return ((*this) == _v);
};

// ________________________________________________________________________________________________________

bool Vector3D::IsModulusEqualWith(const Vector3D & _v) const
{
return (
       ((_v.modulus >= (modulus - 0.01)) && ((_v.modulus <= (modulus + 0.01))))
       );
};

// ________________________________________________________________________________________________________

bool Vector3D::IsUnitVectorTowardsX() const
{
return (
       (   (x >= (-1.01)) && ((x <= (+1.01))))
       && ((y >= (-0.01)) && ((y <= (+0.01))))
       && ((z >= (-0.01)) && ((z <= (+0.01))))
       );
};

// ________________________________________________________________________________________________________

bool Vector3D::IsUnitVectorTowardsY() const
{
return (
       (   (x >= (-0.01)) && ((x <= (+0.01))))
       && ((y >= (-1.01)) && ((y <= (+1.01))))
       && ((z >= (-0.01)) && ((z <= (+0.01))))
       );
};

// ________________________________________________________________________________________________________

bool Vector3D::IsUnitVectorTowardsZ() const
{
return (
       (   (x >= (-0.01)) && ((x <= (+0.01))))
       && ((y >= (-0.01)) && ((y <= (+0.01))))
       && ((z >= (-1.01)) && ((z <= (+1.01))))
       );
};

// ________________________________________________________________________________________________________

bool Vector3D::IsUnitVectorTowardsXYZ() const
{
return (
       (   (x >= (-1.01)) && ((x <= (+1.01))))
       && ((y >= (-1.01)) && ((y <= (+1.01))))
       && ((z >= (-1.01)) && ((z <= (+1.01))))
       );
};

// ________________________________________________________________________________________________________

bool Vector3D::IsZeroVector() const
{
return (
       (   (x >= (-0.01)) && ((x <= (+0.01))))
       && ((y >= (-0.01)) && ((y <= (+0.01))))
       && ((z >= (-0.01)) && ((z <= (+0.01))))
       );
};

// ________________________________________________________________________________________________________

double Vector3D::GetVectorAngleWithOX() const
{
return (acos(x / modulus));
};

// ________________________________________________________________________________________________________

double Vector3D::GetVectorAngleWithOY() const
{
return (acos(y / modulus));
};

// ________________________________________________________________________________________________________

double Vector3D::GetVectorAngleWithOZ() const
{
return (acos(z / modulus));
};

// ________________________________________________________________________________________________________

double Vector3D::GetCoordinateXProjectionToOX() const
{
return (x * (x / modulus));
};

// ________________________________________________________________________________________________________

double Vector3D::GetCoordinateYProjectionToOY() const
{
return (y * (y / modulus));
};

// ________________________________________________________________________________________________________

double Vector3D::GetCoordinateZProjectionToOZ() const
{
return (z * (z / modulus));
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::VectorProjectionToOX()
{
// Declarations.
double * proj = new double;

// Counting the projection to OX-axis.
*proj = (x / modulus);
this->MultiplyByAConst(*proj);
this->modulus = CountModulus();

// Deallocating the memory.
delete proj;

return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::VectorProjectionToOY()
{
// Declarations.
double * proj = new double;

// Counting the projection to OX-axis.
*proj = (y / modulus);
this->MultiplyByAConst(*proj);
this->modulus = CountModulus();

// Deallocating the memory.
delete proj;

return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::VectorProjectionToOZ()
{
// Declarations.
double * proj = new double;

// Counting the projection to OX-axis.
*proj = (z / modulus);
this->MultiplyByAConst(*proj);
this->modulus = CountModulus();

// Deallocating the memory.
delete proj;

return (*this);
};

// ________________________________________________________________________________________________________

/*** static ***/
double Vector3D::DegreesToRadians(double _degrees)
{
return ((_degrees * (atan(1.0) * 4.0)) / 180.0);
};

// ________________________________________________________________________________________________________

/*** static ***/
double Vector3D::RadiansToDegrees(double _radians)
{
return (_radians * (180.0 / (atan(1.0) * 4.0)));
};

// ________________________________________________________________________________________________________

double Vector3D::GetAngleXToY() const
{
return (atan(x/y));
};

// ________________________________________________________________________________________________________

double Vector3D::GetAngleYToZ() const
{
return (atan(y/x));
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::RotateByAngleToX(double _angle)
{
double y_ = y;
double z_ = z;
double cos_ = cos(_angle);
double sin_ = sin(_angle);
y = (y_ * cos_) + (z_ * (-sin_));
z = (y_ * sin_) + (z_ * cos_);
modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::RotateByAngleToY(double _angle)
{
double x_ = x;
double z_ = z;
double cos_ = cos(_angle);
double sin_ = sin(_angle);
x = (x_ * cos_) + (z_ * sin_);
z = (x_ * (-sin_)) + (z_ * cos_);
modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::RotateByAngleToZ(double _angle)
{
double x_ = x;
double y_ = y;
double cos_ = cos(_angle);
double sin_ = sin(_angle);
x = (x_ * cos_) + (y_ * (-sin_));
y = (x_ * sin_) + (y_ * cos_);
modulus = CountModulus();
return (*this);
};

// ________________________________________________________________________________________________________

double Vector3D::GetAngleWithOtherVector(const Vector3D & _v)
{
return (acos(((x * _v.x) + (y * _v.y) + (z * _v.z)) / (modulus * _v.modulus)));
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::AddVectorAndSaveDirection(const Vector3D & _b)
{
// Declarations.
Vector3D * rv = new Vector3D;
double * sc = new double;
double * dp = new double;

// Counting the resultant vector.
rv->SetVectorCoordinates(x,y,z);
rv->Add(_b);

// Counting the projection to the vector A.
*dp = Vector3D::DotProduct(*rv,*this);
*sc = modulus * modulus;
*sc = (*dp) / (*sc);
this->MultiplyByAConst(*sc);
this->modulus = CountModulus();

// Deallocating the memory.
delete rv;
delete sc;
delete dp;

return (*this);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::VectorProjectionToAnotherVector(const Vector3D & _b)
{
// Declarations.
double dp;
double sc;

// Counting the orthogonal projection of the vector A to the direction of the vector B.
dp = DotProduct(*this,_b);
sc = _b.GetModulus();
sc = sc * sc;
sc = dp / sc;

// Changing the poles.
x = _b.GetX() * sc;
y = _b.GetY() * sc;
z = _b.GetZ() * sc;
this->modulus = CountModulus();

return (*this);
};

// ________________________________________________________________________________________________________

/*** static ***/
double Vector3D::GetComponentBAlongA(const Vector3D & _a, const Vector3D & _b)
{
return ((DotProduct(_a,_b)) / _a.modulus);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::AlterToProjectionOfBAlongA(const Vector3D & _b)
{
// Declarations.
double * tmp = new double;

// Counting the projection.
*tmp = (DotProduct(*this,_b) / (modulus * modulus));
this->MultiplyByAConst(*tmp);
this->modulus = CountModulus();

// Deallocating the memory.
delete tmp;

return (*this);
};

// ________________________________________________________________________________________________________

bool Vector3D::IsVectorColinearWith(const Vector3D & _b)
{
// Declarations.
Vector3D * tmp = new Vector3D(x,y,z);
bool op = false;

// Counting the necessary cross product.
tmp->CrossProductWith(_b);
if ((*tmp) == 0.0) op = true;

// Deallocating the memory.
delete tmp;

return (op);
};

// ________________________________________________________________________________________________________

bool Vector3D::IsPerpendicularWith(const Vector3D & _b)
{
return ( (((DotProduct(*this,_b)) >= -0.01 ) && (((DotProduct(*this,_b)) <= +0.01 ))) ? true : false);
};

// ________________________________________________________________________________________________________

Vector3D & Vector3D::AlterToVectorMomentusWith(const Vector3D & _v)
{
// Creating a temporal copy of the values.
double * coord_x = new double(x);
double * coord_y = new double(y);
double * coord_z = new double(z);

// Counting the right coordinates.
x = ((*coord_y) * _v.GetZ()) - ((*coord_z) * _v.GetY());
y = ((*coord_z) * _v.GetX()) - ((*coord_x) * _v.GetZ());
z = ((*coord_x) * _v.GetY()) - ((*coord_y) * _v.GetX());
this->modulus = CountModulus();

// Deallocating the memory.
delete coord_x;
delete coord_y;
delete coord_z; 

return (*this);
};

// ________________________________________________________________________________________________________

/*** static ***/
bool Vector3D::AreVectorsCoplanar(const Vector3D & _a, const Vector3D & _b, const Vector3D & _c)
{
// Declarations.
bool op = false;
Vector3D * tmp = new Vector3D;
double * sc = new double;

// Counting the mixed vector product.
*tmp = _b;
tmp->CrossProductWith(_c);
*sc = DotProduct(*tmp,_a);
if ((*sc) == 0.0) op = true;

// Deallocating the memory.
delete tmp;
delete sc;

return (op);
};

// ________________________________________________________________________________________________________

bool Vector3D::IsCollinearWith(const Vector3D & _b)
{
// Declarations.
bool op = false;
double * div_x = new double;
double * div_y = new double;
double * div_z = new double;

// Counting the 'coordinates scale'.
*div_x = (_b.GetX() / this->GetX());
*div_y = (_b.GetY() / this->GetY());
*div_z = (_b.GetZ() / this->GetZ());

if ( 
   (((*div_x) >= (-(*div_y)-0.01)) && (((*div_x) <= (+(*div_y)+0.01)))) &&
   (((*div_y) >= (-(*div_z)-0.01)) && (((*div_y) <= (+(*div_z)+0.01))))
   ) 
    op = true;

// Deallocating the memory.
delete div_x;
delete div_y;
delete div_z;

return (op);
};

// ________________________________________________________________________________________________________

double Vector3D::GetSurfaceAreaOfParallelogramWith(const Vector3D & _v)
{
return ( abs(Vector3D::CrossProductAsScalar(*this,_v)) );
};

// ________________________________________________________________________________________________________

double Vector3D::GetSurfaceAreaOfTriangleWith(const Vector3D & _v)
{
return ( 0.5 * abs(Vector3D::CrossProductAsScalar(*this,_v)) );
};

// ________________________________________________________________________________________________________

/*** static ***/
double Vector3D::GetMixedVectorProduct(const Vector3D & _v1, const Vector3D & _v2, const Vector3D & _v3)
{
// Declarations.
double result;
Vector3D * tmp = new Vector3D(_v2);

// Counting the mixed vector product.
tmp->CrossProductWith(_v3);
result = Vector3D::DotProduct(_v1,*tmp);

// Deallocating the memory.
delete tmp;

return (result);
};

// ________________________________________________________________________________________________________

double Vector3D::GetVolumeOfParallelepipedWith(const Vector3D & _v2, const Vector3D & _v3)
{
return ( abs(Vector3D::GetMixedVectorProduct(*this,_v2,_v3)) );
};

// ________________________________________________________________________________________________________

double Vector3D::GetVolumeOfPyramidWith(const Vector3D & _v2, const Vector3D & _v3)
{
return ( (1.0 / 6.0) * abs(Vector3D::GetMixedVectorProduct(*this,_v2,_v3)) );
};

// ________________________________________________________________________________________________________

long double Vector3D::CountModulus() const
{
return (sqrt((long double)((x*x)+(y*y)+(z*z))));
};

// ________________________________________________________________________________________________________

double Vector3D::CountCoordinateX(double _modulus, double _ang1, double _ang2) const
{
return (_modulus * (cos(_ang2)) * (sin(_ang1)));
};

// ________________________________________________________________________________________________________

double Vector3D::CountCoordinateY(double _modulus, double _ang1, double _ang2) const
{
return (_modulus * (cos(_ang2)) * (cos(_ang1)));
};

// ________________________________________________________________________________________________________

double Vector3D::CountCoordinateZ(double _modulus, double _ang2) const
{
return (_modulus * (sin(_ang2)));
};

// ________________________________________________________________________________________________________
// ________________________________________________________________________________________________________

std::ostream & operator<< (std::ostream & _os, const Vector3D & _v)
    {
    // Using a specified output format.
    std::cout << "[" << _v.GetX() << "," << _v.GetY() << "," << _v.GetZ() << "]" << std::endl;

    // Reinvoking the output stream.
    return (_os);
    };

// ________________________________________________________________________________________________________

std::istream & operator>> (std::istream & _is, Vector3D & _v)
    {
    // Declarations.
    double coord_x = 0.0;
    double coord_y = 0.0;
    double coord_z = 0.0;

    // Reading for the carthesian coordinates.
    std::cout << "x = ";
    std::cin >> coord_x;
    std::cout << "y = "; 
    std::cin >> coord_y;
    std::cout << "z = "; 
    std::cin >> coord_z;

    // Checking the actual state of the variables.
    if ( ((coord_x >= (-0.01)) && ((coord_x <= (0.01))))
            && ((coord_y >= (-0.01)) && ((coord_y <= (+0.01))))
            && ((coord_z >= (-0.01)) && ((coord_z <= (+0.01)))) )
        {
        // Setting the failbit flag, when no valid object was found.
        _is.setstate(std::ios::failbit);
        }
    else
        {
        // Changing the object.
        _v.SetVectorCoordinates(coord_x,coord_y,coord_z);
        };

    // Reinvoking the input stream.
    return (_is);
    };

// ________________________________________________________________________________________________________
