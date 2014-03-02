/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2013 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    testSmartPointers

Description

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

template<typename Type>
class infoField 
: 
    public Field<Type>
{
    public: 

        infoField()
            : 
                Field<Type>()
        {
            Info << "empty constructor" << endl;
        }

        infoField(const infoField& other)
            : 
                Field<Type>(other)
        {
            Info << "copy constructor" << endl;
        }

        infoField (int size, Type value)
            : 
                Field<Type>(size, value)
        {
            Info << "size, value constructor" << endl;
        }

        ~infoField()
        {
            Info << "destructor" << endl;
        }

        void operator=(const infoField& other)
        {
            if (this != &other)
            {
                Field<Type>::operator=(other);  
                Info << "assignment operator" << endl;
            }
        }
};

template<typename Type>
Type valueReturn(Type const & t)
{
    // One copy construction for the temporary.
    Type temp = t; 

    // ... operations (e.g. interpolation) on the temporary variable. 
    
    return temp; 
}

// Shorten the type name.  
typedef infoField<scalar> infoScalarField;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{
    // First example

    //Info << "Value construction : "; 
    //infoScalarField valueConstructed(1e07, 5);  

    //Info << "Empty construction : "; 
    //infoScalarField assignedTo; 

    //Info << "Function call" << endl; 
    //assignedTo = valueReturn(valueConstructed); 
    //Info << "Function exit" << endl; 

    // Second example 
    
    // Construct the infoField pointer 
    autoPtr<infoScalarField> ifPtr (new infoScalarField(1e06, 0));  

    // Output the pointer data by accessing the reference -  
    // using the operator T const & autoPtr<T>::operator()
    Info << ifPtr() << endl;

    // Create a copy of the ifPtr and transfer the object ownership
    // to ifPtrCopy. 
    autoPtr<infoScalarField> ifPtrCopy (ifPtr);  

    Info << ifPtrCopy() << endl;

    // Segmentation fault - accessing a deleted pointer. 
    //Info << ifPtr() << endl; 

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    return 0;
}


// ************************************************************************* //
