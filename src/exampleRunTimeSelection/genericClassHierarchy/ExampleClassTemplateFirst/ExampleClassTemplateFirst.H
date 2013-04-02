/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2012 OpenFOAM Foundation
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

Class
    Foam::ExampleClassTemplateFirst

Description

SourceFiles
    ExampleClassTemplateFirstI.H
    ExampleClassTemplateFirst.C
    ExampleClassTemplateFirstIO.C

\*---------------------------------------------------------------------------*/

#ifndef ExampleClassTemplateFirst_H
#define ExampleClassTemplateFirst_H

#include "ExampleClassTemplateBase.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace BookExamples
{

/*---------------------------------------------------------------------------*\
                         Class ExampleClassTemplateFirst Declaration
\*---------------------------------------------------------------------------*/

template<class Parameter>
class ExampleClassTemplateFirst
:
    public ExampleClassTemplateBase<Parameter>
{

public:

    // Static data members
    TypeName("genericFirst");

    // Constructors

        //- Construct from components
        ExampleClassTemplateFirst(const dictionary& dict);

    //- Destructor
    virtual ~ExampleClassTemplateFirst() {};

    // Member functions
        virtual void execute() const;
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Macros for template instantiation: these classes get compiled to the library, 
// and have RTS enabled.

#define makeExampleClassTemplateFirst(Parameter)                                \
                                                                                \
defineNamedTemplateTypeNameAndDebug(exampleClass##Parameter##First, 0);         \
addToRunTimeSelectionTable                                                      \
(                                                                               \
    exampleClass##Parameter##Base,                                              \
    exampleClass##Parameter##First,                                             \
    Dictionary                                                                  \
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace BookExamples 

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "ExampleClassTemplateFirst.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
