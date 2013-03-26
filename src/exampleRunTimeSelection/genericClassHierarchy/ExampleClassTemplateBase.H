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
    Foam::ExampleClassTemplateBase

Description

SourceFiles
    ExampleClassTemplateBaseI.H
    ExampleClassTemplateBase.C
    ExampleClassTemplateBaseIO.C

\*---------------------------------------------------------------------------*/

#ifndef ExampleClassTemplateBase_H
#define ExampleClassTemplateBase_H

#include "dictionary.H"
#include "typeInfo.H"
#include "runTimeSelectionTables.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace BookExamples
{

/*---------------------------------------------------------------------------*\
                         Class ExampleClassTemplateBase Declaration
\*---------------------------------------------------------------------------*/

template<class Parameter>
class ExampleClassTemplateBase
{

public:

    // Static data members
    TypeName("ExampleClassTemplateBase");

    declareRunTimeSelectionTable ( 	  	
            autoPtr,
		  	ExampleClassTemplateBase,
		  	Dictionary,
		  	(
                const dictionary& dict
            ),
		    (dict)	
	) 		

    //declareRunTimeSelectionTable ( 	  	
            //autoPtr,
			  //ExampleClassTemplateBase,
			  //Word,
			  //(
                //const word& name 
            //),
			//(name)	
	//) 		

    // Constructors

        //- Construct from components
        ExampleClassTemplateBase(const dictionary& dict);
        //ExampleClassTemplateBase(const word& dict);

    // Selectors
        static autoPtr<ExampleClassTemplateBase<Parameter> > New(
            const dictionary& dict
        );
        //static autoPtr<ExampleClassTemplateBase<Parameter> > New(
            //const dictionary& dict
        //);

    //- Destructor
    virtual ~ExampleClassTemplateBase();

    // Member functions
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Macros for template instantiation: these classes get compiled to the library, 
// and have RTS enabled.

#define makeExampleClassTemplateBase(Parameter)                                 \
                                                                                \
defineNamedTemplateTypeNameAndDebug(exampleClass##Parameter##Base, 0);          \
defineTemplateRunTimeSelectionTable(exampleClass##Parameter##Base, Dictionary); \
addToRunTimeSelectionTable                                                      \
(                                                                               \
    exampleClass##Parameter##Base,                                              \
    exampleClass##Parameter##Base,                                              \
    Dictionary                                                                  \
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace BookExamples 

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "ExampleClassTemplateBase.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
