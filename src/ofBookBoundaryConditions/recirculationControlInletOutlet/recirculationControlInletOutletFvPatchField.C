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

\*---------------------------------------------------------------------------*/

#include "recirculationControlInletOutletFvPatchField.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF
)
:
    inletOutletFvPatchField<Type>(p, iF), 
    recirculationRate_(0),
    controlledField_()
{
}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const recirculationControlInletOutletFvPatchField<Type>& ptf,
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    inletOutletFvPatchField<Type>(ptf, p, iF, mapper), 
    recirculationRate_(0),
    controlledField_()
{}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF,
    const dictionary& dict
)
:
    inletOutletFvPatchField<Type>(p, iF, dict), 
    recirculationRate_(), 
    controlledField_(dict.lookupOrDefault<word>("controlled", "inlet"))
{
   
}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const recirculationControlInletOutletFvPatchField<Type>& ptf
)
:
    inletOutletFvPatchField<Type>(ptf),
    recirculationRate_(ptf.recirculationRate_),
    controlledField_(ptf.controlledField_)
{}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const recirculationControlInletOutletFvPatchField<Type>& ptf,
    const DimensionedField<Type, volMesh>& iF
)
:
    inletOutletFvPatchField<Type>(ptf, iF),
    recirculationRate_(ptf.recirculationRate_),
    controlledField_(ptf.controlledField_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void Foam::recirculationControlInletOutletFvPatchField<Type>::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    typedef GeometricField<Type, fvPatchField, volMesh>  VolumetricField; 

    const Field<scalar>& phip =
        this->patch().template lookupPatchField<surfaceScalarField, scalar>
        (
            inletOutletFvPatchField<Type>::phiName_
        );

    // Compute the total and the negative volumetric flux.
    scalar totalFlux = 0; 
    scalar negativeFlux = 0; 

    forAll (phip, I)
    {
        totalFlux += mag(phip[I]); 
        negativeFlux -= min(0, phip[I]); 
    }
    negativeFlux *= -1; 

    // Compute the percentage of the inflow volumetric flux (recirculation rate).   
    recirculationRate_ = min(1, negativeFlux / totalFlux); 

    // Finding the controlled inlet patch and controling its field values. 
    
     //- Get the name of the internal field.
    const word volFieldName = this->dimensionedInternalField().name(); 

     //- Get access to the regitstry.
    const objectRegistry& db = this->db(); 

     //- Find the GeometricField in the registry using the internal field name.
    const VolumetricField& vfConst = db.lookupObject<VolumetricField>(volFieldName);

     // Cast away constness to be able to control other boundary patch fields. 
    VolumetricField& vf = const_cast<VolumetricField&>(vfConst); 

     //- Get the non-const reference to the boundary field of the GeometricField.
    typename VolumetricField::GeometricBoundaryField& bf = vf.boundaryField();

     //- Find the controlled boundary patch field using the name defined by the user.
    forAll (bf, patchI)
    {
        // Control the boundary patch field using the recirculation rate.  
        const fvPatch& p = bf[patchI].patch();

        if (p.name() == controlledField_)
        {
            // Impose control on the controlled inlet patch field.  
            bf[patchI] *= recirculationRate_; 
        }
    }

    // Update parent class. 
    inletOutletFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void Foam::recirculationControlInletOutletFvPatchField<Type>::write(Ostream& os) const
{
    inletOutletFvPatchField<Type>::write(os); 
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void Foam::recirculationControlInletOutletFvPatchField<Type>::operator=
(
    const fvPatchField<Type>& ptf
)
{
    inletOutletFvPatchField<Type>::operator=(ptf); 
}


// ************************************************************************* //
