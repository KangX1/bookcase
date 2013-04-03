/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
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

Description 
    Define the template argument set for the class template that uses RTS.
 
Authors
    Tomislav Maric tomislav.maric@gmx.com

\*---------------------------------------------------------------------------*/

#ifndef parameterTypes_H
#define parameterTypes_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    namespace BookExamples
    {

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        // Type definitions for the possible parameters for the 
        // ExampleClassTemplateBase: built in types used here, but otherwise, 
        // this header must include declarations of all possible template 
        // arguments to be used together with the ExampleClassTemplateBase.
        typedef int    One;  
        typedef float  Two;
        typedef double Three; 
    
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace BookExamples 

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
