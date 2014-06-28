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

Class
    Foam::recirculationControlFvPatchField

Description

    Decorator for the fvPatchField.

    This boundary condition checks for recirculation using the specified flux
    field and controls the specified controlled patch in order to reduce the 
    recirculation.

    Usage

        type             controlledRecirculation;
        baseType         zeroGradient;
        fluxField        phi; 
        controlledPatch  inlet;  

SeeAlso
    Foam::fvPatchField

SourceFiles
    recirculationControlFvPatchField.C
    recirculationControlFvPatchFields.C

Authors:
    Tomislav Maric tomislav.maric@gmx.com

\*---------------------------------------------------------------------------*/

#include "recirculationControlFvPatchField.H"
#include "fvPatchField.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
Foam::recirculationControlFvPatchField<Type>::recirculationControlFvPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF
)
:
    fvPatchField<Type>(p, iF), 
    baseTypeTmp_(), 
    applyControl_(), 
    baseTypeName_(), 
    fluxFieldName_(), 
    controlledPatchName_(), 
    maxValue_(), 
    recirculationRate_(1)
{}


template<class Type>
Foam::recirculationControlFvPatchField<Type>::recirculationControlFvPatchField
(
    const recirculationControlFvPatchField<Type>& ptf,
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fvPatchField<Type>(ptf, p, iF, mapper), 
    baseTypeTmp_(), 
    applyControl_(ptf.applyControl_), 
    baseTypeName_(ptf.baseTypeName_), 
    fluxFieldName_(ptf.fluxFieldName_), 
    controlledPatchName_(ptf.controlledPatchName_), 
    maxValue_(ptf.maxValue_), 
    recirculationRate_(ptf.recirculationRate_)
{
    // Instantiate the baseType based on the dictionary entries. 
    baseTypeTmp_ = fvPatchField<Type>::New
    (
        ptf.baseTypeTmp_, 
        p, 
        iF, 
        mapper
    ); 
}


template<class Type>
Foam::recirculationControlFvPatchField<Type>::recirculationControlFvPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF,
    const dictionary& dict
)
:
    fvPatchField<Type>(p, iF, dict), 
    baseTypeTmp_(), 
    applyControl_(dict.lookupOrDefault<word>("applyControl", "no")),
    baseTypeName_(dict.lookupOrDefault<word>("baseType", "zeroGradient")),
    fluxFieldName_(dict.lookupOrDefault<word>("fluxFieldName", "phi")),
    controlledPatchName_(dict.lookupOrDefault<word>("controlledPatchName", "phi")),
    maxValue_(dict.lookupOrDefault<Type>("maxValue", Type())),
    recirculationRate_(1)
{
    // Instantiate the baseType based on the dictionary entries. 
    baseTypeTmp_ = fvPatchField<Type>::New
    (
        baseTypeName_, 
        p, 
        iF
    ); 
}


template<class Type>
Foam::recirculationControlFvPatchField<Type>::recirculationControlFvPatchField
(
    const recirculationControlFvPatchField<Type>& ptf
)
:
    fvPatchField<Type>(ptf),
    baseTypeTmp_(ptf.baseTypeTmp_),  
    applyControl_(ptf.applyControl_),  
    baseTypeName_(ptf.baseTypeName_),  
    fluxFieldName_(ptf.fluxFieldName_), 
    controlledPatchName_(ptf.controlledPatchName_), 
    maxValue_(ptf.maxValue_),
    recirculationRate_(1)
{}


