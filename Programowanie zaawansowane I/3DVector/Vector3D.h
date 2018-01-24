// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Vector3D
//
// Representant of a vector in a three-dimentional carthesian coordinate system.
// Not designed to be derived.
// The copy construction is allowed.
//
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//
// -----------------    ----------------    -------------------------------------------------------------
// Executor             Date                Description
// -----------------    ----------------    -------------------------------------------------------------
// Siciñski P.          21/03/2016          Start of the project.
// Siciñski P.          23/03/2016          Development of the main functionalities was ended.
// Siciñski P.          25/03/2016          AngleWithVector() method was added and finished.
// Siciñski P.          31/03/2016          AddVectorAndSaveDirection() method was added and finished.
// Siciñski P.          01/04/2016          Some methods was added for completeness of the class.
// Siciñski P.          02/04/2016          IsZeroVector() method was added and finished.
//
//



#ifndef VECTOR3D_H
#define VECTOR3D_H

// ****************************************************************************************************************

    #include <iostream>

// ****************************************************************************************************************

    class Vector3D
        {

        // ________________________________________________________________________________________________________

        // *** THE POLES ***

        private:

            // A coordinate on the x-axis (length).
            double x;

            // A coordinate on the y-axis (width).
            double y;

            // A coordinate on the z-axis (depth).
            double z;

            // A modulus (magnitude) of the vector itself.
            long double modulus;

        // ________________________________________________________________________________________________________

        // *** THE CONSTRUCTORS AND THE DESTRUCTOR ***

        public:

            // The default constructor.
            // This is a vector of a value [1,1,1].
            Vector3D();

            // A constructor that using coordinates.
            // The valid order is [x,y,z].
            Vector3D(double, double, double);

            // A constructor using modulus and angles alfa and beta.
            // Alfa angle is from X toward Y axis.
            // Beta angle is from Y toward Z axis.
            // Angles are coincident with maneuvers of the hands of the clock.
            // If bool is true then angles are interpreted as radians, otherwise as degrees.
            Vector3D(double, double, double, bool);

            // The destructor.
            ~Vector3D();

            // The copy constructor.
            Vector3D (const Vector3D &);

        // ________________________________________________________________________________________________________

        // *** THE SET-CLASS FUNCTIONS ***

        public:

            // Changing the x-axis coordinate.
            void SetX(double);

            // Changing the y-axis coordinate.
            void SetY(double);

            // Changing the z-axis coordinate.
            void SetZ(double);

            // Altering the vector coordinates at ones.
            void SetVectorCoordinates(double, double, double);

            // Altering the vector by interpreting the parameters as a polar coordinates.
            // See description of the related constructor.
            void SetPolarCoordinates(long double,double,double,bool);

        private:

            // Changing the magnitude of the vector without impacting on its coordinates.
            // Note that this method is available only for completness.
            void SetModulus(long double);

        // ________________________________________________________________________________________________________

        // *** THE GET-CLASS FUNCTIONS ***

        public:

            // Giving the x-axis coordinate.
            double GetX() const;

            // Giving the y-axis coordinate.
            double GetY() const;

            // Giving the z-axis coordinate.
            double GetZ() const;

            // Giving the modulus.
            long double GetModulus() const;

            // Retrieves the vector coordinates to the pointed array.
            void GetVectorCoordinates(double *) const;

            // Retrieves the vector polar coordinates to the pointed array.
            void GetPolarCoordinates(long double *) const;

        // ________________________________________________________________________________________________________

        // *** THE OVERLOADED OPERATORS ***

        public:

            // The assignment operator.
            // Use of this operator is not recommended with others operators, but possible.
            Vector3D & operator= (const Vector3D &);

            // The class-type-casting operator.
            // Currently this has no use.
            operator Vector3D() const;

            // The addition operator.
            // Use to change the left-value vector to its addition with the right-value vector.
            Vector3D & operator+ (const Vector3D &);

            // The addition with assignment operator.
            // Use to change the left-value vector to its addition with the right-value vector.
            Vector3D & operator+= (const Vector3D &);

            // The substraction operator.
            // Use to change the left-value vector to its substraction with the right-value vector.
            Vector3D & operator- (const Vector3D &);

            // The substraction with assignment operator.
            // Use to change the left-value vector to its substraction with the right-value vector.
            Vector3D & operator-= (const Vector3D &);

            // The multiplication with an assignment operator.
            // Use to change the left-value vector to its cross product with the right-value vector.
            Vector3D & operator*= (const Vector3D &);

            // The multiplication operator.
            // Use to multiply the left-value vector by a constant right-value.
            Vector3D & operator* (double);

            // The long double-cast operator.
            // Use to get the sum of the vector coordinates using type casting.
            operator long double() const;

            // The bitwise NOT operator.
            // Use to normalize the vector.
            Vector3D & operator~ ();

            // The call operator.
            // Use to change coordinates at ones using carthesian coordinate system.
            // See description of the related constructor.
            Vector3D & operator() (double, double, double);

            // The call operator.
            // Use to change coordinates at ones using polar coordinate system.
            // See description of the related constructor.
            Vector3D & operator() (double, double, double, bool);

            // The call operator.
            // Use to set or create the vector as a zero vector of [0,0,0].
            Vector3D & operator() (void);

            // The negation operator.
            // Use to reverse signs of the coordinates in the vector.
            Vector3D & operator! ();

            // The equality operator.
            // Use to check if coordinates [x,y,z] are equal with the other vector.
            bool operator== (const Vector3D &) const;

            // The left bitshift with an assignment operator.
            // Use to add the vector B to the vector A with saving the direction of the vector A.
            Vector3D & operator<<= (const Vector3D &);

            // The right bitshift with an assignment operator.
            // Use to add the vector A to the vector B with saving the direction of the vector B.
            const Vector3D & operator>>= (Vector3D &);

            // The array subscript operator.
            // Use to get a quick access to view of the carthesian and polar coordinates of the vector.
            const long double & operator[] (char) const;

            // The array subscript operator.
            // Use to get a quick access to alter the carthesian and polar coordinates of the vector.
            long double & operator[] (char);

        // ________________________________________________________________________________________________________

        // *** THE CLASS INTERFACE ***

        public:

            // Adding two vectors.
            void Add(const Vector3D &);

            // Adding three vectors.
            void Add(const Vector3D &, const Vector3D &);

            // Adding four vectors.
            void Add(const Vector3D &, const Vector3D &, const Vector3D &);

            // Substracting two vectors.
            void Substract(const Vector3D &);

            // Substracting three vectors.
            void Substract(const Vector3D &, const Vector3D &);

            // Substracting four vectors.
            void Substract(const Vector3D &, const Vector3D &, const Vector3D &);

            // Normalize the vector.
            void Normalize();

            // Multiplying the vector by a constant value.
            void MultiplyByAConst(const double);

            // Giving the cross (vector) product of two vectors.
            Vector3D & CrossProduct(const Vector3D &, const Vector3D &);

            // Giving the cross product with the another vector.
            Vector3D & CrossProductWith(const Vector3D &);

            // Giving the cross product with the other vector as a scalar value.
            static double CrossProductAsScalar(const Vector3D &, const Vector3D &);

            // Giving the numerical dot (scalar) product of two vectors.
            static double DotProduct(const Vector3D &, const Vector3D &);

            // Changing return of the vector to opposite.
            void ReturnVector();

            // The reciprocal of the vector's coordinates.
            Vector3D & InverseVector();

            // Checking if vectors are equal using internal defined circumscription.
            bool IsVectorEqualWith(const Vector3D &) const;

            // Checking if moduluses of vectors are equal using internal defined circumscription.
            bool IsModulusEqualWith(const Vector3D &) const;

            // Checking if vector is a unit vector of [1,0,0].
            bool IsUnitVectorTowardsX() const;

            // Checking if vector is a unit vector of [0,1,0].
            bool IsUnitVectorTowardsY() const;

            // Checking if vector is a unit vector of [0,0,1].
            bool IsUnitVectorTowardsZ() const;

            // Checking if vector is a unit vector of [1,1,1].
            bool IsUnitVectorTowardsXYZ() const;

            // Checking if vector is a zero vector of [0,0,0].
            bool IsZeroVector() const;

            // Giving a radius angle value between the vector and the OX-axis.
            double GetVectorAngleWithOX() const;

            // Giving a radius angle value between the vector and the OY-axis.
            double GetVectorAngleWithOY() const;

            // Giving a radius angle value between the vector and the OZ-axis.
            double GetVectorAngleWithOZ() const;

            // Projection scalar value of the x carthesian coordinate of the vector on the OX-axis.
            double GetCoordinateXProjectionToOX() const;

            // Projection scalar value of the y carthesian coordinate of the vector on the OY-axis.
            double GetCoordinateYProjectionToOY() const;

            // Projection scalar value of the z carthesian coordinate of the vector on the OZ-axis.
            double GetCoordinateZProjectionToOZ() const;

            // Projection of the vector on the OX-axis.
            Vector3D & VectorProjectionToOX();

            // Projection of the vector on the OY-axis.
            Vector3D & VectorProjectionToOY();

            // Projection of the vector on the OZ-axis.
            Vector3D & VectorProjectionToOZ();

            // Converts from degrees to radians.
            static double DegreesToRadians(double);

            // Converts from radians to degrees.
            static double RadiansToDegrees(double);

            // Giving a radius angle from x-axis toward y-axis of the vector.
            // It is equivalent to the alfa angle of the vector polar interpretation.
            double GetAngleXToY() const;

            // Giving a radius angle from y-axis toward z-axis of the vector.
            // It is equivalent to the beta angle of the vector polar interpretation.
            double GetAngleYToZ() const;

            // Rotates the vector by a radius angle towards OX-axis.
            Vector3D & RotateByAngleToX(double);

            // Rotates the vector by a radius angle towards OY-axis.
            Vector3D & RotateByAngleToY(double);

            // Rotates the vector by a radius angle towards OZ-axis.
            Vector3D & RotateByAngleToZ(double);

            // Gives a radius angle with another vector.
            double GetAngleWithOtherVector(const Vector3D &);

            // Add vector A to the vector B, but holds the direction of the vector A.
            Vector3D & AddVectorAndSaveDirection(const Vector3D &);

            // Gives the orthogonal projection of the A vector to the direction of the B vector.
            Vector3D & VectorProjectionToAnotherVector(const Vector3D &);

            // Gives the component of the vector B along the vector A.
            static double GetComponentBAlongA(const Vector3D &, const Vector3D &);

            // Altering the vector itself to a projection of the vector B along the vector A.
            Vector3D & AlterToProjectionOfBAlongA(const Vector3D &);

            // Checking if the vector A is colinear with the vector B.
            bool IsVectorColinearWith(const Vector3D &);

            // Checking if the vector A is perpendicular with the vector B.
            bool IsPerpendicularWith(const Vector3D &);

            // Altering the vector to its momentus with another vector.
            Vector3D & AlterToVectorMomentusWith(const Vector3D &);

            // Checking if the three vectors are coplanar (are they suited on the same plain).
            static bool AreVectorsCoplanar(const Vector3D &, const Vector3D &, const Vector3D &);

            // Checking if the vector is collinear with the another vector.
            bool IsCollinearWith(const Vector3D &);

            // Giving the surface area of the parallelogram determined by the two unbuttoned vectors.
            // This had a well-defined sense only for the vectors of [x,y,0].
            double GetSurfaceAreaOfParallelogramWith(const Vector3D &);

            // Giving the surface area of the triangle determined by the two unbuttoned vectors.
            // This had a well-defined sense only for the vectors of [x,y,0].
            double GetSurfaceAreaOfTriangleWith(const Vector3D &);

            // Giving the result of the mixed vector product of the three vectors.
            static double GetMixedVectorProduct(const Vector3D &, const Vector3D &, const Vector3D &);

            // Giving the volume of the parallelepiped determined by the three unbuttoned vectors.
            double GetVolumeOfParallelepipedWith(const Vector3D &, const Vector3D &);

            // Giving the volume of the pyramid determined by the three unbuttoned vectors.
            double GetVolumeOfPyramidWith(const Vector3D &, const Vector3D &);

        // ________________________________________________________________________________________________________

        // *** THE INTERNAL FUNCTIONS ***

        private:
            
            // Counting the modulus (magnitude) of the vector.
            long double CountModulus() const;

            // Counting the X coordinate from the polar coordinate system data.
            double CountCoordinateX(double, double, double) const;

            // Counting the Y coordinate from the polar coordinate system data.
            double CountCoordinateY(double, double, double) const;

            // Counting the Z coordinate from the polar coordinate system data.
            double CountCoordinateZ(double, double) const;

        // ________________________________________________________________________________________________________

        };

// ****************************************************************************************************************

    // *** THE C++ INPUT/OUTPUT OVERLOADED BITSHIFT OPERATORS ***

    // The inserter operator.
    // Use to print out the carthesian coordinates of the vector to the standard output.
    std::ostream & operator<< (std::ostream &, const Vector3D &);

    // The extractor operator.
    // Use to get the carthesian coordinates of the vector from the standard input.
    // The zero vector cannot be assigned this way.
    std::istream & operator>> (std::istream &, Vector3D &);


// ****************************************************************************************************************

#endif // VECTOR3D_H
