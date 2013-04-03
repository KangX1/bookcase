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
    runTimeSelectionMinimalExample

Description
    This is an test application with a minimal example of the Run Time Selection
    (RTS) mechanism added into a object oriented class hierarchy. 
    The RTS mechanism in this example doesn't use dictionary entries, it relies
    on user specified type names through the console I/O. 

Authors
    Tomislav Maric tomislav.maric@gmx.com

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

class AlgorithmBase
{
    public: 

        // Declare the static variable typeName.
        TypeName ("algorithmBase");

        // Empty constructor. 
        AlgorithmBase () {};

        // Word constructor.
        AlgorithmBase (const word& algorithmName) {};

        declareRunTimeSelectionTable
        (
             
        );

        virtual void operator()() 
        {
            Info << "AlgorithmBase::operator()()" << endl;
        }
};

class AlgorithmNew
:
    public AlgorithmBase
{

};

class AlgorithmAdditional
:
    public AlgorithmNew
{
};

int main(int argc, char *argv[])
{

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nEnd\n" << endl;
    return 0;
}


// ************************************************************************* //
