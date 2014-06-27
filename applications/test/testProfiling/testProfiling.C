/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by authors 
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
    testDebugAndProfile

Description
    Tester for Chapter 6 : Debugging and Profiling

Authors:
    Tomislav Maric tomislav@sourceflux.de
    Jens Hoepken jens@sourceflux.de
    Kyle Mooney kyle.g.mooney@gmail.com

Contributors:

\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "Time.H"
#include "IOmanip.H"
#include "clockTime.H"
#include "DynamicField.H"
#include "vector.H"

#include <vector>

typedef Foam::DynamicField<Foam::vector> dynamicVectorField;

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    
    argList::addOption
    (
        "containerSize",
        "testing size of the container"
    );

    argList args(argc, argv);

    if (args.optionFound("containerSize"))
    {
        const label SIZE = args.optionRead<label>("containerSize");

        Info << "Size = " << " " << SIZE << "; ";

        clockTime c; 
        double timeDynamicListNoInit = 0;
        c.timeIncrement();

        DynamicList<vector> d1; 
        for (label I = 0; I < SIZE ; ++I)
        {
            d1.append(vector(I,I,I));
        }

        timeDynamicListNoInit = c.timeIncrement();  
        Info << "Initialized time = " << Foam::setprecision(12) 
            << timeDynamicListNoInit << "; ";

        double timeDynamicListInit  = 0;  
        c.timeIncrement(); 
        DynamicList<label> d2(SIZE); 
        for (label I = 0; I < SIZE; ++I)
        {
            d2.append(I);
        }
        timeDynamicListInit = c.timeIncrement(); 
        Info << "Uninitialized time = " << Foam::setprecision(12) 
            << timeDynamicListInit  << ";" << endl;
    }
    else
    {
        FatalErrorIn
        (
            "main()"
        )   << "Please provide an integer value for the 'containerSize' option." << endl
            << exit(FatalError);
    }


    Info<< "\nEND\n" << endl;
    return 0;
}


// ************************************************************************* //
