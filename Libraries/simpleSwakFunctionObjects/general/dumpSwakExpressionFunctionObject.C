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

Contributors/Copyright:
    2011-2014, 2016-2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>

 SWAK Revision: $Id:  $
\*---------------------------------------------------------------------------*/

#include "dumpSwakExpressionFunctionObject.H"
#include "addToRunTimeSelectionTable.H"

#include "volFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(dumpSwakExpressionFunctionObject, 0);

    addToRunTimeSelectionTable
    (
        functionObject,
        dumpSwakExpressionFunctionObject,
        dictionary
    );



// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

dumpSwakExpressionFunctionObject::dumpSwakExpressionFunctionObject
(
    const word& name,
    const Time& t,
    const dictionary& dict
)
:
    timelineFunctionObject(name,t,dict),
    expression_(
        dict.lookup("expression"),
        dict
    ),
    driver_(
        CommonValueExpressionDriver::New(
            dict,
            refCast<const fvMesh>(obr_)
        )
    )
{
    const string warnSwitch="IKnowThatThisFunctionObjectMayWriteExcessiveAmountsOfData";
    if(!dict.lookupOrDefault<bool>(warnSwitch,false)) {
        WarningIn("dumpSwakExpressionFunctionObject::dumpSwakExpressionFunctionObject")
            << "This functionObject may write huge amounts of data. "
                << "If you understand the risks set the switch " << warnSwitch
                << " to 'true' to get rid of this warning"
                << endl;
    }

    driver_->createWriterAndRead(name+"_"+type());
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

word dumpSwakExpressionFunctionObject::dirName()
{
    return typeName;
}

wordList dumpSwakExpressionFunctionObject::fileNames()
{
    return wordList(1,name());
}

stringList dumpSwakExpressionFunctionObject::columnNames()
{
    return stringList(1,"No way to know how much data will follow");
}

void dumpSwakExpressionFunctionObject::writeSimple()
{

    if(verbose()) {
        Info << "Expression " << name() << " : ";
    }

    driver_->clearVariables();
    driver_->parse(expression_);
    word rType=driver_->CommonValueExpressionDriver::getResultType();

    if(rType==pTraits<scalar>::typeName) {
        writeTheData<scalar>(driver_());
    } else if(rType==pTraits<vector>::typeName) {
        writeTheData<vector>(driver_());
    } else if(rType==pTraits<tensor>::typeName) {
        writeTheData<tensor>(driver_());
    } else if(rType==pTraits<symmTensor>::typeName) {
        writeTheData<symmTensor>(driver_());
    } else if(rType==pTraits<sphericalTensor>::typeName) {
        writeTheData<sphericalTensor>(driver_());
    } else {
        WarningIn("dumpSwakExpressionFunctionObject::writeSimple()")
            << "Don't know how to handle type " << rType
                << endl;
    }

    if(verbose()) {
        Info << endl;
    }

    // make sure that the stored Variables are consistently written
    driver_->tryWrite();
}

} // namespace Foam

// ************************************************************************* //
