#!/bin/bash

# Tests the parser on all tutorial files which claim to be OpenFOAM dictionaries
# Does not a working OpenFOAM installation but point $FOAM_TUTORIALS to the testing directory

# Generate the grammar
echo "Generating the parser"
npx tree-sitter generate
if [[ $? != 0 ]]; then
    exit 1
fi

# Parse the example file (Parsing for 1st time yields performance overhead)
npx tree-sitter parse test/highlight/example-file.foam 2&>1 > /dev/null

# Returns 1 if $2 is found in the list $1
doesNotContain()
{
    # Files that are known to fail, faulty from source
    declare -A failingFiles=(["$FOAM_TUTORIALS"/lagrangian/MPPICFoam/column/constant/kinematicCloudPositions]=
    ["$FOAM_TUTORIALS"/incompressible/pimpleFoam/RAS/wingMotion/wingMotion_snappyHexMesh/system/controlDict]=
    ["$FOAM_TUTORIALS"/incompressible/pimpleDyMFoam/wingMotion/wingMotion_snappyHexMesh/system/controlDict]=
    ["$FOAM_TUTORIALS"/solidMechanics/elasticIncrSolidFoam/slidingFrictionBallIncr/0/DU]=
    )

    #[[ $1 =~ (^|[[:space:]])"$2"($|[[:space:]]) ]] && return 1 || return 0
    [[ -v failingFiles["$1"] ]] && return 1 || return 0
}

# Returns true if the file contains FoamFile in first 10 lines
# and if it does not appear in the failing_files list
# $1 : path to target file
function selector()
{
    head -10 $1 | grep 'FoamFile' > /dev/null
    err1=$?
    doesNotContain $1
    err2=$?
    return $((err1+err2))
}

# Time a command
# Returns error status of the run command
# Prints execution time info in sub-second precision
function timeTreeSitterCommand()
{
    start=$(date +%s.%N)
    npx tree-sitter parse $1 > /dev/null
    error=$?
    end=$(date +%s.%N)
    result=$(echo "$end - $start" | bc -l)
    if [[ $error == 0 ]]; then
        echo "Pass: $1 "$(printf "%.3f" $result)
    else
        echo "Fail: $1 "$(printf "%.3f" $result)
        # Uncomment to edit failing file at failing position
        coords=$(npx tree-sitter parse $1 | tail -1 | grep -o "[0-9]\+, [0-9]\+" | head -1)
        line=$(echo $coords | awk -F, '{print($1+1)}')
        colu=$(echo $coords | awk -F, '{print($2+1)}')
        vim "+call cursor($line, $colu)" $1
        exit 1
    fi
}

# All potential files; skips deprecatedTutorials from FE4 tree
files=$(find $FOAM_TUTORIALS -not -name "*.m4" -not -iwholename "*/deprecatedTutorials/*" -type f)

for fl in $files
do
    if(selector $fl)
    then
        timeTreeSitterCommand $fl
    fi
done