template<class Type>
Foam::recirculationControlFvPatchField<Type>::recirculationControlFvPatchField
(
    const recirculationControlFvPatchField<Type>& ptf,
    const DimensionedField<Type, volMesh>& iF
)
:
    fvPatchField<Type>(ptf, iF),
    baseTypeTmp_(ptf.baseTypeTmp_),
    applyControl_(ptf.applyControl_),  
    baseTypeName_(ptf.baseTypeName_),
    fluxFieldName_(ptf.fluxFieldName_), 
    controlledPatchName_(ptf.controlledPatchName_), 
    maxValue_(ptf.maxValue_), 
    recirculationRate_(1)
{}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void Foam::recirculationControlFvPatchField<Type>::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    typedef GeometricField<Type, fvPatchField, volMesh>  VolumetricField; 

    // Get the flux field
    const Field<scalar>& phip =
    this->patch().template lookupPatchField<surfaceScalarField, scalar>
    (
        fluxFieldName_
    );

    // Compute the total and the negative volumetric flux.
    scalar totalFlux = 0; 
    scalar negativeFlux = 0; 

    forAll (phip, I)
    {
        totalFlux += mag(phip[I]); 

        if (phip[I] < 0)
        {
            negativeFlux += mag(phip[I]);
        }
    }

    // Compute the recirculation rate.  
    scalar newRecirculationRate = min(1, negativeFlux / (totalFlux + SMALL));  

    Info << "Total flux " <<  totalFlux << endl;
    Info << "Recirculation flux " << negativeFlux << endl;
    Info << "Recirculation ratio " << newRecirculationRate << endl;

    // If there is no recirculation.
    if (negativeFlux < SMALL) 
    {
        // Update the decorated boundary condition. 
        baseTypeTmp_->updateCoeffs(); 
        // Mark the BC updated. 
        fvPatchField<Type>::updateCoeffs(); 
        return;
    }

    if ((applyControl_ == "yes") && (newRecirculationRate > recirculationRate_))
    {
        Info << "Executing control..." << endl;

        // Get the name of the internal field.
        const word volFieldName = this->dimensionedInternalField().name(); 

        // Get access to the regitstry.
        const objectRegistry& db = this->db(); 

        // Find the GeometricField in the registry using the internal field name.
        const VolumetricField& vfConst = db.lookupObject<VolumetricField>(volFieldName);

        // Cast away constness to be able to control other boundary patch fields. 
        VolumetricField& vf = const_cast<VolumetricField&>(vfConst); 

        // Get the non-const reference to the boundary field of the GeometricField.
        typename VolumetricField::GeometricBoundaryField& bf = vf.boundaryField();

        // Find the controlled boundary patch field using the name defined by the user.
        forAll (bf, patchI)
        {
            // Control the boundary patch field using the recirculation rate.  
            const fvPatch& p = bf[patchI].patch();

            if (p.name() == controlledPatchName_)
            {
                if (! bf[patchI].updated())
                {
                    // Envoke a standard update first to avoid the field being later 
                    // overwritten.
                    bf[patchI].updateCoeffs(); 
                }
                // Compute new boundary field values.
                Field<Type> newValues (bf[patchI]); 

                scalar maxNewValue = mag(max(newValues)); 

                if (maxNewValue < SMALL)
                {
                    bf[patchI] == 0.1 * maxValue_; 
                } else if (maxNewValue < mag(maxValue_))
                {
                    // Impose control on the controlled inlet patch field.  
                    bf[patchI] == newValues * 1.01; 
                }
            }
        }
    }

    // Update the recirculation rate. 
    recirculationRate_ = newRecirculationRate; 

    // Mark the BC updated. 
    fvPatchField<Type>::updateCoeffs(); 
}


template<class Type>
void Foam::recirculationControlFvPatchField<Type>::write(Ostream& os) const
{
    fvPatchField<Type>::write(os); 
}

template<class Type>
Foam::tmp<Foam::Field<Type > > 
Foam::recirculationControlFvPatchField<Type>::valueInternalCoeffs 
(
    const Foam::tmp<Foam::Field<scalar > > & f
) const
{
    return baseTypeTmp_->valueInternalCoeffs(f); 
}

template<class Type>
Foam::tmp<Foam::Field<Type > >
Foam::recirculationControlFvPatchField<Type>::valueBoundaryCoeffs 
(
    const Foam::tmp<Foam::Field<scalar > > & f
) const
{
    return baseTypeTmp_->valueBoundaryCoeffs(f); 
}

template<class Type>
Foam::tmp<Foam::Field<Type > > 
Foam::recirculationControlFvPatchField<Type>::gradientInternalCoeffs () const
{
    return baseTypeTmp_->gradientInternalCoeffs(); 
}

template<class Type>
Foam::tmp<Foam::Field<Type > >
Foam::recirculationControlFvPatchField<Type>::gradientBoundaryCoeffs () const
{
    return baseTypeTmp_->gradientBoundaryCoeffs(); 
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void Foam::recirculationControlFvPatchField<Type>::operator=
(
    const fvPatchField<Type>& ptf
)
{
    fvPatchField<Type>::operator=(ptf); 
}


// ************************************************************************* //
