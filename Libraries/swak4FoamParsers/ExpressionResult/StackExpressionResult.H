/*---------------------------------------------------------------------------*\
|                       _    _  _     ___                       | The         |
|     _____      ____ _| | _| || |   / __\__   __ _ _ __ ___    | Swiss       |
|    / __\ \ /\ / / _` | |/ / || |_ / _\/ _ \ / _` | '_ ` _ \   | Army        |
|    \__ \\ V  V / (_| |   <|__   _/ / | (_) | (_| | | | | | |  | Knife       |
|    |___/ \_/\_/ \__,_|_|\_\  |_| \/   \___/ \__,_|_| |_| |_|  | For         |
|                                                               | OpenFOAM    |
-------------------------------------------------------------------------------
License
    This file is part of swak4Foam.

    swak4Foam is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    swak4Foam is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with swak4Foam; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    Foam::StackExpressionResult

Description

SourceFiles
    StackExpressionResultI.H
    StackExpressionResult.C
    StackExpressionResultIO.C

Contributors/Copyright:
    2012-2013, 2016-2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

#ifndef StackExpressionResult_H
#define StackExpressionResult_H

#include "ExpressionResult.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class StackExpressionResult Declaration
\*---------------------------------------------------------------------------*/

class StackExpressionResult
:
    public ExpressionResult
{
    // Private data

    template<class T>
    ExpressionResult popInternal();

    template<class T>
    void pushInternal(ExpressionResult &);

public:

     //- Runtime type information
    TypeName("StackExpressionResult");

    // Constructors

    //- Construct null
    StackExpressionResult();

    //- Construct as copy
    StackExpressionResult(const StackExpressionResult&);

    //- Construct from a dictionary
    StackExpressionResult(const dictionary&);

    // Destructor

    virtual ~StackExpressionResult();

    void operator=(const StackExpressionResult&);

    void operator=(const ExpressionResult&);

    virtual autoPtr<ExpressionResult> clone() const {
        return autoPtr<ExpressionResult>(
            new StackExpressionResult(*this)
        );
    }

    // friend Ostream & operator<<(Ostream &,const StackExpressionResult &);

    // friend Istream & operator>>(Istream &,StackExpressionResult &);

    // friend bool operator!=(
    //     const StackExpressionResult &,const StackExpressionResult &
    // );

    ExpressionResult pop();

    void push(ExpressionResult &);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "StackExpressionResultI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
